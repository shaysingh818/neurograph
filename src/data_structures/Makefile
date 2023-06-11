#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/data_structures
TEST_TARGET=target/test_data_structures

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)


# source objects
SRC_OBJS = matrix.o map.o adj_list.o queue.o node.o set.o ll.o

# unit test objects
TEST_OBJS = test_ll.o test_set.o test_map.o test_adj_list.o test_matrix.o test_queue.o

# flags
FLAGS = -g -lm -lpthread


# link all programs here
all: unit_test source

unit_test: unit_test.o $(SRC_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(SRC_OBJS) $(TEST_OBJS) $(FLAGS)

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o  $(SRC_OBJS) $(FLAGS)


# build source and test objects 
$(SRC_OBJS): %.o: %.c $(HEADERS)
	$(CC) -c $<

$(TEST_OBJS): %.o: tests/%.c tests/includes/%.h $(HEADERS)
	$(CC) -c $< -o $@

unit_test.o: tests/unit_test.c $(TEST_HEADERS)
	$(CC) -c $< -o $@

main.o: main.c $(HEADERS)
	$(CC) -c $< -o $@



# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o *~ *.pyc