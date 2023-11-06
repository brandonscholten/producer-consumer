//This file is responsible for displaying and then removing items from the table in shared memory
#include "semaphore.hpp"
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

int shmid;

void signalCallbackHandler(int signal){
    std::cout << "\ncleaning up shared memory...\n";
    //clean up shared memory
    shmctl(shmid, IPC_RMID, NULL);
    //exit
    exit(signal);
}

void criticalSection() {
    std::cout << "critical section running...\n";
    //set up interprocess communication
    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    table* items = (table*)shmat(shmid, (void*)0,0);
    std::cout << "IPC initialized!\n";
    //pop rows off the table forever
    while (true) {    
        std::cout << "popping off 😎\n";
        std::cout << "waiting...\n";
        sem_wait(&semaphore);
        std::cout << "consumed table item: ";
        std::vector<std::string> row = items->popRow();
        std::vector<std::string>::iterator iter;
        for ( ; iter != row.end(); ++iter) {std::cout << (*iter); std::cout << ", ";}
        std::cout << std::endl;
        shmdt(items);
        sem_post(&semaphore);
        std::cout << "finished...\n";
    }
}

int main() {
    signal(SIGINT, signalCallbackHandler);
    std::cout << "\n";
    std::thread t1(criticalSection);
    t1.join();
}
