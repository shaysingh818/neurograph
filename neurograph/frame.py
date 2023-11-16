
import cython
from tabulate import tabulate
from cython.cimports.pxds.extractors import cframe, coperations
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
        encoded_filepath = filepath.encode("utf-8")
        self._c_frame = cframe.dataframe(encoded_filepath, 1024, row_limit, ",")
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
    def add_cols(self, col1: str, col2: str):
        results = coperations.add_frame_cols(
            self._c_frame,
            col1.encode('utf-8'), col2.encode('utf-8')
        )

    def subtract_cols(self, col1: str, col2: str):
        results = coperations.subtract_frame_cols(
            self._c_frame,
            col1.encode('utf-8'), col2.encode('utf-8')
        )

    def get_headers(self):
        header_list = []
        for i in range(self._c_frame.header_count):
            obj = {
                "index": self._c_frame.headers.items[i].id,
                "name": bytearray(self._c_frame.headers.items[i].label).decode("utf-8") 
            }
            header_list.append(obj)
        return header_list

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
    
    def rows(self):
        result_dict = {}
        for i in range(self._c_frame.header_count):
            header = bytearray(self._c_frame.headers.items[i].label)
            key = header.decode('utf-8')
            result_dict[key] = []
            rows = cframe.get_row_key(self._c_frame, header)
            for item in range(self._c_frame.row_limit):
                value = bytearray(rows[item].value)
                result_dict[key].append(value.decode('utf-8'))
        return result_dict
    

    def html(self):
        rows_dict = self.rows()
        table = [dict(zip(rows_dict, row)) for row in zip(*rows_dict.values())]
        html_table = tabulate(table, tablefmt='html', headers='keys')
        return html_table



