import os
import sys
sys.path.append(os.path.dirname(__file__))
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva
from vadef.common import *
from vadef.enum import *

w, h = 320, 240
pyva.init()

dec_cfg = D3D11VideoDecoderConfig()
# print(dec_cfg)

td = D3D11TextureDesc()
td.Width, td.Height, td.MipLevels, td.ArraySize, td.Format = w, h, 1, 1, DXGI_FORMAT.NV12
td.SampleDesc.Count, td.SampleDesc.Quality = 1, 0
td.Usage = D3D11_USAGE.DEFAULT
td.BindFlags = D3D11_BIND.DECODER
td.CPUAccessFlags = 0
td.MiscFlags = D3D11_RESOURCE_MISC.SHARED
surf_rt = pyva.create_texture2d(np_from_struct(td))

td.Usage = D3D11_USAGE.STAGING
td.BindFlags = 0
td.CPUAccessFlags = D3D11_CPU_ACCESS.READ
td.MiscFlags = 0
surf_staging = pyva.create_texture2d(np_from_struct(td))

pl = pyva.profiles()
print('\n'.join(pl))

# for p in pl: pyva.test_guid(p)

decoder = pyva.create_decoder('DXVA_ModeH264_E', w, h, DXGI_FORMAT.NV12)
print('decoder = %x'%decoder)

pyva.release_texture2d(surf_rt)
pyva.release_texture2d(surf_staging)
pyva.release_decoder(decoder)
pyva.close()
print('done')