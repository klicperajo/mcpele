# distutils: language = c++
# distutils: sources = takestep.cpp

import sys

#===============================================================================
# RandomCoordsDisplacement
#===============================================================================

cdef class _Cdef_RandomCoordsDisplacement(_Cdef_TakeStep):
    """This class is the python interface for the c++ pele::RandomCoordsDisplacement take step class implementation
    """
    cdef cppRandomCoordsDisplacement* newptr
    def __cinit__(self, rseed):
        self.thisptr = <cppTakeStep*>new cppRandomCoordsDisplacement(rseed)
        self.newptr = <cppRandomCoordsDisplacement*> self.thisptr
    
    def __dealloc__(self):
        del self.thisptr
        
class RandomCoordsDisplacement(_Cdef_RandomCoordsDisplacement):
    """This class is the python interface for the c++ RandomCoordsDisplacement implementation.
    """

#===============================================================================
# GaussianCoordsDisplacement
#===============================================================================

cdef class _Cdef_GaussianCoordsDisplacement(_Cdef_TakeStep):
    """This class is the python interface for the c++ pele::RandomCoordsDisplacement take step class implementation
    """
    cdef cppGaussianCoordsDisplacement* newptr
    def __cinit__(self, rseed):
        self.thisptr = <cppTakeStep*>new cppGaussianCoordsDisplacement(rseed)
        self.newptr = <cppGaussianCoordsDisplacement*> self.thisptr
    
class GaussianCoordsDisplacement(_Cdef_GaussianCoordsDisplacement):
    """This class is the python interface for the c++ RandomCoordsDisplacement implementation.
    """