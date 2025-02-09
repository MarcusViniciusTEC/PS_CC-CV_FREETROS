
#ifndef _HMI_TARGET_H_
#define _HMI_TARGET_H_


#include "buttons_types.h"
#include "encoder_types.h"

void hmi_target_init(void);
void hmi_target_show_screen(void);
void hmi_target_update_data(void);
void hmi_target_update_button(button_id_t button_id, button_press_type_t button_press_type);
void hmi_target_update_encoder(enc_state_t enc_state);

#endif