#include "hmi_dashboard.h"
#include "hmi_dashboard_types.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"

/***********************************************************************************/

static const cursor_retangle_t vector_cursor_retangle_voltage[VOLTAGE_NUMBER_OF_COORDINATE] = vector_hmi_coordinate_voltage_default;
static const cursor_retangle_t vector_cursor_retangle_current[CURRENT_NUMBER_OF_COORDINATE] = vector_hmi_coordinate_current_default;

static hmi_dashboard_crtl_t hmi_dashboard_crtl = {0};

static hmi_edit_value_t hmi_edit_value_voltage;
static hmi_edit_value_t hmi_edit_value_current;

/***********************************************************************************/

void hmi_dashboard_init(void);
void hmi_dashboard_show_screen(void);
void hmi_dashboard_show_data(void);
void hmi_dashboard_update_screen(button_id_t button_id, button_press_type_t button_press_type);
void hmi_dashboard_update_encoder(enc_state_t enc_state);

static void hmi_dashboard_draw_cursor_voltage(void);
static void hmi_dashboard_draw_cursor_current(void);
static void hmi_dashboard_update_state_cursor(void);

static void hmi_dashboard_increment_index(void);
static void hmi_dashboard_decrement_index(void);
static void hmi_dashboard_cursor_edit_toggle(void);

static void hmi_dashboard_target_voltage(void);
static void hmi_dashboard_target_current(void);

static void hmi_dashboard_draw_voltage_input(void);
static void hmi_dashboard_draw_voltage_output(void);
static void hmi_dashboard_draw_current(void);

static void hmi_dashboard_draw_info_fan(void);
static void hmi_dashboard_draw_out_state(void);

static void hmi_dashboard_draw_mode_control(void);

static void hmi_dashboard_draw_all_parameters(void);

/***********************************************************************************/

void hmi_dashboard_init(void)
{
    hmi_dashboard_crtl.cursor_edit =  HMI_CURSOR_EDIT_VOLTAGE;

    hmi_edit_value_voltage.digit[INDEX_FIRST_DIGIT ] = 0;
    hmi_edit_value_voltage.digit[INDEX_SECOND_DIGIT] = 0;
    hmi_edit_value_voltage.digit[INDEX_THIRD_DIGIT ] = 0;
    hmi_edit_value_voltage.digit[INDEX_FOURTH_DIGIT] = 0;
}

/***********************************************************************************/

static void hmi_dashboard_increment_index(void)
{
    hmi_dashboard_crtl.index_digit ++;
}

/***********************************************************************************/

static void hmi_dashboard_decrement_index(void)
{
    hmi_dashboard_crtl.index_digit --;
}

/***********************************************************************************/

static void hmi_dashboard_cursor_edit_toggle(void)
{
    hmi_dashboard_crtl.cursor_edit =! hmi_dashboard_crtl.cursor_edit; 
}

/***********************************************************************************/

static void hmi_dashboard_draw_cursor_current(void)
{
    cursor_retangle_t cursor_current = {0};

    cursor_current = vector_cursor_retangle_current[hmi_dashboard_crtl.index_digit];
    ssd1306_InvertRectangle(cursor_current.x1, cursor_current.y1, cursor_current.x2, cursor_current.y2);
}

/***********************************************************************************/

static void hmi_dashboard_draw_cursor_voltage(void)
{
    cursor_retangle_t cursor_voltage = {0};

    cursor_voltage = vector_cursor_retangle_voltage[hmi_dashboard_crtl.index_digit];
    ssd1306_InvertRectangle(cursor_voltage.x1, cursor_voltage.y1, cursor_voltage.x2, cursor_voltage.y2);
}

/***********************************************************************************/

static void hmi_dashboard_target_voltage(void)
{
    static uint16_t value = 0;

    hmi_edit_value_voltage.digit[INDEX_FIRST_DIGIT ] = 1000;
    hmi_edit_value_voltage.digit[INDEX_SECOND_DIGIT] = 200;
    hmi_edit_value_voltage.digit[INDEX_THIRD_DIGIT ] = 30;
    hmi_edit_value_voltage.digit[INDEX_FOURTH_DIGIT] = 4;

    for(hmi_digit_types_t index = 0; index < NUMBER_OF_INDEX_DIGITS; index++)
    {
        value += hmi_edit_value_voltage.digit[index];
    }
}

/***********************************************************************************/

static void hmi_dashboard_target_current(void)
{
    static uint16_t value = 0;

    hmi_edit_value_current.digit[INDEX_FIRST_DIGIT ] = 200;
    hmi_edit_value_current.digit[INDEX_SECOND_DIGIT] = 30;
    hmi_edit_value_current.digit[INDEX_THIRD_DIGIT ] = 1;
    hmi_edit_value_current.digit[INDEX_FOURTH_DIGIT] = NO_DIGIT;

    for(hmi_digit_types_t index = 0; index <= INDEX_FOURTH_DIGIT; index++)
    {
        value += hmi_edit_value_current.digit[index];
    }
}

/***********************************************************************************/

static void hmi_dashboard_update_state_cursor(void)
{
    switch (hmi_dashboard_crtl.cursor_edit)
    {
    case HMI_CURSOR_EDIT_CURRENT:
        hmi_dashboard_draw_cursor_current();
        break;
    case HMI_CURSOR_EDIT_VOLTAGE:
        hmi_dashboard_draw_cursor_voltage();
        break;;
    default:
        break;
    }
}

/***********************************************************************************/

static void hmi_dashboard_draw_current(void)
{
    ssd1306_SetCursor(16, 38);
    ssd1306_WriteString("2.22A", Font_16x26, White);
}

/***********************************************************************************/

static void hmi_dashboard_draw_voltage_output(void)
{
    char sz_string[15] = {0};
    ssd1306_SetCursor(1, 13);
    snprintf(sz_string, 12, "%u%u.%u%uV", hmi_edit_value_voltage.digit[INDEX_FIRST_DIGIT ], hmi_edit_value_voltage.digit[INDEX_SECOND_DIGIT], 
    hmi_edit_value_voltage.digit[INDEX_THIRD_DIGIT], hmi_edit_value_voltage.digit[INDEX_FOURTH_DIGIT]);

    ssd1306_WriteString(sz_string, Font_16x26, White); 
}

/***********************************************************************************/

static void hmi_dashboard_draw_voltage_input(void)
{
    ssd1306_SetCursor(80, 2);
    ssd1306_WriteString("25.0Vin", Font_6x8, White);
} 

/***********************************************************************************/

static void hmi_dashboard_draw_info_fan(void)
{
    ssd1306_SetCursor(1, 2);
    ssd1306_WriteString("Fan 30% 45'C", Font_6x8, White);
} 

/***********************************************************************************/

static void hmi_dashboard_draw_out_state(void)
{
    ssd1306_SetCursor(106, 14);
    ssd1306_WriteString("OUT", Font_6x8, White);
    ssd1306_SetCursor(106, 25);
    ssd1306_WriteString("OFF", Font_6x8, White);
}

/***********************************************************************************/

static void hmi_dashboard_draw_mode_control(void)
{
    ssd1306_SetCursor(106, 38);
    ssd1306_WriteString("MOD", Font_6x8, White);
    ssd1306_SetCursor(107, 50);
    ssd1306_WriteString("CC", Font_7x10, White);
}

/***********************************************************************************/

static void hmi_dashboard_draw_all_parameters(void)
{
    display_clear();
    hmi_dashboard_draw_info_fan();
    

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
    DRAW_INVERT_RECTANGLE_MODE;

    


}

/***********************************************************************************/

void hmi_dashboard_show_screen(void)
{
    display_clear();
    hmi_dashboard_draw_all_parameters();
    display_update();
}

/***********************************************************************************/

void hmi_dashboard_update_data(void)
{
    
}

/***********************************************************************************/

void hmi_dashboard_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    switch (button_id)
    {
    case BUTTON_LEFT_ID:
        hmi_dashboard_decrement_index();
        
        break;
    case BUTTON_RIGHT_ID:
        hmi_dashboard_increment_index();
        
        break;
    case BUTTON_SEL_CC_CV_ID:
            switch (button_press_type)
            {
            case BUTTON_SHORT_PRESS:
                hmi_dashboard_cursor_edit_toggle();
                break;
            case BUTTON_LONG_PRESS:

                break;
            default:
                break;
            }
        break;
    default:
        break;
    }

    display_clear();
    hmi_dashboard_draw_all_parameters();
    display_update();

    
}

/***********************************************************************************/

void hmi_dashboard_update_encoder(enc_state_t enc_state)
{
    switch (enc_state)
    {
    case ENC_STATE_CCW:
        switch (hmi_dashboard_crtl.cursor_edit)
        {
            case HMI_CURSOR_EDIT_CURRENT:
                hmi_edit_value_current.digit[hmi_dashboard_crtl.index_digit] --;
                break;
            case HMI_CURSOR_EDIT_VOLTAGE:
                hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit] --;
                break;
            default:
            break;
        }
        break;
    case ENC_STATE_CW:
        switch (hmi_dashboard_crtl.cursor_edit)
        {
            case HMI_CURSOR_EDIT_CURRENT:
                hmi_edit_value_current.digit[hmi_dashboard_crtl.index_digit] ++;
                break;
            case HMI_CURSOR_EDIT_VOLTAGE:
                hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit] ++;
                break;
            default:
            break;
        }
        break;
    default:
        break;
    }

    if(hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit] > 9)
    {
        if(hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit-1] <= 9 )
        {
            hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit -1 ] = hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit-1] + 1;
            hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit] = 0;
            if(hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit-1] > 9)
            {
                hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit - 2] = hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit-2] + 1;
                hmi_edit_value_voltage.digit[hmi_dashboard_crtl.index_digit - 1] = 0;
            }
        }
    }


    display_clear();
    hmi_dashboard_draw_all_parameters();
    display_update();
}
