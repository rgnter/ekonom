cmake_minimum_required(VERSION 3.19)
project(ekonom)

set(CMAKE_CXX_STANDARD 20)


add_executable(ekonom main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC deps/submodules/spdlog/include)
target_link_libraries(${PROJECT_NAME} deps/lib/spdlog/libspdlog.a)