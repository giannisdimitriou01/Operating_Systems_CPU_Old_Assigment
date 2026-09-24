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
        struct node *shortest = NULL, *curr = head;
        while (curr != NULL) {
            if (!shortest || curr->task->burst < shortest->task->burst) {
                shortest = curr;
            }
            curr = curr->next;
        }

        if (shortest) {
            run(shortest->task, 1);
            shortest->task->burst--;
            if (shortest->task->burst == 0) {
                delete(&head, shortest->task);
            }
        }
    }
}
