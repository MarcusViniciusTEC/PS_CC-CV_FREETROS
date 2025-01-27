#include "hmi_dashboard.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"


/***********************************************************************************/

void hmi_dashboard_init(void)
{
    // ssd1306_Fill(Black);
    // ssd1306_SetCursor(10, 10);
    // ssd1306_WriteString("hmi init", Font_7x10, White) ;
    // ssd1306_UpdateScreen();
}

/***********************************************************************************/

void hmi_dashboard_show_screen(void)
{
    
}

/***********************************************************************************/

void hmi_dashboard_show_data(void)
{

}

/***********************************************************************************/

void hmi_dashboard_update_screen(button_id_t button_id, button_press_type_t button_press_type)
{
    // char *string;


    // if(button_id == BUTTON_SEL_CC_CV_ID) 
    // {
    //     string = "BUTTON_SEL_CC_CV_ID";
    // }
    // else if (button_id == BUTTON_OUT_STATE_ID) 
    // {
    //     string = "BUTTON_OUT_STATE_ID";
    // }
    

    // char buff[10];
    // ssd1306_Fill(Black);
    // ssd1306_SetCursor(0, 46);
    // sprintf(buff, "%d", button_id);
    // ssd1306_WriteString(buff, Font_7x10, White) ;
    // ssd1306_UpdateScreen();
}

void hmi_dashboard_update_encoder(enc_state_t enc_state)
{

    static uint16_t count = 0;

    switch (enc_state)
    {
    case ENC_STATE_CCW:
        count--;
        break;
    
    case ENC_STATE_CW:
        count++;
        break;

    default:
        break;
    }


    char buff[10];
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 46);
    sprintf(buff, "%d", count);
    ssd1306_WriteString(buff, Font_7x10, White) ;
    ssd1306_UpdateScreen();
}
