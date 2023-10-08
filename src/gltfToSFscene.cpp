//
// Created by Admin on 2022/6/18.
//

#include "scene.h"
#include "gltfToSFscene.h"
#include <iostream>
#include <string>
#include "tool.h"
#include "tiny_gltf.h"
#include "ParseMaterial.h"
#include "ParseNode.h"

#pragma optimize("", off)

std::unique_ptr<sf::SceneT> gltfToSFscene(std::string filename) {
    using namespace tinygltf;

    Model model;
    TinyGLTF loader;
    std::string err;
    std::string warn;

    bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
    if (!ret) {
        RTP_LOG("load gltf file failed:", err);
        return nullptr;
    }
    if (!warn.empty()) {
        RTP_LOG("load gltf file warning:", warn);
    }
    ModelSingleton::get_mutable_instance().value = &model;

    // convert to flatbuffers
    auto scene = new sf::SceneT();
    SceneSingleton::get_mutable_instance().value = scene;

    // parse material first
    uint64_t idx = 0;
    for (tinygltf::Material & glmat : model.materials) {
        scene->materials.push_back(ParseMaterial(glmat, idx++));
    }

    // parse root node
    scene->root = ParseNode(model.nodes[0], 0, glm::mat4(1.0f));

    return std::unique_ptr<sf::SceneT>(scene);
}

