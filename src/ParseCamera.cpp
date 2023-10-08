//
// Created by administrator on 10/7/2023.
//
#include "ParseCamera.h"
#define GLM_SWIZZLE
#define GLM_EXT_INCLUDED
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

std::unique_ptr<sf_CameraT> ParseCamera(const tinygltf::Camera &glcam, const tinygltf::Node &glnode, const glm::mat4 & parent_transform) {
    std::unique_ptr<sf_CameraT> sfcam = std::make_unique<sf_CameraT>();
    sfcam->name = glcam.name;
    // no orthographic camera for now, and y-up for default
    if (glcam.type == "perspective") {
        glm::vec4 eye(0.0f, 0.0f, 0.0f, 1.0f);
        eye = parent_transform * eye;
        eye = eye / eye.w;
        sfcam->eye = std::make_unique<Vec3d>(GLVecToSFVec(glm::vec3(eye)));
        glm::vec4 center(0.0f, 0.0f, -1.0f, 1.0f);
        center = parent_transform * center;
        center = center / center.w;
        sfcam->center = std::make_unique<Vec3d>(GLVecToSFVec(glm::vec3(center)));
        glm::vec4 up(0.0f, 1.0f, 0.0f, 1.0f);
        up = parent_transform * up;
        up = up / up.w;
        sfcam->upAxis = std::make_unique<Vec3d>(GLVecToSFVec(glm::vec3(up)));
    }
    else {
        RTP_LOG("Camera type not supported: " , glcam.type);
    }

    return sfcam;
}
