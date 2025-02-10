
#ifndef _HMI_DASHBOARD_TYPES_H_
#define _HMI_DASHBOARD_TYPES_H_

#include "hmi_dashboard_cfg.h"

typedef struct 
{
    uint8_t x1;
    uint8_t y1;
    uint8_t x2;
    uint8_t y2;
}cursor_retangle_t;

typedef enum
{
    INDEX_FIRST_DIGIT = 0U,
    INDEX_SECOND_DIGIT,
    INDEX_THIRD_DIGIT,
    INDEX_FOURTH_DIGIT,
    NUMBER_OF_INDEX_DIGITS
}hmi_digit_types_t;

typedef enum
{
    HMI_CURSOR_EDIT_FIELD_VOLTAGE = 0U,
    HMI_CURSOR_EDIT_FIELD_CURRENT,
    HMI_NUMBER_OF_FIELDS_EDITS,
}hmi_cursor_edit_t;

typedef enum
{
    HMI_FIELD_VOLTAGE = 0U,
    HMI_FIELD_CURRENT,
    HMI_NUMBER_OF_FIELDS
}hmi_cursor_field_types_t;


typedef enum
{
    CURSOR_STATE_ON = 0U,
    CURSOR_STATE_OFF,
    CURSOR_STATE_WAIT_EVENT

}hmi_cursor_state_t;

typedef struct 
{
    hmi_digit_types_t index_digit;
    hmi_digit_types_t last_index_digit;
    hmi_cursor_edit_t cursor_edit;
    hmi_cursor_state_t cursor_state;
    uint32_t last_time_cursor;
}hmi_dashboard_crtl_t;

typedef struct 
{
    uint8_t digit[NUMBER_OF_INDEX_DIGITS];
}hmi_edit_value_t;

#endif