cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_library(core SHARED library.cpp library.h src/attribute/AttributeTree.h src/serializers/ISerializer.h src/serializers/PlainSerializer/PlainSerializer.cpp src/serializers/PlainSerializer/PlainSerializer.h src/serializers/index.h src/attribute/AttributeNode.cpp src/attribute/AttributeNode.h src/attribute/index.h src/attribute/types.h src/attribute/AttributeTree.cpp src/attribute/HasAttributes.h src/attribute/IAttributeModel.h)
