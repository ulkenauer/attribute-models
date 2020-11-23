cmake_minimum_required(VERSION 3.16)
project(prog)

set(CMAKE_CXX_STANDARD 14)

add_executable(prog src/main.cpp)

add_library(mylib SHARED IMPORTED )
# You can define two import-locations: one for debug and one for release.
#set_target_properties(mylib PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/res/libcore.so )
#set_target_properties(mylib PROPERTIES IMPORTED_LOCATION /home/ulkenauer/coding/projects/cpp/prog/libcore.so )

#set_target_properties(mylib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libcore.so ) #works
set_target_properties(mylib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-debug/libcore.so)
TARGET_LINK_LIBRARIES(prog mylib)