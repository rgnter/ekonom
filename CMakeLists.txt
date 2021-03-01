project(Ekonom C CXX)
cmake_minimum_required(VERSION 3.3.2)

include_directories(build/SDK/include)

include(cmake/App.cmake)

set(SOURCES "src/EkonomApp.hpp"
            "src/EkonomApp.cpp"
            "src/main.cpp"
            "src/sys/SalesReport.hpp")

add_app("${SOURCES}")
