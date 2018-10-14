cmake_minimum_required(VERSION 3.2.0)
project(Cinder-ImGui)

get_filename_component(CINDER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)

list( APPEND CINDER_IMGUI_SOURCES
	./src/CinderImGui.cpp
	./lib/imgui/imconfig.h
	./lib/imgui/imgui.cpp
	./lib/imgui/imgui.h
	./lib/imgui/imgui_demo.cpp
	./lib/imgui/imgui_draw.cpp
	./lib/imgui/imgui_internal.h
	./lib/imgui/imgui_widgets.cpp
	./lib/imgui/imstb_rectpack.h
	./lib/imgui/imstb_textedit.h
	./lib/imgui/imstb_truetype.h
)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

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


add_library( ${PROJECT_NAME} ${CINDER_IMGUI_SOURCES} )

target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui ${CMAKE_CURRENT_SOURCE_DIR}/include)
	  
include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
find_package( cinder REQUIRED PATHS
	  "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
	  "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
target_link_libraries( ${PROJECT_NAME} PRIVATE cinder )

if(MSVC)
	set_target_properties( ${PROJECT_NAME} PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG			"${CMAKE_CURRENT_SOURCE_DIR}/lib/msw/${PLATFORM}/Debug"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE		"${CMAKE_CURRENT_SOURCE_DIR}/lib/msw/${PLATFORM}/Release"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG			"${CMAKE_CURRENT_SOURCE_DIR}/lib/msw/${PLATFORM}/Debug"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE		"${CMAKE_CURRENT_SOURCE_DIR}/lib/msw/${PLATFORM}/Release"
    )
endif()