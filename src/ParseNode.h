//
// Created by administrator on 10/7/2023.
//

#ifndef GLTF2SF_PARSENODE_H
#define GLTF2SF_PARSENODE_H


#include <iostream>
#include "bvh_accel.h"
#include <string>
#include "tool.h"
#include "tiny_gltf.h"
#include "glm/glm.hpp"

std::unique_ptr<sf::BVHNodeT> ParseNode(const tinygltf::Node &glnode, uint64_t idx, glm::mat4 parent_transform);

#endif //GLTF2SF_PARSENODE_H
