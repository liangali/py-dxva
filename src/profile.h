#pragma once

#include <windows.h>
#include <string>
#include <map>

using namespace std;

struct GUIDComparer
{
    bool operator()(const GUID & Left, const GUID & Right) const
    {
        return memcmp(&Left, &Right, sizeof(Right)) < 0;
    }
};

static map<GUID, string, GUIDComparer> g_GuidMap;

#define DEFINE_GUID_MAP(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }; \
        g_GuidMap[name] = #name;

string getGUIDName(GUID guid);

