#include <stdio.h>
#include "task.h"

void run(Task *task, int slice) {
    printf("Running task = [%s] [%d] units\n", task->name, slice);
}
