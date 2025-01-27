#include "hmi.h"
#include "hmi_types.h"

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

// private function

static void hmi_showing_screen(void);
static void hmi_showing_data(void);
static void hmi_encoder_update_state(void);
void hmi_showing_update_data_encoder(enc_state_t enc_state);



/***********************************************************************************/

static const encoder_data_t encoder_data [] = {hmi_showing_update_data_encoder, 0, 0};



void hmi_init(void)
{
    hmi_ctrl.id = HMI_ID_DASHBOARD;
    hmi_vector_screens[hmi_ctrl.id].init();
    TaskHandle_t xHandle = NULL;
     xTaskCreate((TaskFunction_t)hmi_tread,         /* Function that implements the task. */
                    "HMI",                         /* Text name for the task. */
                    128	,                           /* Stack size in words, not bytes. */
                    NULL,                           /* Parameter passed into the task. */
                    osPriorityAboveNormal,          /* Priority at which the task is created. */
                    &xHandle );                     /* Used to pass out the created task's handle. */
}

/***********************************************************************************/

static void hmi_showing_screen(void)
{
    hmi_vector_screens[hmi_ctrl.id].show_screen();
}

/***********************************************************************************/

static void hmi_showing_data(void)
{
    hmi_vector_screens[hmi_ctrl.id].show_data();
}

/***********************************************************************************/

void hmi_showing_update_data(button_id_t button_id, button_press_type_t button_press_type)
{
    hmi_vector_screens[hmi_ctrl.id].update_data_buttons(button_id,  button_press_type);
}

/***********************************************************************************/

void hmi_showing_update_data_encoder(enc_state_t enc_state)
{
    hmi_vector_screens[hmi_ctrl.id].update_data_encoder(enc_state);
}

/***********************************************************************************/

static void hmi_buttons_update_state(void)
{
    for(uint8_t index_buttons = 0; index_buttons < NUMBER_OF_BUTTONS; index_buttons++)
    {
        read_buttons_state(&buttons_data_vector[index_buttons]);    
    }
}

static void hmi_encoder_update_state()
{
    read_encoder_state(&encoder_data[0]);
}

/***********************************************************************************/

void hmi_tread(void const *pvParameters)
{
    for(;;)
    {
        switch (hmi_ctrl.state)
        {
        case HMI_SHOWING_SCREEN:
            hmi_showing_screen();
            hmi_ctrl.state = HMI_SHOWING_DATA;
            break;
        case HMI_SHOWING_DATA:
            hmi_showing_data();
            hmi_ctrl.state = HMI_SHOWING_UPDATE_DATA;
            break;
        case HMI_SHOWING_UPDATE_DATA:
            hmi_buttons_update_state();
            hmi_encoder_update_state();
            break;
        default:
            break;
        }
        vTaskDelay(1);
    }
}