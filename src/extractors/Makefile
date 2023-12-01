#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/extractors
OBJS = objs



# dependencies
DATA_STRUCTURES := $(wildcard ../data_structures/objs/*.o)
DATAFRAME := $(wildcard ./dataframe/objs/*.o)
DATABASES := $(wildcard ./databases/objs/*.o)
DEPS = $(DATA_STRUCTURES) $(DATAFRAME) $(DATABASES)


OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

# flags
CFLAGS =  -lm -lpthread -g

all:
	$(MAKE) build
	$(MAKE) source
	$(MAKE) obj

package:
	$(MAKE) -C ./dataframe package
	$(MAKE) -C ./databases
	$(MAKE) obj

source:  $(OBJECTS) $(DEPS)
	cc -o $(TARGET) $(OBJECTS) $(DEPS) $(CFLAGS)

build: 
	$(MAKE) -C ./dataframe
	$(MAKE) -C ./databases


headers:
	mkdir -p extractors/dataframe
	cp -r dataframe/includes extractors/dataframe
	mkdir -p extractors/databases
	cp -r databases/includes extractors/databases	
	mv extractors ../neurograph
	cp extractors.h ../neurograph

obj:
	mkdir $(OBJS)
	cp $(DATAFRAME) $(DATABASES) $(OBJS)


clean_package:
	rm -f  *.o *~ *.pyc
	rm -rf $(OBJS)
	$(MAKE) -C ./dataframe clean_package
	$(MAKE) -C ./databases clean

# clean compilation (target doesn't work)
clean:
	rm -f  *.o *~ *.pyc
	rm -rf $(OBJS)
	$(MAKE) -C ./dataframe clean
	$(MAKE) -C ./databases clean
