#ifndef _LED_H_
#define _LED_H_

#include "led_types.h"

void led_init(void);
void led_set_pulse(led_names_t name, led_mode_pulse_t mode_pulse);

#endif