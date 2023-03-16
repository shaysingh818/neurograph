BIN=bin
CC=gcc
TARGET=target/utils
TEST_TARGET=target/test_utils

GRAPH_OBJS = ../graph/graph.o ../list/adj_list.o ../list/node.o ../graph/path.o ../graph/search.o ../graph/community.o
QUEUE_OBJS = ../queue/queue.o
MAP_OBJS = ../map/map.o
MATRICE_OBJS = ../matrice/matrix.o
CSV_OBJS = ../csv/csv.o
UTIL_OBJS = utils.o serializers.o 

# object files
TEST_OBJS = test_serializers.o
OBJS = $(GRAPH_OBJS) $(CSV_OBJS) $(MATRICE_OBJS) $(MAP_OBJS) $(QUEUE_OBJS) $(UTIL_OBJS)
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source


csv:
	$(MAKE) -C ../csv

graph:
	$(MAKE) -C ../graph

matrice:
	$(MAKE) -C ../matrice

list:
	$(MAKE) -C ../list

queue:
	$(MAKE) -C ../queue

map:
	$(MAKE) -C ../map


unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)

utils.o: utils.c includes/utils.h
	$(CC) -c utils.c

serializers.o: serializers.c includes/serializers.h
	$(CC) -c serializers.c

test_serializers.o: tests/test_serializers.c tests/includes/test_serializers.h
	$(CC) -c tests/test_serializers.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_serializers.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	$(MAKE) -C  ../graph clean
	$(MAKE) -C ../csv clean
	$(MAKE) -C ../queue clean
	$(MAKE) -C ../matrice clean
	$(MAKE) -C ../map clean
	$(MAKE) -C ../list clean
