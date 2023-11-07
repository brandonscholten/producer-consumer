#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

struct SharedData {
    int data [3];
};

int main() {
    const char* shm_name = "/my_shared_memory";
    const char* sem_name = "/my_semaphore";
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(shm_fd, sizeof(SharedData));
    SharedData *shared_data = (SharedData *)mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sem_t *sem = sem_open(sem_name, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 3; ++i) {
        // Wait for the semaphore
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }

        // Consume data
        std::cout << "Consumer is consuming data: " << shared_data->data[i] << std::endl;
        sleep(1); // Simulate some work

        // Release the semaphore
        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
    }
    // Close the semaphore
    if (sem_close(sem) == -1) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }

    // Cleanup shared memory
    munmap(shared_data, sizeof(SharedData));
    close(shm_fd);
    return 0;
}
