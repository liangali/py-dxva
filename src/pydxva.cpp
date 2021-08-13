#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

#include <vector>
#include <string>

#include <windows.h>
#include <D3D11.h>
#include <dxva.h>

#include "profile.h"

typedef py::array_t<uint8_t, py::array::c_style | py::array::forcecast> PyArray;

static HRESULT hr = S_OK;
static ID3D11Device* pD3D11Device = NULL;
static ID3D11DeviceContext* pDeviceContext = NULL;
static ID3D11VideoDevice * pD3D11VideoDevice = NULL;
static ID3D11VideoContext* pVideoContext = NULL;

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

    hr = pDeviceContext->QueryInterface(&pVideoContext);
    CHECK_SUCCESS(hr, "QueryInterface");
    printf("#### pVideoContext = %llx\n", (uint64_t)pVideoContext);

    return hr;
}

void pyCloseDevice()
{
    FREE_RESOURCE(pD3D11Device);
    FREE_RESOURCE(pDeviceContext);
    FREE_RESOURCE(pD3D11VideoDevice);
}

uint64_t pyCreateTexture2D(py::array_t<uint8_t, py::array::c_style | py::array::forcecast> inparams)
{
    if (!inparams.data() || inparams.size() != sizeof(D3D11_TEXTURE2D_DESC)) {
        printf("#### ERROR: invalid input params\n");
        return 0;
    }

    ID3D11Texture2D *pTexture2D = nullptr;
    D3D11_TEXTURE2D_DESC* pDesc = (D3D11_TEXTURE2D_DESC*)inparams.data();
    hr = pD3D11Device->CreateTexture2D(pDesc, NULL, &pTexture2D);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR: CreateTexture2D failed\n");
        return 0;
    }

    return (uint64_t)pTexture2D;
}

void pyReleaseTexture2D(uint64_t ptr)
{
    ((ID3D11Texture2D *)ptr)->Release();
}

uint64_t pyCreateVideoDecoderOutputView(uint64_t dec_rt, std::string guid)
{
    if (!dec_rt) {
        printf("#### ERROR in %s:%d: invalid input params\n", __FUNCTION__, __LINE__);
        return 0;
    }
    ID3D11VideoDecoderOutputView *pDecodeOutputView = NULL;
    D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC viewDesc = { 0 };
    viewDesc.DecodeProfile = str2GUID(guid);
    viewDesc.ViewDimension = D3D11_VDOV_DIMENSION_TEXTURE2D;
    hr = pD3D11VideoDevice->CreateVideoDecoderOutputView((ID3D11Texture2D*)dec_rt, &viewDesc, &pDecodeOutputView);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR in %s:%d: CreateVideoDecoderOutputView failed\n", __FUNCTION__, __LINE__);
        return 0;
    }

    return (uint64_t)pDecodeOutputView;
}

void pyReleaseVDOutputView(uint64_t ptr)
{
    ((ID3D11VideoDecoderOutputView *)ptr)->Release();
}

std::vector<std::string> pyGetProfiles()
{
    std::vector<std::string> profile_list;
    UINT profileCount = pD3D11VideoDevice->GetVideoDecoderProfileCount();
    for (UINT i = 0; i < profileCount; i++)
    {
        GUID guid = {};
        hr = pD3D11VideoDevice->GetVideoDecoderProfile(i, &guid);
        if (!SUCCEEDED(hr)) {
            printf("#### ERROR: GetVideoDecoderProfile failed\n");
            continue;
        }
        profile_list.push_back(GUID2Str(guid));
    }
    return profile_list;
}

void printGUID(GUID guid)
{
    char strGUID[256] = {};
    sprintf_s(strGUID, 256, "%08x-%04x-%04x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    printf("strGUID = %s\n", strGUID);
}

void pyTestGUID(std::string strGUID)
{
    printGUID(str2GUID(strGUID));
}

uint64_t pyCreateVideoDecoder(std::string guid, uint32_t w, uint32_t h, uint64_t fmt)
{
    ID3D11VideoDecoder *pVideoDecoder = NULL;
    D3D11_VIDEO_DECODER_DESC decoderDesc = { 0 };
    decoderDesc.Guid = str2GUID(guid);
    decoderDesc.SampleWidth = w;
    decoderDesc.SampleHeight = h;
    decoderDesc.OutputFormat = (DXGI_FORMAT)fmt;
    D3D11_VIDEO_DECODER_CONFIG config = { 0 };
    config.ConfigBitstreamRaw = 1; // 0: long format; 1: short format
    hr = pD3D11VideoDevice->CreateVideoDecoder(&decoderDesc, &config, &pVideoDecoder);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR: CreateVideoDecoder failed\n");
        return 0;
    }

    return (uint64_t)pVideoDecoder;
}

uint64_t pyCreateVideoDecoder2(py::array_t<uint8_t, py::array::c_style | py::array::forcecast> desc_data, 
    py::array_t<uint8_t, py::array::c_style | py::array::forcecast> cfg_data)
{
    if (!desc_data.data() || desc_data.size() != sizeof(D3D11_VIDEO_DECODER_DESC) ||
        !cfg_data.data() || cfg_data.size() != sizeof(D3D11_VIDEO_DECODER_CONFIG)) {
        printf("#### ERROR: invalid data\n");
        return 0;
    }

    ID3D11VideoDecoder *pVideoDecoder = nullptr;
    D3D11_VIDEO_DECODER_DESC* decoderDesc = (D3D11_VIDEO_DECODER_DESC*)desc_data.data();
    D3D11_VIDEO_DECODER_CONFIG* config = (D3D11_VIDEO_DECODER_CONFIG*)cfg_data.data();
    hr = pD3D11VideoDevice->CreateVideoDecoder(decoderDesc, config, &pVideoDecoder);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR: CreateVideoDecoder failed\n");
        return 0;
    }

    return (uint64_t)pVideoDecoder;
}

void pyReleaseVideoDecoder(uint64_t ptr)
{
    ((ID3D11VideoDecoder *)ptr)->Release();
}

HRESULT pyDecoderBeginFrame(uint64_t decoder, uint64_t outview)
{
    if (!decoder || !outview) {
        printf("#### ERROR in %s:%d: invalid input params\n", __FUNCTION__, __LINE__);
        return -1;
    }

    ID3D11VideoDecoder *pVideoDecoder = (ID3D11VideoDecoder*)decoder;
    ID3D11VideoDecoderOutputView *pDecodeOutputView = (ID3D11VideoDecoderOutputView*)outview;
    hr = pVideoContext->DecoderBeginFrame(pVideoDecoder, pDecodeOutputView, 0, 0);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR in %s:%d: DecoderBeginFrame failed\n", __FUNCTION__, __LINE__);
        return hr;
    }

    return hr;
}

HRESULT pySubmitDecoderBuffers(uint64_t decoder, std::vector<std::pair<int32_t, PyArray>> buf_list)
{
    ID3D11VideoDecoder *pVideoDecoder = (ID3D11VideoDecoder*)decoder;
    // Prepare DXVA buffers for decoding
    uint32_t sizeDesc = sizeof(D3D11_VIDEO_DECODER_BUFFER_DESC) * (uint32_t)buf_list.size();
    D3D11_VIDEO_DECODER_BUFFER_DESC *descDecBuffers = new D3D11_VIDEO_DECODER_BUFFER_DESC[buf_list.size()];
    memset(descDecBuffers, 0, sizeDesc);
    for (uint32_t i = 0; i < buf_list.size(); i++)
    {
        BYTE* buffer = 0;
        uint32_t bufferSize = 0;
        descDecBuffers[i].BufferIndex = i;
        descDecBuffers[i].BufferType = (D3D11_VIDEO_DECODER_BUFFER_TYPE)buf_list[i].first;
        descDecBuffers[i].DataSize = (uint32_t)buf_list[i].second.size();

        hr = pVideoContext->GetDecoderBuffer(pVideoDecoder, descDecBuffers[i].BufferType, &bufferSize, reinterpret_cast<void**>(&buffer));
        CHECK_SUCCESS(hr, "GetDecoderBuffer");

        uint32_t copySize = min(bufferSize, descDecBuffers[i].DataSize);
        memcpy_s(buffer, copySize, buf_list[i].second.data(), copySize);

        hr = pVideoContext->ReleaseDecoderBuffer(pVideoDecoder, descDecBuffers[i].BufferType);
        CHECK_SUCCESS(hr, "ReleaseDecoderBuffer");
    }

    // Submit decode workload to GPU
    hr = pVideoContext->SubmitDecoderBuffers(pVideoDecoder, (uint32_t)buf_list.size(), descDecBuffers);
    CHECK_SUCCESS(hr, "SubmitDecoderBuffers");
    delete[] descDecBuffers;

    return hr;
}

HRESULT pyDecoderEndFrame(uint64_t decoder)
{
    if (!decoder) {
        printf("#### ERROR in %s:%d: invalid input params\n", __FUNCTION__, __LINE__);
        return -1;
    }

    ID3D11VideoDecoder *pVideoDecoder = (ID3D11VideoDecoder*)decoder;
    hr = pVideoContext->DecoderEndFrame(pVideoDecoder);
    if (!SUCCEEDED(hr)) {
        printf("#### ERROR in %s:%d: DecoderEndFrame failed\n", __FUNCTION__, __LINE__);
        return hr;
    }

    return hr;
}

PYBIND11_MODULE(pydxva, m) {
    m.doc() = "dxva python binding library"; 
    m.def("init", &pyCreateDevice, "Create Device");
    m.def("close", &pyCloseDevice, "Create Device");

    m.def("create_texture2d", &pyCreateTexture2D, "Create Texture2D");
    m.def("release_texture2d", &pyReleaseTexture2D, "Release Texture2D");

    m.def("create_decoutview", &pyCreateVideoDecoderOutputView, "Create VideoDecoderOutputView");
    m.def("release_decoutview", &pyReleaseVDOutputView, "Release VideoDecoderOutputView");

    m.def("create_decoder", &pyCreateVideoDecoder, "Create Video Decoder");
    m.def("create_decoder2", &pyCreateVideoDecoder2, "Create Video Decoder");
    m.def("release_decoder", &pyReleaseVideoDecoder, "Release Video Decoder");

    m.def("begin_frame", &pyDecoderBeginFrame, "Decoder Begin Frame");
    m.def("submit_buffers", &pySubmitDecoderBuffers, "Submit Decoder Buffers");
    m.def("end_frame", &pyDecoderEndFrame, "Decoder End Frame");

    m.def("profiles", &pyGetProfiles, "Query Profiles");
    m.def("test_guid", &pyTestGUID, "Test GUID");

    m.def("test_func", [](std::pair<int, PyArray> p) {
        int a = p.first;
        int b = (int)p.second.size();
        uint8_t* ptr = (uint8_t*)p.second.data();
    });
}
