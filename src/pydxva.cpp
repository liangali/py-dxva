#include <pybind11/pybind11.h>

#include <windows.h>
#include <D3D11.h>
#include <dxva.h>

int pyCreateDevice()
{
    HRESULT hr = S_OK;
    ID3D11Device* pD3D11Device = NULL;
    ID3D11DeviceContext* pDeviceContext = NULL;
    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_1 };
    D3D_FEATURE_LEVEL fl;

    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 1,
        D3D11_SDK_VERSION, &pD3D11Device, &fl, &pDeviceContext);
 
    return hr;
}

PYBIND11_MODULE(pydxva, m) {
    m.doc() = "pybind11 example plugin"; 
    m.def("create_device", &pyCreateDevice, "Create Device");
}
