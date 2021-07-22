import os
import sys
sys.path.append(os.path.dirname(__file__))
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva
from vadef.common import *
from vadef.enum import *

pyva.init()

dec_cfg = D3D11VideoDecoderConfig()
# print(dec_cfg)

desc = D3D11TextureDesc()
desc.Width, desc.Height, desc.MipLevels, desc.ArraySize, desc.Format = 320, 240, 1, 1, DXGI_FORMAT.NV12
desc.SampleDesc.Count, desc.SampleDesc.Quality = 1, 0
desc.Usage = D3D11_USAGE.DEFAULT
desc.BindFlags = D3D11_BIND.DECODER
desc.CPUAccessFlags = 0
desc.MiscFlags = D3D11_RESOURCE_MISC.SHARED
surf_rt = pyva.create_texture2d(np_from_struct(desc))

desc.Usage = D3D11_USAGE.STAGING
desc.BindFlags = 0
desc.CPUAccessFlags = D3D11_CPU_ACCESS.READ
desc.MiscFlags = 0
surf_staging = pyva.create_texture2d(np_from_struct(desc))

pyva.release_texture2d(surf_rt)
pyva.release_texture2d(surf_staging)
pyva.close()
print('done')