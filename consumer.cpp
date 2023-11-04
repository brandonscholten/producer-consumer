//This file is responsible for displaying and then removing items from the table in shared memory
#include "table/table.hpp"
#include "semaphore.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <semaphore>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;

void signalCallbackHandler(int signal){
    //clean up shared memory
    shmctl(shmid, IPC_RMID, NULL);
    //exit
    exit(signal);
}

void criticalSection() {
    //set up shared memory
    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    table* items = (table*)shmat(shmid, (void*)0,0);
    //pop rows off the table forever
    while (true) {    
        criticalSignal.acquire();
        std::cout << "consumed table item: ";
        std::vector<std::string> row = items->popRow();
        std::vector<std::string>::iterator iter;
        for ( ; iter != row.end(); ++iter) {std::cout << (*iter); std::cout << ", ";}
        std::cout << std::endl;
        shmdt(items);
        criticalSignal.release();
    }
}

int main() {
    signal(SIGINT, signalCallbackHandler);
    std::cout << "\n";
    std::thread t1(criticalSection);
}
