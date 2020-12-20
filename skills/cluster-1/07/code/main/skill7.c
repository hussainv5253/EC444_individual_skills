/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define LED0 12
#define LED1 27
#define LED2 33
#define LED3 32

void app_main(void)
{
    /* Configure the IOMUX register for pad LEDS (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(LED0);
    gpio_pad_select_gpio(LED1);
    gpio_pad_select_gpio(LED2);
    gpio_pad_select_gpio(LED3);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED0, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);

    while(1) {

    	for(int i = 0; i < 2; i++){
    		for(int j = 0; j < 2; j++){
    			for(int k = 0; k < 2; k++){
    				for(int l = 0; l < 2; l++){
    					gpio_set_level(LED0, l);
				        gpio_set_level(LED1, k);
				        gpio_set_level(LED2, j);
				        gpio_set_level(LED3, i);
				        vTaskDelay(1000 / portTICK_PERIOD_MS);
    				}
    			}
    		}
    	}
    }
}
