#ifndef __HMI_TYPES_H__
#define __HMI_TYPES_H__


#include "hmi_cfg.h"
#include "buttons_types.h"

typedef enum
{
    HMI_ID_DASHBOARD = 0U,
    HMI_ID_MENU,
    HMI_NUMBERS_OF_ID
}hmi_screens_id_t;

typedef struct 
{
    hmi_screens_id_t screen_id;
    void(*init)(void);
    void(*show_screen)(void);
    void(*show_data)(void);
    void(*update_data)(button_id_t button_id, button_press_type_t button_press_type);
}hmi_screen_info_t;

typedef enum
{
    HMI_SHOWING_SCREEN = 0U,
    HMI_SHOWING_DATA,
    HMI_SHOWING_UPDATE_DATA
}hmi_screens_update_state_t;


typedef struct 
{
    hmi_screens_id_t id;
    hmi_screens_update_state_t state;
    
}hmi_ctrl_t;



#endif