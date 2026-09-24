#ifndef TASK_H
#define TASK_H

typedef struct task {
    char *name;
    int tid;
    int arrival;
    int priority;
    int burst;
    int period;
} Task;

#endif
