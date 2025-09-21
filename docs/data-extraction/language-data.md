# Language Data

* Convert raw text data to knowledge graphs 
* Nodes in graphs are nouns (people, places, things)
* Edges in the graph are action words (Adjectives)


# Knowledge Graph Interpretation 

* Data inputs can ether be a raw text file or comma separated file
* If the input is a csv file, load it to data frame and choose text column
* If it's a raw text file, load the data into a buffer


# Regular Expression

* Word extraction: Split by spaces in characters
* Sentence Extraction: Split the characters by periods or commas
* For paragraphs, choose a specific amount of sentences to extract from expression


# Word Frequency

* Extract a corpus of text
* Iterate through the corpus and store the frequencies of the words that occur
* Occurrences should be stored in hash map data structure