

#include "hmi.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#define HMI_STACK_SIZE									( (configSTACK_DEPTH_TYPE)(configMINIMAL_STACK_SIZE * 3U) )


void hmi_tread(void const *pvParameters);

void hmi_init(void)
{
    TaskHandle_t xHandle = NULL;
     xTaskCreate((TaskFunction_t)hmi_tread,      /* Function that implements the task. */
                    "HMI",                         /* Text name for the task. */
                    HMI_STACK_SIZE	,               /* Stack size in words, not bytes. */
                    NULL,                           /* Parameter passed into the task. */
                    osPriorityAboveNormal,          /* Priority at which the task is created. */
                    &xHandle );                     /* Used to pass out the created task's handle. */
}

void hmi_tread(void const *pvParameters)
{
    for(;;)
    {
        ssd1306_Fill(Black);
        ssd1306_SetCursor(46, 2);
        ssd1306_WriteString("CURRENT", Font_7x10, White) ;
        ssd1306_InvertRectangle(0,1,127,10);  
        ssd1306_Line(0,13,128,13,White);
        ssd1306_UpdateScreen();
        static uint8_t count = 0;
        count++;

    }
}