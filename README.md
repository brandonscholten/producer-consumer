Brandon Scholten - Operating Systems - 2023
# Overview
This project uses two separate processes to simulate the producer consumer problem using a buffer of size three. The buffer is loaded into shared memory and modified by the producer, which adds values to it in a loop. The consumer reads each value as it is added and displays it in the terminal. The shared memory buffer is then deallocated. THe project uses the semaphore.h library and sys/mman library to implement semaphores and interprocess communication. 

# Compilation
To compile the program, clone the repository and run the following:

```
g++ producer.cpp -o producer
g++ consumer.cpp -o consumer
./producer && ./consumer
```
# old folder
The old folder contains a failed implementation of this project. My original ambition was to have the producer and comsumer modify a "table" ADT that would display more structured and visually appealing output to the terminal. Unfortunately, the process of sharing an object through IPC led me to abandon this part of the project. I ran into a situation in which there was not enough memory on the heap to allocate a meltidimensional vector used for the table. While it is likely possible to complete th project using such an object, I found it dificult to manage with the amount of time I have left. 
