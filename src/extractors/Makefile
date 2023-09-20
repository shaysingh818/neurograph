BIN=bin
CC=gcc
TARGET=target/extractors
TEST_TARGET=target/test_extractors
FLAGS = -g -lm -lpthread $(INCLUDES)

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)

# Graph dependencies
DATA_STRUCTURES = ../data_structures/queue.o ../data_structures/matrix.o ../data_structures/adj_list.o ../data_structures/node.o ../data_structures/map.o ../data_structures/ll.o ../data_structures/set.o ../data_structures/array.o

# source objects for extractors library
TEST_OBJS = test_frame.o test_re.o test_gml.o
SRC_OBJS = $(DATA_STRUCTURES) frame.o re.o gml.o


# link all programs here
all: data_structures source unit_test

data_structures:
	$(MAKE) -C ../data_structures

unit_test: unit_test.o $(SRC_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(SRC_OBJS) $(TEST_OBJS) $(FLAGS)

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o  $(SRC_OBJS) $(FLAGS)


# build source and test objects 
$(SRC_OBJS): %.o: %.c $(HEADERS)
	$(CC) -c $<

$(TEST_OBJS): %.o: tests/%.c tests/includes/%.h $(HEADERS)
	$(CC) -c $< -o $@


# main files
unit_test.o: tests/unit_test.c
	gcc -c tests/unit_test.c

main.o: main.c
	gcc -c main.c

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
