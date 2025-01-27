#include "encoder.h"
#include "encoder_types.h"
#include "stdbool.h"


/***********************************************************************************/
 static enc_ctrl_t  enc_ctrl = {0};



void encoder_init(void)
{

    enc_ctrl.state = ENC_STATE_STOPED;
    enc_ctrl.event = EVENT_STOPED;
}


/***********************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == IT_ENC_CLK_Pin)
    {
        enc_ctrl.event = EVENT_RUN;
        if(HAL_GPIO_ReadPin(IT_ENC_DT_GPIO_Port, IT_ENC_DT_Pin) == GPIO_PIN_RESET)
        {
            enc_ctrl.state = ENC_STATE_CW;
        }
        else 
        {
            enc_ctrl.state = ENC_STATE_CCW;
        } 

    }
}

/***********************************************************************************/

void read_encoder_state(encoder_data_t *encoder_data)
{
    if(enc_ctrl.event == EVENT_RUN)
    {
        if(enc_ctrl.state == ENC_STATE_CW)
        {
            encoder_data->encoder_event(ENC_STATE_CW);
            enc_ctrl.event = EVENT_STOPED;
        }

        if(enc_ctrl.state == ENC_STATE_CCW)
        {
            encoder_data->encoder_event(ENC_STATE_CCW);
            enc_ctrl.event = EVENT_STOPED;
        }
    }
    else
    {
        enc_ctrl.event =  EVENT_STOPED;
        enc_ctrl.state =  ENC_STATE_STOPED;
    }
}

