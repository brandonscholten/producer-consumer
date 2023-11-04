CC = clang++
OPTIONS = -g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++17

#compile table ADT
table: table/table.hpp table/table.cpp
	$(CC) -c  $(OPTIONS) table/table.cpp -o table/table.o

#compile producer
producer: semaphore.hpp producer.cpp
	$(CC) -c $(OPTIONS) producer.cpp -o producer

#compile consumer
consumer: semaphore.hpp consumer.cpp
	$(CC) -c $(OPTIONS) consumer.cpp -o consumer

#run producer
run-producer:
	./producer.o

#run consumer
run-consumer:
	./consumer.o

#TODO: make tests

#clean
clean:
	rm -rf *.o
	rm -- **/*.o
