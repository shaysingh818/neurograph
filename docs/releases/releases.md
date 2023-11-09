## V 0.1.0
* Support CSV graph ingestion for the following graph representations
    * Weighted/Unweighted
    * Added parameters for directed or non-directed
* Be able to represent graphs abstractly using the following structures
    * Adjacency List (Weighted, Unweighted, Directed, Un Directed)
    * Adjacency Matrix (Weighted, Unweighted, Directed, Un Directed)
* Ability to convert graphs between different structural representations
    * Adjacency Matrix → Adjacency List
    * Adjacency List → Adjacency Matrix
* Support feature(header) extraction of csv files.
* Generate unique character labels for each node that is created in any type of graph representation
* Fixed initial memory leaks
	* Added compilation tasks for checking memory leaks
* Graphs should have these algorithms implemented.
    * Depth First Search (Searching)
    * Breath First Search (Searching)
    * Bellman Ford (Path finding)
    * Unweighted Random Walk (Path finding)
    * Degree Centrality (Centrality Algorithms)
    * Strongly connected components (Community Detection)

## V 0.2.0
* Allow relative path access for shared object file
* Add remaining test cases for matrice library and refactor
* Refactored Matrice library
* Supporting these matrice graph algorithms
	* Dijkstras (shortest path)
	* Random Walk (Unweighted)
	* Degree Centrality
* Graph representation algorithms
	* Closeness Centrality
	* Dijkstras
	* Shortest Path 
* Fix segmentation fault for `csv_to_graph` method
* Fix memory leaks in csv and graph library


## V 0.3.0
* Community detection
	* Label Propagation
	* Method for labeling nodes
* Added Neural Network with backpropagation algorithm
	* Added module for layers, network and used matrice library
* Refactor modules into separate categories
	* Module for deep learning research
	* Created module for graph theory algorithms
	* Added data extraction and structures module
* New operations added for matrix library
	* Matrix multiplication
	* Scalar value multiplication
	* Raise matrix to a power 

## V 0.4.0

* Release structure has features covered for each category/module of neurograph
* Categories are separated based on
	* Data Structures
	* Extraction
	* Graph Library
	* User interface
	* Deep Learning

### Data Structures
* Save and load model parameters
	* Integrate these functions with neural network library
* Finish all unit tests for matrice library 
* Implement a unique set data structure (tree based approach)

### Data Extraction
* Redesign CSV reading and keep track of header and column counts
	* Rewrite frame to graph conversion
* Create module for regular expressions
	* Single match
* Data frame to graph conversion

### Deep Learning
* Create Computational graph for back propagation
* Create network with multiple hidden layers

### Graph Library
* Community detection
	* Label Propagation (Iterative)
	* Works with up to 2 specific label classes currently
* Add general matrix structure as part of the matrix graph representation
* Triangle count

### User Interface
* Expose these functionalities from the graph library
	* Searching algorithms (DFS, BFS)
	* Path Finding (Shortest Path, Dijkstra, Weighted Random Walk)
* Expose these functions from the queue library
	* Initialization
	* Push, Pop and printing queue values
* Demonstrate these in a jupyter notebook

### Fixes and Improvements
* Documented steps for all graph theory algorithms 
* Cleaned up makefiles 
	* Removed repetitive commands in the build process
	* Making use of wildcards for header files
* Ditched the csv library 
	* Replaced with generic data frame library


## V 0.5.0


### Data Structures

* Implement a hash map library 
	* Create POC, avoid collisions at all costs
	* Throw exceptions for key lookup that don't exist
* Improvement and fix for the adjacency list data structure
	* Detect unused slots in the graph 
	* Don't allocate more nodes that aren't needed for both unweighted, weighted and directed/un-directed graphs
	* Use array of pointers for node_list structure, use arrow deference for head pointer
* Matrix library
	* Add method for getting columns of matrix `to_cols`
	* Allow option for batching a matrix and selecting a certain amount or rows

### Data Extraction 

* Add hash map as attribute for data frame
	* Replicate similar methods for getting cols and rows
* Create a prototype of GML (graph markup language)
	* Create a regular expression for parsing this type of file format
	* Create an interpreter that can serialize files
	* Will not do weighted graphs in this version

### Deep Learning

* Refactored computation graph to forward and backward all node types
* Added refactored computation graph representation to network module

### Graph Library

* Make all random walk methods use the walk structure 
	* Easier to use on the python front end
* Create general graph structure that makes use of data structures
	* Include the adjacency list and matrices as inherited attributes
	* Add attribute for keeping track of labeled nodes
* Label propagation with multiple classes
	* Should work with more than two labels
	* Discovered that graph markup serialization doesn't work here



## V 0.6.0


### Data Structures

* Create an array based implementation for the set data structure
	* Needs to handle whether it's only looking for unique character or integer values
	* Array should resize dynamically
* Replace code for generating unique node ID's with set implementation

### Graph Library 

* Use asserts for the graph library unit tests
	* Remove repetitive if statements 
* Thoroughly test serialization of graph markup language files
	* Allow entries for directed and non directed graphs
	* Replicate results for similar graphs in depth and breadth first search test cases
	* De-Serialize in memory graphs to markup files
	* Add labels and weights entry in graph markup files
* Create a shared interface that can be applied for both matrix and list represented graphs
	* Shared method for adding nodes
	* Printing out nodes and relationships in a graph
	* Serializing and de-seralizing to markup files
* Migrate all matrice graph methods to adjacency matrix structure

### Deep Learning 

* Read/learn about convolutional neural networks
	* Program a convolution operation for a layer

### Remove

* Eliminate unique linked list implementation
	* Replace existing use cases with the hash set data structure
	* Use hash map with out application key value
* Remove item structure from queue
	* It's redundant, replace with the node structure instead

### General Issues

* De serializing graphs doesn't fully work as expected
	* Labels that have quotes within them won't be written to the file
	* This is due to the fact that the regex extracts values between the quotes
	* Need to remove quotes from label nodes and neighbors during serialization process


## V 0.7.0

### Deep Learning

* Refactored computation graph to work on operation level
* Created methods for arithmetic and basic matrix operations
* Defined general methods for operations backward and forward pass
* Created general definition of a `value` in the computation graph
* Flushed out logic for how loss functions will be added to computation graph
* Created general union abstraction around layer types for neural nets
* Implemented basic multi layer perceptron with newly refactored computation graph
* Added layer implementations for activation and linear concepts
* Refactored neural network library
* Added network methods for training and adding layers

### Graph Library 

* Added integration tests for GMUL file interpretation

### Extractors

* Added row limit for data frame structure
* Integration tests for how many rows a data frame can load

### Pipeline

* Refactored pipeline workflow
* Separated build and test steps for core package
* Provided binaries in commit history

## V 0.8.0

### Data Structures

* Create array data structure with reallocation logic

### Extractors

* Frame to matrix conversion for training models
* Handle frame row limit counts greater than the rows in the file itself
* Handle blank values in csv file with regex
* Refactor the regex library (based on handling blank values)
* Refactor unit tests to test each method of the frame library (be more thorough)

### Deep Learning

* Add batch size training for frames in Neural Net training
* Train models using selected columns for data frame
* Save and load trained models for neural nets
* Train on row by by row basis instead of feeding the entire matrix
* Trained sample model on iris dataset