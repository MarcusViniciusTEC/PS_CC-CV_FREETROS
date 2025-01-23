
#ifndef _HMI_CFG_H_
#define _HMI_CFG_H_

/*******************************************************************************/

#include "hmi_dashboard.h"
#include "buttons_types.h"
#include "hmi.h"


/*******************************************************************************/

#define HMI_NUMBER_OF_SCREENS 1

/*******************************************************************************/

#define vector_hmi_screens_default      \
{                                       \
    {                                   \
        HMI_ID_DASHBOARD,               \
        hmi_dashboard_init,             \
        hmi_dashboard_show_screen,      \
        hmi_dashboard_show_data,        \
        hmi_dashboard_update_screen     \
    }                                   \
}

/*******************************************************************************/

#define vector_buttons_data_default                     \
{                                                       \
    {                                                   \
        {BT_OUT_STATE_GPIO_Port, BT_OUT_STATE_Pin},     \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_OUT_STATE_ID,                            \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {BT_SEL_CC_CV_GPIO_Port, BT_SEL_CC_CV_Pin},     \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_SEL_CC_CV_ID,                            \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {BT_LEFT_GPIO_Port, BT_LEFT_Pin},               \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_LEFT_ID,                                 \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {BT_RIGHT_GPIO_Port, BT_RIGHT_Pin},             \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_RIGHT_ID,                                \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {ENC_BT_GPIO_Port, ENC_BT_Pin},                 \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_ENC_ID,                                  \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
}

/*******************************************************************************/

#endif

/*******************************************************************************/