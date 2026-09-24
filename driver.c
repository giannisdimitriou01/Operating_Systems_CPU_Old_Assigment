#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"

int main(int argc, char *argv[]) {
    FILE *in;
    char *filename;
    char task[100];
    int arrival, priority, burst, period;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    filename = argv[1];
    in = fopen(filename, "r");
    if (!in) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    while (fscanf(in, "%s %d %d %d %d", task, &arrival, &priority, &burst, &period) != EOF) {
        add(task, arrival, priority, burst, period);
    }

    fclose(in);
    schedule();
    return 0;
}
