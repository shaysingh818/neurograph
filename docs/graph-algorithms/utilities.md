
# Graph Utilities

* [Graph Representation](#Graph%20Representation)
* [Conversions](#Conversions)
* [Data Frame](#Data%20Frame)
	* [Data Frame to Unweighted Graph](#Data%20Frame%20to%20Unweighted%20Graph)
	* [Data Frame to Weighted Graph](#Data%20Frame%20to%20Weighted%20Graph)
* [General Utilities](#General%20Utiltiies)
	* [Get Unique Nodes](#Get%20Unique%20Nodes)
	* [Unique Nodes (File Based)](#Unique%20Nodes%20(File%20Based))
	* [Max Vertex Count](#Max%20Vertex%20Count)
	* [Clear Unused Slots](#Clear%20Unused%20Slots)
* [Serialization](#Serialization)
	* [Serialize Sorted Labels](#Serialize%20Sorted%20Labels)
	* [Serialize Weights, ID's](#Serialize%20Weights,%20ID's)
	* [De Serialization](#De%20Serialization)

# Graph Representation

|Attribute Name| Description|
|---------------|-------------|
|Adjacency list| Reference to the adjacency list structure|
| Matrix | Reference to the matrix structure |
| Map | Hash map representation of graph | 
|Labels| List of labels associated with the corresponding vertices |
| Directed | Boolean to say if graphs relationships are directed|
| Vertice Count | Amount of nodes in the graph | 
| Filename | Optional path to a file for graph serializing/deserializing|

# Conversions

Graph Conversions are used to represent a graph in multiple different formats, like an adjacency list or matrix. We also have the option to speciifc whether it's weighted or not.  These are the conversions to support. 

*  Convert a adjacency list to adjacency matrix
*  Convert an non directed, unweighted adjacency list to a non directed, unweighted matrix
*  Convert a directed, unweighted adjacency list to a directed, unweighted matrix
*  Convert a directed, weighted adjacency list to directed, weighted matrix
*  Convert a adjacency matrix to adjacency list
*  Convert an non directed, unweighted adjacency matrix to a non directed, unweighted list
*  Convert a directed, unweighted adjacency matrix to a directed, unweighted list
*  Convert a directed, weighted adjacency matrix to directed, weighted list


# Data Frame 

* Methods that use data frames to work with graphs
* Convert and exchange data between graphs
* Essential component for getting standard csv data to graphs

## Data Frame to Unweighted Graph

|Parameter Name|Type| Description|
|--------------|-----|------------|
|`frame`|`frame_t`|Instance of data frame structure|
|`cols`|`int*`|Array of cols to select from|
|`size`|`int`|Size of the column selection|
|`directed`|`bool`|Boolean to set graph to directed|

* Pass in instance of data frame, selected column indexes, size and boolean for direction
* Vertex count for graph is based on frame row count times the size specified
* Create instance of unique set data structure, capacity is the vertex count
* Validate graph is not weighted, col index length should be even
* Iterate through items in data frame
* Grab the src and destination labels and add to unique set data structure instance
* Look up the src and destination id from the set data structure instance
* src and dst id's are determined based on the order they come in from the file
* Add node relationship with source, destination and their respective ID's
* Return graph instance

## Data Frame to Weighted Graph

|Parameter Name|Type| Description|
|--------------|-----|------------|
|`frame`|`frame_t`|Instance of data frame structure|
|`cols`|`int*`|Array of cols to select from|
|`size`|`int`|Size of the column selection|
|`directed`|`bool`|Boolean to set graph to directed|

* Pass in instance of data frame, selected column indexes, size and boolean for direction
* Vertex count for graph is based on frame row count times the size specified
* Create instance of unique set data structure, capacity is the vertex count
* Validate graph is not unweighted, col index length should be odd (divisible by 3)
* Iterate through items in data frame
* Grab the src,destination labels and add to unique set data structure instance
* Grab the weight values from the data frame (should be last index in pair of 3)
* Look up the src ,destination and weight id from the set data structure instance
* Add node relationship with src, src_id, dst and dst_id
* Return graph instance

# General Utilities


* General processes/utilities needed in the graph library
* Utilities are methods that aren't specific algorithms in graph theory
* Methods that involve making it easier to work with graph data
* General utilities should be applicable to multiple representations of a graph 

## Get Unique Nodes

|Parameter Name|Type| Description|
|--------------|-----|------------|
|`graph`|`graph_t`|Instance of graph structure|

* Supply the graph structure as a parameter
* Set the capacity of the unique set to be the amount of vertices in the graph
* Iterate through the nodes and it's neighbors
* Add each node to a unique set data structure
* Return the set instance

## Unique Nodes  (File Based)

|Parameter Name|Type| Description|
|--------------|-----|------------|
|`filename`|`char*`|Name of file and path|
|`file_size`|`int`|Buffer size of file|

* Take in a graph markup language file and expected file buffer size
* Open file and allocate buffer size 
* Create instance of set data structure with (sorts by character value)
* Iterate through each line in the file
* Use regular expression to extract nodes
* Add each item from regex to unique sorted set data structure
* Return the instance of the unique set data structure populated

## Max Vertex Count

|Parameter Name|Type| Description|
|--------------|-----|------------|
|`filename`|`char*`|Name of file and path|
|`file_size`|`int`|Buffer size of file|

* Finds the max vertex count in a markup file based on node id's
* Supply markup file and buffer size as parameters
* Assign a variable as max_vertex_count and assign to 0
* Iterate through each line in the file
* Extract the node label, id and weight using a regular expression
* Check if the id is greater or less then the max_vertex_count
* If the id is greater than the max_vertex_count, set it to the current id
* Return max vertex count

## Detect Unused Slots

|Parameter Name|Type| Description|
|--------------|-----|------------|
|`graph`|`graph_t`|Instance of graph structure|

* Keep track of the last indice that has had neighbors
* Iterate from the last node id in the graph backwards
* If a node is used, set the last used indice to that current node
* Calculate and store the remainder
* Remainder is the amount of vertices minus the last used indice
* Store the new size as the vertice subtracted from the remainder
* Resize the adjacency list (only supported method for now)
* Return true for indication of success

# Serialization 

* Methods that work with graph markup files
* Serialize and de serialize content from in memory graphs
* Create configuration files for graph unit tests

## Graph Markup Serialization ( Sorted Labels)

* Supply in file name and selected file buffer size
* File name only takes in string values as nodes and neighbors
* Call get unique graph nodes (file based method), store in set data structure
* Create graph instance and vertex count is the count of the set data structure
* Iterate through each line in the file
* Extract node and it's neighbors using the regular expression
* Get the src, src_id, dst, dst_id using the get_value id method from the set data structure
* Add the src to dst using all the fields to the graph
* return the graph data structure instance

## Graph Markup Serialization (Weights, ID)

* Supply in file name and selected buffer size
* Markup files takes in labels, id's and weights.
* Id's in markup file must be in incremental order and cannot exceed vertex count
* Call method to find max vertex count by scanning all graph node id's
* Create graph instance and supply a vertex count (based on max vertex count)
* Iterate through each line of the markup file
* Extract node id, label and weight and it's neighbors using regular expression
* Grab id, label and weight for source destination, extract from tokens in regular expression
* Add the node relationship using all the attributes
* return the graph data structure instance

## Graph Markup De Serialization

* Supply in graph instance and filename to export to
* Open file and allocate expected file size
* Iterate through graph instance's nodes and neighbors
* Check if there are quotes in the label nodes or neighbors and remove them
* Format string for graphs node and it's neighbor
* Write format string to file and proceed to next line
* Return file instance when done