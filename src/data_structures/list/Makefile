#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/list
TEST_TARGET=target/test_list

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)


# source objects
SRC_OBJS = ll.o array.o adj_list.o ../node/node.o 

# unit test objects
TEST_OBJS = test_adj_list.o test_ll.o 

# flags
FLAGS =  -lm -lpthread -g

# link all programs here
all: node unit_test source

node: 
	$(MAKE) -C ../node

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
clean:
	rm -f  *.o *~ *.pyc
	$(MAKE) -C  ../node clean
