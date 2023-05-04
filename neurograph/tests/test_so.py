from pprint import pprint
import unittest
import os.path
import sys
sys.path.append("..")

from dg import *

class TestSharedObject(unittest.TestCase):

    def test_shared_object_reference(self):

        # check if python version is 3.8 above
        result = "3.8" in sys.version
        self.assertEqual(result, True)

        # validate shared object file can be read
        lib_path = os.path.join(
            os.path.dirname(os.path.abspath(__file__)), 
            'lib', 'neurograph.so'
        )

        print(lib_path)


if __name__ == '__main__':
    unittest.main()
