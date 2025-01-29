
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
    HMI_CURSOR_EDIT_CURRENT = 0U,
    HMI_CURSOR_EDIT_VOLTAGE
}hmi_dashboard_cursor_edit_t;


typedef struct 
{
    uint8_t index_cursor;
    hmi_dashboard_cursor_edit_t cursor_edit;

}hmi_dashboard_crtl_t;




#endif