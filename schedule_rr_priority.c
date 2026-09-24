#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

#define TIME_QUANTUM 10

struct node *head = NULL;

void add(char *name, int arrival, int priority, int burst, int period) {
    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->arrival = arrival;
    t->priority = priority;
    t->burst = burst;
    t->period = period;
    insert(&head, t);
}

void schedule() {
    while (head != NULL) {
        struct node *highest = NULL, *ptr = head;
        while (ptr != NULL) {
            if (!highest || ptr->task->priority < highest->task->priority) {
                highest = ptr;
            }
            ptr = ptr->next;
        }

        if (highest) {
            int slice = highest->task->burst > TIME_QUANTUM ? TIME_QUANTUM : highest->task->burst;
            run(highest->task, slice);
            highest->task->burst -= slice;

            if (highest->task->burst == 0) {
                delete(&head, highest->task);
            } else {
                delete(&head, highest->task);
                insert(&head, highest->task);
            }
        }
    }
}
