#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

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
        struct node *min = head, *ptr = head->next;
        while (ptr) {
            if (ptr->task->period < min->task->period) {
                min = ptr;
            }
            ptr = ptr->next;
        }

        run(min->task, min->task->burst);
        delete(&head, min->task);
    }
}
