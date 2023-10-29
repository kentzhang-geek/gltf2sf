//
// Created by administrator on 10/13/2023.
//

#ifndef GLTF2SF_PARSELIGHT_H
#define GLTF2SF_PARSELIGHT_H

#include <iostream>
#include "light.h"
#include <string>
#include "tool.h"
#include "tiny_gltf.h"

std::unique_ptr<sf::LightT> ParseLight(const tinygltf::Light & glLight, const tinygltf::Node &glnode, const glm::mat4 & parent_transform);

#endif //GLTF2SF_PARSELIGHT_H
