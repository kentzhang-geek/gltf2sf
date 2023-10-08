//
// Created by administrator on 10/7/2023.
//

#ifndef GLTF2SF_ACCESSOR_H
#define GLTF2SF_ACCESSOR_H

#include <iostream>
#include <string>
#include "tool.h"
#include "tiny_gltf.h"
#include "common.h"
#include <vector>

template <typename T>
std::vector<T> ExtractAccessor(int accIdx);

sf::ElementType TypeElementofAccessor(int accIdx);

template<typename T>
std::vector<T> ReadBuffer(int accessorIdx) {
    std::vector<T> ret;
    tinygltf::Accessor &accessor = gModel->accessors[accessorIdx];
    tinygltf::BufferView &bufferView = gModel->bufferViews[accessor.bufferView];
    tinygltf::Buffer &buffer = gModel->buffers[bufferView.buffer];
    if (bufferView.byteStride % sizeof(T) != 0) {
        RTP_LOG("BufferView byteStride is not a multiple of sizeof(T)", bufferView.name, typeid(T).name());
        return ret;
    }
    if (bufferView.byteLength % sizeof(T) != 0) {
        RTP_LOG("BufferView byteStride is not a multiple of sizeof(T)", bufferView.name, typeid(T).name());
        return ret;
    }
    std::unordered_map<int, int> typeCount = {
            {TINYGLTF_TYPE_SCALAR, 1},
            {TINYGLTF_TYPE_VEC2, 2},
            {TINYGLTF_TYPE_VEC3, 3},
            {TINYGLTF_TYPE_VEC4, 4},
    };
    ret.resize(accessor.count * typeCount[accessor.type]);
    memcpy(ret.data(), buffer.data.data() + bufferView.byteOffset + accessor.byteOffset, accessor.count * typeCount[accessor.type] * sizeof(T));
    return ret;
}

#endif //GLTF2SF_ACCESSOR_H
