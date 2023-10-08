//
// Created by administrator on 10/7/2023.
//

#ifndef GLTF2SF_PARSEMATERIAL_H
#define GLTF2SF_PARSEMATERIAL_H

#include "scene.h"
#include <iostream>
#include <string>
#include "tool.h"
#include "tiny_gltf.h"

std::unique_ptr<sf::MaterialT> ParseMaterial(const tinygltf::Material & glmat, uint64_t idx);


#endif //GLTF2SF_PARSEMATERIAL_H
