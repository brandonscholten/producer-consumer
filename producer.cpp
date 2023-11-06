//This file creates a new thread responsible for creating a table based on items.csv
#include "semaphore.hpp"

void criticalSection() {
    std::cout << "critical section running...\n";
    //setup interprocess communication
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    //table* items = (table*)shmat(shmid, (void*)0, 0);
    char* items = (char*)shmat(shmid, (void*)0, 0);
    std::cout << "IPC initialized!\n";
    //create a table using items.csv
    std::ifstream file;
    file.open("items.csv");
    std::string line;
    std::cout << "creating table from CSV\n";
    while(getline(file, line)){
        std::cout << "line: " << line << std::endl;
        std::cout << "waiting..." << std::endl;
        sem_wait(&semaphore);
        std::cout << "producing...\n";
        std::vector<std::string> lineVec;
        std::cout << "created vector for line.\n";
        for (size_t i = 0; i < line.length(); ++i) {
            std::cout << "in vector creation loop:\n";
            std::cout << "i = "; std::cout << i << std::endl;
            std::string element;
            if (line[i] == ',') {
                lineVec.push_back(element);
                element = "";
            } else {
                element.push_back(line[i]);
            }
            std::cout << "element = "; std::cout << element << std::endl;
        } 
        std::cout << "pushing to table...\n";
        items->pushRow(lineVec);
        //write table to shared memory
        std::cout << "writing to shared memory...\n";
        shmdt(items);
        std::cout << "produced item: \n";
        items->display(std::cout); 
        sem_post(&semaphore);
        std::cout << "finished...\n";
    }
}

int main() {
    //initialize semaphore
    sem_init(&semaphore, 1, 1);
    std::cout << "\n";
    //run critical section
    std::thread t1(criticalSection);
    t1.join();
}
