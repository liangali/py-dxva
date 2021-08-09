import os
import sys
sys.path.append(os.path.dirname(__file__))
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva
from vadef.common import *
from vadef.enum import *

def check_error(hr):
    if hr < 0:
        print("ERROR: function failed, hr =%x"%hr)
        exit()

w, h, p = 320, 240, 'DXVA_ModeH264_E'
check_error(pyva.init())

dec_cfg = D3D11VideoDecoderConfig()

td = D3D11TextureDesc(w, h, 1, 1, DXGI_FORMAT.NV12, DXGISampleDesc(1, 0), D3D11_USAGE.DEFAULT, D3D11_BIND.DECODER, 0, D3D11_RESOURCE_MISC.SHARED)
surf_rt = pyva.create_texture2d(np_from_struct(td))

td = D3D11TextureDesc(w, h, 1, 1, DXGI_FORMAT.NV12, DXGISampleDesc(1, 0), D3D11_USAGE.STAGING, 0, D3D11_CPU_ACCESS.READ, 0)
surf_staging = pyva.create_texture2d(np_from_struct(td))

pl = pyva.profiles()
print('\n'.join(pl))

# for p in pl: pyva.test_guid(p)

if p in pl:
    print('#### find profile %s'%p)
    decoder = pyva.create_decoder(p, w, h, DXGI_FORMAT.NV12)
    print('decoder = %x'%decoder)
    pyva.release_decoder(decoder)
    
pyva.release_texture2d(surf_staging)
pyva.release_texture2d(surf_rt)

pyva.close()
print('done')