
# Regular Expressions 

* Critical needed component for data extraction and manipulation
* Will be used to create our graph markup language
* Expressions are needed for parsing delimiter file formats and custom languages

# Match Single

* Provide character buffer and regular expression pattern
* Compile the regular expression and check for errors
* iterate through the character buffer with the match pattern
* Allocate space for end and start match
* Gather the token results from the end and start match
* Add the token to the array based set
* Add the end match to the buffer (pointer arithmetic)
* Compare the match with another sub string
* If the compare is true, break out of the loop

## Replace Character 

* Provide a buffer, the string and the portion to replace (with regex pattern)
* Set string equal to character pointer
* Start with a do statement, within the statement
* while the character pointer is equal to the character to remove
* Increment the character pointer  (arithmetic)
* `while(*test_string++ = *d++)`