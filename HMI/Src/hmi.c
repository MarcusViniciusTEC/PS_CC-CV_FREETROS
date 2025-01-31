#include "hmi.h"


#include "buttons.h"
#include "encoder.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/***********************************************************************************/

hmi_screen_info_t hmi_vector_screens[HMI_NUMBER_OF_SCREENS] = vector_hmi_screens_default;
hmi_ctrl_t hmi_ctrl = {0};
button_data_t buttons_data_vector[NUMBER_OF_BUTTONS] = vector_buttons_data_default;

/***********************************************************************************/
// Function prototypes

void hmi_tread(void const *pvParameters);
void hmi_tread_update_screen(void const *pvParameters);

// private function

static void hmi_showing_screen(void);
static void hmi_showing_data(void);
static void hmi_encoder_update_state(void);
void hmi_showing_update_data_encoder(enc_state_t enc_state);
void hmi_set_screen(hmi_screens_id_t hmi_screens_id);
hmi_screens_id_t hmi_get_screen(void);

/***********************************************************************************/

static const encoder_data_t encoder_data [] = {{hmi_showing_update_data_encoder, 0, 0}};

/***********************************************************************************/

void hmi_init(void)
{
    hmi_ctrl.screen_id = HMI_ID_INTRO;
    hmi_vector_screens[hmi_ctrl.screen_id].init();
    TaskHandle_t xHandle = NULL;
     xTaskCreate((TaskFunction_t)hmi_tread,         /* Function that implements the task. */
                    "HMI",                         /* Text name for the task. */
                    256	,                                   /* Stack size in words, not bytes. */
                    NULL,                             /* Parameter passed into the task. */
                    osPriorityNormal ,                        /* Priority at which the task is created. */
                    &xHandle );                     /* Used to pass out the created task's handle. */

    xTaskCreate((TaskFunction_t)hmi_tread_update_screen,         /* Function that implements the task. */
                    "HMI UPDATE",                         /* Text name for the task. */
                    512	,                           /* Stack size in words, not bytes. */
                    NULL,                           /* Parameter passed into the task. */
                    osPriorityNormal,                      /* Priority at which the task is created. */
                    &xHandle );                     /* Used to pass out the created task's handle. */                
}

/***********************************************************************************/

hmi_screens_id_t hmi_get_screen(void)
{
    return hmi_ctrl.screen_id;
}

/***********************************************************************************/

void hmi_set_screen(hmi_screens_id_t hmi_screens_id)
{
    hmi_ctrl.next_screen_id = hmi_screens_id;
}

/***********************************************************************************/

static void hmi_showing_screen(void)
{
    hmi_vector_screens[hmi_ctrl.screen_id].show_screen();
}

/***********************************************************************************/

static void hmi_showing_data(void)
{
    hmi_vector_screens[hmi_ctrl.screen_id].show_data();
}

/***********************************************************************************/

void hmi_showing_update_data(button_id_t button_id, button_press_type_t button_press_type)
{
    hmi_vector_screens[hmi_ctrl.screen_id].update_data_buttons(button_id,  button_press_type);
}

/***********************************************************************************/

void hmi_showing_update_data_encoder(enc_state_t enc_state)
{
    hmi_vector_screens[hmi_ctrl.screen_id].update_data_encoder(enc_state);
}

/***********************************************************************************/

static void hmi_buttons_update_state(void)
{
    for(uint8_t index_buttons = 0; index_buttons < NUMBER_OF_BUTTONS; index_buttons++)
    {
        read_buttons_state(&buttons_data_vector[index_buttons]);    
    }
}

/***********************************************************************************/

static void hmi_encoder_update_state()
{
    read_encoder_state(&encoder_data[0]);
}

/***********************************************************************************/

void hmi_tread(void const *pvParameters)
{
    for(;;)
    {
        if(hmi_ctrl.screen_id != hmi_ctrl.next_screen_id)
        {
            hmi_ctrl.last_screen_id = hmi_ctrl.screen_id;
            hmi_ctrl.screen_id = hmi_ctrl.next_screen_id;
            hmi_ctrl.state = HMI_SHOWING_SCREEN;
        }

        switch (hmi_ctrl.state)
        {
        case HMI_SHOWING_SCREEN:
            hmi_showing_screen();
            hmi_ctrl.state = HMI_SHOWING_DATA;
            break;
        case HMI_SHOWING_DATA:
            
            hmi_ctrl.state = HMI_SHOWING_UPDATE_DATA;
            break;
        case HMI_SHOWING_UPDATE_DATA:
            hmi_buttons_update_state();
            hmi_encoder_update_state();
           // hmi_ctrl.state = HMI_SHOWING_DATA;
            break;
        default:
            break;
        }
        vTaskDelay(1);
    }
}

/***********************************************************************************/

void hmi_tread_update_screen(void const *pvParameters)
{
    for(;;)
    {
         hmi_showing_data();
        vTaskDelay(100);
    }
}


/***********************************************************************************/