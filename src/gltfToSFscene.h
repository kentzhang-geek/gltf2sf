//
// Created by administrator on 10/6/2023.
//

#ifndef GLTF2SF_GLTFTOSFSCENE_H
#define GLTF2SF_GLTFTOSFSCENE_H

#include <memory>
#include "scene.h"
#include <string>

std::unique_ptr<sf::SceneT> gltfToSFscene(std::string filename);

#endif //GLTF2SF_GLTFTOSFSCENE_H
