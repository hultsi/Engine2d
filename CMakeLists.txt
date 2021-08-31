cmake_minimum_required(VERSION 3.16.3)

# project
project(Engine2d)
add_executable(${CMAKE_PROJECT_NAME} main.cpp ./src/Vector2d.cpp ./src/Engine2d.cpp ./src/Rectangle.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include headers
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

# include opengl/vulkan & glfw headers
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/libglfw3.a)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glut)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GLU)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GL)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC dl)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC pthread)