# Producer-Consumer

This project analyzes the performance of a multi-threaded producer-consumer system implemented in C. It measures the average waiting time of tasks in a shared FIFO queue, across different numbers of producer and consumer threads.

## Overview

- **Producers** generate tasks (`workFunction` structs) and push them into a shared queue.
- **Consumers** dequeue and execute those tasks.
- Each task performs sine calculations on an array of angles.
- The system uses timestamps to record how long tasks wait in the queue.
- The goal is to evaluate how the number of consumer threads affects overall performance.

## Features

- Bounded FIFO queue with synchronization (mutexes and condition variables)
- Poison pill mechanism for clean thread termination
- Configurable number of producers and consumers

## Build Instructions

Make sure you have `gcc` installed. Then run:

```bash
make
```

This compiles the project and outputs the executable to ./bin/prod-con.

## Usage

Run the executable with the number of producer and consumer threads as arguments:

```bash
./bin/prod-con "$PRODUCERS" "$CONSUMERS"
```

Example:

```bash
./bin/prod-con 3 5
```

This will run the system with 3 producers and 5 consumers.

## Output

The program prints the average waiting time (in seconds) between the moment a producer pushes a task into the queue and the moment a consumer dequeues it. This time does **not** include the task’s execution time — it only measures how long the task waited in the queue.