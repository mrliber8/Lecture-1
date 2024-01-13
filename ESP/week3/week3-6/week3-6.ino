// week2-5.ino 
// MIT License (see file LICENSE)

#include "time.h"

// LED is active high
// One LED and Two Buttons
#define GPIO_LED_SEM 14 
#define GPIO_BUTTONL  27
#define GPIO_BUTTONR  26

#define DEBOUNCE_TIME  30 // the debounce time in millisecond, increase this time if it still chatters

//Declare SemaphoreHandle
SemaphoreHandle_t xSemaphore = NULL;


volatile int lastButtonStateL = LOW;
volatile int lastButtonStateR = LOW;
volatile unsigned long lastDebounceTimeL = 0;
volatile unsigned long lastDebounceTimeR = 0;

void IRAM_ATTR handleInterruptL() {
  int reading = digitalRead(GPIO_BUTTONL);
  if (reading != lastButtonStateL) {
    lastDebounceTimeL = millis();
  }
  lastButtonStateL = reading;
  if ((millis() - lastDebounceTimeL) > DEBOUNCE_TIME) {
    xSemaphoreGiveFromISR(xSemaphore, NULL);
  }
}

void IRAM_ATTR handleInterruptR() {
  int reading = digitalRead(GPIO_BUTTONR);
  if (reading != lastButtonStateR) {
    lastDebounceTimeR = millis();
  }
  lastButtonStateR = reading;
  if ((millis() - lastDebounceTimeR) > DEBOUNCE_TIME) {
    xSemaphoreGiveFromISR(xSemaphore, NULL);
  }
}

// function blinks GPIO_led_sem in given rate(ms) for 10 times 
void blink_sem_led(int rate){
  //set Semaphore and when done relase the Semaphore
  //......
  if(xSemaphoreTake(xSemaphore, portMAX_DELAY)){
    int count = 0;
    printf("BLINK_SEM_LED, rate: %d\r\n",rate );

    while (count<10){
      digitalWrite(GPIO_LED_SEM,HIGH);
      delay(rate);
      digitalWrite(GPIO_LED_SEM,LOW);
      delay(rate);
      count++;
    }
    //free Semaphore
    xSemaphoreGive(xSemaphore);
  }
}



//
// Initialization:
//
void setup() {
  int app_cpu = xPortGetCoreID();
  static int left = GPIO_BUTTONL;
  static int right = GPIO_BUTTONR;
  TaskHandle_t h;
  BaseType_t rc;
  
  delay(2000);          // Allow USB to connect

  // create here binary Semaphore and release the Semaphore
  // handle = binary semaphore.........
  xSemaphore = xSemaphoreCreateBinary();
  // free binarys semaphore........
  xSemaphoreGive(xSemaphore);
 
  pinMode(GPIO_LED_SEM,OUTPUT);
  pinMode(GPIO_BUTTONL,INPUT_PULLUP);
  pinMode(GPIO_BUTTONR,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(GPIO_BUTTONL), handleInterruptL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GPIO_BUTTONR), handleInterruptR, CHANGE);
}

// Not used
void loop() {
  vTaskDelete(nullptr);
}
