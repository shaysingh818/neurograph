import frame as ng
import cython
from pprint import pprint

def main():

    # create dataframe
    df = ng.DataFrame(b"../examples/data/ms_prediction.csv", 10)
    pprint(df.props())    
    
    # # select features to work with 
    # df.features()
    # df.select_cols(cols=[
    #     "Gender",
    #     "Age",
    #     "Schooling"
    # ])

    # print("Show selected features\n")
    # df.view_selected_features()
    # print("\n")
    # df.to_matrix()



main()