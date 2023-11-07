CC = g++
OPTIONS = -pthread 

#compile producer
producer: semaphore.hpp
	$(CC) $(OPTIONS) producer.cpp -o producer.o

#compile consumer
consumer: semaphore.hpp
	$(CC) $(OPTIONS) consumer.cpp -o consumer.o

#run producer
run-producer:
	./producer_exec.o

#run consumer
run-consumer:
	./consumer_exec.o

#clean
clean:
	rm -rf *.o
	rm -rf *.gch
	rm -- **/*.o
