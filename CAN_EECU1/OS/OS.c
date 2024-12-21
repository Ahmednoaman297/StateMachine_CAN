/*

  ModuleName: OS
 Author: elder
 Purpose: Scheduling tasks

 */

/**************************************************************Includes*********************************************************************/
#include "OS.h"
#include "OS_CONFIG.h"



/*******************************************************global and static variables*********************************************************/
uint8_t g_OS_intTasksFlag = 1;



/*******************************************************Functions Definitions***************************************************************/

/*******************************************************************************************************************************************/
/*Function Name   : OS_Init                                                                                                                */
/*Inputs          : void                                                                                                                   */
/*Outputs         : void                                                                                                                   */
/*Reentrancy      : Non-Reentrant                                                                                                          */
/*Synchronous     : Synchronous                                                                                                            */
/*Description     : initialize the operating system's internal data structures and prepare the system for scheduling or managing tasks     */
/*******************************************************************************************************************************************/

void OS_Init(void)
{
    SYSTICK_Flag = ZERO;
    uint8_t i;
    for ( i = ZERO; i < NUMBER_OF_tasks; i++)
    {
        taskList[i].tickCount = ZERO;
    }
}

/*******************************************************************************************************************************************/
/*Function Name   : OS_Run                                                                                                                 */
/*Inputs          : void                                                                                                                   */
/*Outputs         : void                                                                                                                   */
/*Reentrancy      : Non-Reentrant                                                                                                          */
/*Synchronous     : Synchronous                                                                                                            */
/*Description     : handles task scheduling and timing                                                                                     */
/*******************************************************************************************************************************************/
void OS_Run(void)
{

    static volatile uint32_t LAST_SYSTICK_VALUE = 0;

    uint32_t NUMBER_OF_TICK_PASSED = SYSTICK_Flag - LAST_SYSTICK_VALUE;
    LAST_SYSTICK_VALUE = SYSTICK_Flag;
    uint8_t k;
    for ( k = ZERO; k < NUMBER_OF_tasks; k++)
    {
        if ((taskList[k].tickCount > ZERO) && (taskList[k].isHighPriority ==ZERO)) {
            taskList[k].tickCount-=NUMBER_OF_TICK_PASSED;
        }
        if((taskList[k].tickCount > taskList[k].priodicity )&& (taskList[k].isHighPriority ==ZERO ) )
        {
            taskList[k].tickCount = (uint32_t)0;
        }
    }

    if (g_OS_intTasksFlag == (uint8_t)1)
    {
        uint8_t i;
        for ( i = ZERO; i < NUMBER_OF_tasks; i++)
        {
            if ((taskList[i].isHighPriority) && (taskList[i].tickCount == ZERO))
            {
                taskList[i].task();
                taskList[i].tickCount = (uint32_t)123;
            }
        }
        g_OS_intTasksFlag =ZERO;
    }

    uint8_t l;
        for ( l = ZERO; l < (uint8_t)NUMBER_OF_tasks; l++)
        {
            if (taskList[l].tickCount == ZERO)
            {
                taskList[l].task();
                if (taskList[l].isPreiodic)
                {
                    taskList[l].tickCount = taskList[l].priodicity;
                }
            }
        }

}




