cimport pxds.cll
cimport pxds.cmap
cimport pxds.cmatrix
cimport pxds.cset


cdef extern from "../src/extractors/includes/frame.h":

    struct RowValue:
        size_t value_size
        int index
        char *value

    struct Header:
        int index
        int values_amount
        size_t name_size
        RowValue **values

    struct Frame:
        int buffer_size
        int header_count
        int current_row
        int row_count
        int row_limit
        char *filename
        char *file_buffer
        char *delimeter
        bint status
        Header **headers
        pxds.cmap.HashTable *map

    ctypedef Frame frame_t

    frame_t* init_frame(char *filepath, int buffer_size, int row_limit)
    Frame* create_frame(char *filepath, int buffer_size, int row_limit)
    Frame* dataframe(char *filepath, int buffer_size, int row_limit)

    void extract_frame_headers(Frame *frame)
    void init_frame_rows_regex(Frame *frame)
    void init_frame_map(Frame *frame)

    pxds.cll.Array *match_delimeter_file(char *line, char *delimiter)
    pxds.cmatrix.Matrix *frame_to_mat(Frame *frame, pxds.cll.Array *headers)

    void allocate_frame_headers(Frame *frame, pxds.cll.Array *row_values);
    void copy_row_values(Frame *Frame, pxds.cll.Array *row_values);
    void allocate_header_rows(Frame *frame);
    int match_header(Frame *frame, char *header_key);

    void f_cols(Frame *frame);
    void f_rows(Frame *frame, Header *header);

    void end_line_terminate(char *buffer);
    int count_lines(char *filename, int file_size);
