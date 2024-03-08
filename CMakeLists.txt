cmake_minimum_required(VERSION 3.23)
project(LearnOpengl)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/glad.c main1.cpp)
#link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
