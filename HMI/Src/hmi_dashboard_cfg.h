#ifndef __HMI_DASHBOARD_CFG_H__
#define __HMI_DASHBOARD_CFG_H__


#define VOLTAGE_NUMBER_OF_COORDINATE 4
#define CURRENT_NUMBER_OF_COORDINATE 3

#define NO_DIGIT 0


#define display_clear() ssd1306_Fill(Black)

#define display_update() ssd1306_UpdateScreen()  

#define MAX_DIGIT 9
#define MIN_DIGIT 0
#define TIME_SHOW_CURSOR 8000

#define DRAW_INVERT_RECTANGLE_STATUS_BAR        ssd1306_InvertRectangle(0,1,127,9)
#define DRAW_INVERT_RECTANGLE_MODE              ssd1306_InvertRectangle(104,37,124,46)
#define DRAW_INVERT_RECTANGLE_OUT_STATE         ssd1306_InvertRectangle(104,13,124,21)
#define DRAW_MAIN_RECTANGLE                     ssd1306_DrawRectangle(0, 11, 100, 63, White)
#define DRAW_INFO_RECTANGLE                     ssd1306_DrawRectangle(102, 11, 126, 63, White)
#define DRAW_LINE_BETWEEN_MAIN_RECTANGLE        ssd1306_Line(1,35,99,35, White)
#define DRAW_LINE_BETWEEN_INFO_RECTANGLE        ssd1306_Line(102,35,126,35, White)


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