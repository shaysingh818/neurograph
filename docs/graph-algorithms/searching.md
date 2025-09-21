# Searching

* Optimize algorithms to search graph data structures efficiently
* Create tools to benchmark searching algorithm performance
* Invent a searching algorithm

## Depth First Search

* Grab the root node in the adjacency list
* Store the root node in a temporary value
* Push root node to queue (queue is parameter to method)
* Iterate through the temporary values neighbors
* If the neighbor has been visited, recursively call the method
* Return once done

## Breath First Search

* Initiate 2 queues, one for graph nodes, one for visited nodes
* Iterate through the queue (while it's not empty)
* Get current item in the queue
* Pop element from the queue and add to visited queue
* Add non visited neighbor nodes to the queue
* Return results from visited queue results