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
    ssd1306_Fill(Black);
    ssd1306_SetCursor(1, 2);


    ssd1306_WriteString("Fan 30% 45'C", Font_6x8, White);
    ssd1306_SetCursor(80, 2);

    

    ssd1306_WriteString("25.0Vin", Font_6x8, White);
    ssd1306_InvertRectangle(0,1,127,9);

    ssd1306_Line(0,11,99,11, White);


    ssd1306_SetCursor(1, 13);
    ssd1306_WriteString("23.12V", Font_16x26, White);
    ssd1306_Line(0,35,100,35, White);


    ssd1306_SetCursor(16, 38);
    ssd1306_WriteString("3.23A", Font_16x26, White);

    ssd1306_InvertRectangle(2,13,16,33);

    ssd1306_SetCursor(107, 40);
    ssd1306_WriteString("", Font_6x8, White);

    ssd1306_SetCursor(107, 50);
    ssd1306_WriteString("CC", Font_7x10, White);

    ssd1306_Line(100,12,100,63, White);

    ssd1306_SetCursor(106, 14);
    ssd1306_WriteString("OUT", Font_6x8, White);
    ssd1306_InvertRectangle(104,13,124,21);

    ssd1306_DrawRectangle(102, 11, 126, 63, White);

    ssd1306_SetCursor(106, 25);
    ssd1306_WriteString("OFF", Font_6x8, White);
    ssd1306_Line(102,35,126,35, White);
    ssd1306_Line(0,12,0,63, White);

    ssd1306_Line(0,63,99,63, White);

    





    ssd1306_UpdateScreen();
}

/***********************************************************************************/

void hmi_dashboard_show_data(void)
{

}

/***********************************************************************************/

void hmi_dashboard_update_screen(button_id_t button_id, button_press_type_t button_press_type)
{

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
