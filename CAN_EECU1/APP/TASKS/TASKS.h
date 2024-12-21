/*
 * TASKS.h
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#ifndef APP_TASKS_TASKS_H_
#define APP_TASKS_TASKS_H_
/*************************************************************Includes**************************************************************/
#include "../../OS/OS.h"
#include <stdint.h>
#include <stdbool.h>
#include "../../HAL/LED/LED.h"
#include "../../HAL/BTN/BTN.h"
#include "../../MCAL/CAN/CAN.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../MCAL/UARTs/UARTS.h"
/********************************************Definitions and Macros*********************************/
#define INIT_ZERO               0u
#define CONDITION_ZERO          0u

#define SetFlag                 1u
#define ConditionFlag           1u

#define PRESSED                 0u
#define NOTPRESSED              1u
#define FIRST_SWITCH          GPIO_PIN_0      /* Indicates the first button which sends the first state*/
#define SECOND_SWITCH         GPIO_PIN_4

#define CW                      1u
#define CCW                     2u
#define Initial                 3u
#define Unidentefied_state      9u
#define Connection_lost         8u
#define IDLE_STATE              6u
#define HoldSTATE               4u
#define NO_DATATOSEND           0u
#define SENDERRORCHECK          7u

#define CAN0_Index                          0u
#define MSG_LENGTH                          1u
#define DataSendingObject                   1u
#define ISConnectedSendingObject            4u
#define ISConnectedReceivingObject          3u
#define DATAERRORRECEIVING_OBJECT           2u

#define White                   0u
#define Green                   1u
#define Red                     2u
#define Blue                    3u

/**********************************Function Defintions********************************************/

void TASK_INITS (void);
void TASK_BTN_READ(void);
void TASK_LEDGREEN(void);
void TASK_LEDRED(void);
void TASK_LEDWHITE(void);
void TASK_LEDBLUE(void);
void TASK_CLOCKWISE(void);
void TASK_COUNTERCLOCKWISE(void);
void TASK_UARTSEND (void);
void TASK_SendCAN (void);
void TASK_ReceiveCAN (void);
void TASK_errorCheck (void);
void TASK_blinkRedLED (void);
/*******************************************************Shared Global Variable(extern)**********************************************************/
extern uint8_t STATE;
extern uint8_t LED ;


#endif /* APP_TASKS_TASKS_H_ */
