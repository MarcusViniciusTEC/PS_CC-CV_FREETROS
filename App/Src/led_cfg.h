#ifndef _LED_CFG_H_
#define _LED_CFG_H_

#include "main.h"


#define TIME_SHORT_PULSE 100
#define TIME_LONG_PULSE 400
#define TIME_VERY_LONG_PULSE 800

#define vector_led_board_defaut                 \
{                                               \
    {   .name = LED_NAME_MCU_STATUS,            \
        .GPIO = LED_MCU_STATUS_GPIO_Port,       \
        .pin  = LED_MCU_STATUS_Pin,             \
        .state = LED_STATE_INIT,                \
        .mode = LED_MODE_OFF,                   \
        .last_tick = 0U                         \
    }                                           \
    ,                                           \
    {   .name = LED_NAME_UPDATE_DISPLAY,        \
        .GPIO = LED_MCU_STATUS_1_GPIO_Port,     \
        .pin  = LED_MCU_STATUS_1_Pin,           \
        .state = LED_STATE_INIT,                \
        .mode = LED_MODE_OFF,                   \
        .last_tick = 0U                         \
    }                                           \
    ,                                           \
    {   .name = LED_NAME_USER,                  \
        .GPIO = MCU_STATUS_LED_GPIO_Port,       \
        .pin  = MCU_STATUS_LED_Pin,             \
        .state = LED_STATE_INIT,                \
        .mode = LED_MODE_OFF,                   \
        .last_tick = 0U                         \
    }                                           \
}                                           


#endif