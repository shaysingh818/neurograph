# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/test_neurograph
OBJ_DIR = objs

FLAGS = -lm -lpthread -lds -lextractors -lgraph -lcgraph -lnetworks
SO_FLAGS =  -fPIC 

# source objects 
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

all:
	$(MAKE) build
	$(MAKE) source

source:  $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS) $(FLAGS)
	mkdir $(OBJ_DIR)
	cp $(DEPS) $(OBJ_DIR)

clean_binary:
	rm $(TARGET)


clean:
	rm -f *.o *~
	rm -rf $(OBJ_DIR)
	$(MAKE) -C  ../data_structures clean
	$(MAKE) -C ../networks clean
	$(MAKE) -C ../graph clean
	$(MAKE) -C ../extractors clean
	$(MAKE) -C  ../computation_graph clean

