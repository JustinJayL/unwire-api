# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 17)
project(UnwireApi)

add_executable(UnwireApi UnwireApi.cpp)

find_package(OpenSSL REQUIRED)
find_package(CURL CONFIG REQUIRED)

target_link_libraries(UnwireApi PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(UnwireApi PRIVATE CURL::libcurl)
