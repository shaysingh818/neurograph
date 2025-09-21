# Adjacency Matrix

* Methods for creating a matrix based graph
* Uses the regular matrix structure with set data structure
* Has the same methods as adjacency list with different implementation


| Field Name | Description                                                  |     |
| ---------- | ------------------------------------------------------------ | --- |
| V          | Amount of vertices in graph                                  |     |
| E          | Number of edges                                              |     |
| Visited    | Array of indices corresponding to visited nodes              |     |
| Used       | Amount of array slots used in the matrix                     |     |
| Err        | Status flag for adjacency matrix                             |     |
| Weights    | Matrix that stores the weights of the relationships in graph |     |
| items      | Set data structure containing nodes of graph                 |     |


## Initialize

* Create instance of adjacency list structure
* Allocate edges, visited, used and items arrays to the size of the vertices
* Set directed, error status and the vertice and edge counts
* Allocate the node lists, size is the amount of vertices
* Allocate edge list, size is the amount of edges
* Iterate for the amount of vertices set in the graph, set used and visited to 0


## Add Node

* Provide set data structure instance, source and destination with their id's and weight
* Keep track of the source
* Get the directed and non directed index
* Directed index is source id times the number of vertices plus destination id
* Non directed is destination id times vertices plus source id
* If the graph is directed
	* Add destination item to the directed index of the items array
	* Set the weight matrix to the weight value using the directed index
* In the case that the graph is not directed
	* Set the set items to both the non directed and directed index with src and dst
	* Set the weight matrix to the non directed and directed matrix with weight value
