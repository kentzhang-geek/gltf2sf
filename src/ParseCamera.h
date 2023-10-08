//
// Created by administrator on 10/7/2023.
//

#ifndef GLTF2SF_PARSECAMERA_H
#define GLTF2SF_PARSECAMERA_H

#include <iostream>
#include "camera.h"
#include <string>
#include "tool.h"
#include "tiny_gltf.h"

std::unique_ptr<sf_CameraT> ParseCamera(const tinygltf::Camera & glcam, const tinygltf::Node &glnode, const glm::mat4 & parent_transform);

#endif //GLTF2SF_PARSECAMERA_H
