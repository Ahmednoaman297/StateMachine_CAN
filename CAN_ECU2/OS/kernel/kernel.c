/*
 * kernel.c
 *
 *  Created on: Dec 16, 2024
 *      Author: Ahmedmohamed
 */

/********************************************Includes*********************************/
#include "kernel.h"





/*******************************************************Functions Definitions***************************************************************/

/*******************************************************************************************************************************************/
/*Function Name   : kernel_split                                                                                                           */
/*Inputs          : void                                                                                                                   */
/*Outputs         : void                                                                                                                   */
/*Reentrancy      : Non-Reentrant                                                                                                          */
/*Synchronous     : Synchronous                                                                                                            */
/*Description     : managing task execution based on their readiness                                                                       */
/*******************************************************************************************************************************************/
void kernel_split(void)
{
    uint8_t l;
    for ( l = ZERO_VALUE; l < (uint8_t)NUMBER_OF_tasks; l++)
    {
        if (taskList[l].tickCount == ZERO_VALUE)
        {
            taskList[l].task();
            if (taskList[l].isPreiodic)
            {
                taskList[l].tickCount = taskList[l].priodicity;
            }
        }

}
}
