
#include "hmi.h"
#include "hmi_types.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/***********************************************************************************/

hmi_screen_info_t hmi_vector_screens[HMI_NUMBER_OF_SCREENS] = vector_hmi_screens_default;
hmi_ctrl_t hmi_ctrl = {0};

/***********************************************************************************/
// Function prototypes

void hmi_tread(void const *pvParameters);

// private function

static void hmi_showing_screen(void);
static void hmi_showing_data(void);
static void hmi_showing_update_data(void);


/***********************************************************************************/

void hmi_init(void)
{
    hmi_ctrl.id = hmi_id_dashboard;

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

static void hmi_showing_update_data(void)
{
    hmi_vector_screens[hmi_ctrl.id].update_data();
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
            hmi_showing_update_data();
            break;
        default:
            break;
        }
        vTaskDelay(200);
        // ssd1306_Fill(Black);
        // ssd1306_SetCursor(46, 2);
        // ssd1306_WriteString("CURRENT", Font_7x10, White) ;
        // ssd1306_InvertRectangle(0,1,127,10);  
        // ssd1306_Line(0,13,128,13,White);
        // ssd1306_UpdateScreen();
        // static uint8_t count = 0;
        // count++;

    }
}