CC = gcc
#OPTIONS = -g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++20
OPTIONS = -pthread -Irt

#compile table ADT
table: table/table.hpp table/table.cpp
	$(CC) -c  $(OPTIONS) table/table.cpp -o table/table.o

#compile producer
producer: semaphore.hpp producer.cpp
	$(CC) -c $(OPTIONS) producer.cpp -o producer_exec.o

#compile consumer
consumer: semaphore.hpp consumer.cpp
	$(CC) -c $(OPTIONS) consumer.cpp -o consumer_exec.o

#run producer
run-producer:
	sudo ./producer_exec.o

#run consumer
run-consumer:
	sudo ./consumer_exec.o

#TODO: make tests

#clean
clean:
	rm -rf *.o
	rm -- **/*.o
