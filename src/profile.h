#pragma once

#include <windows.h>
#include <string>
#include <map>
#include <vector>

struct GUIDComparer
{
    bool operator()(const GUID & Left, const GUID & Right) const
    {
        return memcmp(&Left, &Right, sizeof(Right)) < 0;
    }
};

static std::map<GUID, std::string, GUIDComparer> g_GuidMap;

#define DEFINE_GUID_MAP(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }; \
        g_GuidMap[name] = #name;

std::string GUID2Str(GUID guid);
GUID str2GUID(std::string str);
