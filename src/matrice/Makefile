BIN=bin
CC=gcc
TARGET=target/matrix
TEST_TARGET=target/test_matrix

# object files
TEST_OBJS = test_matrix.o
OBJS = matrix.o
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source

unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)

matrix.o: matrix.c includes/matrix.h
	$(CC) -c matrix.c

test_matrix.o: tests/test_matrix.c tests/includes/test_matrix.h
	$(CC) -c tests/test_matrix.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_matrix.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
