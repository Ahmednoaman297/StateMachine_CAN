/*
 * OS_CONFIG.c
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */



/* TaskConfiguration.c*/
#include "OS_CONFIG.h"



TaskDescriptor taskList[MAX_TASKS] =
{
 {&TASK_INITS,
  .priodicity = (uint32_t)0,
  .tickCount = ZERO,
  .isPreiodic = false,
  .isHighPriority = true},     /* Initialization task*/



  {&TASK_ReceiveCAN,
   .priodicity = (uint32_t)10,
   .tickCount = ZERO,
   .isPreiodic = true,
   .isHighPriority = false},

   {&TASK_RECEIVED_DATA_CHECK,
    .priodicity = (uint32_t)1,
    .tickCount = ZERO,
    .isPreiodic = true,
    .isHighPriority = false},


    {&TASK_CLOCKWISE,
     .priodicity = (uint32_t)1,
     .tickCount = ZERO,
     .isPreiodic = true,
     .isHighPriority = false},

     {&TASK_COUNTERCLOCKWISE,
      .priodicity = (uint32_t)1,
      .tickCount = ZERO,
      .isPreiodic = true,
      .isHighPriority = false},

      {&TASK_INITIAL,
       .priodicity = (uint32_t)1,
       .tickCount = ZERO,
       .isPreiodic = true,
       .isHighPriority = false},

       {&TASK_Idle,
        .priodicity = (uint32_t)1,
        .tickCount = ZERO,
        .isPreiodic = true,
        .isHighPriority = false},

        {&TASK_CanSend,
         .priodicity = (uint32_t)1,
         .tickCount = ZERO,
         .isPreiodic = true,
         .isHighPriority = false},

         {&TASK_errorCheck,
          .priodicity = (uint32_t)100,
          .tickCount = ZERO,
          .isPreiodic = true,
          .isHighPriority = false}
};

const uint8_t NUMBER_OF_tasks = MAX_TASKS;

