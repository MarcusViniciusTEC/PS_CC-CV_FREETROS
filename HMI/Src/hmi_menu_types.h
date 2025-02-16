#ifndef _HMI_MENU_TYPES_H_
#define _HMI_MENU_TYPES_H_

#include "hmi_menu_cfg.h"

typedef enum
{
    HMI_MENU_ID_ITEM_VOLTAGE_MAX = 0U,
    HMI_MENU_ID_ITEM_CURRENT_MAX,
    HMI_MENU_ID_ITEM_CONTROL_MODE,
    HMI_MENU_ID_ITEM_CONFIG_FAN,
    HMI_MENU_ID_ITEM_CONFIG_BUZZER,
    HMI_NUMBER_ID_OF_MENU_ITEM
}menu_item_id_t;

typedef enum
{
    SUBMENU_ON = 0U,
    SUBMENU_OFF,
}hmi_menu_submenu_state_t;

typedef struct 
{
    menu_item_id_t id;
    char *string;
}hmi_menu_data_t;

typedef struct 
{
    hmi_menu_submenu_state_t submenu_state;
    uint8_t item_index;
}hmi_menu_ctrl_t;

typedef struct 
{

    menu_item_id_t id;
    char *tittle;
    char *string[5];
    uint8_t value[5];
    uint8_t number_itens;
}hmi_submenu_data_t;





#endif