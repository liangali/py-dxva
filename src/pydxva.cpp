#include <pybind11/pybind11.h>

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

int pyCreateDevice()
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

void pyCloseDevice()
{
    FREE_RESOURCE(pD3D11Device);
    FREE_RESOURCE(pDeviceContext);
    FREE_RESOURCE(pD3D11VideoDevice);
}

PYBIND11_MODULE(pydxva, m) {
    m.doc() = "dxva python binding library"; 
    m.def("init", &pyCreateDevice, "Create Device");
    m.def("close", &pyCloseDevice, "Create Device");
}
