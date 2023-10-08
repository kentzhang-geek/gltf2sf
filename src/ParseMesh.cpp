//
// Created by administrator on 10/7/2023.
//

#include "ParseMesh.h"

std::unique_ptr<sf_MeshPrimitiveT> ParseMesh(const tinygltf::Mesh &glmesh) {
    std::unique_ptr<sf_MeshPrimitiveT> ret = std::make_unique<sf_MeshPrimitiveT>();
    glmesh.primitives[0].attributes;
    return ret;
}
