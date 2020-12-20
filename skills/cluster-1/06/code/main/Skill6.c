#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLINK_GPIO 13

void app_main()
{
    /* LED Blink settup    */
	gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
      256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

      int mode = 0;#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLINK_GPIO 13

void app_main()
{
    /* LED Blink settup    */
	gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
      256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

      int mode = 0;
      int lastmode = 3;
      char str[30];
      char ch[2];
      int toggle = 0;
      int decimal;

    while(1) {

      // mode starts at 0 which is toggle mode
      //0 = toogle mode, 1 = echo mode, 2 = dec to hex mode

	    if(lastmode != mode){      	
	      	lastmode = mode;
		    switch(mode)
		    {
		     	case 0: 
		      		printf("toggle mode\n");
		      		break;

		      	case 1:
		      		printf("echo mode\n");
		      		break;

		      	case 2:
		      		printf("echo dec to hex mode\n");
		      		break;
		    }
	  	}

      	switch(mode) {

	      	case 0 :
	      		scanf("%s", ch);
	      		printf("Read: %c\n", ch[0]);
	      		if(ch[0] == 's'){
	      			mode = (mode + 1) % 3;
	      		}
	      		else if(ch[0] == 't'){
	      			toggle = (toggle + 1) % 2; 
	      			gpio_set_level(BLINK_GPIO, toggle);
	      		}
	      		break;

	      	case 1 :
	      		scanf("%s", str);
	      		if(str[0] == 's' && str[1] == '\0'){
	      			mode = (mode + 1) % 3;
	      		}
	      		printf("echo: %s\n", str);
	      		break;

	      	case 2 :
	      		printf("Enter an integer: \n");
	      		scanf("%s", str);
	      		if(str[0] == 's' && str[1] == '\0'){
	      			mode = (mode + 1) % 3;
	      		}
	      		else{
	      			decimal = atoi(str);
	      			printf("Hex: %X\n", decimal);
	      		}
	      		break;
      	} 
    
      vTaskDelay(50 / portTICK_RATE_MS);
    }
}

      int lastmode = 3;
      char str[30];
      char ch[2];
      int toggle = 0;
      int decimal;

    while(1) {

      // mode starts at 0 which is toggle mode
      //0 = toogle mode, 1 = echo mode, 2 = dec to hex mode

	    if(lastmode != mode){      	
	      	lastmode = mode;
		    switch(mode)
		    {
		     	case 0: 
		      		printf("toggle mode\n");
		      		break;

		      	case 1:
		      		printf("echo mode\n");
		      		break;

		      	case 2:
		      		printf("echo dec to hex mode\n");
		      		break;
		    }
	  	}

      	switch(mode) {

	      	case 0 :
	      		scanf("%s", ch);
	      		printf("Read: %c\n", ch[0]);
	      		if(ch[0] == 's'){
	      			mode = (mode + 1) % 3;
	      		}
	      		else if(ch[0] == 't'){
	      			toggle = (toggle + 1) % 2; 
	      			gpio_set_level(BLINK_GPIO, toggle);
	      		}
	      		break;

	      	case 1 :
	      		scanf("%s", str);
	      		if(str[0] == 's' && str[1] == '\0'){
	      			mode = (mode + 1) % 3;
	      		}
	      		printf("echo: %s\n", str);
	      		break;

	      	case 2 :
	      		printf("Enter an integer: \n");
	      		scanf("%s", str);
	      		if(str[0] == 's' && str[1] == '\0'){
	      			mode = (mode + 1) % 3;
	      		}
	      		else{
	      			decimal = atoi(str);
	      			printf("Hex: %X\n", decimal);
	      		}
	      		break;
      	} 
    
      vTaskDelay(50 / portTICK_RATE_MS);
    }
}
