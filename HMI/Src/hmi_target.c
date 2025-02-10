
/***********************************************************************************/

#include "hmi_target.h"
#include "hmi_target_types.h"
#include "hmi_dashboard.h"
#include "hmi_dashboard_cfg.h"
#include "hmi.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "buzzer.h"

/***********************************************************************************/

void hmi_target_init(void);
void hmi_target_show_screen(void);
void hmi_target_update_data(void);
void hmi_target_update_button(button_id_t button_id, button_press_type_t button_press_type);
void hmi_target_update_encoder(enc_state_t enc_state);


static void hmi_target_draw_all_parameters(void);

/***********************************************************************************/

static void hmi_target_draw_all_parameters(void)
{
    ssd1306_SetCursor(26, 2);
    ssd1306_WriteString("TARGET VALUES", Font_6x8, White);

    DRAW_INFO_RECTANGLE; 
    hmi_dashboard_draw_mode_control();
    
    DRAW_LINE_BETWEEN_INFO_RECTANGLE;
    hmi_dashboard_draw_out_state();
    DRAW_INVERT_RECTANGLE_OUT_STATE; 

    hmi_dashboard_draw_voltage_output();
    DRAW_LINE_BETWEEN_MAIN_RECTANGLE; 
    hmi_dashboard_draw_current();
    hmi_dashboard_update_state_cursor();
    DRAW_MAIN_RECTANGLE;
    DRAW_INVERT_RECTANGLE_STATUS_BAR;
}

/***********************************************************************************/

void hmi_target_init(void)
{

}

/***********************************************************************************/

void hmi_target_show_screen(void)
{
    display_clear();
    hmi_target_draw_all_parameters();
    display_update();
}

/***********************************************************************************/

void hmi_target_update_data(void)
{
    hmi_dashboard_update_cursor();
}

/***********************************************************************************/

void hmi_target_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    switch (button_id)
    {
    case BUTTON_LEFT_ID:
        hmi_dashboard_decrement_index_field();
        break;
    case BUTTON_RIGHT_ID:
        hmi_dashboard_increment_index_field();
        break;
    case BUTTON_SEL_CC_CV_ID:
        switch (button_press_type)
        {
        case BUTTON_SHORT_PRESS:
            hmi_dashboard_cursor_edit_toggle();
            break;
        case BUTTON_LONG_PRESS:
            hmi_set_screen(HMI_ID_DASHBOARD);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    hmi_dashboard_cursor_update_status();
    set_short_pulse_buzzer(BUZZER_MEDIUM_PULSE, BUZZER_AUTO_RESTART_OFF, BUZZER_PULSE_INIT, BUZZER_VOL_MEDIUM);
    hmi_dashboard_correction_cursor_field_current();

    display_clear();
    hmi_target_draw_all_parameters();
    display_update();
}

/***********************************************************************************/

void hmi_target_update_encoder(enc_state_t enc_state)
{
    switch (enc_state)
    {
    case ENC_STATE_CCW:
        hmi_dashboard_decrement_digit();
        break;
    case ENC_STATE_CW:
        hmi_dashboard_increment_digit();
        break;
    default:
        break;
    }

    hmi_dashboard_set_limits();
    hmi_dashboard_cursor_update_status();
    set_short_pulse_buzzer(BUZZER_SHORT_PULSE, BUZZER_AUTO_RESTART_OFF, BUZZER_PULSE_INIT, BUZZER_VOL_MEDIUM);

    display_clear();
    hmi_target_draw_all_parameters();
    display_update();
}