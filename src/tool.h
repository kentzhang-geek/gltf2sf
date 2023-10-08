//
// Created by administrator on 9/30/2023.
//

#ifndef RPD_FBX_PLUGIN_TOOL_H
#define RPD_FBX_PLUGIN_TOOL_H

#include <memory>
#include <atomic>
#include <fstream>
#include "common.h"
#include <iostream>
#include <utility>
#include <unordered_map>
#include <boost/serialization/config.hpp>
#include <boost/serialization/singleton.hpp>
#include "glm/glm.hpp"

#define RTP_LOG(...) internel_cpp_printer(__VA_ARGS__)

static inline void internel_cpp_printer() {
    std::cout << std::endl;
}

template <typename First, typename ...Args>
static inline void internel_cpp_printer(First&& first, Args&&... args)
{
    std::cout << first << " ";
    internel_cpp_printer(std::forward<Args>(args)...);
}

static inline std::unique_ptr<sf::Vec4d> MakeVec4d(double x, double y, double z, double w) {
    return std::make_unique<sf::Vec4d>(x,y,z, w);
};

static inline std::unique_ptr<sf::Vec3d> MakeVec3d(double x, double y, double z) {
    return std::make_unique<sf::Vec3d>(x,y,z);
};

static inline std::unique_ptr<sf::Vec2d> MakeVec2d(double x, double y) {
    return std::make_unique<sf::Vec2d>(x,y);
};

static inline std::vector<uint8_t> && ReadFileContent(std::string file_name) {
    // read file content to a byte vector
    std::ifstream ifs(file_name, std::ios::binary);
    if (!ifs.is_open())
    {
        RTP_LOG("Failed to open file:", file_name);
        return {};
    }
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(ifs), {});
    return std::forward<std::vector<uint8_t>>(buffer);
}

//static inline std::string to_string(FbxVector4 v) {
//    return std::string("(") + std::to_string(v[0]) + " " + std::to_string(v[1]) + " " + std::to_string(v[2]) + " " + std::to_string(v[3]) + ")";
//}
//
//typedef boost::serialization::singleton<std::unordered_map<uint64_t, FbxSurfaceMaterial*>> MaterialMapUniqueID;

template <typename T> class SingleContainer {
public:
    T value;
    SingleContainer(const T &input) {
        value = input;
    }

    SingleContainer() = default;

    T operator = (const T &input) {
        value = input;
        return value;
    }
};

//static inline sf::Matrix44d FbxAMaxtirxToFlatbuffersMatrix(FbxAMatrix am) {
//    sf::Matrix44d ret;
//    Vec4d row0(am.Get(0, 0), am.Get(0, 1), am.Get(0, 2), am.Get(0, 3));
//    Vec4d row1(am.Get(1, 0), am.Get(1, 1), am.Get(1, 2), am.Get(1, 3));
//    Vec4d row2(am.Get(2, 0), am.Get(2, 1), am.Get(2, 2), am.Get(2, 3));
//    Vec4d row3(am.Get(3, 0), am.Get(3, 1), am.Get(3, 2), am.Get(3, 3));
//    return sf::Matrix44d(flatbuffers::make_span({row0, row1, row2, row3}));
//}
//
//static inline FbxVector4 DumpVec4d(Vec4d v) {
//    return FbxVector4(v.x(), v.y(), v.z(), v.w());
//}
//
//static inline FbxAMatrix DumpTransform(sf::Matrix44d m) {
//    FbxAMatrix ret;
//    for (int i = 0; i < 4; ++i) {
//        auto v = DumpVec4d(*m.idx()->Get(i));
//        ret.SetRow(i, v);
//    }
//    return ret;
//}

namespace sf {
    struct SceneT;
}
typedef boost::serialization::singleton<SingleContainer<sf::SceneT *>> SceneSingleton;
namespace tinygltf {
    class Model;
}
typedef boost::serialization::singleton<SingleContainer<tinygltf::Model *>> ModelSingleton;

static inline sf::Matrix44d GLMMatrixToSFMatrix(glm::mat4 m) {
    sf::Matrix44d ret;
    sf::Vec4d row0(m[0][0], m[0][1], m[0][2], m[0][3]);
    sf::Vec4d row1(m[1][0], m[1][1], m[1][2], m[1][3]);
    sf::Vec4d row2(m[2][0], m[2][1], m[2][2], m[2][3]);
    sf::Vec4d row3(m[3][0], m[3][1], m[3][2], m[3][3]);
    return sf::Matrix44d(flatbuffers::make_span({row0, row1, row2, row3}));
}

static inline sf::Vec3d GLVecToSFVec(glm::vec3 v) {
    return sf::Vec3d(v.x, v.y, v.z);
}

static inline sf::Vec4d GLVecToSFVec(glm::vec4 v) {
    return sf::Vec4d(v.x, v.y, v.z, v.w);
}

//#define DEBUG_MODE

#endif //RPD_FBX_PLUGIN_TOOL_H
