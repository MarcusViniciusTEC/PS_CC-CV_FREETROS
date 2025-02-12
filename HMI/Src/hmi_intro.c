
#include "hmi_intro.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "buzzer.h"
#include "led.h"

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

void hmi_intro_update_data(void)
{
    static uint32_t last_tick = 0;
    led_set_pulse(LED_NAME_MCU_STATUS, LED_MODE_HEARTBEAT_PULSE);
    led_set_pulse(LED_NAME_UPDATE_DISPLAY, LED_MODE_HEARTBEAT_PULSE);
    led_set_pulse(LED_NAME_USER, LED_MODE_HEARTBEAT_PULSE);
    led_set_pulse(LED_NAME_UART_RX, LED_MODE_HEARTBEAT_PULSE);
    led_set_pulse(LED_NAME_UART_TX, LED_MODE_HEARTBEAT_PULSE);
    
    if(HAL_GetTick() - last_tick >= TIME_EXECUTIN_INTRO)
    {
        led_set_pulse(LED_NAME_MCU_STATUS, LED_MODE_OFF);
        led_set_pulse(LED_NAME_UPDATE_DISPLAY, LED_MODE_OFF);
        led_set_pulse(LED_NAME_USER, LED_MODE_OFF);
        led_set_pulse(LED_NAME_UART_RX, LED_MODE_OFF);
        led_set_pulse(LED_NAME_USER, LED_MODE_OFF);
        set_short_pulse_buzzer(BUZZER_SHORT_PULSE, BUZZER_AUTO_RESTART_OFF, BUZZER_PULSE_INIT, BUZZER_VOL_MEDIUM);
        hmi_set_screen(HMI_ID_DASHBOARD);
    }
}

/***********************************************************************************/

void hmi_intro_update_button(button_id_t button_id, button_press_type_t button_press_type)
{

}

/***********************************************************************************/

void hmi_intro_update_encoder(enc_state_t enc_state)
{


}

/***********************************************************************************/