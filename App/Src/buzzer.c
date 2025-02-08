#include "buzzer.h"
#include "buzzer_types.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/***********************************************************************************/

QueueHandle_t queue_buzzer = NULL;

void buzzer_thread(void const *pvParameters);
void set_short_pulse_buzzer(buzzer_pulse_types_t buzzer_pulse_types, buzzer_auto_restart_state_t buzzer_auto_restart_state, buzzer_state_t buzzer_state, buzzer_vol_t buzzer_vol);
static void buzzer_set_vol(buzzer_vol_t volume);


/***********************************************************************************/

void set_short_pulse_buzzer(buzzer_pulse_types_t buzzer_pulse_types, buzzer_auto_restart_state_t buzzer_auto_restart_state, buzzer_state_t buzzer_state, buzzer_vol_t buzzer_vol)
{
    queue_buzzer_crtl_t queue_set_pulse_buzzer_send = {0};

    queue_set_pulse_buzzer_send.buzzer_auto_restart_state = buzzer_auto_restart_state;
    queue_set_pulse_buzzer_send.buzzer_pulse_type = buzzer_pulse_types;
    queue_set_pulse_buzzer_send.buzzer_state= buzzer_state;
    queue_set_pulse_buzzer_send.volume = buzzer_vol;

    if(queue_buzzer != NULL)
    {
        xQueueSend(queue_buzzer, &queue_set_pulse_buzzer_send, pdMS_TO_TICKS(200));
    }

}

/***********************************************************************************/

static void buzzer_set_vol(buzzer_vol_t volume)
{
    TIM1->CCR1 = (uint16_t)volume;
}

/***********************************************************************************/

void buzzer_init(void)
{
    TaskHandle_t xHandle = NULL;

    if(queue_buzzer == NULL)
    {
        queue_buzzer = xQueueCreate((UBaseType_t) (10), sizeof(queue_buzzer_crtl_t));
    }
    buzzer_set_vol(BUZZER_MUTE);
    xTaskCreate((TaskFunction_t)buzzer_thread,     /* Function that implements the task. */
                    "BUZZER",                      /* Text name for the task. */
                    64	,                           /* Stack size in words, not bytes. */
                    NULL,                           /* Parameter passed into the task. */
                    osPriorityNormal,               /* Priority at which the task is created. */
                    &xHandle );                     /* Used to pass out the created task's handle. */
}

/***********************************************************************************/

void buzzer_thread(void const *pvParameters)
{
    queue_buzzer_crtl_t queue_buzzer_received, queue_buzzer_crtl = {0};
    for (;;)
    {
        if (xQueueReceive(queue_buzzer, &queue_buzzer_received, 10 == pdPASS))
        {
            queue_buzzer_crtl = queue_buzzer_received;
        }

        switch (queue_buzzer_crtl.buzzer_state)
        {
        case BUZZER_PULSE_INIT:
            queue_buzzer_crtl.buzzer_state = BUZZER_PULSE_START;
            break;
        case BUZZER_PULSE_START:
            queue_buzzer_crtl.buzzer_state = BUZZER_PULSE_TURN_ON;
            buzzer_set_vol(BUZZER_MUTE);
            break;
        case BUZZER_PULSE_TURN_ON:
            buzzer_set_vol(queue_buzzer_crtl.volume);
            queue_buzzer_crtl.last_time = xTaskGetTickCount();
            queue_buzzer_crtl.buzzer_state = BUZZER_PULSE_WAIT_TIME;
            break;
        case BUZZER_PULSE_WAIT_TIME:
            if (xTaskGetTickCount() - queue_buzzer_crtl.last_time > (uint32_t)(queue_buzzer_crtl.buzzer_pulse_type))
            {
                queue_buzzer_crtl.buzzer_state = BUZZER_PULSE_TURN_OFF;
            }
            break;
        case BUZZER_PULSE_TURN_OFF:
            buzzer_set_vol(BUZZER_MUTE);
            break;
        default:
            break;
        }
    }
}


