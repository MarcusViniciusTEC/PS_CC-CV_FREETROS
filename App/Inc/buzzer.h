#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "buzzer_types.h"


void buzzer_init(void);
void set_short_pulse_buzzer(buzzer_pulse_types_t buzzer_pulse_types, buzzer_auto_restart_state_t buzzer_auto_restart_state, buzzer_state_t buzzer_state, buzzer_vol_t buzzer_vol);

#endif

