//
// Created by administrator on 10/7/2023.
//

#ifndef GLTF2SF_ACCESSOR_H
#define GLTF2SF_ACCESSOR_H

#include <iostream>
#include <string>
#include "tool.h"
#include "tiny_gltf.h"
#include "common.h"
#include <vector>

template <typename T>
std::vector<T> ExtractAccessor(int accIdx);

sf::ElementType TypeElementofAccessor(int accIdx);

template <typename T>
std::vector<T> ReadBuffer(int bufferViewIdx);

#endif //GLTF2SF_ACCESSOR_H
