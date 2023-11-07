#include "semaphore.hpp"
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

void criticalSection() {

    buffer_t items;

    //handle shared memory
    {
        //set up shared memory
        int res;
        int fd;
        pid_t pid;
        void *addr;

        pid = getpid();

        fd = shm_open(STORAGE_ID, O_RDONLY, S_IRUSR | S_IWUSR);

        if (fd == -1) {
            perror("open");
        }

        addr = mmap(NULL, 3, PROT_READ, MAP_SHARED, fd, 0);

        if (addr == MAP_FAILED) {
            perror("mmap");
        }

        //place buffer into shared memory
        memcopy(items, addr, STORAGE_SIZE);

    }

    sem_wait(&buffer.occupied);
    sem_wait(&buffer.cmut);
    std::cout << "consumed item: ";

    std::cout <<  buffer.buf[buffer.nextout] << std::endl;
    buffer.nextout++;
    buffer.nextout %= 3;

    sem_post(&buffer.cmut);
    sem_post(&buffer.empty);
}

int main() {
    for (int i = 0; i < 3; ++i) {
        std::thread t1(criticalSection);
        t1.join();
    }
}
