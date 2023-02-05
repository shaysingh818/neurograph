BIN=bin
CC=gcc
TARGET=../target/unit_test

# Header files
MATRIX_HEADER = includes/matrix_test.h
GRAPH_HEADER = includes/graph_test.h
QUEUE_HEADER = includes/queue_test.h
MAP_HEADER = includes/map_test.h
UTILITY_HEADER_FILES = $(MATRIX_HEADER) $(GRAPH_HEADER) $(QUEUE_HEADER) $(MAP_HEADER)

# Extension header files
CSV_HEADER = includes/csv_test.h
PATH_HEADER = includes/path_test.h
COMMUNITY_HEADER = includes/community_test.h
SEARCH_HEADER = includes/search_test.h
EXTENSION_HEADER_FILES = $(CSV_HEADER) $(PATH_HEADER) $(COMMUNITY_HEADER) $(SEARCH_HEADER)

# Object files (For test cases)
PATH_OBJS = path_test.o path.o
CSV_OBJS = csv_test.o csv.o
COMMUNITY_OBJS = community_test.o community.o
SEARCH_OBJS = search_test.o search.o
EXTENSION_OBJECT_FILES = $(CSV_OBJS) $(PATH_OBJS) $(COMMUNITY_OBJS) $(SEARCH_OBJS)

GRAPH_OBJS = graph_test.o graph.o node.o
QUEUE_OBJS = queue_test.o queue.o
MATRIX_OBJS = matrix_test.o matrix.o
MAP_OBJS = map_test.o map.o
OBJECT_FILES = $(GRAPH_OBJS) $(QUEUE_OBJS) $(MATRIX_OBJS) $(MAP_OBJS)

# Flags
FLAGS = -lm -lpthread

all: main.o $(OBJECT_FILES) $(EXTENSION_OBJECT_FILES)
	gcc -o $(TARGET) main.o $(OBJECT_FILES) $(EXTENSION_OBJECT_FILES) $(FLAGS)

# extensions off the graph library
csv.o: ../src/csv.c ../src/includes/csv.h
	gcc -c ../src/csv.c

csv_test.o: csv_test.c includes/csv_test.h
	gcc -c csv_test.c

map.o: ../src/map.c ../src/includes/map.h
	gcc -c ../src/map.c

map_test.o: map_test.c includes/map_test.h
	gcc -c map_test.c

path.o: ../src/path.c ../src/includes/path.h
	gcc -c ../src/path.c

path_test.o: path_test.c includes/path_test.h
	gcc -c path_test.c

community.o: ../src/community.c ../src/includes/community.h
	gcc -c ../src/community.c

community_test.o: community_test.c includes/community_test.h
	gcc -c community_test.c

search.o: ../src/search.c ../src/includes/search.h
	gcc -c ../src/search.c

search_test.o: search_test.c includes/search_test.h
	gcc -c search_test.c


# utility files
node.o: ../src/node.c ../src/includes/node.h
	gcc -c ../src/node.c

graph.o: ../src/graph.c ../src/includes/graph.h
	gcc -c ../src/graph.c

graph_test.o: graph_test.c includes/graph_test.h
	gcc -c graph_test.c

queue.o: ../src/queue.c ../src/includes/queue.h
	gcc -c ../src/queue.c

queue_test.o: queue_test.c includes/queue_test.h
	gcc -c queue_test.c

matrix.o: ../src/matrix.c ../src/includes/matrix.h
	gcc -c ../src/matrix.c

matrix_test.o: matrix_test.c includes/matrix_test.h
	gcc -c matrix_test.c

main.o: main.c $(UTILITY_HEADER_FILES) $(EXTENSION_HEADER_FILES)
	gcc -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
