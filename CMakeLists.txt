cmake_minimum_required(VERSION 2.8)

project(HootsimSDL)

# Setup Options
# no options yet.

# TODO:
# - Non GCC compiler support

IF ( CMAKE_COMPILER_IS_GNUCXX )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

	IF(CMAKE_BUILD_TYPE MATCHES Debug)
		# Enable debug flags and stricter compliation for debug builds.
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wextra -Werror -Wno-unused-parameter" )
	ELSE()
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" )
	ENDIF()
ENDIF ( )

# Disable GLM radian warnings
add_definitions(-DGLM_FORCE_RADIANS)

find_package(OpenGL REQUIRED)

# TODO add package for SDL 2

SET(GL_SRC ${CMAKE_SOURCE_DIR}/opengl/gl_core_3_3.c ${CMAKE_SOURCE_DIR}/opengl/hootgl.cpp)
SET(GL_INCLUDE ${CMAKE_SOURCE_DIR}/opengl)

add_subdirectory(hootsim2000)

add_subdirectory(main)

# Tests to come.
# add_subdirectory(tests)
