#ifndef _BUZZER_TYPES_H_
#define _BUZZER_TYPES_H_

#include "buzzer_cfg.h"

typedef enum
{
    BUZZER_PULSE_INIT = 0U,
    BUZZER_PULSE_START,
    BUZZER_PULSE_TURN_ON,
    BUZZER_PULSE_WAIT_TIME,
    BUZZER_PULSE_TURN_OFF
}buzzer_state_t;

typedef enum
{
    BUZZER_SHORT_PULSE = 75,
    BUZZER_MEDIUM_PULSE = 150,
    BUZZER_LONG_PULSE = 230,
}buzzer_pulse_types_t;


typedef enum
{
    BUZZER_MUTE             = 0,
    BUZZER_VOL_LOW          = 50,
    BUZZER_VOL_MEDIUM       = 100,
    BUZZER_VOL_HIGH         = 300,
    BUZZER_VOL_VERY_HIGH    = 800,
}buzzer_vol_t;

typedef enum
{
    BUZZER_AUTO_RESTART_ON = 0U,
    BUZZER_AUTO_RESTART_OFF
}buzzer_auto_restart_state_t;

typedef struct 
{
    uint32_t last_time;
    buzzer_vol_t volume;
    buzzer_state_t buzzer_state;
    buzzer_pulse_types_t buzzer_pulse_type;
    buzzer_auto_restart_state_t buzzer_auto_restart_state;
}queue_buzzer_crtl_t;


#endif
