cmake_minimum_required(VERSION 3.2.0)
project(blocks)

#get_filename_component(CINDER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)

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

set (BLOCK_PROJECT_1 ciWMFVideoPlayer)

set (CIWMFVIDEOPLAYER_MAIN
	./ciWMFVideoPlayer/ciWMFVideoPlayer.cpp
	./ciWMFVideoPlayer/ciWMFVideoPlayerUtils.cpp
	./ciWMFVideoPlayer/ciWMFVideoPlayer.h
	./ciWMFVideoPlayer/ciWMFVideoPlayerUtils.h
)

set (CIWMFVIDEOPLAYER_PRESENTER
	./ciWMFVideoPlayer/presenter/PresentEngine.cpp
	./ciWMFVideoPlayer/presenter/Presenter.cpp
	./ciWMFVideoPlayer/presenter/PresenterHelpers.cpp
	./ciWMFVideoPlayer/presenter/scheduler.cpp
	./ciWMFVideoPlayer/presenter/EVRPresenter.h
	./ciWMFVideoPlayer/presenter/EVRPresenterUuid.h
	./ciWMFVideoPlayer/presenter/PresentEngine.h
	./ciWMFVideoPlayer/presenter/Presenter.h
	./ciWMFVideoPlayer/presenter/PresenterHelpers.h
	./ciWMFVideoPlayer/presenter/scheduler.h
)

set (CIWMFVIDEOPLAYER_PRESENTER_COMMON
	./ciWMFVideoPlayer/presenter/common/AsyncCB.h
	./ciWMFVideoPlayer/presenter/common/BufferLock.h
	./ciWMFVideoPlayer/presenter/common/ClassFactory.h
	./ciWMFVideoPlayer/presenter/common/GrowArray.h
	./ciWMFVideoPlayer/presenter/common/PropVar.h
	./ciWMFVideoPlayer/presenter/common/TinyMap.h
	./ciWMFVideoPlayer/presenter/common/common.h
	./ciWMFVideoPlayer/presenter/common/critsec.h
	./ciWMFVideoPlayer/presenter/common/linklist.h
	./ciWMFVideoPlayer/presenter/common/logging.h
	./ciWMFVideoPlayer/presenter/common/logmediatype.h
	./ciWMFVideoPlayer/presenter/common/mediatype.h
	./ciWMFVideoPlayer/presenter/common/mfutils.h
	./ciWMFVideoPlayer/presenter/common/registry.h
	./ciWMFVideoPlayer/presenter/common/trace.h
)

source_group(presenter FILES ${CIWMFVIDEOPLAYER_PRESENTER})
source_group(presenter\\common FILES ${CIWMFVIDEOPLAYER_PRESENTER_COMMON})

add_library( ${BLOCK_PROJECT_1} ${CIWMFVIDEOPLAYER_PRESENTER_COMMON} ${CIWMFVIDEOPLAYER_PRESENTER} ${CIWMFVIDEOPLAYER_MAIN})

target_include_directories( ${BLOCK_PROJECT_1} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ciWMFVideoPlayer)

include( "${CINDER_PATH}/proj/cmake/configure.cmake" )

find_package( cinder REQUIRED PATHS
	  "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
	  "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
target_link_libraries( ${BLOCK_PROJECT_1} PUBLIC cinder )

set_target_properties(${BLOCK_PROJECT_1} PROPERTIES FOLDER blocks)