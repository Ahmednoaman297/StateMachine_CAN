/*
 * TASKS.c
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#include "TASKS.h"


/**********************************Function Defintions********************************************/

uint8_t STATE =INIT_ZERO;
uint8_t LED = INIT_ZERO ;
uint8_t received_data[8];
uint8_t SEND_DATA=0;
uint8_t Queue[QUEUE_LEN] ;
uint8_t ClockwiseTask_SEMAPHORE = INIT_ZERO;
uint8_t CounterClockwiseTask_SEMAPHORE = INIT_ZERO;
uint8_t InitialTask_SEMAPHORE =INIT_ZERO;
uint32_t TASK_TimerIdleDelay=INIT_ZERO;

void TASK_INITS (void)
{
    GPIO_init(GPIO_PORTF_Index);
    CANInitialize(CAN0_Index);
}
void TASK_ReceiveCAN(void)
{
    static uint8_t Queue_Counter =INIT_ZERO;
    uint8_t ReceivedMSG_LEN =  CanReceiveMessage(CAN0_Index,DATARECEIVING_OBJECT,received_data);
    if (MSG_LENGTH == ReceivedMSG_LEN)
    {
        if (received_data[0] != HoldSTATE)
        {
            Queue[Queue_Counter] = received_data[0];
            if (Queue_Counter >= (uint8_t)29)
            {
                Queue_Counter = (uint8_t)INIT_ZERO;
            }
            else
            {
                Queue_Counter ++;
            }

        }
    }
    else
    {
        /* Error*/
    }
}

void TASK_RECEIVED_DATA_CHECK (void)
{
    static uint8_t READING_QUEUE_COUNTER =INIT_ZERO;
    if ((ClockwiseTask_SEMAPHORE == CONDITION_ZERO )&&( CounterClockwiseTask_SEMAPHORE == CONDITION_ZERO) &&( InitialTask_SEMAPHORE ==CONDITION_ZERO ))
    {
        switch(Queue[READING_QUEUE_COUNTER])
        {
        case CW:
        {

            ClockwiseTask_SEMAPHORE =SetSEAMPHORE;
            Queue[READING_QUEUE_COUNTER] = HoldSTATE;
            READING_QUEUE_COUNTER ++;
            break;
        }
        case CCW:
        {

            CounterClockwiseTask_SEMAPHORE =SetSEAMPHORE;
            Queue[READING_QUEUE_COUNTER] = HoldSTATE;
            READING_QUEUE_COUNTER ++;
            break;
        }
        case Initial:
        {

            InitialTask_SEMAPHORE = SetSEAMPHORE;
            Queue[READING_QUEUE_COUNTER] = HoldSTATE;
            READING_QUEUE_COUNTER ++;
            break;
        }
        case HoldSTATE:
        {

            READING_QUEUE_COUNTER ++;
            break;
        }
        default:
        {
            SEND_DATA = Unidentefied_state;
            Queue[READING_QUEUE_COUNTER] = HoldSTATE;
            READING_QUEUE_COUNTER ++;

            break;
        }
        }
        if (READING_QUEUE_COUNTER >= (uint8_t)29)
        {
            READING_QUEUE_COUNTER =INIT_ZERO;
        }
    }
}

void TASK_CLOCKWISE(void)
{
    static uint32_t TimeDelay_ClockWise =INIT_ZERO;
    if((ClockwiseTask_SEMAPHORE == ConditionSEAMPHORE) && (TimeDelay_ClockWise==CONDITION_ZERO))
    {
        TimeDelay_ClockWise = SYSTICK_Flag;
        TASK_TimerIdleDelay=SYSTICK_Flag;
        uint8_t LED_RED_STATUS = LED_read((uint8_t)REDLED, (uint32_t)GPIO_PORTF_BASE);
        uint8_t LED_BLUE_STATUS = LED_read((uint8_t)BLUELED, (uint32_t)GPIO_PORTF_BASE);
        uint8_t LED_GREEN_STATUS = LED_read((uint8_t)GREENLED, (uint32_t)GPIO_PORTF_BASE);
        /*If the white led*/
        if(   (LED_RED_STATUS ) && (LED_BLUE_STATUS )&& (LED_GREEN_STATUS))
        {
            LED_redLight();
        }
        /*if no led is on (when the connection is reconnected)*/
        else if((!LED_RED_STATUS)  && (!LED_BLUE_STATUS) && (!LED_GREEN_STATUS))
        {
            LED_redLight();
        }
        /*if the red is on*/
        else if( (LED_RED_STATUS)  && (!LED_BLUE_STATUS) && (!LED_GREEN_STATUS))
        {
            LED_greenLight();
        }
        /*if the Green is on*/
        else if( (!LED_RED_STATUS)  && (!LED_BLUE_STATUS) && (LED_GREEN_STATUS))
        {
            LED_blueLight();
        }
        /*if the Blue is on*/
        else if( (!LED_RED_STATUS)  && (LED_BLUE_STATUS) && (!LED_GREEN_STATUS))
        {
            LED_redLight();
        }
        else{}
    }
    else if ((SYSTICK_Flag - TimeDelay_ClockWise) >= (uint32_t)1000)
    {
        TimeDelay_ClockWise = INIT_ZERO;
        ClockwiseTask_SEMAPHORE = INIT_ZERO;
    }
    else{}

}

void TASK_COUNTERCLOCKWISE(void)
{
    /*entrance only once till another smphr*/
    static uint32_t TimeDelay_CounterClockWise =INIT_ZERO;
    if ((CounterClockwiseTask_SEMAPHORE == ConditionSEAMPHORE )&& (TimeDelay_CounterClockWise == CONDITION_ZERO))
    {
        TASK_TimerIdleDelay=SYSTICK_Flag;
        TimeDelay_CounterClockWise = SYSTICK_Flag;
        uint8_t LED_RED_STATUS = LED_read((uint8_t)REDLED, (uint32_t)GPIO_PORTF_BASE);
        uint8_t LED_BLUE_STATUS = LED_read((uint8_t)BLUELED, (uint32_t)GPIO_PORTF_BASE);
        uint8_t LED_GREEN_STATUS = LED_read((uint8_t)GREENLED, (uint32_t)GPIO_PORTF_BASE);


        /*If the white led*/
        if(   (LED_RED_STATUS)  && (LED_BLUE_STATUS) && (LED_GREEN_STATUS))
        {
            LED_blueLight();
        }
        /*if no led is on (when the connection is reconnected)*/
        else if((!LED_RED_STATUS)  && (!LED_BLUE_STATUS) && (!LED_GREEN_STATUS))
        {
            LED_blueLight();
        }
        /*if the red is on*/
        else if( (LED_RED_STATUS)  && (!LED_BLUE_STATUS) && (!LED_GREEN_STATUS))
        {
            LED_blueLight();
        }
        /*if the Green is on*/
        else if( (!LED_RED_STATUS)  && (!LED_BLUE_STATUS) && (LED_GREEN_STATUS))
        {
            LED_redLight();
        }
        /*if the Blue is on*/
        else if( (!LED_RED_STATUS)  && (LED_BLUE_STATUS) && (!LED_GREEN_STATUS))
        {
            LED_greenLight();
        }
        else{}
    }
    else if ((SYSTICK_Flag - TimeDelay_CounterClockWise) >= (uint32_t)1000)
    {
        TimeDelay_CounterClockWise =INIT_ZERO;
        CounterClockwiseTask_SEMAPHORE =INIT_ZERO;
    }
    else{}

}


void TASK_INITIAL(void)
{

    static uint32_t TimeDelay_INITIAL =INIT_ZERO;
    if((InitialTask_SEMAPHORE == ConditionSEAMPHORE) && (TimeDelay_INITIAL==CONDITION_ZERO))
    {
        TASK_TimerIdleDelay=SYSTICK_Flag;
        TimeDelay_INITIAL = SYSTICK_Flag;
        LED_redLight();
    }
    else if ((SYSTICK_Flag - TimeDelay_INITIAL) >= (uint32_t)1000)
    {
        TimeDelay_INITIAL = INIT_ZERO;
        InitialTask_SEMAPHORE = INIT_ZERO;
    }
    else{}
}
void TASK_Idle(void)
{
    if((SYSTICK_Flag-TASK_TimerIdleDelay)>=(uint32_t)10000)
    {
        LED_whiteLight();
        SEND_DATA = IDLE_STATE;
    }

}
void TASK_CanSend(void)
{
    if (SEND_DATA != CONDITION_ZERO)
    {
        CANTransmit(CAN0_Index, DataErrorSendingObject, &SEND_DATA, MSG_LENGTH);
        SEND_DATA =INIT_ZERO;
    }

}

void TASK_errorCheck (void)
{
    uint8_t received_data_error[8]= {INIT_ZERO} ;
    uint32_t ReceivedMSG_LEN =  CanReceiveMessage(CAN0_Index,ISConnectedReceivingObject,received_data_error);
    if (MSG_LENGTH == ReceivedMSG_LEN)
    {
        uint8_t  error_check_data = 0x07 ;
        CANTransmit(CAN0_Index, ISConnectedSendingObject, &error_check_data, MSG_LENGTH);
    }

}
