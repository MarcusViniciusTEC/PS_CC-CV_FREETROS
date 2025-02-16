#ifndef _HMI_MENU_CFG_H_
#define _HMI_MENU_CFG_H_


#endif

#define HMI_MENU_NUMBER_OF_ITEMS 5

#define vector_hmi_coordinate_retangle_menu_default     \
{                                                       \
    {0,13,127,21},                                      \
    {0,23,127,31},                                      \
    {0,33,127,41},                                      \
    {0,43,127,51},                                      \
    {0,53,127,61}                                       \
}                                       


#define hmi_menu_vector_item_default            \
{                                               \
    {                                           \
        .id = HMI_MENU_ID_ITEM_VOLTAGE_MAX,     \
        .string = "1.VOLTAGE "                  \
    }                                           \
    ,                                           \
    {                                           \
        .id = HMI_MENU_ID_ITEM_CURRENT_MAX,     \
        .string ="2.CURRENT "                   \
    }                                           \
    ,                                           \
    {                                           \
        .id = HMI_MENU_ID_ITEM_CONTROL_MODE,    \
        .string ="3.MODE CONTROL"               \
    }                                           \
    ,                                           \
    {                                           \
        .id = HMI_MENU_ID_ITEM_CONFIG_FAN,      \
        .string ="4.FAN"                        \
    }                                           \
    ,                                           \
    {                                           \
        .id = HMI_MENU_ID_ITEM_CONFIG_BUZZER,   \
        .string = "5.BUZZER"                    \
    }                                           \
}