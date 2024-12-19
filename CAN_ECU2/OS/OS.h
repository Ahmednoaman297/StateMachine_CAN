/*
 * OS.h
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */

#ifndef OS_OS_H_
#define OS_OS_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>
#include "../MCAL/SYSTICK/SYSTICK.h"


/********************************************type declarations*********************************/
typedef struct {
    void (*task)(void);         /* Function pointer to task execution*/
    uint32_t priodicity;        /* Task interval in ticks*/
    uint32_t tickCount;         /* Count of ticks since last execution*/
    bool isPreiodic;            /* True if the task is recurring*/
    bool isHighPriority;        /* True if the task has high priority (e.g., initialization)*/
} TaskDescriptor;

/********************************************functions prototypes*********************************/
void OS_Init(void);
void OS_Run(void);




#endif /* OS_OS_H_ */
