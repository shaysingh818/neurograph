BIN=bin
CC=gcc
TARGET=target/adj_list
TEST_TARGET=target/test_adj_list

# object files
TEST_OBJS = test_adj_list.o
OBJS = adj_list.o node.o
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source

unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)

node.o: node.c includes/node.h
	$(CC) -c node.c

adj_list.o: adj_list.c includes/adj_list.h
	$(CC) -c adj_list.c

test_adj_list.o: tests/test_adj_list.c tests/includes/test_adj_list.h
	$(CC) -c tests/test_adj_list.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_adj_list.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
