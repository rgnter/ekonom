project(Ekonom C CXX)
cmake_minimum_required(VERSION 3.3.2)

set(EKONOM_VERMAJOR 1)
set(EKONOM_VERMINOR 0)
set(EKONOM_VERPATCH 0)

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

if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/deps/x64-win/include)
    link_directories(${PROJECT_SOURCE_DIR}/deps/x64-win/lib)
endif()


link_libraries(spdlog::spdlog "openxlsx-static")

set(WEB_SOURCE_ROOT "src/web")
set(SOURCES "src/cxx/EkonomApp.hpp"
            "src/cxx/EkonomApp.cpp"
            "src/cxx/main.cpp"
            )

add_app("${SOURCES}" "${WEB_SOURCE_ROOT}")



