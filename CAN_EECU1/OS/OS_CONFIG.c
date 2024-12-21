/*
 * OS_CONFIG.c
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */



/********************************************Includes*********************************/
#include "OS_CONFIG.h"


/********************************************global and static variables*********************************/

TaskDescriptor taskList[MAX_TASKS] =
{
 {&TASK_INITS,
  .priodicity = 0,
  .tickCount = 0,
  .isPreiodic = false,
  .isHighPriority = true},     /* Initialization task*/

  {&TASK_BTN_READ,
   .priodicity = 1,
   .tickCount = 0,
   .isPreiodic = true,
   .isHighPriority = false}, /* Periodic task with 1000 ticks interval*/

   {&TASK_ReceiveCAN,
    .priodicity = 10,
    .tickCount = 0,
    .isPreiodic = true,
    .isHighPriority = false},

    {&TASK_UARTSEND,
     .priodicity = 100,
     .tickCount = 0,
     .isPreiodic = true,
     .isHighPriority = false}, /* Periodic task with 1000 ticks interval*/

     {&TASK_SendCAN,
      .priodicity = 50,
      .tickCount = 0,
      .isPreiodic = true,
      .isHighPriority = false}, /* Periodic task with 1000 ticks interval*/

      {&TASK_errorCheck ,
       .priodicity = 100,
       .tickCount = 0,
       .isPreiodic = true,
       .isHighPriority = false},

       {&TASK_blinkRedLED,
        .priodicity = (uint32_t)1,
        .tickCount = ZERO,
        .isPreiodic = true,
        .isHighPriority = false} /* Periodic task with 1000 ticks interval*/


};

const uint8_t NUMBER_OF_tasks = MAX_TASKS;
