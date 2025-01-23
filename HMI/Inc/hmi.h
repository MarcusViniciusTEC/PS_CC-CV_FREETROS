#ifndef __HMI_H__
#define __HMI_H__

#include "buttons_types.h"

void hmi_init(void);
void hmi_showing_update_data(button_id_t button_id, button_press_type_t button_press_type);

#endif