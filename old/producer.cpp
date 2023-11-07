#include "semaphore.hpp"

buffer_t buffer;
char items[] = {'a', 'b', 'c', '\n'};

void criticalSection() {
    sem_wait(&buffer.empty);
    sem_wait(&buffer.pmut);

    buffer.buf[buffer.nextin] = items[buffer.nextin];
    buffer.nextin++;
    buffer.nextin %= 3;

    //handle shared memory
    {
        int res;
        int fd;
        int len;
        pid_t pid;
        void *addr;

        pid = getpid();

        // get shared memory file descriptor (NOT a file)
        fd = shm_open(STORAGE_ID, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
            perror("open");
        }

        // extend shared memory object as by default it's initialized with size 0
        res = ftruncate(fd, 3);
        if (res == -1)
        {
            perror("ftruncate");
        }

        // map shared memory to process address space
        addr = mmap(NULL, 3, PROT_WRITE, MAP_SHARED, fd, 0);
        if (addr == MAP_FAILED)
        {
            perror("mmap");
        }

        //shmat
        //shmget

        std::cout << "produced item: ";
        std::cout << items[buffer.nextin] << std::endl;
        sem_post(&buffer.pmut);
        sem_post(&buffer.occupied);

        // place data into memory
        len = 3;
        memcpy(addr, items, len);

        // wait for someone to read it
        sleep(2);

        // mmap cleanup
        res = munmap(addr, 3);
        if (res == -1)
        {
            perror("munmap");
        }

        // shm_open cleanup
        fd = shm_unlink(STORAGE_ID);
        if (fd == -1)
        {
            perror("unlink");
        }

    }
}

int main() {
    //initialize semaphore
    //buffer.buf = {"a","b","c"};
    sem_init(&buffer.occupied, 0, 0);
    sem_init(&buffer.empty, 0, 3);
    sem_init(&buffer.pmut, 0, 1);
    sem_init(&buffer.cmut, 0, 1);
    buffer.nextin = 0; 
    buffer.nextout = 0;
    std::cout << "\n";
    for (int i = 0; i < 3; ++i) {
        std::thread t1(criticalSection);
        t1.join();
    }
}
