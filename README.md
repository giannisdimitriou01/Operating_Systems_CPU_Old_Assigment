# CPU Scheduling Simulator

A mini CPU scheduling simulation written in **C**, implementing five classic task scheduling algorithms. This is a university assignment for the Operating Systems course.

---

## Overview

The program reads a list of tasks from an input file and simulates how a CPU scheduler would process them using one of the supported algorithms. Each algorithm is implemented as a **separate, swappable module** — you compile the driver with the desired scheduler to produce a different binary.

The simulation is structured around a simple **linked-list task queue** and a lightweight **CPU runner** that prints which task is executing and for how long.

---

## Scheduling Algorithms

| File | Algorithm | Type | Description |
|---|---|---|---|
| `schedule_fcfs.c` | **FCFS** | Non-preemptive | First-Come, First-Served — tasks run in arrival order to completion |
| `schedule_srtf.c` | **SRTF** | Preemptive | Shortest Remaining Time First — always runs the task with the least burst time left (1-unit time slices) |
| `schedule_rr_priority.c` | **Priority RR** | Preemptive | Priority-based Round Robin — picks the highest-priority task each round, runs it for a time quantum (10 units) |
| `schedule_edf.c` | **EDF** | Non-preemptive | Earliest Deadline First — selects the task with the smallest period (deadline proxy) |
| `schedule_monotonic.c` | **Rate Monotonic** | Non-preemptive | Rate Monotonic — selects the task with the shortest period (highest frequency = highest priority) |

---

## Project Structure

```
.
├── CPU.c                   # CPU runner — prints task execution info
├── driver.c                # Entry point — reads input file, calls add() and schedule()
├── list.c / list.h         # Singly linked list (insert, delete, traverse)
├── task.h                  # Task struct definition
├── schedulers.h            # Scheduler interface (add, schedule)
├── schedule_fcfs.c         # FCFS implementation
├── schedule_srtf.c         # SRTF implementation
├── schedule_rr_priority.c  # Priority Round Robin implementation
├── schedule_edf.c          # EDF implementation
└── schedule_monotonic.c    # Rate Monotonic implementation
```

---

## Task Model

Each task is defined by 5 fields (as read from the input file):

```c
typedef struct task {
    char *name;     // Task identifier (e.g. "T1")
    int tid;        // Task ID (internal)
    int arrival;    // Arrival time
    int priority;   // Priority (1 = highest, 10 = lowest)
    int burst;      // CPU burst time (units of work needed)
    int period;     // Period / deadline (used by EDF and Rate Monotonic)
} Task;
```

---

## Input File Format

Each line in the input file describes one task:

```
<name> <arrival> <priority> <burst> <period>
```

**Example:**
```
T1 0 4 20 50
T2 0 2 35 100
T3 0 6 15 75
T4 0 1 10 30
```

---

## Building & Running

You need a C compiler (e.g. `gcc`). Since each scheduler is a separate translation unit, compile `driver.c`, `CPU.c`, `list.c` together with the scheduler of your choice.

### Compile (choose one algorithm)

```bash
# FCFS
gcc driver.c CPU.c list.c schedule_fcfs.c -o scheduler_fcfs

# Shortest Remaining Time First
gcc driver.c CPU.c list.c schedule_srtf.c -o scheduler_srtf

# Priority Round Robin
gcc driver.c CPU.c list.c schedule_rr_priority.c -o scheduler_rr

# Earliest Deadline First
gcc driver.c CPU.c list.c schedule_edf.c -o scheduler_edf

# Rate Monotonic
gcc driver.c CPU.c list.c schedule_monotonic.c -o scheduler_monotonic
```

### Run

```bash
./scheduler_fcfs input.txt
```

### Example Output

```
Running task = [T4] [10] units
Running task = [T2] [10] units
Running task = [T2] [10] units
Running task = [T1] [10] units
...
```

---

## Implementation Notes

- The **linked list** (`list.c`) provides `insert`, `delete`, and `traverse` operations shared by all schedulers.
- The **CPU** (`CPU.c`) provides a single `run(task, slice)` function that simulates execution by printing to stdout.
- The `TIME_QUANTUM` for the Round Robin scheduler is defined as **10 units** in `schedule_rr_priority.c`.
- EDF and Rate Monotonic use the `period` field as the scheduling key (shortest period = runs first).
- SRTF uses **1-unit time slices** to simulate true preemption at every time step.

---

## Requirements

- C compiler: `gcc` or compatible
- Standard C library (`stdlib.h`, `stdio.h`, `string.h`)
- No external dependencies
