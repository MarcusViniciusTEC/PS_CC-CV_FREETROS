#include "hmi_dashboard.h"
#include "hmi_dashboard_types.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"

/***********************************************************************************/

static const cursor_retangle_t vector_cursor_retangle_voltage[VOLTAGE_NUMBER_OF_COORDINATE] = vector_hmi_coordinate_voltage_default;
static const cursor_retangle_t vector_cursor_retangle_current[CURRENT_NUMBER_OF_COORDINATE] = vector_hmi_coordinate_current_default;

static hmi_dashboard_crtl_t hmi_dashboard_crtl = {0};

static hmi_edit_value_t hmi_edit_value[HMI_NUMBER_OF_FIELDS_EDITS] = {0};

/***********************************************************************************/

void hmi_dashboard_init(void);
void hmi_dashboard_show_screen(void);
void hmi_dashboard_show_data(void);
void hmi_dashboard_update_screen(button_id_t button_id, button_press_type_t button_press_type);
void hmi_dashboard_update_encoder(enc_state_t enc_state);

static void hmi_dashboard_draw_cursor_voltage(void);
static void hmi_dashboard_draw_cursor_current(void);
static void hmi_dashboard_update_state_cursor(void);

static void hmi_dashboard_increment_index_field(void);
static void hmi_dashboard_decrement_index_field(void);
static void hmi_dashboard_cursor_edit_toggle(void);

static void hmi_dashboard_decrement_digit(void);
static void hmi_dashboard_increment_digit(void);

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
    hmi_dashboard_crtl.cursor_edit =  HMI_CURSOR_EDIT_FIELD_VOLTAGE;

    for(uint8_t index_filed = 0; index_filed < HMI_NUMBER_OF_FIELDS_EDITS; index_filed++)
    {
        hmi_edit_value[index_filed].digit[INDEX_FIRST_DIGIT ] = 0;
        hmi_edit_value[index_filed].digit[INDEX_SECOND_DIGIT] = 0;
        hmi_edit_value[index_filed].digit[INDEX_THIRD_DIGIT ] = 0;
        hmi_edit_value[index_filed].digit[INDEX_FOURTH_DIGIT] = 0;
    }
}

/***********************************************************************************/

static void hmi_dashboard_increment_index_field(void)
{
    switch (hmi_dashboard_crtl.cursor_edit)
    {
    case HMI_CURSOR_EDIT_FIELD_CURRENT:
        if(hmi_dashboard_crtl.index_digit <= INDEX_FOURTH_DIGIT)
        {
            hmi_dashboard_crtl.index_digit++;
            if(hmi_dashboard_crtl.index_digit >= INDEX_FOURTH_DIGIT)
            {
                hmi_dashboard_crtl.index_digit = INDEX_THIRD_DIGIT;
            }
        }
        break;
    case HMI_CURSOR_EDIT_FIELD_VOLTAGE:
        if(hmi_dashboard_crtl.index_digit < INDEX_FOURTH_DIGIT)
        {
            hmi_dashboard_crtl.index_digit++;
        } 
        else if (hmi_dashboard_crtl.index_digit > INDEX_FOURTH_DIGIT)
        {
            hmi_dashboard_crtl.index_digit = INDEX_FIRST_DIGIT;
        }
        break;
    default:
        break;
    }
}

/***********************************************************************************/

static void hmi_dashboard_decrement_index_field(void)
{
    switch (hmi_dashboard_crtl.cursor_edit)
    {
    case HMI_CURSOR_EDIT_FIELD_CURRENT:
        if(hmi_dashboard_crtl.index_digit < INDEX_FOURTH_DIGIT)
        {
            hmi_dashboard_crtl.index_digit--;
            if(hmi_dashboard_crtl.index_digit > INDEX_FOURTH_DIGIT)
            {
                hmi_dashboard_crtl.index_digit = INDEX_FIRST_DIGIT;
            }
        }
        break;
    case HMI_CURSOR_EDIT_FIELD_VOLTAGE:
        if(hmi_dashboard_crtl.index_digit <= INDEX_FOURTH_DIGIT)
        {
            hmi_dashboard_crtl.index_digit--;
            if(hmi_dashboard_crtl.index_digit > INDEX_FOURTH_DIGIT)
            {
                hmi_dashboard_crtl.index_digit = INDEX_FIRST_DIGIT;
            }
        }
        break;
    default:
        break;
    }
}

/***********************************************************************************/

static void hmi_dashboard_decrement_digit(void)
{
    switch (hmi_dashboard_crtl.cursor_edit)
    {
        case HMI_CURSOR_EDIT_FIELD_CURRENT:
            hmi_edit_value[HMI_CURSOR_EDIT_FIELD_CURRENT].digit[hmi_dashboard_crtl.index_digit] --;
            break;
        case HMI_CURSOR_EDIT_FIELD_VOLTAGE:
            hmi_edit_value[HMI_CURSOR_EDIT_FIELD_VOLTAGE].digit[hmi_dashboard_crtl.index_digit] --;
            break;
        default:
        break;
    }
    
    for(uint8_t index_field = 0; index_field < HMI_NUMBER_OF_FIELDS_EDITS; index_field++)
    {
        if(hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit] > MAX_DIGIT)
        {
            if(hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit - 1] > MIN_DIGIT)
            {
                hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit - 1]  = hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit - 1] - 1; 
                hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit] = MAX_DIGIT;
            }
        }

        if (hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit] > MAX_DIGIT)
        {
            hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit] = MIN_DIGIT;
        }
    }
}

/***********************************************************************************/

static void hmi_dashboard_increment_digit(void)
{
    switch (hmi_dashboard_crtl.cursor_edit)
    {
    case HMI_CURSOR_EDIT_FIELD_CURRENT:
        hmi_edit_value[HMI_CURSOR_EDIT_FIELD_CURRENT].digit[hmi_dashboard_crtl.index_digit]++;
        break;
    case HMI_CURSOR_EDIT_FIELD_VOLTAGE:
        hmi_edit_value[HMI_CURSOR_EDIT_FIELD_VOLTAGE].digit[hmi_dashboard_crtl.index_digit]++;
        break;
    default:
        break;
    }

    for(uint8_t index_field = 0; index_field < HMI_NUMBER_OF_FIELDS_EDITS; index_field++)
    {
        if(hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit] > MAX_DIGIT)
        {
            if(hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit-1] <= MAX_DIGIT )
            {
                hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit -1 ] = hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit-1] + 1;
                hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit] = MIN_DIGIT;
                if(hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit-1] > MAX_DIGIT)
                {
                    hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit - 2] = hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit-2] + 1;
                    hmi_edit_value[index_field].digit[hmi_dashboard_crtl.index_digit - 1] = MIN_DIGIT;
                }
            }
        }
    }
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

}

/***********************************************************************************/

static void hmi_dashboard_target_current(void)
{

}

/***********************************************************************************/

static void hmi_dashboard_update_state_cursor(void)
{
    switch (hmi_dashboard_crtl.cursor_edit)
    {
    case HMI_CURSOR_EDIT_FIELD_CURRENT:
        hmi_dashboard_draw_cursor_current();
        break;
    case HMI_CURSOR_EDIT_FIELD_VOLTAGE:
        hmi_dashboard_draw_cursor_voltage();
        break;;
    default:
        break;
    }
}

/***********************************************************************************/

static void hmi_dashboard_draw_current(void)
{   
    char sz_string[15] = {0};
    ssd1306_SetCursor(16, 38);

    snprintf(sz_string, sizeof(sz_string), "%u.%u%uA", 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_CURRENT].digit[INDEX_FIRST_DIGIT], 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_CURRENT].digit[INDEX_SECOND_DIGIT], 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_CURRENT].digit[INDEX_THIRD_DIGIT]);
    ssd1306_WriteString(sz_string, Font_16x26, White); 
}

/***********************************************************************************/

static void hmi_dashboard_draw_voltage_output(void)
{
    char sz_string[15] = {0};
    ssd1306_SetCursor(1, 13);
    snprintf(sz_string, sizeof(sz_string), "%u%u.%u%uV", 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_VOLTAGE].digit[INDEX_FIRST_DIGIT], 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_VOLTAGE].digit[INDEX_SECOND_DIGIT], 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_VOLTAGE].digit[INDEX_THIRD_DIGIT], 
    hmi_edit_value[HMI_CURSOR_EDIT_FIELD_VOLTAGE].digit[INDEX_FOURTH_DIGIT]);
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

                break;
            default:
                break;
            }
        break;
    default:
        break;
    }

    if(hmi_dashboard_crtl.cursor_edit == HMI_CURSOR_EDIT_FIELD_CURRENT && hmi_dashboard_crtl.index_digit > INDEX_THIRD_DIGIT)
    {
        hmi_dashboard_crtl.index_digit = INDEX_THIRD_DIGIT;
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
        hmi_dashboard_decrement_digit();
        break;
    case ENC_STATE_CW:
        hmi_dashboard_increment_digit();
        break;
    default:
        break;
    }

    for (uint8_t index_field = 0; index_field < HMI_NUMBER_OF_FIELDS_EDITS; index_field++)
    {
        if (hmi_edit_value[index_field].digit[INDEX_FIRST_DIGIT] >= NUMBER_OF_INDEX_DIGITS)
        {
            hmi_edit_value[index_field].digit[INDEX_FIRST_DIGIT] = 3;
        }
        if (hmi_edit_value[index_field].digit[INDEX_FIRST_DIGIT] == 3)
        {
            hmi_edit_value[index_field].digit[INDEX_SECOND_DIGIT] = MIN_DIGIT;
            hmi_edit_value[index_field].digit[INDEX_THIRD_DIGIT] = MIN_DIGIT;
            hmi_edit_value[index_field].digit[INDEX_FOURTH_DIGIT] = MIN_DIGIT;
        }
    }

    display_clear();
    hmi_dashboard_draw_all_parameters();
    display_update();
}
