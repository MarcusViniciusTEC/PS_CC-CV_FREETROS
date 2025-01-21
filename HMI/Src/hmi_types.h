#ifndef __HMI_TYPES_H__
#define __HMI_TYPES_H__


#include "hmi_cfg.h"


typedef struct 
{
    void(*init)(void);
    void(*show_screen)(void);
    void(*show_data)(void);
    void(*update_data)(void);
}hmi_screen_info_t;


#endif