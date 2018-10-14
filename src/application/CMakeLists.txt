cmake_minimum_required (VERSION 3.2)
project(MFVideoPlayer C CXX)

SET (MAIN_SOURCES
    VideoPlayerApp.cpp
	UIThreadRunner.h
	UIThreadRunner.cpp
	resources/Resources.h
    resources/Resources.rc
)

SET (COMMON_SOURCES
	../common/string_util.hpp
)

SET (UI_SOURCES
	./ui/Widget.h
	./ui/ImPopup.cpp
	./ui/ImPopup.h
	./ui/ImWidget.cpp
	./ui/ImWidget.h
	./ui/Widget.cpp
)

SET (SOURCES ${MAIN_SOURCES} ${COMMON_SOURCES} ${UI_SOURCES})

source_group(common FILES ${COMMON_SOURCES})
source_group(ui FILES ${UI_SOURCES})

if(MSVC)
	# Override the default /MD with /MT
	foreach( 
		flag_var
		CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO 
		CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO 
	)
		if( ${flag_var} MATCHES "/MD" )
			string( REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}" )
		endif()
	endforeach()
endif()

# define project's build target with project's source files
add_executable(${PROJECT_NAME} WIN32  ${SOURCES})

include_directories(BEFORE ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../common)
target_link_libraries(${PROJECT_NAME} ciWMFVideoPlayer youtube)

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/cinder-imgui.cmake)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET (INSTALL_DEST ${CMAKE_BINARY_DIR}/bin/${PLATFORM}/)

if( WIN32 )
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_BINARY_DIR}/.cppan/cmake/.cppan/cmake_bdir/cppan_build_deps_$<CONFIG>.bat)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ARGS /y \"${CMAKE_BINARY_DIR}/$<CONFIG>\\*.dll\" \"$<TARGET_FILE_DIR:${PROJECT_NAME}>\")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:youtube> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

file(MAKE_DIRECTORY ${INSTALL_DEST})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E make_directory "${INSTALL_DEST}$<CONFIG>")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> "${INSTALL_DEST}$<CONFIG>/")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:youtube> "${INSTALL_DEST}$<CONFIG>/")
