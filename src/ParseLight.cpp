//
// Created by administrator on 10/13/2023.
//

#include "ParseLight.h"

std::unique_ptr<sf::LightT>
ParseLight(const tinygltf::Light &glLight, const tinygltf::Node &glnode, const glm::mat4 &parent_transform) {
    std::unique_ptr<sf::LightT> sflight = std::make_unique<sf::LightT>();
    RTP_LOG("Light name: ", glLight.name);
    RTP_LOG("Light type: ", glLight.type);
    // TODO
    return sflight;
}
