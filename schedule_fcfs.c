#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head;

void add(char *name, int arrival, int priority, int burst, int period) {
    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->arrival = arrival;
    t->priority = priority;
    t->burst = burst;
    t->period = period;

    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = t;
    newNode->next = NULL;

    if (!head)
        head = newNode;
    else {
        struct node *temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void schedule() {
    struct node *temp = head;
    while (temp != NULL) {
        run(temp->task, temp->task->burst);
        temp = temp->next;
    }
}
