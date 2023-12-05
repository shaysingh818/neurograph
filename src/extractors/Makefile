#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/extractors
OBJS = objs
SO_TARGET = libextractors.so

# dependencies
DATAFRAME := $(wildcard ./dataframe/objs/*.o)
DATABASES := $(wildcard ./databases/objs/*.o)
DEPS = $(DATAFRAME) $(DATABASES)


OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

# flags
CFLAGS =  -lm -lpthread -g -lds
SO_FLAGS =  -fPIC -shared

all:
	$(MAKE) build
	$(MAKE) source
	$(MAKE) obj

install:
	$(MAKE) shared
	$(MAKE) headers

uninstall:
	rm -r /usr/local/include/extractors
	rm /usr/local/lib/$(SO_TARGET)

package:
	$(MAKE) -C ./dataframe package
	$(MAKE) -C ./databases
	$(MAKE) obj

source:  $(OBJECTS) $(DEPS)
	cc -o $(TARGET) $(OBJECTS) $(DEPS) $(CFLAGS)

build: 
	$(MAKE) -C ./dataframe
	$(MAKE) -C ./databases

shared: $(OBJECTS) $(DEPS)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(OBJECTS) $(DEPS) $(CFLAGS)
	sudo mv $(SO_TARGET) /usr/local/lib
	ldconfig

headers:
	mkdir -p extractors/dataframe
	cp -r dataframe/includes extractors/dataframe
	mkdir -p extractors/databases
	cp -r databases/includes extractors/databases	
	mv extractors /usr/local/include

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
