/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "scheduler.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task names */
char one[]   = {'O','N','E'};
char two[]   = {'T','W','O'};
char three[] = {'T','H','R','E','E'};
char four[]  = {'F','O','U','R'};
char five[]  = {'F','I','V','E'};
char six[]   = {'S','I','X'};
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
uint8_t main(){
	BOARD_InitPins();
	BOARD_InitBootClocks();
   	BOARD_InitDebugConsole();
    add_task(&one, 1, task_one);
    add_task(&two, 2, task_two);
    add_task(&three, 3, task_three);
    add_task(&four, 4, task_four);
    add_task(&five, 5, task_five);
    add_task(&six, 6, task_six);
    fifo_scheduler();
    do{}while(1);
    return 0;
}
