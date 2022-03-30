/*
 * scheduler.h
 *
 *  Created on: Sep 14, 2020
 *      Author: richa
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/* Pointer to function typedef */
typedef void (*taskfunc)();

/* Node struct for task queue. Elements: burst time, pointer to task function
 * pointer to previous node, pointer to next node, and task name. */
struct task_node {
  uint8_t burst_time;
  taskfunc mytask;
  struct task_node* prev;
  struct task_node* next;
  char name[];
};

/* Add task to queue */
void add_task(char name[], uint8_t burst_time, void *task_func);

/* Pre-defined tasks */
void task_one();
void task_two();
void task_three();
void task_four();
void task_five();
void task_six();

/* Default prototype for new tasks */
void default_task();

#endif /* SCHEDULER_H_ */
