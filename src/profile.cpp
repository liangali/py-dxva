#include "profile.h"

#include <sstream>
#include <iostream>

static struct _InitGuidMap {

    _InitGuidMap()
    {
        DEFINE_GUID_MAP(DXVA_ModeMPEG2_MoComp, 0xe6a9f44b, 0x61b0, 0x4563, 0x9e, 0xa4, 0x63, 0xd2, 0xa3, 0xc6, 0xfe, 0x66);
        DEFINE_GUID_MAP(DXVA_ModeMPEG2_IDCT, 0xbf22ad00, 0x03ea, 0x4690, 0x80, 0x77, 0x47, 0x33, 0x46, 0x20, 0x9b, 0x7e);
        DEFINE_GUID_MAP(DXVA_ModeMPEG2_VLD, 0xee27417f, 0x5e28, 0x4e65, 0xbe, 0xea, 0x1d, 0x26, 0xb5, 0x08, 0xad, 0xc9);
        DEFINE_GUID_MAP(DXVA_ModeMPEG1_VLD, 0x6f3ec719, 0x3735, 0x42cc, 0x80, 0x63, 0x65, 0xcc, 0x3c, 0xb3, 0x66, 0x16);
        DEFINE_GUID_MAP(DXVA_ModeMPEG2and1_VLD, 0x86695f12, 0x340e, 0x4f04, 0x9f, 0xd3, 0x92, 0x53, 0xdd, 0x32, 0x74, 0x60);

        DEFINE_GUID_MAP(DXVA_ModeH264_A, 0x1b81be64, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeH264_B, 0x1b81be65, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeH264_C, 0x1b81be66, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeH264_D, 0x1b81be67, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeH264_E, 0x1b81be68, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeH264_F, 0x1b81be69, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeH264_VLD_WithFMOASO_NoFGT, 0xd5f04ff9, 0x3418, 0x45d8, 0x95, 0x61, 0x32, 0xa7, 0x6a, 0xae, 0x2d, 0xdd);
        DEFINE_GUID_MAP(DXVA_ModeH264_VLD_Stereo_Progressive_NoFGT, 0xd79be8da, 0x0cf1, 0x4c81, 0xb8, 0x2a, 0x69, 0xa4, 0xe2, 0x36, 0xf4, 0x3d);
        DEFINE_GUID_MAP(DXVA_ModeH264_VLD_Stereo_NoFGT, 0xf9aaccbb, 0xc2b6, 0x4cfc, 0x87, 0x79, 0x57, 0x07, 0xb1, 0x76, 0x05, 0x52);
        DEFINE_GUID_MAP(DXVA_ModeH264_VLD_Multiview_NoFGT, 0x705b9d82, 0x76cf, 0x49d6, 0xb7, 0xe6, 0xac, 0x88, 0x72, 0xdb, 0x01, 0x3c);

        DEFINE_GUID_MAP(DXVA_ModeWMV8_A, 0x1b81be80, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeWMV8_B, 0x1b81be81, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeWMV9_A, 0x1b81be90, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeWMV9_B, 0x1b81be91, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeWMV9_C, 0x1b81be94, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);

        DEFINE_GUID_MAP(DXVA_ModeVC1_A, 0x1b81beA0, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeVC1_B, 0x1b81beA1, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeVC1_C, 0x1b81beA2, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeVC1_D, 0x1b81beA3, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
        DEFINE_GUID_MAP(DXVA_ModeVC1_D2010, 0x1b81beA4, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);

        DEFINE_GUID_MAP(DXVA_ModeMPEG4pt2_VLD_Simple, 0xefd64d74, 0xc9e8, 0x41d7, 0xa5, 0xe9, 0xe9, 0xb0, 0xe3, 0x9f, 0xa3, 0x19);
        DEFINE_GUID_MAP(DXVA_ModeMPEG4pt2_VLD_AdvSimple_NoGMC, 0xed418a9f, 0x010d, 0x4eda, 0x9a, 0xe3, 0x9a, 0x65, 0x35, 0x8d, 0x8d, 0x2e);
        DEFINE_GUID_MAP(DXVA_ModeMPEG4pt2_VLD_AdvSimple_GMC, 0xab998b5b, 0x4258, 0x44a9, 0x9f, 0xeb, 0x94, 0xe5, 0x97, 0xa6, 0xba, 0xae);

        DEFINE_GUID_MAP(DXVA_ModeHEVC_VLD_Main, 0x5b11d51b, 0x2f4c, 0x4452, 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0);
        DEFINE_GUID_MAP(DXVA_ModeHEVC_VLD_Main10, 0x107af0e0, 0xef1a, 0x4d19, 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13);

        DEFINE_GUID_MAP(DXVA_ModeVP9_VLD_Profile0, 0x463707f8, 0xa1d0, 0x4585, 0x87, 0x6d, 0x83, 0xaa, 0x6d, 0x60, 0xb8, 0x9e);
        DEFINE_GUID_MAP(DXVA_ModeVP9_VLD_10bit_Profile2, 0xa4c749ef, 0x6ecf, 0x48aa, 0x84, 0x48, 0x50, 0xa7, 0xa1, 0x16, 0x5f, 0xf7);
        DEFINE_GUID_MAP(DXVA_ModeVP8_VLD, 0x90b899ea, 0x3a62, 0x4705, 0x88, 0xb3, 0x8d, 0xf0, 0x4b, 0x27, 0x44, 0xe7);

        DEFINE_GUID_MAP(DXVA_ModeAV1_VLD_Profile0, 0xb8be4ccb, 0xcf53, 0x46ba, 0x8d, 0x59, 0xd6, 0xb8, 0xa6, 0xda, 0x5d, 0x2a);

        DEFINE_GUID_MAP(DXVA_DeinterlaceAdaptiveDevice, 0xaedc1d5d, 0x8546, 0x440e, 0xaa, 0xb2, 0xb6, 0x9f, 0xa7, 0x25, 0xaf, 0x82);
        DEFINE_GUID_MAP(DXVA_DeinterlaceMODEASTDevice, 0xbf752ef6, 0x8cc4, 0x457a, 0xbe, 0x1b, 0x08, 0xbd, 0x1c, 0xae, 0xee, 0x9f);
        DEFINE_GUID_MAP(DXVA_SurfaceRegistrationDevice, 0x44dee63b, 0x77e6, 0x4dd2, 0xb2, 0xe1, 0x44, 0x3b, 0x13, 0x0f, 0x2e, 0x2f);

        DEFINE_GUID_MAP(DXVA_NoEncrypt, 0x1b81beD0, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
        DEFINE_GUID_MAP(GUID_Zero, 0x0000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

    }
} g_initGuidMap;

std::vector<std::string> splitStr(std::string str)
{
    std::vector<std::string> str_list;
    while (1) {
        size_t pos = str.find("-");
        if (pos == std::string::npos) {
            str_list.push_back(str);
            break;
        }
        str_list.push_back(str.substr(0, pos));
        str = str.substr(pos + 1);
    }
    return str_list;
}

uint32_t str2Int(std::string str)
{
    uint32_t x; 
    std::stringstream ss;
    ss << std::hex << str;
    ss >> x;
    return x;
}

std::string GUID2Str(GUID guid)
{
    std::map<GUID, std::string, GUIDComparer>::iterator it;

    it = g_GuidMap.find(guid);
    if (it != g_GuidMap.end()) {
        return g_GuidMap[guid];
    } else {
        char strGUID[256] = {};
        sprintf_s(strGUID, 256, "%08x-%04x-%04x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x", 
            guid.Data1, guid.Data2, guid.Data3, 
            guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], 
            guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
        return strGUID;
    }
}

GUID str2GUID(std::string str)
{
    GUID result = {};
    std::vector<std::string> str_list = splitStr(str);
    if (str_list.size() == 11) {
        result.Data1 = str2Int(str_list[0]);
        result.Data2 = str2Int(str_list[1]);
        result.Data3 = str2Int(str_list[2]);
        for (size_t i = 0; i < 8; i++) {
            result.Data4[i] = str2Int(str_list[3 + i]);
        }
    } else {
        for (const auto & kv: g_GuidMap) {
            if (str == kv.second) {
                result = kv.first;
                break;
            }
        }
    }

    return result;
}