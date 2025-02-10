
/***********************************************************************************/

#ifndef __HMI_DASHBOARD_H__
#define __HMI_DASHBOARD_H__

/***********************************************************************************/

#include "buttons_types.h"
#include "encoder_types.h"

/***********************************************************************************/

void hmi_dashboard_init(void);
void hmi_dashboard_show_screen(void);
void hmi_dashboard_update_data(void);
void hmi_dashboard_update_button(button_id_t button_id, button_press_type_t button_press_type);
void hmi_dashboard_update_encoder(enc_state_t enc_state);

/***********************************************************************************/

void hmi_dashboard_draw_voltage_output(void);
void hmi_dashboard_draw_current(void);
void hmi_dashboard_increment_index_field(void);
void hmi_dashboard_decrement_index_field(void);
void hmi_dashboard_decrement_digit(void);
void hmi_dashboard_increment_digit(void);
void hmi_dashboard_update_state_cursor(void);
void hmi_dashboard_update_cursor(void);
void hmi_dashboard_cursor_update_status(void);
void hmi_dashboard_set_limits(void);
void hmi_dashboard_correction_cursor_field_current(void);
void hmi_dashboard_cursor_edit_toggle(void);
void hmi_dashboard_draw_out_state(void);
void hmi_dashboard_draw_mode_control(void);
void hmi_dashboard_target_voltage(void);
void hmi_dashboard_target_current(void);

/***********************************************************************************/

#endif