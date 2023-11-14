# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/neurograph
SO_TARGET = libneurograph.so
INSTALL_DIR = /usr/local/lib
OBJ_DIR = objs

FLAGS = -lm -lpthread
SO_FLAGS =  -fPIC 

# package objects
DATA_STRUCTURES := $(wildcard ./data_structures/objs/*.o)
EXTRACTORS := $(wildcard ./extractors/objs/*.o)
CGRAPH := $(wildcard ./computation_graph/objs/*.o)
GRAPH := $(wildcard ./graph/objs/*.o)
NETWORKS := $(wildcard ./networks/objs/*.o)
DEPS = $(DATA_STRUCTURES) $(EXTRACTORS) $(CGRAPH) $(GRAPH) $(NETWORKS)

# source objects 
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

all:
	$(MAKE) build
	$(MAKE) source

shared: $(OBJS) $(DEPS)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(OBJS) $(DEPS) $(FLAGS)

source:  $(OBJS) $(DEPS)
	$(CC) -o $(TARGET) $(OBJS) $(DEPS)  $(FLAGS)
	mkdir $(OBJ_DIR)
	cp $(DEPS) $(OBJ_DIR)

build:
	$(MAKE) -C ./data_structures
	$(MAKE) -C ./extractors package
	$(MAKE) -C ./graph package
	$(MAKE) -C ./computation_graph package
	$(MAKE) -C ./networks package

install:
	cp $(SO_TARGET) $(INSTALL_DIR)
	ldconfig
	rm $(SO_TARGET)

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
	rm -rf $(OBJ_DIR)
	$(MAKE) -C  ./data_structures clean
	$(MAKE) -C ./networks clean
	$(MAKE) -C ./graph clean
	$(MAKE) -C ./extractors clean
	$(MAKE) -C  ./computation_graph clean
