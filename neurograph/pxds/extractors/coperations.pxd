cimport pxds.extractors.cre as re
cimport pxds.extractors.cframe as frame


cdef extern from "../src/extractors/dataframe/includes/operations.h":

    cframe.Frame *add_frame_cols(frame.Frame *frame, void *col1, void *col2); 
    cframe.Frame *subtract_frame_cols(frame.Frame *frame, void *col1, void *col2); 
