//
// Created by administrator on 10/7/2023.
//

#ifndef GLTF2SF_PARSEMESH_H
#define GLTF2SF_PARSEMESH_H


#include <iostream>
#include "mesh_primitive.h"
#include <string>
#include "tool.h"
#include "tiny_gltf.h"

std::unique_ptr<sf::MeshPrimitiveT> ParseMesh(const tinygltf::Primitive & glmesh);


#endif //GLTF2SF_PARSEMESH_H
