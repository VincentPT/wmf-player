cmake_minimum_required (VERSION 3.2)
project(MultiVideoPlayer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

add_subdirectory(blocks)
add_subdirectory(youtube)
add_subdirectory(application)