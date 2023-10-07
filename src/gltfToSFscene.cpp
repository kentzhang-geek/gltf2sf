//
// Created by Admin on 2022/6/18.
//

#include "scene.h"
#include "gltfToSFscene.h"
#include <iostream>
#include <string>
#include "tool.h"
#include "tiny_gltf.h"

std::unique_ptr<sf_SceneT> gltfToSFscene(std::string filename) {
    using namespace tinygltf;

    Model model;
    TinyGLTF loader;
    std::string err;
    std::string warn;

    bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);

    // convert to flatbuffers
    auto scene = new sf_SceneT();
    SceneSingleton::get_mutable_instance().value = scene;

    // parse material first


    return std::unique_ptr<sf_SceneT>(scene);
}

