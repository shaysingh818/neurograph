cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix
from tabulate import tabulate

cdef class DataFrame:

    def __cinit__(self):
        self.frame = NULL

    def __init__(self, filepath, row_limit):
        encoded_filepath = filepath.encode("utf-8")
        self.frame = fr.dataframe(encoded_filepath, 1024, row_limit, ",")
        self.selected_cols = ll.init_array()
        if self.frame is NULL:
            raise MemoryError()
 
    def features(self):
        fr.print_cols(self.frame)

    def view_selected_features(self):
        ll.print_array(self.selected_cols)

    def props(self):
        return {
            "buffer_size": self.frame.buffer_size,
            "header_count": self.frame.header_count,
            "current_row": self.frame.curr_row,
            "row_count": self.frame.row_count,
            "row_limit": self.frame.row_limit,
            "status": bool(self.frame.status),
            "filename": bytearray(self.frame.filename).decode("utf-8"),
        }

    def get_headers(self):
        header_list = []
        for i in range(self.frame.header_count):
            obj = {
                "index": self.frame.headers.items[i].id,
                "name": bytearray(self.frame.headers.items[i].label).decode("utf-8") 
            }
            header_list.append(obj)
        return header_list

    def rows(self):
        result_dict = {}
        for i in range(self.frame.header_count):
            header = bytearray(self.frame.headers.items[i].label)
            key = header.decode('utf-8')
            result_dict[key] = []
            rows = fr.get_row_key(self.frame, header)
            for item in range(self.frame.row_limit):
                value = bytearray(rows[item].value)
                result_dict[key].append(value.decode('utf-8'))
        return result_dict

    def html(self):
        rows_dict = self.rows()
        table = [dict(zip(rows_dict, row)) for row in zip(*rows_dict.values())]
        html_table = tabulate(table, tablefmt='html', headers='keys')
        return html_table


