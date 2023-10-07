//
// Created by Kent on 2022/6/18.
//
#include "gltfToSFscene.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "tool.h"
#include "scene.h"

std::vector<unsigned char> && ReadGltfFileToSF(std::string filepath) {
    flatbuffers::FlatBufferBuilder builder;
    printf("get file %s\n", filepath.c_str());
    fflush(stdout);
    auto scene = gltfToSFscene(filepath);
    builder.Finish(Scene::Pack(builder, scene.get()));
    std::vector<unsigned char> ret(builder.GetSize());
    memcpy(ret.data(), builder.GetBufferPointer(), builder.GetSize());

    return std::move(ret);
}

int main(int argc, char **argv) {
    if (argc == 3) {
        std::string path(argv[1]);
        auto buffer = ReadGltfFileToSF(path);
        std::string outfile(argv[2]);
        // write data to file
        std::ofstream ofile(outfile, std::ios::binary);
        ofile.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        ofile.close();
        exit(0);
    } else if (argc == 4) {
        if (std::string(argv[1]) == "-r") {
            std::ifstream infile(argv[2], std::ios::binary);
            std::vector<char> buffer(std::istreambuf_iterator<char>(infile), {});
            // TODO
            std::string fpath = argv[3];
            exit(0);
        }
    }

    // print usage
    {
        std::cout << "Usage: gltf2sf <input.glb> <output.sf>" << std::endl;
        std::cout << "Usage: gltf2sf -r <input.sf> <output.glb>" << std::endl;
        exit(0);
    }

    return 0;
}
