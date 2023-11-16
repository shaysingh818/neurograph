from setuptools import setup
from Cython.Build import cythonize
from distutils.extension import Extension


# # C Extension
# extensions = [
#     Extension(
#         "frame",  # Change this to match your package and module name
#         sources=["frame.py"],  # Use the correct path to your Cython source file
#     ),
# ]

# setup(
#     name='neurograph',
#     version='0.8.0',
#     description='Graph Neural Network Library',
#     author='Shalin Singh',
#     license='MIT',
#     include_package_data=True,
#     ext_modules=cythonize(extensions),
# )

setup(
    ext_modules = cythonize([
        Extension(
            name="frame", 
            sources=[
                "frame.py",

                # data structures
                "../src/data_structures/map/hash.c",
                "../src/data_structures/map/table.c",
                "../src/data_structures/map/map.c",
                "../src/data_structures/node/node.c",
                "../src/data_structures/matrix/matrix.c",
                "../src/data_structures/list/array.c",
                "../src/data_structures/list/ll.c",

                # extractors
                "../src/extractors/dataframe/frame.c", 
                "../src/extractors/dataframe/re.c",
                "../src/extractors/dataframe/utils.c",
                "../src/extractors/dataframe/operations.c"
            ],
        )
    ])
)