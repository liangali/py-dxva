import os
import sys
sys.path.append(os.path.dirname(__file__))
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva
from vadef.common import *
from vadef.enum import *


ret = pyva.init()
print(ret)

dec_cfg = D3D11VideoDecoderConfig()
# print(dec_cfg)

desc = D3D11TextureDesc()
desc.Width, desc.Height, desc.MipLevels, desc.ArraySize = 320, 240, 1, 1
desc.SampleDesc.Count, desc.SampleDesc.Quality = 1, 0
desc.Format = DXGI_FORMAT.NV12
desc.Usage = D3D11_USAGE.DEFAULT
desc.BindFlags = D3D11_BIND.DECODER
desc.MiscFlags = D3D11_RESOURCE_MISC.SHARED
surf = pyva.create_texture2d(np_from_struct(desc))
pyva.release_texture2d(surf)

pyva.close()
print('done')