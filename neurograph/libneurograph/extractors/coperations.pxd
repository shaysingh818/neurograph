cimport libneurograph.extractors.cre as re
cimport libneurograph.extractors.cframe as frame

cdef extern from "<neurograph/extractors/dataframe/includes/operations.h>":

    frame.Frame *add_frame_cols(
        frame.Frame *frame, 
        char *col1, 
        char *col2, 
        char *result_col
    ) 

    frame.Frame *subtract_frame_cols(
        frame.Frame *frame, 
        char *col1, 
        char *col2, 
        char *result_col
    )
