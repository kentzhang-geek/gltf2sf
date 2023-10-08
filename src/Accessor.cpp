//
// Created by administrator on 10/7/2023.
//

#include "Accessor.h"
#pragma optimize("", off)

typedef std::tuple<int, int> ElementType;

template <>
struct std::hash<ElementType>
{
    std::size_t operator()(const ElementType & k) const
    {
        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        return (hash<int>()(std::get<0>(k)
                            ^ (hash<int>()(std::get<1>(k)) << 1)) >> 1);
    }
};

template<typename T>
std::vector<T> ExtractAccessor(int accIdx) {
    return std::vector<T>();
}

sf::ElementType TypeElementofAccessor(int accIdx) {
    tinygltf::Accessor acc = gModel->accessors[accIdx];
    const static std::unordered_map<ElementType , sf::ElementType> typeMap = {
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::ElementType_eXu8},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::ElementType_eXYu8},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::ElementType_eXYZu8},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::ElementType_eXYZWu8},
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_BYTE}, sf::ElementType_eXi8},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_BYTE}, sf::ElementType_eXYi8},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_BYTE}, sf::ElementType_eXYZi8},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_BYTE}, sf::ElementType_eXYZWi8},
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::ElementType_eXu16},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::ElementType_eXYu16},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::ElementType_eXYZu16},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::ElementType_eXYZWu16},
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_SHORT}, sf::ElementType_eXi16},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_SHORT}, sf::ElementType_eXYi16},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_SHORT}, sf::ElementType_eXYZi16},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_SHORT}, sf::ElementType_eXYZWi16},
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::ElementType_eXu32},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::ElementType_eXYu32},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::ElementType_eXYZu32},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::ElementType_eXYZWu32},
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_INT}, sf::ElementType_eXi32},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_INT}, sf::ElementType_eXYi32},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_INT}, sf::ElementType_eXYZi32},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_INT}, sf::ElementType_eXYZWi32},
            {{TINYGLTF_TYPE_SCALAR, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::ElementType_eXf32},
            {{TINYGLTF_TYPE_VEC2, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::ElementType_eXYf32},
            {{TINYGLTF_TYPE_VEC3, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::ElementType_eXYZf32},
            {{TINYGLTF_TYPE_VEC4, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::ElementType_eXYZWf32},
    };
    if (typeMap.find({acc.type, acc.componentType}) != typeMap.end()) {
        return typeMap.at({acc.type, acc.componentType});
    } else {
        RTP_LOG("unsupported accessor type", acc.type, acc.componentType);
    }
    return sf::ElementType_eNone;
}

template<typename T>
std::vector<T> ReadBuffer(int bufferViewIdx) {
    std::vector<T> ret;
    tinygltf::BufferView bufferView = gModel->bufferViews[bufferViewIdx];
    tinygltf::Buffer buffer = gModel->buffers[bufferView.buffer];
    if (bufferView.byteStride % sizeof(T) != 0) {
        RTP_LOG("BufferView byteStride is not a multiple of sizeof(T)", bufferView.name, typeid(T).name());
        return ret;
    }
    if (bufferView.byteLength % sizeof(T) != 0) {
        RTP_LOG("BufferView byteStride is not a multiple of sizeof(T)", bufferView.name, typeid(T).name());
        return ret;
    }
    ret.resize(bufferView.byteLength / sizeof(T));
    memcpy(ret.data(), buffer.data.data() + bufferView.byteOffset, bufferView.byteLength);
    return ret;
}
