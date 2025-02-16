

#include "hmi_menu.h"
#include "hmi_menu_types.h"
#include "hmi_dashboard_types.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "buzzer.h"
#include "led.h"
#include <stdbool.h>

#include "hmi.h"
#include "hmi_submenu.h"

/***********************************************************************************/

static const hmi_menu_data_t hmi_menu_item_vector[HMI_MENU_NUMBER_OF_ITEMS] = hmi_menu_vector_item_default;
static const cursor_retangle_t vector_cursor_retangle[HMI_MENU_NUMBER_OF_ITEMS] = vector_hmi_coordinate_retangle_menu_default;

static hmi_menu_ctrl_t hmi_menu_ctrl = {0};
static hmi_submenu_data_t hmi_submenu_data[HMI_MENU_NUMBER_OF_ITEMS] = {0};

/***********************************************************************************/

static void hmi_menu_show_draw_menu_itens(void);
static void hmi_menu_show_draw_menu_cursor(void);

static void hmi_menu_insert_data_submenu(void);
/***********************************************************************************/

void hmi_menu_init(void)
{
    hmi_menu_ctrl.submenu_state = SUBMENU_OFF;
}


/***********************************************************************************/
static void hmi_menu_show_draw_menu_cursor(void)
{
    cursor_retangle_t cursor_retangle;
    cursor_retangle = vector_cursor_retangle[hmi_menu_ctrl.item_index];
    ssd1306_InvertRectangle(cursor_retangle.x1,cursor_retangle.y1,cursor_retangle.x2,cursor_retangle.y2); 
}

/***********************************************************************************/

static void hmi_menu_show_draw_menu_itens(void)
{
    ssd1306_SetCursor(43, 2);
    ssd1306_WriteString("SETTINGS", Font_6x8, White) ;
    ssd1306_InvertRectangle(0,1,127,9); 
    ssd1306_Line(0,11,128,11,White);

    for(uint8_t index = 0; index < HMI_NUMBER_ID_OF_MENU_ITEM;  index++)
    {
        ssd1306_SetCursor(10, 14+(index*10));
        ssd1306_WriteString(hmi_menu_item_vector[index].string, Font_6x8, White) ;
    }

    hmi_menu_insert_data_submenu();
    
}

/***********************************************************************************/

void hmi_menu_show_screen(void)
{
    display_clear();
    hmi_menu_show_draw_menu_itens();
    hmi_menu_show_draw_menu_cursor();
    display_update();
}

/***********************************************************************************/

void hmi_menu_insert_data_submenu(void)
{
    hmi_submenu_data[1].tittle =  "VOLTAGE";
    hmi_submenu_data[1].string[0]= "Vin  Max";
    hmi_submenu_data[1].string[1]= "Vout Max";
    hmi_submenu_data[1].string[2]= "User    ";
    hmi_submenu_data[1].value[0] = 10;
    hmi_submenu_data[1].value[1] = 15;
    hmi_submenu_data[1].value[2] = 20;
    hmi_submenu_data[1].number_itens = 3;
}

/***********************************************************************************/


void hmi_menu_update_data(void)
{

}

/***********************************************************************************/

void hmi_menu_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    switch (button_id)
    {
    case BUTTON_LEFT_ID:
        
        break;
    case BUTTON_RIGHT_ID:
        hmi_menu_ctrl.item_index++;
        break;
    case BUTTON_SEL_CC_CV_ID:
        switch (button_press_type)
        {
        case BUTTON_SHORT_PRESS:
            break;
        case BUTTON_LONG_PRESS:
            break;
        default:
            break;
        }
        break;
    case BUTTON_ENC_ID:
        switch (button_press_type)
        {
        case BUTTON_SHORT_PRESS:
            hmi_submenu_show_items_screen(&hmi_submenu_data[1]);
            hmi_menu_ctrl.submenu_state = SUBMENU_ON;
            break;
        case BUTTON_LONG_PRESS:
            hmi_set_screen(HMI_ID_DASHBOARD);
            break;
        default:
            break;
        }

        break;
        break;
    default:
        break;
    }
    set_short_pulse_buzzer(BUZZER_SHORT_PULSE, BUZZER_AUTO_RESTART_OFF, BUZZER_PULSE_INIT, BUZZER_VOL_MEDIUM);
}

/***********************************************************************************/

void hmi_menu_update_encoder(enc_state_t enc_state)
{

    switch (enc_state)
    {
    case ENC_STATE_CCW:
        break;
    case ENC_STATE_CW:
        break;
    default:
        break;
    }

    if(hmi_menu_ctrl.item_index > (HMI_NUMBER_ID_OF_MENU_ITEM-1))
    {
        hmi_menu_ctrl.item_index = HMI_MENU_ID_ITEM_CONFIG_BUZZER;
    }

    if (hmi_menu_ctrl.submenu_state == SUBMENU_OFF)
    {
        switch (enc_state)
        {
        case ENC_STATE_CCW:
            hmi_menu_ctrl.item_index --;
            break;
        case ENC_STATE_CW:
            hmi_menu_ctrl.item_index ++;
            break;
        default:
            break;
        }
    
        set_short_pulse_buzzer(BUZZER_SHORT_PULSE, BUZZER_AUTO_RESTART_OFF, BUZZER_PULSE_INIT, BUZZER_VOL_MEDIUM);
        display_clear();
        hmi_menu_show_draw_menu_itens();
        hmi_menu_show_draw_menu_cursor();
        display_update();
    }
    else
    {
        hmi_sub_menu_update_data_encoder(&enc_state);
        hmi_submenu_show_items_screen(&hmi_submenu_data[1]);
    }
}


/***********************************************************************************/