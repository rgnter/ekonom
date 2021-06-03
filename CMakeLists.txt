cmake_minimum_required(VERSION 3.3.2)

project(ekonom VERSION 1.0.2)
configure_file(src/EkonomVersion.hpp.in EkonomVersion.hpp)

include(cmake/App.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/cmake/conan.cmake")
endif()
include("${CMAKE_BINARY_DIR}/cmake/conan.cmake")

if (UNIX)
  if (APPLE)
    set(EKONOM_PLATFORM "mac")
  else ()
    set(EKONOM_PLATFORM "lnx")
  endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(EKONOM_PLATFORM "win")
else ()
  message(FATAL_ERROR "Unsupported OS '${CMAKE_SYSTEM_NAME}'")
endif ()

conan_cmake_configure(REQUIRES spdlog/1.8.2 nlohmann_json/3.9.1 cxxopts/2.2.1
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conan-center
                    SETTINGS ${settings})
find_package(spdlog)
find_package(nlohmann_json)
find_package(cxxopts)

add_library(openxlsx STATIC IMPORTED)

if(EKONOM_PLATFORM MATCHES "win")    
   set_target_properties(openxlsx PROPERTIES
  	IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/deps/x64-win/lib/openxlsx-static.lib"
  	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/deps/include/openxlsx")
elseif(EKONOM_PLATFORM MATCHES "lnx")
   set_target_properties(openxlsx PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/deps/x64-lnx/lib/openxlsx-static.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/deps/include/openxlsx")
endif()

link_libraries(spdlog::spdlog openxlsx nlohmann_json::nlohmann_json cxxopts::cxxopts)

set(WEB_SOURCE_ROOT "src/web")
set(SOURCES "src/cxx/EkonomApp.hpp"
            "src/cxx/EkonomApp.cpp"
            "src/cxx/main.cpp"
            "src/cxx/cfg/config_provider.hpp"
            "src/cxx/cfg/config_provider.cpp"
            )

add_app("${SOURCES}" "${WEB_SOURCE_ROOT}")
target_include_directories(ekonom PUBLIC
        "${PROJECT_BINARY_DIR}"
        )



