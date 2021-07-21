import os
import sys
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva

ret = pyva.init()
print(ret)

pyva.close()
print('done')