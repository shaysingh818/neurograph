cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.ctable as table
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.data_structures.cset as set
cimport libneurograph.extractors.cre as re
cimport libneurograph.extractors.cutils as utils 

cdef extern from "<extractors/dataframe/includes/frame.h>":

    struct RowValue:
        size_t value_size
        int index
        char *value

    struct Frame:
        int buffer_size
        int header_count
        int curr_row
        int row_count
        int row_limit
        char *filename
        char *file_buffer
        char *delimeter
        bint status
        ll.Array *headers
        table.BinTable *frame

    ctypedef Frame frame_t


    Frame* create_frame(
        char *filepath, 
        int buffer_size, 
        int row_limit, 
        char *delimiter
    )

    Frame* dataframe(
        char *filepath, 
        int buffer_size, 
        int row_limit,
        char *delimiter
    )

    RowValue *init_row_value(int index, char *value)

    matrix.Matrix *frame_to_matrix(Frame *frame, ll.Array *cols)

    void frame_matrix(Frame *frame, ll.Array *cols, matrix.Matrix *m) 

    void extract_headers(Frame *frame)

    void init_rows(Frame *frame)

    void print_cols(Frame *frame)

    void print_rows(Frame *frame)

    void select_cols(Frame *frame, void **headers)

    void drop_cols(Frame *frame, ll.Array *cols)

    char **get_row_key(frame_t *frame, char *key) 