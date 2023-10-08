//
// Created by administrator on 10/7/2023.
//

#include "ParseMesh.h"

std::unique_ptr<sf::MeshPrimitiveT> ParseMesh(const tinygltf::Mesh &glmesh) {
    std::unique_ptr<sf::MeshPrimitiveT> ret = std::make_unique<sf::MeshPrimitiveT>();
    glmesh.primitives[0].attributes;
    return ret;
}
