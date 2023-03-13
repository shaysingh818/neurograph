from setuptools import find_packages, setup, Extension
import os


setup(
    name='dgraph',
    packages=find_packages(include=['dg']),
    version='0.2.0',
    description='Diffusion graph library',
    author='Shalin Singh',
    license='MIT',
    setup_requires=['pytest-runner'],
    tests_require=['pytest==4.4.1'],
    test_suite='tests',
    package_data={'dg': ['*.so']}, 
    include_package_data=True 
)
