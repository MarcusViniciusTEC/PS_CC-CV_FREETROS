#ifndef __HMI_DASHBOARD_CFG_H__
#define __HMI_DASHBOARD_CFG_H__


#define VOLTAGE_NUMBER_OF_COORDINATE 4
#define CURRENT_NUMBER_OF_COORDINATE 3

#define NO_DIGIT 0

#define vector_hmi_coordinate_voltage_default   \
{                                               \
    { 2,12,16,34},                              \
    {18,12,32,34},                              \
    {50,12,64,34},                              \
    {66,12,80,34}                               \
}                                               


#define vector_hmi_coordinate_current_default   \
{                                               \
    {17,37,31,59},                              \
    {49,37,63,59},                              \
    {65,37,79,59}                               \
}         


#endif