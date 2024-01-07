import os
import cython
from pprint import pprint
from neurograph.structures import ndarray
from itertools import chain

def main():

    x = ndarray(shape=[4, 3], values=[
        [0,0,0],
        [2,2,2],
        [2,2,2],
        [4,4,4]
    ])
    y = ndarray(shape=[1, 3], values=[1,1,1])
    x.scale_add(y)
        








    

main()

