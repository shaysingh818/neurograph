import frame

def main():

    # create dataframe
    df = frame.DataFrame(b"../examples/data/ms_prediction.csv", 10)
    df.features()
    
    # select features to work with 
    df.select_cols(cols=[
        "Gender",
        "Age",
        "Schooling"
    ])

    print("Show selected features\n")
    df.view_selected_features()
    print("\n")
    df.to_matrix()



main()