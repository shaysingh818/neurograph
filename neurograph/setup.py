from setuptools import find_packages, setup, Extension
import os


setup(
    name='neurograph',
    packages=find_packages(include=['ngraph']),
    version='0.4.0',
    description='Graph Neural Network Library',
    author='Shalin Singh',
    license='MIT',
    setup_requires=['pytest-runner'],
    tests_require=['pytest==4.4.1'],
    test_suite='tests',
    package_data={'ngraph': ['*.so']}, 
)
