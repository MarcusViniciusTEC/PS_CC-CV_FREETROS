#ifndef _LED_TYPES_H_
#define _LED_TYPES_H_

#include "led_cfg.h"


typedef enum 
{
    LED_AUTO_RELOAD_ON = 0,
    LED_AUTO_RELOAD_OFF
}led_auto_reload_type_t;

typedef enum
{
    LED_NAME_MCU_STATUS  = 0U,
    LED_NAME_UPDATE_DISPLAY, 
    LED_NAME_USER,
    LED_NAME_UART_TX,
    LED_NAME_UART_RX,
    LED_NUMBER_OF_NAMES
}led_names_t;

typedef enum
{
    LED_STATE_INIT = 0U,
    LED_STATE_IDLE,
    LED_STATE_TURN_ON,
    LED_STATE_WAIT_DELAY,
    LED_STATE_TURN_OFF,
    LED_NUMBER_OF_STATES
}led_state_t;

typedef enum
{
    LED_MODE_ON = 0U,
    LED_MODE_OFF,
    LED_MODE_SHORT_PULSE,
    LED_MODE_LONG_PULSE,
    LED_MODE_VERY_LONG_PULSE,
    LED_MODE_HEARTBEAT_PULSE,
    LED_MODE_NUMBER_OF_PULSES
}led_mode_pulse_t;

typedef struct 
{
    led_names_t name;
    GPIO_TypeDef* GPIO;
    uint16_t pin;
    led_state_t state;
    led_mode_pulse_t mode;
    uint32_t last_tick;
}led_data_t;

typedef struct 
{
    led_names_t name;
    led_mode_pulse_t mode;
    led_state_t state;
}queue_led_crtl_t;



#endif