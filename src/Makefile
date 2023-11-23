# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/neurograph
SO_TARGET = libneurograph.so
INSTALL_DIR = /usr/local/lib
OBJ_DIR = objs

FLAGS = -lm -lpthread
SO_FLAGS =  -shared -fPIC  

# package objects
DATA_STRUCTURES := $(wildcard ./data_structures/objs/*.o)
EXTRACTORS := $(wildcard ./extractors/objs/*.o)
CGRAPH := $(wildcard ./computation_graph/objs/*.o)
GRAPH := $(wildcard ./graph/objs/*.o)
NETWORKS := $(wildcard ./networks/objs/*.o)
DEPS = $(DATA_STRUCTURES) $(EXTRACTORS) $(GRAPH) $(CGRAPH) $(NETWORKS)

# source objects 
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
ALL_OBJS = $(DATA_STRUCTURES) $(EXTRACTORS) $(GRAPH) $(CGRAPH) $(NETWORKS)

all:
	$(MAKE) build
	$(MAKE) source

install:
	$(MAKE) shared
	$(MAKE) headers
	ldconfig

uninstall:
	rm -r /usr/local/include/neurograph
	rm /usr/local/lib/libneurograph.so

shared: $(ALL_OBJS)
	$(CC) -o $(SO_TARGET) $(ALL_OBJS) $(FLAGS) $(SO_FLAGS)
	cp $(SO_TARGET) /usr/local/lib

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

headers:
	mkdir neurograph/
	$(MAKE) -C ./data_structures headers
	$(MAKE) -C ./extractors headers
	$(MAKE) -C ./graph headers
	$(MAKE) -C ./computation_graph headers
	$(MAKE) -C ./networks headers
	mv neurograph /usr/local/include

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *.so *~
	rm -rf $(OBJ_DIR)
	rm -rf neurograph/
	$(MAKE) -C  ./data_structures clean
	$(MAKE) -C ./networks clean
	$(MAKE) -C ./graph clean
	$(MAKE) -C ./extractors clean
	$(MAKE) -C  ./computation_graph clean
