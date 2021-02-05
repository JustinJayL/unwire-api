# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(UnwireApi)

add_executable(UnwireApi UnwireApi.cpp)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(UnwireApi PRIVATE CURL::libcurl)
