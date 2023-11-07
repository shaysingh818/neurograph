#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/data_structures
OBJS = objs
OUTPUT_OBJ = data_structures.o

# dependencies
NODE := $(wildcard ./node/objs/*.o)
QUEUE := $(wildcard ./queue/objs/*.o)
SET := $(wildcard ./set/objs/*.o)
LIST := $(wildcard ./list/objs/*.o)
MAP := $(wildcard ./map/objs/*.o)
MATRIX := $(wildcard ./matrix/objs/*.o)
DATA_STRUCTURES = $(NODE) $(QUEUE) $(SET) $(LIST) $(MAP) $(MATRIX)

# source objects
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

# flags
CFLAGS =  -lm -lpthread -g

all: 
	$(MAKE) build
	$(MAKE) source
	$(MAKE) obj	

source: $(OBJECTS) $(DATA_STRUCTURES)
	cc -o $(TARGET) $(OBJECTS) $(DATA_STRUCTURES) $(CFLAGS)

obj: 
	mkdir $(OBJS)
	cp $(DATA_STRUCTURES) $(OBJS)

build:
	$(MAKE) -C ./node
	$(MAKE) -C ./queue
	$(MAKE) -C ./set
	$(MAKE) -C ./list
	$(MAKE) -C ./map
	$(MAKE) -C ./matrix

# clean compilation (target doesn't work)
clean:
	rm -f  *.o *~ *.pyc
	rm -rf objs
	$(MAKE) -C  ./map clean
	$(MAKE) -C ./matrix clean
	$(MAKE) -C ./set clean
	$(MAKE) -C ./list clean
	$(MAKE) -C  ./queue clean
	$(MAKE) -C  ./node clean
