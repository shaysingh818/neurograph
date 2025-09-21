
# Community Detection 

* Algorithms for detecting clusters in graphs
* Utility for feature extraction built off these algorithms

## Kosaraju

* Perform depth first search on adjacency list graph
	* Push depth first search results to a queue
* Transpose the graph based on the depth first search results
* Perform depth first search on the transposed graph
	* Push depth first search results to a queue
* Mark all the transpose nodes as un-visited 
* Allocate space for community results
* Iterate through queue while it's not empty
	* Grab item from the front of the queue and remove it
	* If the transpose item was not visited
	* Perform a depth first search and store results in a temp queue
	* Get the results from the queue and add it to communities result

## Label Propagation

* Perform a depth first search on the graph
* Export the node order from the depth first search to a queue
* Go through each node for the results in the queue
	* Get each nodes neighbors with it's labels
	* Add the label and it's the amount of times it was inserted to a unique set
* Choose the label where it has the highest insert count on the set
* Assign the current the node with the highest occurring label


## Triangle Count Clustering Coefficient

* Triangle - Set of three nodes where each node has a relationship to all nodes
* Clustering coefficient can be found by the following steps
	* Multiplying the number of triangles passing through the node by two
	* Dividing that number by the maximum number of relationships in the group