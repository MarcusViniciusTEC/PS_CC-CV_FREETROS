#ifndef __HMI_INTRO_H__
#define __HMI_INTRO_H__


#include "buttons_types.h"
#include "encoder_types.h"

void hmi_intro_init(void);
void hmi_intro_show_screen(void);
void hmi_intro_show_data(void);
void hmi_intro_update_screen(button_id_t button_id, button_press_type_t button_press_type);
void hmi_intro_update_encoder(enc_state_t enc_state);



#define TIME_EXECUTIN_INTRO 4000


#endif