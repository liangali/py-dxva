import os
import sys
import cv2

sys.path.append(os.path.dirname(__file__))
sys.path.append(os.path.dirname(__file__)+'\\..\\build\\Debug')
import pydxva as pyva
from vadef.common import *
from vadef.enum import *

def check_error(hr):
    if hr < 0:
        print("ERROR: function failed, hr =%x"%hr)
        exit()

w, h, p, dec_bufs = 320, 240, 'DXVA_ModeH264_E', []
check_error(pyva.init())

# check decode capability
if p not in pyva.profiles():
    print("ERROR: cannot find %s in current platform"% p)
    pyva.close()
    exit()
decoder = pyva.create_decoder(p, w, h, DXGI_FORMAT.NV12)

# create decode output resource
td = D3D11TextureDesc(w, h, 1, 1, DXGI_FORMAT.NV12, DXGISampleDesc(1, 0), D3D11_USAGE.DEFAULT, D3D11_BIND.DECODER, 0, D3D11_RESOURCE_MISC.SHARED)
surf_rt = pyva.create_texture2d(np_from_struct(td))
outview = pyva.create_decoutview(surf_rt, p)

# prepare input data
dec_bufs.append((D3D11DecBufType.PICTURE_PARAMETERS, np.fromfile('data/dec/pic.bin', dtype=np.uint8)))
dec_bufs.append((D3D11DecBufType.SLICE_CONTROL,      np.fromfile('data/dec/slc.bin', dtype=np.uint8)))
dec_bufs.append((D3D11DecBufType.IQ_MATRIX,          np.fromfile('data/dec/iq.bin',  dtype=np.uint8)))
dec_bufs.append((D3D11DecBufType.BITSTREAM,          np.fromfile('data/dec/bs.bin',  dtype=np.uint8)))

# decode one frame
pyva.begin_frame(decoder, outview)
pyva.submit_buffers(decoder, dec_bufs)
pyva.end_frame(decoder)

# dump decode output
out_nv12 = pyva.read_surface(surf_rt)
out_bgr = cv2.cvtColor(out_nv12, cv2.COLOR_YUV2BGR_NV12)
cv2.imwrite('../../dec_out.bmp', out_bgr)

# free resoruce
pyva.release_decoder(decoder)
pyva.release_decoutview(outview)
pyva.release_texture2d(surf_rt)

pyva.close()
print('done')