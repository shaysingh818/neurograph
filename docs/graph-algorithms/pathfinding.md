
# Pathfinding

* Set of pathfinding algorithms to search graphs
* Store output results in data frames
* Control rate of search within graph

## Shortest Path

* Initialize the following variable trackers
	* head node of the adjacency list for the graph
	* distances - array of distances
	* previous - array of previous distances
	* queue - queue to store node values
* Iterate for the amount of vertices in graph
	* If the current iteration is not equal to the start vertex, initialize
		* previous - Max integer
		* distances - Max Integer
* Push start vertex to the front of the queue
* Mark first item of distances as 0 
* Iterate through queue while it's not empty
	* Get the first item of the queue (at the front)
		* Initilaize this value to u
	* Remove it from the queue
	* Grab the head of the current item, index by u
	* Iterate through the neighbors of the head node
		* if the distance with the head index is greater than the distance with the u index plus the head weight
		* Set the distance with the head id index equal to the distance with u index plus the head weight
		* Set the previous distance list with the head id index to u
		* Add head item to the queue
	* Set head to the next item
* Check if end vertex was reached
* If distance with end vertex index is not equal to a maximum integer, return that value from the distances array
* Default to return to 0 if the above steps don't work

## Random Walk

* Grab the head node of the graph using start vertex as index
* Initialize a random seed
* Iterate through graph for n steps
	* Initalize array of neighbors - array is set to size of graph
	* Intitialize a counter variable

## Dijkstra

* Grab node with start vertex from adjacency list
* Allocate slots for storing previous nodes and distances for each node
* Create a queue to store all nodes from graph
* Set all vertices except the start vertex to the max integer
* Push start vertex to the front of the queue
* Distance for start vertex should be set to 0
* Go through all nodes in the queue
* Get the minimum distance and compare distance for head node and current
* Push node back to queue
* Repeat these steps

## Bellman Ford

* Initiate distances with start vertex and all other nodes in graph
* Relax all the edges in the graph (Refer to code)
* Check for negative weight cycles (Refer to code)
* Return the array of current distances from relax and negative weight cycle step
