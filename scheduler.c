/*
 * scheduler.c
 *
 *  Created on: Sep 14, 2020
 *      Author: richa
 */

#include "board.h"
#include "scheduler.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
char def[]   = {'N','E','W'};

/* Output gpio for red LED */
gpio_pin_config_t led_config = {
    kGPIO_DigitalOutput,
    0,
};

/* Input gpio for red LED */
gpio_pin_config_t led_configIn = {
    kGPIO_DigitalInput,
    0,
};

/* Delay function for burst time */
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1500000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/* Pointer to first node in queue */
struct task_node* head;

/* Pointer to last node in queue */
struct task_node* tail;

/* Task counter */
uint8_t task_num = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Pre-defined tasks */
void task_one() {
  printf("\nThis is task ONE\n");
}

void task_two() {
  printf("This is task TWO\n");
}

void task_three() {
  printf("This is task THREE\n");
}

void task_four() {
  printf("This is task FOUR\n");
}

void task_five() {
  printf("This is task FIVE\n");
}

void task_six() {
  printf("This is task SIX\n");
}

/* Default prototype for new tasks */
void default_task(){
  printf("This is a new task\n");
}

/* Function to add task to queue */
void add_task(char name[], uint8_t burst_time, void *task_func){
	/* Malloc procedure for new task */
	struct task_node* new_node = (struct task_node*)malloc(sizeof(struct task_node));
	/* Assign data to node elements */
	//strcpy(new_node->name,&name);
	new_node->burst_time = burst_time;
	new_node->mytask = task_func;
	/* If first task, assign head and tail to same node */
	if(task_num == 0){
		head = new_node;
		tail = new_node;
	}
	/* If not first task, make connections to next and previous node */
	else {
		tail->next = new_node;
		new_node->prev = tail;
		new_node->next = head;
		tail = new_node;
	}
	/* Increment task counter */
	task_num++;
}

/* Delete last task from queue */
void pop_task(){
  struct task_node* temp = tail;
  temp->prev->next = head;
  tail = temp->prev;
  task_num--;
}

/* Scheduler implementation */
void fifo_scheduler(){
  struct task_node* task = head;
  uint8_t i;
  /* Flag for task number limit */
  uint8_t ten = 0;
  do{
    if(task_num>9) ten=1;
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
    /*Execute task function */
    task->mytask();
    /* Burst time loop */
    for(i=0;i<task->burst_time;i++){
      delay();
      GPIO_PortToggle(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
      delay();
      GPIO_PortToggle(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
    }
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_configIn);
    /* Add new task every time scheduler execute every task in the queue */
    if(task->next == head && !ten){
    	add_task(&def, 8, default_task);
    	task = head;
    }
    /* When task limit is reached, delete tasks until there are 6 again */
    else if(task->next == head && ten) {
    	pop_task();
    	task = head;
    }
    else if(ten && task_num==6){
    	task = head;
    	ten=0;
    }
    else task = task->next;
  }while(1);
}

