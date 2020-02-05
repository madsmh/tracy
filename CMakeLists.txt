cmake_minimum_required(VERSION 3.15)
project(tracy)

set(CMAKE_CXX_STANDARD 20)

add_executable(tracy main.cpp vector3.h objects/object.cpp objects/object.h ray.h cameras/camera.h objects/sphere.cpp objects/sphere.h objects/box.cpp objects/box.h)