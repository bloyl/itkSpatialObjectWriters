cmake_minimum_required(VERSION 2.8.6 FATAL_ERROR)
include(CMakeDependentOption)

if(WIN32)
  cmake_minimum_required(VERSION 2.8.8)
endif()

project(itkSpatialObjectWriters)

#-----------------------------------------------------------------------------
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "Coverage" "MinSizeRel" "RelWithDebInfo")
endif()

#-----------------------------------------------------------------------------
# Support a coverage build type

IF(${CMAKE_GENERATOR} MATCHES "Unix Makefiles" OR ${CMAKE_GENERATOR} MATCHES "MinGW Makefiles")
  IF(${CMAKE_BUILD_TYPE} MATCHES "Coverage")
    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fprofile-arcs")
    SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fprofile-arcs")
  ELSEIF(NOT CMAKE_BUILD_TYPE)
    MESSAGE("Concider using cmake option -DCMAKE_BUILD_TYPE=Debug,Release,Coverage instead of '${CMAKE_BUILD_TYPE}'")
  ENDIF()
ENDIF()

#-----------------------------------------------------------------------------
# Dependencies

# ITK
FIND_PACKAGE( ITK REQUIRED )
IF( ITK_FOUND )
  INCLUDE( ${ITK_USE_FILE} )
ENDIF( ITK_FOUND )

find_package(VTK REQUIRED)
include( ${VTK_USE_FILE} )

include (CTest)
mark_as_advanced (DART_TESTING_TIMEOUT)

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_MODULE_OUTPUT_DIRECTORY)
  set(CMAKE_MODULE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif()

include_directories( include )

if( BUILD_TESTING )
  add_subdirectory( test )
endif( BUILD_TESTING )
