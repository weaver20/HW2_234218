cmake_minimum_required(VERSION 3.19)
project(HW2_WET)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW2_WET main.cpp
        Tree.h
        TNode.h
        Union_Find.h
        CarType.h
        CarModel.h
        DSW.h
        Exceptions.hpp
        Tree2_Key.h
        Tree3_Key.h
        Tree4_Key.h
        Tree4_Data.h
        library.h
        CarType.cpp
        CarModel.cpp
        DSW.cpp
        Tree2_Key.cpp
        Tree3_Key.cpp
        Tree4_Key.cpp
        Tree4_Data.cpp)