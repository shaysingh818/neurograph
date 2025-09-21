# Feature Extraction

* [Feature Extraction](#Feature%20Extraction)
	* [Community Based](#Community%20Based)


# Feature Community Detection

* Randomly detecting communities in graphs for feature extraction
* Triggers based on user specified queries?



```mermaid
flowchart LR
A[Load Graph] --> B[Community Detection] --> C[Extract Features]
A[Load Graph] <--> D[Reorder Nodes]
D[Reorder Nodes] <--> C[Extract Features]

 ```


# Community Feature Extraction

* Input a comma separated flat file, load into data frame
* Extract all the headers of that file
* Create permutations for all combinations of headers in the file
	* Store the permutations in an array of sets
	* Each permutation are headers used to create a temporary graph
* For each graph created from a permutation
	* Run the community detection algorithm on the graph
	* Count the amount of communities
	* Get the average size of the communities
* Select the headers that create a graph with the largest communities
* Return a list of headers that the user should use for data investigation


# Correlation Matrix

* Input comma separated flat file, load into data frame
* Extract the headers of the of the data frame
* Calculate correlation coefficient