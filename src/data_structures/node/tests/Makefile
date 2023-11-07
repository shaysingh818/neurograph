#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/test_node

objects := $(patsubst %.c,%.o,$(wildcard *.c))
test_objects := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))



source: $(objects) 
	cc -o $(TARGET) $(objects)



clean:
	rm -f  *.o *~ *.pyc
