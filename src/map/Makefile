BIN=bin
CC=gcc
TARGET=target/map
TEST_TARGET=target/test_map

# object files
TEST_OBJS = test_map.o
OBJS = map.o
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source

unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)

map.o: map.c includes/map.h
	$(CC) -c map.c

test_map.o: tests/test_map.c tests/includes/test_map.h
	$(CC) -c tests/test_map.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_map.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
