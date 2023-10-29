//
// Created by administrator on 10/7/2023.
//

#include "ParseNode.h"
#include "scene.h"
#include "camera.h"
#include "ParseCamera.h"
#include "ParseMesh.h"
#include "ParseLight.h"
#include "glm/glm.hpp"
#include "tool.h"

std::unique_ptr<sf::BVHNodeT> ParseNode(const tinygltf::Node &glnode, uint64_t idx, glm::mat4 parent_transform) {
    std::unique_ptr<sf::BVHNodeT> sfn = std::make_unique<sf::BVHNodeT>();
    sfn->name = glnode.name;
    glm::mat4 local = glm::mat4(1.0f);
    // parse matrix
    if (glnode.matrix.size() == 16) {
        local = glm::mat4(glnode.matrix[0], glnode.matrix[1], glnode.matrix[2], glnode.matrix[3],
                        glnode.matrix[4], glnode.matrix[5], glnode.matrix[6], glnode.matrix[7],
                        glnode.matrix[8], glnode.matrix[9], glnode.matrix[10], glnode.matrix[11],
                        glnode.matrix[12], glnode.matrix[13], glnode.matrix[14], glnode.matrix[15]);
    }
    sfn->local_transform = std::make_unique<sf::Matrix44d>(GLMMatrixToSFMatrix(local));
    parent_transform = parent_transform * local;
    sfn->global_transform = std::make_unique<sf::Matrix44d>(GLMMatrixToSFMatrix(parent_transform));
    // if mesh
    if (glnode.mesh >= 0) {
        auto mesh = ModelSingleton::get_const_instance().value->meshes[glnode.mesh];
        for (auto prim : mesh.primitives) {
            sfn->meshes.push_back(ParseMesh(prim));
        }
    }
    // if camera
    if (glnode.camera >= 0) {
        SceneSingleton::get_mutable_instance().value->cameras.push_back(ParseCamera(ModelSingleton::get_const_instance().value->cameras[glnode.camera], glnode, parent_transform));
    }
    // if light
    if (glnode.light >= 0) {
        SceneSingleton::get_mutable_instance().value->lights.push_back(ParseLight(ModelSingleton::get_const_instance().value->lights[glnode.light], glnode, parent_transform));
    }
//    sfn->mesh = glnode.mesh;
//    sfn->camera = glnode.camera;
    for (auto cit : glnode.children) {
        sfn->children.push_back(ParseNode(ModelSingleton::get_const_instance().value->nodes[cit], cit, parent_transform));
    }
    return sfn;
}
