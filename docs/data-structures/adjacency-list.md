
# Adjacency List

* Used for representing connections in a graph 
* Makes use of linked lists and standard arrays

| Field Name | Description |
| ---- | ---- |
| `v` | Amount of vertices in graph |
| `e` | Number of edges in graph |
| `visited` | Array of indices corresponding to visited nodes |
| `directed` | Flag to add directed relationships to graph nodes |
| `err` | Status for adjacency list |
| `items` | Node list that takes in inherited node types |

## Initialize 

* Create instance of adjacency list structure
* Allocate edges, visited, used and items arrays to the size of the vertices
* Set directed, error status and the vertice and edge counts
* Allocate the node lists, size is the amount of vertices
* Allocate edge list, size is the amount of edges
* Iterate for the amount of vertices set in the graph, set used and visited to 0
* Return instance of adjacency list

## Add Node

* Take in src and destination with their respective ID's and weights
* Create a null node called "check" to assign temp node values
* Create a new node instance for the destination node
* Mark the first "used" slot as 1 with the destination ID as the index
* Check if source id head in node list is null
* If it is, set the new node instance next pointer to the source id head pointer
* Otherwise, set the src id head pointer to the temp check node
* Iterate through the linked list using check pointer
* Once the end of the list is reached, set the new node instance to the check node
* For non directed, same steps but create new instance for source and 
* iterate with dst pointer instead of src_id for check pointer

## Get Node By Id

* Provide adjacency list instance and id to search for
* Iterate through each vertex in the graph
* Grab the head of the vertex node list
* Iterate through the linked list until the head id matches the item to search for
* return the head id
* If no search_id is found, return blank node instance

## Transpose Items 

* Provide in adjacency list and adjacency list instance to reverse
* Iterate through the vertices in the graph
* Grab the head for each vertex index
* Go through each neighbor by looping in the linked list
* Grab the src node by searching for the node id with the head id as a parameter
* Grab the dst node by searching the node id with the vertex index as a parameter
* Add the relationship, head id is src id and i is destination id
* Return reverse instance of the adjacency list

## Resize List

* Provide adjacency list instance and new size
* Set the vertices and edge count in graph instance to the new size
* Reallocate the edges array to the new size
* Reallocate the items array to the new size

## Print Items

* Iterate through the vertices in the graph
* Print out each vertex before printing it's neighbors
* Grab the head for each vertex index
* Go through each neighbor by looping in the linked list
* Print out each item in the linked list

