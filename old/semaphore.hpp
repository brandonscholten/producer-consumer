#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

//#include "table/table.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>

struct buffer {
    char buf[3];
    sem_t occupied;
    sem_t empty;
    int nextin;
    int nextout;
    sem_t pmut;
    sem_t cmut;
} buffer_t;

// sem_init(&buffer.occupied, 0, 0);
// sem_init(&buffer.empty, 0, 1024);
// sem_init(&buffer.pmut, 0, 1);
// sem_init(&buffer.cmut, 0, 1);
// buffer.nextin = buffer.nextout = 0;

#endif
