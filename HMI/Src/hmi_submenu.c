
/***********************************************************************************/

#include "hmi_submenu.h"
#include "hmi_submenu_types.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
#include "hmi_dashboard_types.h"


/***********************************************************************************/

static hmi_submenu_crtl_t hmi_submenu_crtl = {0};

uint8_t item_index = 0;
/***********************************************************************************/

void hmi_submenu_set_screen(menu_item_id_t sub_id) ;
static const cursor_retangle_t vector_cursor_retangle[HMI_MENU_NUMBER_OF_ITEMS] = vector_hmi_coordinate_retangle_menu_default;
void hmi_sub_menu_update_data_button(button_id_t *button_id, button_press_type_t *button_press_type, hmi_submenu_data_t *hmi_submenu_data_t);
void hmi_sub_menu_update_data_encoder(enc_state_t *enc_state);
void hmi_submenu_show_items_screen(hmi_submenu_data_t *hmi_submenu_data) ;



/***********************************************************************************/

static void hmi_submenu_show_draw_cursor(void)
{
    cursor_retangle_t cursor_retangle;
    cursor_retangle = vector_cursor_retangle[item_index];
    ssd1306_InvertRectangle(cursor_retangle.x1,cursor_retangle.y1,cursor_retangle.x2,cursor_retangle.y2); 
}

/***********************************************************************************/

void hmi_submenu_set_screen(menu_item_id_t sub_id)
{
    hmi_submenu_crtl.id = sub_id;
}

/***********************************************************************************/

void hmi_submenu_show_items_screen(hmi_submenu_data_t *hmi_submenu_data) 
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(43, 2);
    ssd1306_WriteString(hmi_submenu_data->tittle, Font_6x8, White) ;
    ssd1306_InvertRectangle(0,1,127,9); 
    ssd1306_Line(0,11,128,11,White);
    char sz_string[20] = {0};

    for (uint8_t index = 0; index <= hmi_submenu_data->number_itens; index++)
    {
        //ssd1306_SetCursor(10, 14+(index*10));
       // ssd1306_WriteString(hmi_submenu_data->string[index], Font_6x8, White) ;

        snprintf(sz_string, sizeof(sz_string), "%s = %u", hmi_submenu_data->string[index], hmi_submenu_data->value[index]);
        ssd1306_SetCursor(5, 14+(index*10));
        ssd1306_WriteString(sz_string, Font_6x8, White) ;
    }
    
    
    hmi_submenu_show_draw_cursor();
    ssd1306_UpdateScreen();
}

/***********************************************************************************/

void hmi_sub_menu_update_data_buuton(button_id_t *button_id, button_press_type_t *button_press_type, hmi_submenu_data_t *hmi_submenu_data_t)
{

}

/***********************************************************************************/

void hmi_sub_menu_update_data_encoder(enc_state_t *enc_state)
{
    switch (*enc_state)
    {
    case ENC_STATE_CCW:
        item_index --;
        break;
    case ENC_STATE_CW:
        item_index ++;
        break;
    default:
        break;
    }

}

/***********************************************************************************/