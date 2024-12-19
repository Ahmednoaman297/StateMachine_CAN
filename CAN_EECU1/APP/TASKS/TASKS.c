/*
 * TASKS.c
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#include "TASKS.h"

uint8_t STATE =INIT_ZERO;
uint8_t LED =INIT_ZERO;
uint8_t UART_FLAG_SEND=INIT_ZERO;
uint8_t TASK_TimerIdleDelay=INIT_ZERO;
uint8_t Receive_state=INIT_ZERO;
uint8_t received_data[8];

void TASK_INITS (void)
{
    static  uint8_t CanIndex_Array=INIT_ZERO;
    static uint8_t GpioIndex_array=INIT_ZERO;
    UART_FLAG_SEND= GPIO_init(GpioIndex_array);
    UART_FLAG_SEND=configure_all_uarts();
    UART_FLAG_SEND= CANInitialize(CanIndex_Array);
}




void TASK_BTN_READ(void)
{
    static uint8_t TASKBTN_Flag =INIT_ZERO;
    static uint32_t TimeDelay_BTN =INIT_ZERO;
    uint8_t switch1 = BTN_read((uint8_t)FIRST_SWITCH,(uint32_t) GPIO_PORTF_BASE);
    uint8_t switch2 = BTN_read((uint8_t)SECOND_SWITCH, (uint32_t)GPIO_PORTF_BASE);

    if ((switch1 == PRESSED) || (switch2 == PRESSED))
    {
        if ((TASKBTN_Flag == CONDITION_ZERO) && (TimeDelay_BTN == CONDITION_ZERO))
        {

            TimeDelay_BTN = SYSTICK_Flag ;
            TASKBTN_Flag =SetFlag;
        }
        else if (((SYSTICK_Flag - TimeDelay_BTN)>= (uint32_t)150) && (TASKBTN_Flag ==ConditionFlag ))
        {
            switch1 = BTN_read((uint8_t)FIRST_SWITCH, (uint32_t)GPIO_PORTF_BASE);
            switch2 = BTN_read((uint8_t)SECOND_SWITCH, (uint32_t)GPIO_PORTF_BASE);
            TASKBTN_Flag =INIT_ZERO;
            TimeDelay_BTN=INIT_ZERO;
            if ((switch1 == PRESSED) && (switch2 == PRESSED))
            {
                STATE = Initial;
                UART_FLAG_SEND=Initial;
            }
            else if ((switch1 == PRESSED) && (switch2 == NOTPRESSED))
            {
                STATE = CW;
                UART_FLAG_SEND=CW;

            }
            else if ((switch1 == NOTPRESSED) && (switch2 == PRESSED))
            {
                STATE = CCW;
                UART_FLAG_SEND=CCW;
            }else{}

        }else{}
    }
    else
    {
        TimeDelay_BTN=INIT_ZERO;
        TASKBTN_Flag =INIT_ZERO;
        STATE = HoldSTATE;
    }
}

void TASK_UARTSEND (void)
{
    static uint8_t UartIndex_Array=0;

    switch (UART_FLAG_SEND)
    {
    case NO_DATATOSEND:
        {

        break;
        }
    case CW:
    {
        UART_sendString("Machine State is ClockWise\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case CCW:
    {
        UART_sendString("Machine State is Counter ClockWise\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case Initial:
    {
        UART_sendString("Machine State is Initial\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case Connection_lost:
    {
        UART_sendString("ECU2: Connection lost\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case IDLE_STATE:
    {
        UART_sendString("ECU2: Idle state\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }

    case Unidentefied_state:
        UART_sendString("ECU2: Error unidentified state received\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case GPIO_ERROR:
        UART_sendString("ECU2: Error IN GPIO\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case CAN_ERROR_CAN_Module:
        UART_sendString("ECU2: Error IN CAN MODULE\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case UART_ERROR_INVALID_MODULE:
        UART_sendString("ECU2: Error IN UART MODULE\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    default:
        UART_sendString("ECU2: Error unidentified state received\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
}



void TASK_SendCAN (void)
{

    static uint8_t data = INIT_ZERO;


    data= STATE;
    CANTransmit(CAN0_Index, DataSendingObject, &data, MSG_LENGTH);
    STATE = HoldSTATE;

}
void TASK_ReceiveCAN (void)
{
    uint32_t flag =INIT_ZERO;



    flag =CanReceiveMessage(CAN0_Index, DATAERRORRECEIVING_OBJECT, received_data);
    if (flag == MSG_LENGTH )
    {
        UART_FLAG_SEND = received_data[0];
    }

}

void TASK_errorCheck (void)
{
    static uint8_t ErrorCheck_flag =INIT_ZERO;
    static uint32_t ErrorCheck_timedelay =INIT_ZERO;

    uint32_t flag;
    uint8_t received_data_error[8]={INIT_ZERO};

    if (ErrorCheck_flag ==INIT_ZERO)
    {
        ErrorCheck_flag=SetFlag;
        uint8_t  error_check_data =SENDERRORCHECK ;
        CANTransmit(CAN0_Index, ISConnectedSendingObject, &error_check_data, MSG_LENGTH);
        ErrorCheck_timedelay =SYSTICK_Flag;
    }
    else
    {
        flag = CanReceiveMessage(CAN0_Index, ISConnectedReceivingObject, received_data_error);
        if (((SYSTICK_Flag - ErrorCheck_timedelay) <= (uint32_t)1000 )|| (flag==MSG_LENGTH ))
        {

            if (flag!=(uint32_t)CONDITION_ZERO)
            {
                ErrorCheck_timedelay = SYSTICK_Flag;
                if (received_data_error[0] == SENDERRORCHECK)
                {
                    ErrorCheck_flag =INIT_ZERO;
                    LEDS_off();
                }
                else
                {
                    ErrorCheck_flag =INIT_ZERO;
                    UART_FLAG_SEND = Connection_lost;
                }
            }
            else
            {

            }
        }
        else
        {
            ErrorCheck_flag =INIT_ZERO;
            UART_FLAG_SEND = Connection_lost;
        }
    }


}

void TASK_blinkRedLED (void)
{
    static uint32_t BlinkRed_timeDelay = INIT_ZERO;
    static uint8_t BlinkRed_Flag = INIT_ZERO;
    if(UART_FLAG_SEND == Connection_lost)
    {
        uint8_t condition1 = (BlinkRed_Flag == CONDITION_ZERO);
        uint8_t condition3 = (BlinkRed_Flag != CONDITION_ZERO);
        uint8_t condition2 = ((SYSTICK_Flag - BlinkRed_timeDelay) >= (uint32_t)1000);
        if (condition1 && condition2  )
        {
            BlinkRed_Flag = SetFlag;
            BlinkRed_timeDelay = SYSTICK_Flag;
            LED_redLight();
        }
        else if (condition3 && condition2 )
        {
            BlinkRed_Flag = INIT_ZERO;
            BlinkRed_timeDelay = SYSTICK_Flag;
            LEDS_off();
        }
        else{

        }
    }
    else{

    }


}
