cdef extern from "<neurograph/extractors/dataframe/includes/utils.h>":

    void end_line_terminate(char *buffer)
    void remove_character(char *buffer, char remove) 
    int count_lines(char *filename, int file_size)