// press2.ino
// MIT License (see file LICENSE)

// Needed for the wifi
#include <WiFi.h>
#include "secret.h"
#include "time.h"
// Needed fot the SNTP connection
#include "esp_sntp.h"

// LED is active high
#define GPIO_LED 12
#define GPIO_BUTTONL 25
#define GPIO_BUTTONR 26

// Constants for SNTP client
const char* ntpServer = "nl.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
// Queue has to contain 200 presses
//const int QueueSize = 200;

// Global variables for timestamp
const int glob_buf_size = (64 * sizeof(char));
char *glob_time_buf;


static QueueHandle_t queue;
static const int reset_press = -998;

// Global varibles for task counters
volatile int wifi_delay_counter = 0;
volatile int ntp_delay_counter = 0;
volatile int press_task_counter = 0;
volatile int debounce_left_task_counter = 0;
volatile int debounce_right_task_counter = 0;
static int MAX_COUNTER_VALUE = 5;

// global variable to check if time is synced
volatile bool is_time_synced = false;



//
// Button Debouncing task:
//
static void debounce_task(void *argp) {
  unsigned button_gpio = *(unsigned *)argp;
  uint32_t level, state = 0;
  uint32_t mask = 0x7FFFFFFF;
  int event, last = -999;

  if ( button_gpio== GPIO_BUTTONR ) { 
    debounce_right_task_counter++;
    if ( debounce_right_task_counter < MAX_COUNTER_VALUE ) {
        printf("\t\tin debounce_task(): RIGHT start %d\n", 
    debounce_right_task_counter ); 
    } 
  } 
  else if ( button_gpio== GPIO_BUTTONL ) { 
    debounce_left_task_counter++;
    if ( debounce_left_task_counter < MAX_COUNTER_VALUE ) { 
        printf("\t\tin debounce_task(): LEFT start %d\n", 
    debounce_left_task_counter );
    }
  }

  for (;;) {
    level = !digitalRead(button_gpio);
    state = (state << 1) | level;
    if ((state & mask) == mask)
      event = button_gpio;  // Press
    else
      event = -button_gpio;  // Release

    if (event != last) {
      if (xQueueSendToBack(queue, &event, 0) == pdPASS) {
        last = event;
      } else if (event < 0) {
        // Queue full, and we need to send a
        // button release event. Send a reset_press
        // event.
        do {
          xQueueReset(queue);  // Empty queue
        } while (xQueueSendToBack(queue, &reset_press, 0) != pdPASS);
        last = event;
      }
    }
    taskYIELD();
  }

  if ( button_gpio== GPIO_BUTTONR ) { 
    debounce_right_task_counter++;
    if ( debounce_right_task_counter < MAX_COUNTER_VALUE ) {
        printf("\t\tin debounce_task(): RIGHT start %d\n", 
    debounce_right_task_counter ); 
    } 
  } 
  else if ( button_gpio== GPIO_BUTTONL ) { 
    debounce_left_task_counter++;
    if ( debounce_left_task_counter < MAX_COUNTER_VALUE ) { 
        printf("\t\tin debounce_task(): LEFT start %d\n", 
    debounce_left_task_counter );
    }
  }

}

//
// Hydraulic Press Task (LED)
//
static void press_task(void *argp) {
  if ( press_task_counter < MAX_COUNTER_VALUE ) {
    printf("\t\tin press_task(): end %d\n", press_task_counter );
  } 


  static const uint32_t enable = (1 << GPIO_BUTTONL)
                                 | (1 << GPIO_BUTTONR);
  BaseType_t s;
  int event;
  uint32_t state = 0;

  // Make sure press is OFF
  digitalWrite(GPIO_LED, LOW);

  for (;;) {
    s = xQueueReceive(
      queue,
      &event,
      portMAX_DELAY);
    assert(s == pdPASS);

    if (event == reset_press) {
      digitalWrite(GPIO_LED, LOW);
      state = 0;
      printf("RESET!!\n");
      continue;
    }

    if (event >= 0) {
      // Button press
      state |= 1 << event;
    } else {
      // Button release
      state &= ~(1 << -event);
    }

    if (state == enable) {
      // Activate press when both
      // Left and Right buttons are
      // pressed.
      digitalWrite(GPIO_LED, HIGH);
    } else {
      // Deactivate press
      digitalWrite(GPIO_LED, LOW);
    }
  }

  if ( press_task_counter < MAX_COUNTER_VALUE ) {
    printf("\t\tin press_task(): end %d\n", press_task_counter );
  }

}


// connect with NTP server
void SNTP_connect() {
  const time_t old_past = 1577836800; // 2020-01-01T00:00:00Z 
  printf("\r\nConnect to SNTP server\n");
  // init time protocol sync
  sntp_setoperatingmode (SNTP_OPMODE_POLL); 
  sntp_setservername(0, "pool.ntp.org"); 
  sntp_init();
  //https://knowledgebase.progress.com/articles/Article/P129473
  setenv("TZ", "CET-1CEST-2, M3.5.0/02:00:00, M10.5.0/03:00:00", 1); 
  tzset();
  
  bool connected = false;
  while (not connected ) {
    printf("SNTP_connect(): sntp delay begint nu\n");
    delay(500);
    printf("SNTP_connect(): sntp delay eindigt nu\n");
    time_t now;
    if (time(&now) < old_past ) { // if there is no connection with NTP server than local time returns Unix epoch (1970 date)
      printf(".");
    }
    else {
      printf(" CONNECTED\r\n");
      connected = true;
    }
  }
}

// get current time
//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html
void getLocalTime (char * time_buf, int time_buf_size) {
  time_t now;
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);
  strftime(time_buf, time_buf_size, "%c", &timeinfo);
  return;
}

void WiFi_connect() {
  printf("WiFi_connect(): Wifi begin wordt nu uitgevoerd\n");
  WiFi.begin(SSID, PASSWORD);
  printf("WiFi_connect(): Wifi begin is nu klaar\n");
  while (WiFi.status() != WL_CONNECTED){
    printf("WiFi_connect(): wifi delay begint nu\n");
    delay(500);
    printf("WiFi_connect(): wifi delay eindigt nu\n");
    printf(".");
    }
}


// Tasks for the wifi & sntp connect
void WiFi_connect_task(void *pvParameters) {
  WiFi_connect();
  vTaskDelete(nullptr);
}

void SNTP_connect_task(void *pvParameters) {
  SNTP_connect();
  vTaskDelete(nullptr);
}


//
// Initialization:
//
void setup() {
  //
  // Connect to wifi first
  //
  // Uncommented them to replace them with the tasks instea dof functins
  //WiFi_connect();
  //SNTP_connect();

  // allocate heap memory to store 1 timestamp 
  glob_time_buf = (char*)malloc(glob_buf_size);
  // check if memory is allocated 
  assert( glob_time_buf != NULL);

  //
  // Init the press2 secondly
  //
  int app_cpu = xPortGetCoreID();
  static int left = GPIO_BUTTONL;
  static int right = GPIO_BUTTONR;
  TaskHandle_t h;
  BaseType_t rc;

  delay(2000);  // Allow USB to connect
  queue = xQueueCreate(2, sizeof(int));
  assert(queue);

  pinMode(GPIO_LED, OUTPUT);
  pinMode(GPIO_BUTTONL, INPUT_PULLUP);
  pinMode(GPIO_BUTTONR, INPUT_PULLUP);

// C. Zorg dat aan de taken “debounceL”, “debounceR” en “PressTask” de prioriteit 1 wordt toegekend.
// Maar dat hadden ze toch al?????
// Kan zijn dat ik tijdens het testen in week2 dit per ongeluk al had aangepast want ik had best wat
//  moeite toen om het werkend te krijgen, maar het stond tenminste voor mij al op prio 1

  // Task for WiFi_connect with prioriteit 3
  printf(" void setup(): Begin met het maken van WiFi_connect_task...\n");
  xTaskCreatePinnedToCore(
    WiFi_connect_task, 
    "WiFiConnectTask", 
    2048, 
    nullptr, 
    3, 
    nullptr, 
    app_cpu
    );
  printf(" void setup(): WiFi_connect_task gemaakt.\n");

  // Task for SNTP_connect with prioriteit 2
  printf(" void setup(): Begin met het maken van sntp_connect_task...\n");
  xTaskCreatePinnedToCore(
    SNTP_connect_task, 
    "SNTPConnectTask", 
    2048, 
    nullptr, 
    2, 
    nullptr, 
    app_cpu
    );
  printf(" void setup(): sntp_connect_task gemaakt.\n");

printf(" void setup(): Begin met het maken van debounceR_task...\n");
  rc = xTaskCreatePinnedToCore(
    debounce_task,
    "debounceL",
    2048,    // Stack size
    &left,   // Left button gpio
    1,       // Priority
    &h,      // Task handle
    app_cpu  // CPU
  );
  assert(rc == pdPASS);
  assert(h);
  printf(" void setup(): debounceR_task gemaakt.\n");

printf(" void setup(): Begin met het maken van debounceL_task...\n");
  rc = xTaskCreatePinnedToCore(
    debounce_task,
    "debounceR",
    2048,    // Stack size
    &right,  // Right button gpio
    1,       // Priority
    &h,      // Task handle
    app_cpu  // CPU
  );
  assert(rc == pdPASS);
  assert(h);
  printf(" void setup(): debounceL_task gemaakt.\n");

 printf(" void setup(): Begin met het maken van press_task...\n");
  rc = xTaskCreatePinnedToCore(
    press_task,
    "led",
    2048,     // Stack size
    nullptr,  // Not used
    1,        // Priority
    &h,       // Task handle
    app_cpu   // CPU
  );
  printf(" void setup(): press_task gemaakt.\n");

  assert(rc == pdPASS);
  assert(h);
  // Make the queue
  queue = xQueueCreate(200, sizeof(char *));
  // Test if the queue is created
  // Can also be done using an assert assert(audit_queue != NULL);
  // But i perosnally like th eif more
  if (queue == 0){
    printf("Failed to create queue= %p\n", queue);
  }
  
}

// Not used:
void loop() {
  //vTaskDelete(nullptr);
  // put your main code here, to run repeatedly:
  // Call getLocalTime to update glob_time_buf with current time
  getLocalTime(glob_time_buf, glob_buf_size);

  // Print the current time
  printf("Current time: %s\r\n", glob_time_buf);

  //http://www.openrtos.net/a00018.html#uxQueueSpacesAvailable
  //uxQueueSpacesAvailable,Returns the number of free spaces in a queue 
  if (uxQueueSpacesAvailable(queue) == 0) {
    char *oldTimestamp;
    if (xQueueReceive(queue, &oldTimestamp, 0) == pdPASS) {
      free(oldTimestamp); // Free memory of the removed timestamp
    }
  }


  // I couldnt really decide how big i should make it, so instead i just used malloc
  // To increase it lineailry 
  char *newTimestamp = (char *)malloc(glob_buf_size);
  if (newTimestamp != NULL) {
    getLocalTime(newTimestamp, glob_buf_size);
    if(xQueueSendToBack(queue, &newTimestamp, portMAX_DELAY) == pdPASS) {
      //printf("Added a timestamp\r\n");
    } else {
      // If adding to queue fails, free the allocated memory
      free(newTimestamp);
      printf("Failed to send to queue\r\n");
    }
  } else {
    printf("Memory allocation failed\r\n");
  }

  
  // Delay for a while before updating the time again
  // 100 = o.1s
  delay(100); 
}
