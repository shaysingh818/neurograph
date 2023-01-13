# Diffusion
Diffusion is a feature extraction tool for building machine learning models using graphs. The purpose of this library is to utilize concepts from graph theory to allow developers to build models that provide valuable insights about their data. Using concepts from graph theory, developers will have the ability to visualize intriguing relationships in data sets, model dynamic systems and create a starting point for building a model. While there are many deep learning and alternate machine learning libraries out there, the purpose of this library is to show how valuable insights can be derived from simple graph algorithms. This is also provides graph algorithms that the popular graph library “Neo4j” does not have.  


## Compiling the source
cd into the src directory and run the makefile
```
make
```
### Expected compilation output
```
gcc -c main.c
gcc -c graph.c
gcc -c matrix.c
gcc -c queue.c
gcc -c node.c
gcc -c path.c
gcc -c search.c
gcc -c community.c
gcc -o ../target/diffusion main.o graph.o matrix.o queue.o node.o path.o search.o community.o -lm -lpthread
```

## Compiling the test cases
cd into the test directory and run the makefile
```
make
```

## Expected test compilation output
```
gcc -c main.c
gcc -c graph_test.c
gcc -c ../src/graph.c
gcc -c ../src/node.c
gcc -c queue_test.c
gcc -c ../src/queue.c
gcc -c matrix_test.c
gcc -c ../src/matrix.c
gcc -c path_test.c
gcc -c ../src/path.c
gcc -c community_test.c
gcc -c ../src/community.c
gcc -c search_test.c
gcc -c ../src/search.c
gcc -o ../target/unit_test main.o graph_test.o graph.o node.o queue_test.o queue.o matrix_test.o matrix.o path_test.o path.o community_test.o community.o search_test.o search.o -lm -lpthread
```

## Running the test cases
cd into the ```/target``` directory and run the ```./unit_test``` binary

```
./unit_test
```

## Expected test case results
```
queue_test.c::test_init_queue... PASSED
queue_test.c::test_pop_queue... PASSED
matrix_test.c::test_init_matrix... PASSED
graph_test.c::test_adjacency_list... PASSED
graph_test.c::test_transpose_adj_list... PASSED
graph_test.c::test_weighted_adjacency_list... PASSED
graph_test.c::test_to_matrix... PASSED
graph_test.c::test_to_directed_matrix... PASSED
graph_test.c::test_to_weighted_matrix... PASSED
graph_test.c::test_to_directed_weighted_matrix... PASSED
search_test.c::test_bfs_one... PASSED
search_test.c::test_bfs_two...  PASSED
search_test.c::test_dfs_one...  PASSED
path_test.c::test_bellman_ford...  PASSED
path_test.c::test_random_walk...  PASSED
path_test.c::test_random_walk::step_equal...  PASSED
path_test.c::test_weighted_random_walk::sum_path...  PASSED
community_test.c::test_degree_centrality...  PASSED
community_test.c::test_weighted_degree_centrality...  PASSED
community_test.c::test_kosaraju...  PASSED
```






