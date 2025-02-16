
#ifndef _HMI_SUBMENU_H_
#define _HMI_SUBMENU_H_

#include "buttons_types.h"
#include "hmi_menu_types.h"
#include "encoder_types.h"

void hmi_sub_menu_update_data_button(button_id_t *button_id, button_press_type_t *button_press_type, hmi_submenu_data_t *hmi_submenu_data_t);
void hmi_sub_menu_update_data_encoder(enc_state_t *enc_state);
void hmi_submenu_show_items_screen(hmi_submenu_data_t *hmi_submenu_data) ;




#endif
