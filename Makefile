CC = g++
#options for clang++
#OPTIONS = -g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++20
#options for gcc
#OPTIONS = -pthread -lrt -std=c++20
#options for g++
POPTIONS = -pthread -lrt 

#compile table ADT
table: table/table.hpp table/table.cpp
	$(CC) -c table/table.cpp

#compile producer
producer: 
	$(CC) $(POPTIONS) table/table.hpp table/table.cpp semaphore.hpp producer.cpp -o producer_exec.o

#compile consumer
consumer: 
	$(CC) $(POPTIONS) table/table.hpp table/table.cpp semaphore.hpp consumer.cpp -o consumer_exec.o

#run producer
run-producer:
	./producer_exec.o

#run consumer
run-consumer:
	./consumer_exec.o

#TODO: make tests

.PHONY: all table clean

#clean
clean:
	rm -rf *.o
	rm -- **/*.o
