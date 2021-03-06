/* LEDC (LED Controller) fade example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

/*
 * About this example
 *
 * 1. Start with initializing LEDC module:
 *    a. Set the timer of LEDC first, this determines the frequency
 *       and resolution of PWM.
 *    b. Then set the LEDC channel you want to use,
 *       and bind with one of the timers.
 *
 * 2. You need first to install a default fade function,
 *    then you can use fade APIs.
 *
 * 3. You can also set a target duty directly without fading.
 *
 * 4. This example uses GPIO18/19/4/5 as LEDC output,
 *    and it will change the duty repeatedly.
 *
 * 5. GPIO18/19 are from high speed channel group.
 *    GPIO4/5 are from low speed channel group.
 *
 */

#define LEDC_HS_TIMER LEDC_TIMER_0
#define LEDC_HS_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO (15)
#define LEDC_TEST_DUTY (2000)
#define LEDC_TEST_STEP_SIZE (.01 * LEDC_TEST_DUTY)
#define LEDC_NUM_CYCLES 50

void app_main(void)
{

    // ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,256, 0, 0, NULL, 0) );

    // esp_vfs_dev_uart_use_driver(UART_NUM_0);

    /*
     * Prepare and set configuration of timers
     * that will be used by LED Controller
     */
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,           // timer mode
        .timer_num = LEDC_HS_TIMER,           // timer index
        .clk_cfg = LEDC_AUTO_CLK,             // Auto select the source clock
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);
    /*
     * Prepare individual configuration
     * for each channel of LED Controller
     * by selecting:
     * - controller's channel number
     * - output duty cycle, set initially to 0
     * - GPIO number where LED is connected to
     * - speed mode, either high or low
     * - timer servicing selected channel
     *   Note: if different channels use one timer,
     *         then frequency and bit_num of these channels
     *         will be the same
     */
    ledc_channel_config_t channel_config = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0,
        .gpio_num = LEDC_HS_CH0_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_HS_TIMER};

    // Set LED Controller with previously prepared configuration
    ledc_channel_config(&channel_config);

    // Initialize fade service.
    ledc_fade_func_install(0);

    while (1)
    {
        printf("Bright\n");

        ledc_set_fade_step_and_start(channel_config.speed_mode, channel_config.channel, LEDC_TEST_DUTY, LEDC_TEST_STEP_SIZE, LEDC_NUM_CYCLES, LEDC_FADE_WAIT_DONE);

        // vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);

        printf("Dim\n");

        // ledc_set_fade_with_time(channel_config.speed_mode,
        //         channel_config.channel, 0, LEDC_TEST_FADE_TIME);
        // ledc_fade_start(channel_config.speed_mode,
        //         channel_config.channel, LEDC_FADE_NO_WAIT);

        ledc_set_fade_step_and_start(channel_config.speed_mode, channel_config.channel, 0, LEDC_TEST_STEP_SIZE, LEDC_NUM_CYCLES, LEDC_FADE_WAIT_DONE);

        // vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);

        // printf("3. LEDC set duty = %d without fade\n", LEDC_TEST_DUTY);
        // ledc_set_duty(channel_config.speed_mode, channel_config.channel, LEDC_TEST_DUTY);
        // ledc_update_duty(channel_config.speed_mode, channel_config.channel);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);

        // printf("4. LEDC set duty = 0 without fade\n");
        // ledc_set_duty(channel_config.speed_mode, channel_config.channel, 0);
        // ledc_update_duty(channel_config.speed_mode, channel_config.channel);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}