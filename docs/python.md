# Python Library

Neurograph was originally going to have python support in the public release. After finishing the first initial version of the core library in C, it was decided that far more improvements need to be made to the C library before creating a usable python wrapper around it. 

## Why It's Not Support Yet

* Memory Corruption Issues with Cython and C Library
* C Library still needs more performance tuning
* Core library hasn't been used for any serious modeling yet
* Not enough features/algorithms shipped


## Current State

While Python support is not publicly available, there was work done for laying out the shell of how cython would interact with the C library. Sample of the wrapper files can be found [here](https://github.com/shaysingh818/Neurograph/tree/master/neurograph). When running the `main.py` file, you'll notice some memory corruption or double free issues.  