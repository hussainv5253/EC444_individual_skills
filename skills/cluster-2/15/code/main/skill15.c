/* ADC1 Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "math.h"

#define DEFAULT_VREF 1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 40  //Multisampling
#define E 2.718

#if CONFIG_IDF_TARGET_ESP32
static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_6; //A4 GPIO 34
#endif
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

void app_main(void)
{

  if (unit == ADC_UNIT_1)
  {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(channel, atten);
  }
  else
  {
    adc2_config_channel_atten((adc2_channel_t)channel, atten);
  }

#if CONFIG_IDF_TARGET_ESP32
  //Characterize ADC
  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
  //print_char_val_type(val_type);
#endif
  //Continuously sample ADC1
  while (1)
  {
    uint32_t adc_reading = 0;
    double distance = 0;
    double temp = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
      if (unit == ADC_UNIT_1)
      {
        adc_reading += adc1_get_raw((adc1_channel_t)channel);
        vTaskDelay(50 / portTICK_RATE_MS);
      }
    }
    adc_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    double voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    voltage /= 1000;
    if (voltage > 2)
    {
      distance = (30 / (voltage - 1));
    }
    else if (voltage < 2 && voltage > 1)
    {
      distance = (57 / (voltage - 0.08));
    }
    else
    {
      temp = (3 - voltage) / 0.5;
      temp = pow(E, temp);
      temp = temp / 1.4;
      distance = temp + 25.5;
    }
    distance = distance / 100.0;
    printf("Distance: %.2fm\n", distance);

    //vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
