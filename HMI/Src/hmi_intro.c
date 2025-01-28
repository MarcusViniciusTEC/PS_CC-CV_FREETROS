
#include "hmi_intro.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "hmi.h"

/***********************************************************************************/

void hmi_intro_init(void)
{

}

/***********************************************************************************/

void hmi_intro_show_screen(void)
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 10);
    ssd1306_WriteString("POWER SUPPLY CC/CV", Font_7x10, White);
    ssd1306_SetCursor(30, 28);
    ssd1306_WriteString("Init...", Font_7x10, White);
    ssd1306_SetCursor(20, 50);
    ssd1306_WriteString("** MV TECH **", Font_7x10, White);
    ssd1306_UpdateScreen();
}

/***********************************************************************************/

void hmi_intro_show_data(void)
{
    static uint32_t last_tick = 0;
    if(HAL_GetTick() - last_tick >= TIME_EXECUTIN_INTRO)
    {
        hmi_set_screen(HMI_ID_DASHBOARD);
    }
}

/***********************************************************************************/

void hmi_intro_update_screen(button_id_t button_id, button_press_type_t button_press_type)
{
    switch (button_id)
    {
    case BUTTON_ENC_ID:
        hmi_set_screen(HMI_ID_DASHBOARD);
        break;
    
    default:
        break;
    }
}

/***********************************************************************************/

void hmi_intro_update_encoder(enc_state_t enc_state)
{


}

/***********************************************************************************/