cmake_minimum_required(VERSION 3.10)

# set the project name
project(UnwireApi VERSION 0.0.1)

# add the executable
add_executable(UnwireApi.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#target_link_libraries(UnwireApi)



#project( CPP )
#file( GLOB SRCS *.c *.cpp *.cc *.h *.hpp )  # a variable called SRCS with all files whose path match "*.c *.cpp..."
#add_executable( ${PROJECT_NAME} ${SRCS} )
