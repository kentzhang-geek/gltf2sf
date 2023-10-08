//
// Created by administrator on 10/7/2023.
//

#include "ParseMesh.h"
#include "Accessor.h"

#pragma optimize("", off)

template <typename T>
void TrianglesFromIndecis(const std::vector<T> &indices, std::vector<sf::TriangleIndexTuple> &triangles) {
    if (indices.size() % 3 != 0) {
        RTP_LOG("Indices size not multiple of 3");
        return;
    }
    for (int i = 0; i < indices.size(); i += 3) {
        sf::TriangleIndexTuple tri{static_cast<int32_t>(indices[i]), static_cast<int32_t>(indices[i + 1]), static_cast<int32_t>(indices[i + 2])};
        triangles.push_back(tri);
    }
}

template <typename T>
void VecFromVectors(const std::vector<T> &data, std::vector<sf::Vec2d> &array) {
    if (data.size() % 2 != 0) {
        RTP_LOG("Vec3d data size not multiple of 3");
        return;
    }
    for (int i = 0; i < data.size(); i += 2) {
        array.push_back(sf::Vec2d(data[i], data[i + 1]));
    }
}

template <typename T>
void VecFromVectors(const std::vector<T> &data, std::vector<sf::Vec3d> &array) {
    if (data.size() % 3 != 0) {
        RTP_LOG("Vec3d data size not multiple of 3");
        return;
    }
    for (int i = 0; i < data.size(); i += 3) {
        array.push_back(sf::Vec3d(data[i], data[i + 1], data[i + 2]));
    }
}

template <typename T>
void VecFromVectors(const std::vector<T> &data, std::vector<sf::Vec4d> &array) {
    if (data.size() % 4 != 0) {
        RTP_LOG("Vec4d data size not multiple of 4");
        return;
    }
    for (int i = 0; i < data.size(); i += 4) {
        array.push_back(sf::Vec4d(data[i], data[i + 1], data[i + 2], data[i + 3]));
    }
}

std::unique_ptr<sf::MeshPrimitiveT> ParseMesh(const tinygltf::Primitive &glmesh) {
    std::unique_ptr<sf::MeshPrimitiveT> ret = std::make_unique<sf::MeshPrimitiveT>();
    ret->materialIdx = glmesh.material;
    // only support triangles for now
    if (glmesh.mode != TINYGLTF_MODE_TRIANGLES) {
        RTP_LOG("Mesh mode not supported: ", glmesh.mode);
        return ret;
    }
    // index
    if (glmesh.indices >= 0) {
        auto type = TypeElementofAccessor(glmesh.indices);
        switch (type) {
            case sf::ElementType_eXu16: {
                auto indices = ReadBuffer<uint16_t>(glmesh.indices);
                TrianglesFromIndecis(indices, ret->triangles);
            } break;
            case sf::ElementType_eXi16: {
                auto indices = ReadBuffer<int16_t>(glmesh.indices);
                TrianglesFromIndecis(indices, ret->triangles);
            } break;
            case sf::ElementType_eXu32: {
                auto indices = ReadBuffer<uint32_t>(glmesh.indices);
                TrianglesFromIndecis(indices, ret->triangles);
            } break;
            case sf::ElementType_eXi32: {
                auto indices = ReadBuffer<int32_t>(glmesh.indices);
                TrianglesFromIndecis(indices, ret->triangles);
            } break;
            default: {
                RTP_LOG("Index type not supported: ", type);
                return ret;
            }
        }
    }
    // attributes
    for (auto kvpair : glmesh.attributes) {
        if ((kvpair.first == "POSITION") && (kvpair.second >= 0)) {
            auto type = TypeElementofAccessor(kvpair.second);
            switch (type) {
                case sf::ElementType_eXYZf32: {
                    auto data = ReadBuffer<float>(kvpair.second);
                    VecFromVectors(data, ret->vertexs);
                } break;
                default: {
                    RTP_LOG("unsupported attribute type", kvpair.first, type);
                }
            }
        }
        else if ((kvpair.first == "NORMAL") && (kvpair.second >= 0)) {
            auto type = TypeElementofAccessor(kvpair.second);
            switch (type) {
                case sf::ElementType_eXYZf32: {
                    auto data = ReadBuffer<float>(kvpair.second);
                    ret->normalMapMode = sf::AttributeMapMode_eByVertex;
                    VecFromVectors(data, ret->normals);
                } break;
                default: {
                    RTP_LOG("unsupported attribute type", kvpair.first, type);
                }
            }
        }
        else if ((kvpair.first == "TEXCOORD_0") && (kvpair.second >= 0)) {
            auto type = TypeElementofAccessor(kvpair.second);
            switch (type) {
                case sf::ElementType_eXYf32: {
                    auto data = ReadBuffer<float>(kvpair.second);
                    ret->diffuseTexCoord = std::make_unique<sf::MeshTexCoordsT>();
                    ret->diffuseTexCoord->texCoordMapMode = sf::AttributeMapMode_eByVertex;
                    VecFromVectors(data, ret->diffuseTexCoord->texCoords);
                } break;
                default: {
                    RTP_LOG("unsupported attribute type", kvpair.first, type);
                }
            }
        }
        else if ((kvpair.first == "TEXCOORD_1") && (kvpair.second >= 0)) {
            auto type = TypeElementofAccessor(kvpair.second);
            switch (type) {
                case sf::ElementType_eXYf32: {
                    auto data = ReadBuffer<float>(kvpair.second);
                    ret->specularTexCoord = std::make_unique<sf::MeshTexCoordsT>();
                    ret->specularTexCoord->texCoordMapMode = sf::AttributeMapMode_eByVertex;
                    VecFromVectors(data, ret->specularTexCoord->texCoords);
                } break;
                default: {
                    RTP_LOG("unsupported attribute type", kvpair.first, type);
                }
            }
        }
        else if ((kvpair.first == "TEXCOORD_2") && (kvpair.second >= 0)) {
            auto acc = gModel->accessors[kvpair.second];
            auto type = TypeElementofAccessor(kvpair.second);
            switch (type) {
                case sf::ElementType_eXYf32: {
                    auto data = ReadBuffer<float>(acc.bufferView);
                    ret->normalTexCoord = std::make_unique<sf::MeshTexCoordsT>();
                    ret->normalTexCoord->texCoordMapMode = sf::AttributeMapMode_eByVertex;
                    VecFromVectors(data, ret->normalTexCoord->texCoords);
                } break;
                default: {
                    RTP_LOG("unsupported attribute type", kvpair.first, type);
                }
            }
        }
        else {
            RTP_LOG("unsupported attribute", kvpair.first);
        }
    }
    return ret;
}
