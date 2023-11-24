from setuptools import setup
from Cython.Build import cythonize
from distutils.extension import Extension
import os

setup(
    ext_modules = cythonize([
        Extension(
            name="neurograph.extractors", 
            sources=[
                os.path.join("neurograph", "extractors.pyx"),
            ],
            libraries=["neurograph"],
            include_dirs=["include"]
        ),
        Extension(
            name="neurograph.structures",
            sources=[
                os.path.join("neurograph", "structures.pyx"), 
            ],
            libraries=["neurograph"],
            include_dirs=["include"]
        )
    ])
)