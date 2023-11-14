
import cython
from cython.cimports.pxds.extractors import cframe, cutils
from cython.cimports.pxds.data_structures import (
    cmatrix, 
    cll
)

@cython.cclass
class DataFrame:

    _c_frame: cython.pointer(cframe.Frame)
    _c_selected_cols: cython.pointer(cll.Array)
    _c_matrix: cython.pointer(cmatrix.Matrix)

    def __cinit__(self, filepath, row_limit):
        self._c_frame = cframe.dataframe(filepath, 1024, row_limit, ",")
        self._c_selected_cols = cll.init_array()
        if self._c_frame is cython.NULL:
            raise MemoryError()
         
    def features(self):
        cframe.print_cols(self._c_frame)

    def view_selected_features(self):
        cll.print_array(self._c_selected_cols)

    def to_matrix(self):
        self._c_matrix = cframe.frame_to_matrix(
            self._c_frame, 
            self._c_selected_cols
        )
        cmatrix.print_vec(self._c_matrix)

    def select_cols(self, cols):
        for item in cols:
            cll.insert_char(
                self._c_selected_cols, 
                bytes(item, encoding="utf8")
            )

    # operations
    def add_cols(self):
        pass

    def subtract_cols(self):
        pass

    def props(self):
        return {
            "buffer_size": self._c_frame.buffer_size,
            "header_count": self._c_frame.header_count,
            "current_row": self._c_frame.curr_row,
            "row_count": self._c_frame.row_count,
            "row_limit": self._c_frame.row_limit,
            "status": bool(self._c_frame.status),
            "filename": bytearray(self._c_frame.filename).decode("utf-8"),
        } 


