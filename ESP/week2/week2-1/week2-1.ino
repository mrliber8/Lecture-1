#include <WiFi.h>
#include "secret.h"
#include "time.h"
#include "esp_sntp.h"

// data below is set as a define in the file secret.h
// const char* ssid = "Patrick Hotspot";
// const char* password = "Segafredo#";

// Constants for SNTP client
const char* ntpServer = "nl.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

// Global variables for timestamp
const int glob_buf_size = (64 * sizeof(char));
char *glob_time_buf;

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
    delay(500);
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
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    printf(".");
    }
}

void setup(){
  WiFi_connect();
  SNTP_connect();

  // allocate heap memory to store 1 timestamp 
  glob_time_buf = (char*)malloc(glob_buf_size);
  // check if memory is allocated 
  assert( glob_time_buf != NULL);
  }

void loop() {
  // put your main code here, to run repeatedly:
  // Call getLocalTime to update glob_time_buf with current time
  getLocalTime(glob_time_buf, glob_buf_size);

  // Print the current time
  printf("Current time: %s\r\n", glob_time_buf);

  // Delay for a while before updating the time again
  delay(10000);
}
