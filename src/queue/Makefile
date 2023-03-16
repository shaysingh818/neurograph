BIN=bin
CC=gcc
TARGET=target/queue
TEST_TARGET=target/test_queue

# object files
TEST_OBJS = test_queue.o
OBJS = queue.o ../list/node.o
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source

unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)

queue.o: queue.c includes/queue.h
	$(CC) -c queue.c

node.o: ../list/node.c ../list/includes/node.h
	$(CC) -c ../list/node.c

test_queue.o: tests/test_queue.c tests/includes/test_queue.h
	$(CC) -c tests/test_queue.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_queue.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc

