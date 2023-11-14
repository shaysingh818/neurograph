#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/node


objects := $(patsubst %.c,%.o,$(wildcard *.c))
test_objects := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

source: $(objects) $(test_objects)
	cc -o $(TARGET) $(objects) $(test_objects)
	mv $(filter-out main.o, $(objects)) ./objs

clean:
	rm -f  *.o *~ *.pyc
