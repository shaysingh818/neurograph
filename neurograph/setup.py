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
            libraries=["extractors"],
        ),
        Extension(
            name="neurograph.structures",
            sources=[
                os.path.join("neurograph", "structures.pyx"), 
            ],
            libraries=["ds"],
        ),
        Extension(
            name="neurograph.graph",
            sources=[
                os.path.join("neurograph", "graph.pyx"), 
            ],
            libraries=["graph"],
        ),
        Extension(
            name="neurograph.networks",
            sources=[
                os.path.join("neurograph", "networks.pyx"), 
            ],
            libraries=["networks"],
        )
    ])
)