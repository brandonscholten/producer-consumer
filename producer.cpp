//This file creates a new thread responsible for creating a table based on items.csv
#include "table/table.hpp"
#include "semaphore.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <semaphore>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void criticalSection() {
    //setup interprocess communication
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    table* items = (table*)shmat(shmid, (void*)0, 0);
    //create a table using items.csv
    std::ifstream file;
    file.open("items.csv");
    std::string line;
    while(getline(file, line)){
        criticalSignal.acquire();
        std::vector<std::string> lineVec;
        for (size_t i = 0; i < line.length(); ++i) {
            std::string element;
            if (line[i] == ',') {
                lineVec.push_back(element);
                element = "";
            } else {
                element.push_back(line[i]);
            }
        } 
        items->pushRow(lineVec);
        //write table to shared memory
        shmdt(items);
        std::cout << "produced item: \n";
        items->display(std::cout); 
        criticalSignal.release();
    }
}

int main() {
    std::cout << "\n";
    std::thread t1(criticalSection);
}
