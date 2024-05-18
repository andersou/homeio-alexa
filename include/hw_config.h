#pragma once

#include <stdint.h>
#include "espasyncbutton.hpp"

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#define INPUT_1 34
#define INPUT_2 35
#define INPUT_3 32
#define INPUT_4 33
#define INPUT_5 25
#define OUTPUT_1 2
#define OUTPUT_2 4
#define OUTPUT_3 5
#define OUTPUT_4 18
#define OUTPUT_5 19
#define OUTPUT_6 21
#define OUTPUT_7 22
#define OUTPUT_8 23
uint8_t INPUTS[] = {INPUT_1, INPUT_2, INPUT_3, INPUT_4, INPUT_5};
#define INPUT_NUMBER 5
AsyncEventButton buttons[INPUT_NUMBER] = {
    AsyncEventButton((gpio_num_t)INPUT_1, LOW),
    AsyncEventButton((gpio_num_t)INPUT_2, LOW),
    AsyncEventButton((gpio_num_t)INPUT_3, LOW),
    AsyncEventButton((gpio_num_t)INPUT_4, LOW),
    AsyncEventButton((gpio_num_t)INPUT_5, LOW)};

uint8_t OUTPUTS[] = {OUTPUT_1, OUTPUT_2, OUTPUT_3, OUTPUT_4, OUTPUT_5, OUTPUT_6, OUTPUT_7, OUTPUT_8};
#define OUTPUT_NUMBER 8
#define OFF HIGH
#define ON LOW
void button_callback(uint8_t button, uint8_t state);
void initIOs()
{

  for (uint8_t i = 0; i < OUTPUT_NUMBER; i++)
  {
    pinMode(OUTPUTS[i], OUTPUT);
    digitalWrite(OUTPUTS[i], OFF);
  }
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  for (uint8_t i = 0; i < INPUT_NUMBER; i++)
  {
    pinMode(INPUTS[i], INPUT);
    buttons[i] = AsyncEventButton((gpio_num_t)INPUTS[i], LOW);
    buttons[i].begin();
    // on-Press callback
    buttons[i].onPress([i]()
                       { button_callback(i, ON); });

    // on-Release callback
    buttons[i].onRelease([i]()
                         { button_callback(i, OFF); });
    buttons[i].timeouts.setDebounce(500000);
    buttons[i].enable();
  }
}
