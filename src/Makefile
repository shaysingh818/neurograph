# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/neurograph
SO_TARGET = libneurograph.so
INSTALL_DIR = /usr/local/lib
OBJ_DIR = objs

FLAGS = -lm -lpthread -lds -lextractors -lgraph 
SO_FLAGS =  -shared -fPIC  

# source objects 
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

all:
	$(MAKE) build
	$(MAKE) source

source:  $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS) $(FLAGS)

install:
	$(MAKE) -C ./data_structures
	$(MAKE) -C ./data_structures install

	$(MAKE) -C ./extractors 
	$(MAKE) -C ./extractors install

	$(MAKE) -C ./graph 
	$(MAKE) -C ./graph install

	# $(MAKE) -C ./computation_graph 
	# $(MAKE) -C ./computation_graph install

	# $(MAKE) -C ./networks 
	# $(MAKE) -C ./networks install

uninstall:
	$(MAKE) -C ./data_structures uninstall
	$(MAKE) -C ./extractors uninstall 
	$(MAKE) -C ./graph uninstall 
	$(MAKE) -C ./computation_graph uninstall 
	$(MAKE) -C ./networks uninstall 


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
