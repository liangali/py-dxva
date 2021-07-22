from ctypes import *
import numpy as np
from numpy.ctypeslib import ndpointer

class PStruct(Structure):
    indent = -4
    def __repr__(self) -> str:
        res = []
        fdict = {field[0]: getattr(self, field[0]) for field in self._fields_}
        for k in fdict:
            PStruct.indent += 4
            if issubclass(type(fdict[k]), Array):
                res.append('\n'.join(['%s%s[%d] = %s' %(' '*PStruct.indent, k, i, str(obj)) for i, obj in enumerate(fdict[k])]))
            elif hasattr(fdict[k], '_fields_'):
                res.append('%s%s = %s' %(' '*PStruct.indent, k, str(fdict[k])))
            else:
                res.append('%s%s = %s' %(' '*PStruct.indent, k, str(fdict[k])))
            PStruct.indent -= 4
        return '\n%s'%'\n'.join(res)

def np_from_struct(s):
    ptr = cast(pointer(s), POINTER(c_uint8))
    np_array = np.ctypeslib.as_array(ptr, shape=(sizeof(s),))
    return np_array