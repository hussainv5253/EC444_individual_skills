/* ADC1 Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "driver/i2c.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_vfs_dev.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "math.h"

#define DEFAULT_VREF 1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 40  //Multisampling
#define VS 5.1            //V source
#define R2 1000           //Vadc = Vs * R2 / (R1 + R2)

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_3; //A3 GPIO 36
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

////////////////////////////////////////////////////////////////////////////////
void app_main()
{
  //Configure ADC
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

    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
      if (unit == ADC_UNIT_1)
      {
        adc_reading += adc1_get_raw((adc1_channel_t)channel);
        vTaskDelay(50 / portTICK_PERIOD_MS);
      }
    }
    adc_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    float temp, rtherm;
    rtherm = adc_reading;
    rtherm = (1000 * ((4096 / rtherm) - 1));
    temp = rtherm / 10000;
    temp = log(temp);
    temp /= 3435;
    temp += 1.0 / (20 + 273.15);
    temp = 1.0 / temp;
    temp -= 273.15;
    //temperature = temp;
    //Convert voltage to temp

    if ((voltage <= 142) || (voltage >= 3165))
    {
      printf("Temperature out of range!\n");
    }
    else
    {
      printf("Temperature: %f\n", temp);
    }
  }
}
