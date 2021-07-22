from .base import *

class GUID(PStruct):
    _fields_ = [
        ("Data1", c_uint32),
        ("Data2", c_uint16),
        ("Data3", c_uint16),
        ("Data4", c_int8 * 8),
    ]

class D3D11VideoDecoderConfig(PStruct):
    _fields_ = [
        ("guidConfigBitstreamEncryption", GUID),
        ("guidConfigMBcontrolEncryption", GUID),
        ("guidConfigResidDiffEncryption", GUID),
        ("ConfigBitstreamRaw", c_uint32),
        ("ConfigMBcontrolRasterOrder", c_uint32),
        ("ConfigResidDiffHost", c_uint32),
        ("ConfigSpatialResid8", c_uint32),
        ("ConfigResid8Subtraction", c_uint32),
        ("ConfigSpatialHost8or9Clipping", c_uint32),
        ("ConfigSpatialResidInterleaved", c_uint32),
        ("ConfigIntraResidUnsigned", c_uint32),
        ("ConfigResidDiffAccelerator", c_uint32),
        ("ConfigHostInverseScan", c_uint32),
        ("ConfigSpecificIDCT", c_uint32),
        ("Config4GroupedCoefs", c_uint32),
        ("ConfigMinRenderTargetBuffCount", c_uint16),
        ("ConfigDecoderSpecific", c_uint16),
    ]

class D3D11VideoDecoderDesc(PStruct):
    _fields_ = [
        ("Guid", GUID),
        ("SampleWidth", c_uint32),
        ("SampleHeight", c_uint32),
        ("OutputFormat", c_uint32),
    ]