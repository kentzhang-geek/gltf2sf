cmake_minimum_required(VERSION 3.0)
project(gltf2sf)
include_directories(scene_flat_dev/generated/cpp) # for dev compiling

# for flatbuffers
include_directories(SDK/flatbuffers/include)
link_directories(SDK/flatbuffers/lib)
link_libraries(flatbuffers)

# for boost
include_directories(SDK/boost)
link_directories(SDK/boost/stage/lib)

# for tinygltf
include_directories(SDK/tinygltf/include)
link_directories(SDK/tinygltf/lib)
link_libraries(tinygltf)

# for glm
include_directories(SDK/glm)
link_directories(SDK/glm/lib)
link_libraries(glm_static)

set(SRC
		src/gltfToSFscene.cpp
		src/tool.h
		src/gltfToSFscene.h
		src/ParseMaterial.cpp
		src/ParseMaterial.h
		src/ParseCamera.cpp
		src/ParseCamera.h
		src/ParseNode.cpp
		src/ParseNode.h
		src/ParseMesh.cpp
		src/ParseMesh.h
        src/Accessor.cpp
        src/Accessor.h
)

add_executable(${PROJECT_NAME} ${SRC} src/main.cpp
		)
