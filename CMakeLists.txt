cmake_minimum_required(VERSION 3.16.3)

# project
project(Engine2d)

option(DEBUG "Debug mode on or off" ON)

if (DEBUG)
	add_compile_definitions(DEBUG=1)
	add_executable(${CMAKE_PROJECT_NAME} 
		main.cpp
		./src/Engine2d.cpp
		./src/Control.cpp
		./src/Rectangle.cpp
		./src/DebugCircle.cpp
		./src/DebugLine.cpp
		./src/Collision.cpp
		./src/Vector2d.cpp
	)
	add_compile_options(-Wall -Wextra -Wpedantic -g)
else()
	add_compile_definitions(DEBUG=0)
	add_executable(${CMAKE_PROJECT_NAME} 
		main.cpp
		./src/Engine2d.cpp
		./src/Control.cpp
		./src/Rectangle.cpp
		./src/Collision.cpp
		./src/Vector2d.cpp
	)
	add_compile_options(-Wall -Wextra -Wpedantic -g)
endif(DEBUG)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include headers
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

# todo: change the build process
#add_subdirectory(src)

# include opengl/vulkan & glfw headers
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/libglfw3.a)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glut)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GLU)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GL)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC dl)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC pthread)