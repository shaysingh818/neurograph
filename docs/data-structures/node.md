
# Node

* Module for representing generic nodes in a graph
* Multiple node types can be inherited with this new implementation
* Base node attribute will contain the id for mapping to adjacency list index

## Node Type

| Attribute | Description |
| ---- | ---- |
| `node` | General node value structure for testing graph algorithms |
| `variable` | Variable structure for creating computation graphs |
* Structure used for storing all generic types that a node can have
* Any potential structure that will be part of a graph can go here

## Node

| Attribute | Description |
| ---- | ---- |
| `id` | Numerical Identifier for node object |
| `node_type` | Structure that refers to generic node types |
| `next` | Pointer to next node for adjacency list representation |
| `left` | Left pointer for set implementation |
| `right` | Right pointer for set implementation |
* General node structure that will be used for all graph representations
* Temporarily used for representing data structure values


## Node Value

| Attribute | Description |
| ---- | ---- |
| `weight` | Weight value to represent how close nodes are to eachother |
| `counter` | Used in certain algorithms for counting amount of times a node was visited |
| `label` | Used for identifying a node by character label instead of id |

* This node value is used for general graph algorithms and demonstration purpose
* The node value structure is the default for testing out graph algorithms
* It inherits the base node type

## Variable

| Attribute | Description |
| ---- | ---- |
| `label` | Name of operation being performed on inputs |
| `output` | Generic value stored with variable structure |
| `upstream_value` | Gradients passed backward from other nodes |
| `forward` | Operation to perform on inputs during forward pass |
| `backward` | Operation to perform on inputs during backward pass |
| `inputs` | Amount of inputs if the variable is also an operation |
* This structure is meant for creating nodes in a computation graph
* Each variable node uses it's neighbors as inputs

## Edge

| Attribute | Description |
| ---- | ---- |
| `src` | Source node value |
| `dst` | Destination node value |
| `weight` | Weight that represents how closely related the nodes are |
* This is used for some searching/path finding
