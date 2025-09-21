
# Graph Markup Language


* Create graphs using configuration files 
* Define a regular expression that represents the graph markup language
* Allow external database tools to ingest graph configuration files


# Adjacency List Markup (Labels Only)

```
"NODE_1": ("<NODE_1>", "<NODE_1>")
"NODE_1": ("<NODE_1>", "<NODE_1>", "<NODE_2>")
"NODE_1": ("<NODE_1>", "<NODE_1>")
"NODE_1": ("<NODE_1>", "<NODE_1>")
```

* This would be a config if you want to sort by label name
* Should except multi line comments with this syntax: `/* commment */`
* Regular expression contains the following for each line
	* A node is defined by having it's label followed by a colon
	* List of neighbors are surrounded by parenthesis
	* Each element is surrounded by quotations
	* Each element is separated by commas
```
[ID, "NODE_2"]: ([ID, "<NODE_1>"], [ID, "<NODE_1>"])
"NODE_1": ("<NODE_1>", "<NODE_1>", "<NODE_2>")
"NODE_1": ("<NODE_1>", "<NODE_1>")
"NODE_1": ("<NODE_1>", "<NODE_1>")
```


# Matrix Markup

```
rows: <NUMBER>
cols: <NUMBER>

<INT>,<INT>,<INT>
<INT>,<INT>,<INT>
<INT>,<INT>,<INT>
```

* Two regular expressions will be defined since not all lines are the same
* The first regular expression will follow this pattern
	* The rows/cols variable will be defined and have a colon after it
	* The next line can take in any digit except 0
* The second regular expression is for the matrix values
	* Each line is separated by comma values
	* Each element must be a series of digits


# Adjacency List Markup

```
[0,"B"]: ([1,"A",0],[2,"C",0])
[1,"A"]: ([0,"B",0],[2,"C",0],[3,"D",0])
[2,"C"]: ([1,"A",0],[0,"B",0],[4,"E",0])
[3,"D"]: ([1,"A",0])
[4,"E"]: ([2,"C",0])
```

* Weights and id's of nodes are now include in config file
* id is included so calling methods to get unique nodes is not needed
* Regular expression is defined with the following criteria
* Extract integer values or any thing with quotes in between it