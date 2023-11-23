import cython
from pprint import pprint
from neurograph.extractors import DataFrame
from neurograph.structures import Matrix

def main():


    # create dataframe
    df = DataFrame("../examples/data/ms_prediction.csv", 10) 
    df.features()

    x = Matrix(df, cols=["Schooling", "Age", "Gender"])
    x.print_mat()

    y = Matrix(df, ["group"])
    y.print_mat()


    



    




main()
