# Centrality

* Algorithms for detecting clusters/communities
* Good utility for feature extraction for datasets

## Degree Centrality

* Count the amount of neighbors for each node
* Return a list of neighbor counts
* Return value from list with the highest amount of neighbors

## Closeness Centrality

* Provide vertex for finding closeness centrality
* Initialize a sum to 0
* Iterate through each vertex in the graph
* Get the shortest path from the current node and the vertex provided
* Add the result of the shortest path to the sum
* Return value equal to $1/sum$ where sum is the original initlaized value