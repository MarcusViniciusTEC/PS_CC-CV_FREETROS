
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
    INDEX_FOURTH_DIGIT
}hmi_digit_types_t;

typedef enum
{
    HMI_CURSOR_EDIT_VOLTAGE = 0U,
    HMI_CURSOR_EDIT_CURRENT 
}hmi_cursor_edit_t;

typedef struct 
{
    uint8_t index_cursor;
    hmi_cursor_edit_t cursor_edit;

}hmi_dashboard_crtl_t;

typedef struct 
{
    uint16_t digit[4];
}hmi_edit_value_t;





#endif