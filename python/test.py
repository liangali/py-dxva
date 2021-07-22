import os
import sys
sys.path.append(os.path.dirname(__file__))
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva
from vadef.common import *

ret = pyva.init()
print(ret)

dec_cfg = D3D11VideoDecoderConfig()
print(dec_cfg)

pyva.close()
print('done')