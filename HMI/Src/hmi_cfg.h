
#ifndef _HMI_CFG_H_
#define _HMI_CFG_H_


#include "hmi_dashboard.h"


#define HMI_NUMBER_OF_SCREENS 1

#define vector_hmi_screens_default      \
{                                       \
    {                                   \
        hmi_id_dashboard,               \
        hmi_dashboard_init,             \
        hmi_dashboard_show_screen,      \
        hmi_dashboard_show_data,        \
        hmi_dashboard_update_screen     \
    }                                   \
}
#endif