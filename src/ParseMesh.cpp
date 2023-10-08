//
// Created by administrator on 10/7/2023.
//

#include "ParseMesh.h"
#pragma optimize("", off)

std::unique_ptr<sf::MeshPrimitiveT> ParseMesh(const tinygltf::Primitive &glmesh) {
    std::unique_ptr<sf::MeshPrimitiveT> ret = std::make_unique<sf::MeshPrimitiveT>();
    ret->materialIdx = glmesh.material;
    // index
    return ret;
}
