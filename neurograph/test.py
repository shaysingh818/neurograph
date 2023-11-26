import cython
from pprint import pprint
from neurograph.extractors import DataFrame
from neurograph.structures import Matrix

def main():

    # create dataframe
    df = DataFrame("../examples/data/ms_prediction.csv", 10)
    df.subtract(cols=["Patient_ID", "Age"], result="my_sum")
    print(df.map_header("my_sum"))
    # df.sum(cols=["Patient_ID", "Age"], result="my_sum")
    # pprint(df.rows())

    # power_gen_df = DataFrame("../examples/data/power_generation.csv", 10)
    # power_gen_df.subtract(cols=["Deviation", "Actual(MU)"], result="sum")
    # pprint(power_gen_df.rows())

main()
