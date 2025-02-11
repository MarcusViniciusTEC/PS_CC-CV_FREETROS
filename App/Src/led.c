
#include "led.h"
#include "led_types.h"


#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/***********************************************************************************/

led_data_t led_vector_data_default[3] = vector_led_board_defaut;

QueueHandle_t queue_led = NULL;


/***********************************************************************************/

void led_init(void);
void led_update_state(void);
void led_thread(void const *pvParameters);

/***********************************************************************************/

void led_thread(void const *pvParameters)
{
    queue_led_crtl_t queue_led_received = {0};
    for (;;)
    {
        if (xQueueReceive(queue_led, &queue_led_received, 10 == pdPASS))
        {
            for (uint8_t index_led = 0; index_led < 3; index_led++)
            {
                if (queue_led_received.name == led_vector_data_default[index_led].name)
                {
                    led_vector_data_default[index_led].mode = queue_led_received.mode;
                    led_vector_data_default[index_led].state = LED_STATE_INIT;
                }
            }
        }

        for (uint8_t index_led = 0; index_led < 3; index_led++)
        {
            switch (led_vector_data_default[index_led].state)
            {
            case LED_STATE_IDLE:

                break;
            case LED_STATE_INIT:
                led_vector_data_default[index_led].state = LED_STATE_TURN_ON;
                break;
            case LED_STATE_TURN_ON:
                HAL_GPIO_WritePin(led_vector_data_default[index_led].GPIO, led_vector_data_default[index_led].pin, GPIO_PIN_RESET);
                led_vector_data_default[index_led].last_tick = xTaskGetTickCount();
                led_vector_data_default[index_led].state = LED_STATE_WAIT_DELAY;
                break;
            case LED_STATE_WAIT_DELAY:

                switch (led_vector_data_default[index_led].mode)
                {
                case LED_MODE_ON:
                    HAL_GPIO_WritePin(led_vector_data_default[index_led].GPIO, led_vector_data_default[index_led].pin, GPIO_PIN_RESET);
                    led_vector_data_default[index_led].state = LED_STATE_IDLE;
                    break;
                case LED_MODE_OFF:
                    led_vector_data_default[index_led].state = LED_STATE_TURN_OFF;
                    break;
                case LED_MODE_SHORT_PULSE:
                    if (xTaskGetTickCount() - led_vector_data_default[index_led].last_tick >= TIME_SHORT_PULSE)
                    {
                        led_vector_data_default[index_led].state = LED_STATE_TURN_OFF;
                    }
                    break;
                case LED_MODE_LONG_PULSE:
                    if (xTaskGetTickCount() - led_vector_data_default[index_led].last_tick >= TIME_LONG_PULSE)
                    {
                        led_vector_data_default[index_led].state = LED_STATE_TURN_OFF;
                    }
                    break;
                case LED_MODE_VERY_LONG_PULSE:
                    if (xTaskGetTickCount() - led_vector_data_default[index_led].last_tick >= TIME_VERY_LONG_PULSE)
                    {
                        led_vector_data_default[index_led].state = LED_STATE_TURN_OFF;
                    }
                    break;
                case LED_MODE_HEARTBEAT_PULSE:
                    
                    break;
                default:
                    break;
                }
                break;
            case LED_STATE_TURN_OFF:
                HAL_GPIO_WritePin(led_vector_data_default[index_led].GPIO, led_vector_data_default[index_led].pin, GPIO_PIN_SET);
                led_vector_data_default[index_led].state = LED_STATE_IDLE;
                break;
            default:
                break;
            }
        }
    }
}

/***********************************************************************************/

void led_set_pulse(led_names_t name, led_mode_pulse_t mode_pulse)
{
    queue_led_crtl_t queue_led_crtl_send = {0};

    queue_led_crtl_send.mode = mode_pulse;
    queue_led_crtl_send.name = name;

    if(queue_led != NULL)
    {
        xQueueSend(queue_led, &queue_led_crtl_send, pdMS_TO_TICKS(200));
    }
}

/***********************************************************************************/

void led_init(void)
{
    TaskHandle_t xHandle = NULL;
    if(queue_led == NULL)
    {
        queue_led = xQueueCreate((UBaseType_t) (10), sizeof(queue_led_crtl_t));
    }
    if ((xTaskCreate((TaskFunction_t)led_thread, /* Function that implements the task. */
                     "LED",                      /* Text name for the task. */
                     64,                         /* Stack size in words, not bytes. */
                     NULL,                       /* Parameter passed into the task. */
                     osPriorityNormal,           /* Priority at which the task is created. */
                     &xHandle)) != pdPASS)       /* Used to pass out the created task's handle. */
    {
        HAL_GPIO_TogglePin(led_vector_data_default[0].GPIO, led_vector_data_default[0].pin);
    }
}

/***********************************************************************************/