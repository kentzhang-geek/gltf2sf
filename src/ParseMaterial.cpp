//
// Created by administrator on 10/7/2023.
//

#include "ParseMaterial.h"
#pragma optimize("", off)

typedef std::tuple<int, int, int> CompDeptPixelFormat;

template <>
struct std::hash<CompDeptPixelFormat>
{
    std::size_t operator()(const CompDeptPixelFormat & k) const
    {
        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        return (hash<int>()(std::get<0>(k)
                 ^ (hash<int>()(std::get<1>(k)) << 1)) >> 1)
               ^ (hash<int>()(std::get<2>(k)) << 1);
    }
};

std::unique_ptr<sf::TextureT> ParseTexture(int idx) {
    std::unique_ptr<sf::TextureT> sftexture = std::make_unique<sf::TextureT>();
    sftexture->id = idx;
    sftexture->image_type = sf::ImageType_eRawData;
    tinygltf::Texture & gltfTexture = ModelSingleton::get_const_instance().value->textures[idx];
    tinygltf::Image &img = ModelSingleton::get_const_instance().value->images[gltfTexture.source];
    sftexture->media_name = gltfTexture.name;
    sftexture->file_name = img.name;
    sftexture->data = img.image;
    const static std::unordered_map<CompDeptPixelFormat, sf::PixelType> typeMap = {
            {{1,8, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::PixelType_eRu8},
            {{2,8, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::PixelType_eRGu8},
            {{3,8, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::PixelType_eRGBu8},
            {{4,8, TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE}, sf::PixelType_eRGBAu8},
            {{1,16, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::PixelType_eRu16},
            {{2,16, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::PixelType_eRGu16},
            {{3,16, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::PixelType_eRGBu16},
            {{4,16, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT}, sf::PixelType_eRGBAu16},
            {{1,32, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::PixelType_eRu32},
            {{2,32, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::PixelType_eRGu32},
            {{3,32, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::PixelType_eRGBu32},
            {{4,32, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT}, sf::PixelType_eRGBAu32},
            {{1,16, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRf16},
            {{2,16, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRGf16},
            {{3,16, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRGBf16},
            {{4,16, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRGBAf16},
            {{1,32, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRf32},
            {{2,32, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRGf32},
            {{3,32, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRGBf32},
            {{4,32, TINYGLTF_COMPONENT_TYPE_FLOAT}, sf::PixelType_eRGBAf32},
    };
    if (typeMap.find({img.component, img.bits, img.pixel_type}) == typeMap.end()) {
        RTP_LOG("unsupported pixel type", img.component, img.bits, img.pixel_type);
    } else {
        sftexture->pixel_type = typeMap.at({img.component, img.bits, img.pixel_type});
    }
    return sftexture;
}

std::unique_ptr<sf::MaterialT> ParseMaterial(const tinygltf::Material &glmat, uint64_t idx) {
    std::unique_ptr<sf::MaterialT> sfmat = std::make_unique<sf::MaterialT>();
    sfmat->name = glmat.name;
    sfmat->id = idx;
    // gltf pbr surface for gltf
    sfmat->surface.Set(sf::GltfPbrSurfaceT());
    for (auto kvpair : glmat.values) {
        if (kvpair.first == "baseColorTexture") {
            sfmat->surface.AsGltfPbrSurface()->baseColor_texture = ParseTexture(kvpair.second.TextureIndex());
        }
        else if (kvpair.first == "baseColorFactor") {
            if (kvpair.second.number_array.size() >= 3) {
                sfmat->surface.AsGltfPbrSurface()->baseColor = std::make_unique<sf::Vec3d>(
                        kvpair.second.number_array[0], kvpair.second.number_array[1], kvpair.second.number_array[2]);
            } else {
                RTP_LOG("unsupported baseColorFactor type", kvpair.first, glmat.name);
            }
        }
        else if (kvpair.first == "metallicFactor") {
            if (kvpair.second.has_number_value) {
                sfmat->surface.AsGltfPbrSurface()->metallic = std::make_unique<sf::Vec3d>(kvpair.second.number_value, kvpair.second.number_value, kvpair.second.number_value);
            } else {
                RTP_LOG("unsupported metallicFactor type", kvpair.first, glmat.name);
            }
        }
        else if (kvpair.first == "roughnessFactor") {
            if (kvpair.second.has_number_value) {
                sfmat->surface.AsGltfPbrSurface()->roughness = std::make_unique<sf::Vec3d>(kvpair.second.number_value, kvpair.second.number_value, kvpair.second.number_value);
            } else {
                RTP_LOG("unsupported roughnessFactor type", kvpair.first, glmat.name);
            }
        }
        else {
            RTP_LOG("unsupported material parameter", kvpair.first, kvpair.second.string_value);
        }
    }
    return sfmat;
}
