cimport libneurograph.data_structures.clist as ll

cdef extern from "<extractors/dataframe/includes/re.h>":

    struct Tokens:
        char **tokens
        int result_size

    void match_tokens_to_pattern(ll.Array *tokens, char *pattern)

    Tokens *match_single(char *buffer, char *pattern)

    ll.Array *match_pattern_split(char *buffer, char *pattern)

    ll.Array *match_delimeter_file(char *line, char *delimiter)

    void remove_character(char *test_string, char char_to_remove)
