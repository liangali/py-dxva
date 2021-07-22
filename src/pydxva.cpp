#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

#include <windows.h>
#include <D3D11.h>
#include <dxva.h>

static HRESULT hr = S_OK;
static ID3D11Device* pD3D11Device = NULL;
static ID3D11DeviceContext* pDeviceContext = NULL;
static ID3D11VideoDevice * pD3D11VideoDevice = NULL;

#define CHECK_SUCCESS(hr, msg) \
    if (!SUCCEEDED(hr)) { printf("ERROR: Failed to call %s\n", msg); return -1; }

#define FREE_RESOURCE(res) \
    if(res) {res->Release(); res = NULL;}

HRESULT pyCreateDevice()
{
    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_1 };
    D3D_FEATURE_LEVEL fl;

    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 1, D3D11_SDK_VERSION, 
        &pD3D11Device, &fl, &pDeviceContext);
    CHECK_SUCCESS(hr, "D3D11CreateDevice");
    printf("#### pD3D11Device = %llx, pDeviceContext = %llx\n", (uint64_t)pD3D11Device, (uint64_t)pDeviceContext);
 
    hr = pD3D11Device->QueryInterface(&pD3D11VideoDevice);
    CHECK_SUCCESS(hr, "QueryInterface");
    printf("#### pD3D11VideoDevice = %llx\n", (uint64_t)pD3D11VideoDevice);

    return hr;
}

uint64_t pyCreateTexture2D(py::array_t<uint8_t, py::array::c_style | py::array::forcecast> inparams)
{
    if (!inparams.data() || inparams.size() < sizeof(D3D11_TEXTURE2D_DESC)) {
        printf("#### ERROR: invalid input params\n");
        return 0;
    }

    ID3D11Texture2D *pTexture2D = nullptr;
    D3D11_TEXTURE2D_DESC* pDesc = (D3D11_TEXTURE2D_DESC*)inparams.data();
    // printf("#### pydxva: Width = %d, Height = %d, MipLevels = %d, ArraySize = %d\n", 
        //pDesc->Width, pDesc->Height, pDesc->MipLevels, pDesc->ArraySize);
    // printf("#### pydxva: Format = %x, Usage = %x, BindFlags = %x, CPUAccessFlags = %x, MiscFlags = %x, \n", 
    //     pDesc->Format, pDesc->Usage, pDesc->BindFlags, pDesc->CPUAccessFlags, pDesc->MiscFlags);
    hr = pD3D11Device->CreateTexture2D(pDesc, NULL, &pTexture2D);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR: CreateTexture2D failed\n");
        return 0;
    }

    return (uint64_t)pTexture2D;
}

void pyCloseDevice()
{
    printf("size of DXGI_FORMAT = %lld\n", sizeof(DXGI_FORMAT));
    printf("size of D3D11_TEXTURE2D_DESC = %lld\n", sizeof(D3D11_TEXTURE2D_DESC));
    FREE_RESOURCE(pD3D11Device);
    FREE_RESOURCE(pDeviceContext);
    FREE_RESOURCE(pD3D11VideoDevice);
}

void pyReleaseTexture2D(uint64_t ptr)
{
    ((ID3D11Texture2D *)ptr)->Release();
}

PYBIND11_MODULE(pydxva, m) {
    m.doc() = "dxva python binding library"; 
    m.def("init", &pyCreateDevice, "Create Device");
    m.def("close", &pyCloseDevice, "Create Device");

    m.def("create_texture2d", &pyCreateTexture2D, "Create Texture2D");
    m.def("release_texture2d", &pyReleaseTexture2D, "Release Texture2D");
}
