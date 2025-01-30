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

/***********************************************************************************/

void hmi_dashboard_init(void)
{
    hmi_dashboard_crtl.cursor_edit =  HMI_CURSOR_EDIT_VOLTAGE;

    
}

/***********************************************************************************/

static void hmi_dashboard_increment_index(void)
{
    hmi_dashboard_crtl.index_cursor ++;
}

/***********************************************************************************/

static void hmi_dashboard_decrement_index(void)
{
    hmi_dashboard_crtl.index_cursor --;
}

/***********************************************************************************/

static void hmi_dashboard_cursor_edit_toggle(void)
{
    hmi_dashboard_crtl.cursor_edit =! hmi_dashboard_crtl.cursor_edit; 
    HAL_Delay(1);
}

/***********************************************************************************/

static void hmi_dashboard_draw_cursor_current(void)
{
    cursor_retangle_t cursor_current = {0};

    cursor_current = vector_cursor_retangle_current[hmi_dashboard_crtl.index_cursor];
    ssd1306_InvertRectangle(cursor_current.x1, cursor_current.y1, cursor_current.x2, cursor_current.y2);
}

/***********************************************************************************/

static void hmi_dashboard_draw_cursor_voltage(void)
{
    cursor_retangle_t cursor_voltage = {0};

    cursor_voltage = vector_cursor_retangle_voltage[hmi_dashboard_crtl.index_cursor];
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


    for(uint8_t index = 0; index <= 4; index++)
    {
        value += hmi_edit_value_voltage.digit[index];
    }
}


/***********************************************************************************/

void hmi_dashboard_update_state_cursor(void)
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

void hmi_dashboard_show_screen(void)
{

}

/***********************************************************************************/

void hmi_dashboard_update_data(void)
{
    ssd1306_Fill(Black);
    
    /*===================================================*/

    ssd1306_SetCursor(1, 2);
    ssd1306_WriteString("Fan 30% 45'C", Font_6x8, White);
    
    ssd1306_SetCursor(80, 2);
    ssd1306_WriteString("25.0Vin", Font_6x8, White);
    ssd1306_InvertRectangle(0,1,127,9); // bar status
    
    hmi_dashboard_target_voltage();


    /*===================================================*/

    ssd1306_Line(0,11,99,11, White); 
    ssd1306_Line(102,35,126,35, White);
  
    /*===================================================*/

    ssd1306_SetCursor(1, 13);
    ssd1306_WriteString("29.15V", Font_16x26, White); 
    
    /*===================================================*/

    ssd1306_Line(0,35,100,35, White);

    /*===================================================*/
    ssd1306_SetCursor(16, 38);
    ssd1306_WriteString("2.22A", Font_16x26, White);
    
    /*===================================================*/

    hmi_dashboard_update_state_cursor();
    
    /*===================================================*/
    /*DRAW MODE CC OR CV*/
    ssd1306_SetCursor(106, 38);
    ssd1306_WriteString("MOD", Font_6x8, White);
    ssd1306_InvertRectangle(104,37,124,46);
    /*===================================================*/

    ssd1306_SetCursor(107, 50);
    ssd1306_WriteString("CC", Font_7x10, White);
    
    /*===================================================*/
    
    ssd1306_Line(100,12,100,63, White);

    /*===================================================*/

    ssd1306_Line(0,12,0,63, White);
    ssd1306_Line(0,63,99,63, White);

    ssd1306_SetCursor(106, 14);
    ssd1306_WriteString("OUT", Font_6x8, White);
    ssd1306_SetCursor(106, 25);
    ssd1306_WriteString("OFF", Font_6x8, White);
    ssd1306_InvertRectangle(104,13,124,21);

    /*===================================================*/

    ssd1306_DrawRectangle(102, 11, 126, 63, White);

    ssd1306_Line(0,12,0,63, White);
    ssd1306_Line(0,63,99,63, White);
}

/***********************************************************************************/

void hmi_dashboard_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    ssd1306_UpdateScreen();
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

}

/***********************************************************************************/

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

}
