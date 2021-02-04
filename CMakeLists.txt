cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include("cmake/HunterGate.cmake")

HunterGate(
	    URL "https://github.com/cpp-pm/hunter/archive/v0.23.293.tar.gz"
	    SHA1 "e8e5470652db77149d9b38656db2a6c0b7642693"
)

# set the project name
project(UnwireApi VERSION 0.0.1)


hunter_add_package(nlohmann_json)
hunter_add_package(CURL)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

# add the executable
add_executable(UnwireApi UnwireApi.cpp)

target_link_libraries(UnwireApi PUBLIC CURL::libcurl nlohmann_json::nlohmann_json)

#target_link_libraries(UnwireApi CURL::libcurl)

#target_link_libraries(UnwireApi)



#project( CPP )
#file( GLOB SRCS *.c *.cpp *.cc *.h *.hpp )  # a variable called SRCS with all files whose path match "*.c *.cpp..."
#add_executable( ${PROJECT_NAME} ${SRCS} )
