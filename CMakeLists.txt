project(Ekonom C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)
include(cmake/conan.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

conan_cmake_configure(REQUIRES spdlog/1.8.2
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conan-center
                    SETTINGS ${settings})
find_package(spdlog)
link_libraries(spdlog::spdlog)


set(SOURCES "src/EkonomApp.hpp"
            "src/EkonomApp.cpp"
            "src/main.cpp"
            )


add_app("${SOURCES}")