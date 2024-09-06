# philosophers

**philosophers** is a project that involves solving the classic Dining Philosophers Problem using synchronization techniques in C. The goal of this project is to understand and manage concurrency and synchronization between multiple processes or threads.

## Problem Description

The Dining Philosophers Problem is a classic synchronization issue where five philosophers sit at a round table with a fork placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. However, to eat, a philosopher needs both forks on either side. The challenge is to design an algorithm to avoid deadlock and ensure that every philosopher gets a chance to eat.

## Features

- Implement a solution to the Dining Philosophers Problem using mutexes and condition variables.
- Ensure no deadlock occurs.
- Ensure that no philosopher starves and every philosopher gets a chance to eat.
- Handle edge cases such as no philosophers, or an even number of philosophers.

## Getting Started

### Prerequisites

- A Unix-based system (Linux or macOS)
- `gcc` compiler and `make`
- Basic understanding of concurrency and synchronization

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/arnoop88/philosophers.git
   cd philosophers

2. Compile the project:
	
	```bash
	make

## Running the program

To run the program, you need to specify the number of philosophers, the time to die, the time to eat, and the time to sleep in ms. You can also specify the number of times each philosopher has to eat in order to finish the program. For example:
```bash
./philosophers 5 800 200 200 5
```
