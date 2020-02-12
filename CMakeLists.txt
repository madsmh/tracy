cmake_minimum_required(VERSION 3.10)
project(tracy)

set(CMAKE_CXX_STANDARD 17)

add_executable(tracy
               main.cpp
               vector3.h
               objects/object.cpp
               objects/object.h
               ray.h
               cameras/camera.h
               objects/sphere.cpp
               objects/sphere.h
               objects/box.cpp
               objects/box.h objects/circle.cpp objects/circle.h)
