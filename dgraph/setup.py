from setuptools import find_packages, setup

setup(
    name='dgraph',
    packages=find_packages(include=['dg']),
    version='0.1.0',
    description='Diffusion graph library',
    author='Shalin Singh',
    license='MIT',
    setup_requires=['pytest-runner'],
    tests_require=['pytest==4.4.1'],
    test_suite='tests',
)
