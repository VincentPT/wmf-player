cmake_minimum_required (VERSION 3.2)
project(youtube C CXX)

SET (MAIN_SOURCES
    YoutubeInterface.cpp
    YoutubeInterface.h
    YoutubeInterfaces.h
)

SET (COMMON_SOURCES 
	../common/AsyncTask.cpp
	../common/AsyncTask.h
)

SET (SOURCES ${MAIN_SOURCES} ${COMMON_SOURCES})

source_group(common FILES ${COMMON_SOURCES})

# define project's build target with project's source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_definitions(-DEXPORT_YOUTUBE_INTERFACES)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

find_package(CPPAN REQUIRED)
set (CPPREST_PACKAGE pvt.cppan.demo.microsoft.cpprestsdk-2.9.1)
cppan_add_package(${CPPREST_PACKAGE})
cppan_execute()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../common ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_PACKAGE})

SET (INSTALL_DEST ${CMAKE_BINARY_DIR}/bin/${PLATFORM}/)
install(FILES $<TARGET_FILE:${PROJECT_NAME}> DESTINATION ${INSTALL_DEST}/debug CONFIGURATIONS Debug)
install(FILES $<TARGET_FILE:${PROJECT_NAME}> DESTINATION ${INSTALL_DEST}/release CONFIGURATIONS Release)