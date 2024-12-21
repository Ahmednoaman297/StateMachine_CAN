/*
 * TASKS.h
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#ifndef APP_TASKS_TASKS_H_
#define APP_TASKS_TASKS_H_

#include <stdint.h>
#include <stdbool.h>

#include "../../HAL/LED/LED.h"
#include "../../HAL/BTN/BTN.h"
#include "../../MCAL/CAN/CAN.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../OS/OS.h"




#define INIT_ZERO               0u
#define CONDITION_ZERO          0u

#define SetSEAMPHORE            1u
#define ConditionSEAMPHORE      1u

#define CAN0_Index                      0u
#define MSG_LENGTH                      1u
#define DataErrorSendingObject          1u
#define ISConnectedSendingObject        4u
#define ISConnectedReceivingObject      3u
#define DATARECEIVING_OBJECT            2u
#define QUEUE_LEN                       30

#define PRESSED                 0u
#define NOTPRESSED              1u
#define FIRST_SWITCH          GPIO_PIN_0      /* Indicates the first button which sends the first state*/
#define SECOND_SWITCH         GPIO_PIN_4

#define REDLED               GPIO_PIN_1
#define BLUELED              GPIO_PIN_2
#define GREENLED             GPIO_PIN_3
#define GPIO_PORTF_Index        0u


#define Blue                    3u
#define White                   0u
#define Green                   1u
#define Red                     2u


#define CW                      1u
#define CCW                     2u
#define Initial                 3u
#define HoldSTATE               4u
#define Unidentefied_state      9u
#define IDLE_STATE              6u



void TASK_INITS (void);
void TASK_ReceiveCAN(void);
void TASK_RECEIVED_DATA_CHECK (void);
void TASK_CLOCKWISE(void);
void TASK_COUNTERCLOCKWISE(void);
void TASK_COUNTERCLOCKWISE(void);
void TASK_INITIAL(void);
void TASK_Idle(void);
void TASK_CanSend(void);
void TASK_errorCheck(void);




#endif /* APP_TASKS_TASKS_H_ */
