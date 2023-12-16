cimport libneurograph.extractors.cframe as fr
cimport libneurograph.extractors.coperations as ops
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.data_structures.ctable as table
from neurograph.structures cimport Matrix
from tabulate import tabulate
import sys

cdef class DataFrame:

    def __cinit__(self):
        self.frame = NULL

    def __init__(self, filepath: str, row_limit: int, memory_size=1024):
        encoded_filepath = filepath.encode("utf-8")
        self.frame = fr.dataframe(encoded_filepath,memory_size, row_limit, ",")
        self.selected_cols = ll.init_array()
        if self.frame is NULL:
            raise MemoryError()

        # set general attributes
        self.filename = filepath
        self.row_limit = row_limit
 
    def features(self):
        fr.print_cols(self.frame)

    def view_selected_features(self):
        ll.print_array(self.selected_cols)

    def header_count(self):
        return self.frame.header_count

    def props(self):
        return {
            "buffer_size": self.frame.buffer_size,
            "header_count": self.frame.header_count,
            "current_row": self.frame.curr_row,
            "row_count": self.frame.row_count,
            "row_limit": self.frame.row_limit,
            "status": bool(self.frame.status),
            "filename": self.frame.filename.decode("utf-8"),
        }

    def headers(self):
        header_list = []
        for i in range(self.frame.header_count):
            obj = {
                "index": self.frame.headers.items[i].id,
                "name": self.frame.headers.items[i].label.decode("utf-8") 
            }
            header_list.append(obj)
        return header_list

    def cols(self):
        cols = []
        for i in range(self.frame.header_count):
            value = self.frame.headers.items[i].label
            cols.append(value.decode('utf-8'))
        return cols

    def drop_cols(self, cols: list):
        temp_array = ll.init_array()
        for item in cols:
            ll.insert_char(
                temp_array,
                bytes(item, encoding='utf-8')
            )
        fr.drop_cols(self.frame, temp_array)

    def rows(self):
        result_dict = {}
        columns = self.cols()
        for item in columns:
            result_dict[item] = []
            for thing in self.map_header(item):
                result_dict[item].append(thing)
        return result_dict

    def to_matrix(self, cols: list):
        selected_cols = ll.init_array()
        for item in cols:
            ll.insert_char(selected_cols, bytes(item, encoding="utf8"))
 
        matrix = Matrix(self.row_limit, len(cols))
        matrix.mat = fr.frame_to_matrix(self.frame, selected_cols)
        return matrix

    def html(self):
        rows_dict = self.rows()
        table = [dict(zip(rows_dict, row)) for row in zip(*rows_dict.values())]
        html_table = tabulate(table, tablefmt='html', headers='keys')
        return html_table

    def sum(self, cols: list , result: str):

        if len(cols) > 2:
            print("Neurograph only supports 2 columns for ops")
            sys.exit(0)

        col1_encode = cols[0].encode('utf-8')
        col2_encode = cols[1].encode('utf-8')
        ops.add_frame_cols(
            self.frame,
            col1_encode, 
            col2_encode,
            result.encode('utf-8')
        )

    def subtract(self, cols: list, result: str):

        if len(cols) > 2:
            print("Neurograph only supports 2 columns for ops")
            sys.exit(0)

        col1_encode = cols[0].encode('utf-8')
        col2_encode = cols[1].encode('utf-8')
        ops.subtract_frame_cols(
            self.frame,
            col1_encode, 
            col2_encode,
            result.encode('utf-8')
        )

    def map_debug(self):
        table.print_table(self.frame.frame)

    def map_header(self, col: str):
        results = []
        header = col.encode('utf-8')
        rows = fr.get_row_key(self.frame, header)
        for item in range(self.frame.row_limit):
            value = rows[item]
            my_val = value.decode('utf-8')
            results.append(str(my_val))
        return results



