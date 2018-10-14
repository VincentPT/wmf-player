cmake_minimum_required(VERSION 3.2.0)

if (NOT DEFINED CINDER_PATH)
    set(CINDER_PATH ${CMAKE_SOURCE_DIR}/external/Cinder)
endif()

include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
find_package( cinder REQUIRED PATHS
	  "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
	  "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
target_link_libraries( ${PROJECT_NAME} cinder )