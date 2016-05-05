project(jsonc-path)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_definitions(-std=c++0x)
add_definitions(-O0)
add_definitions(-g)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
    json-c
)
