cmake_minimum_required(VERSION 3.15)
project(parallel_sum LANGUAGES CXX)

# Find pybind11
find_package(pybind11 REQUIRED)

# Include directories for pybind11
include_directories(${pybind11_INCLUDE_DIRS})

# Define the Swift package path
set(SWIFT_PACKAGE_PATH ${CMAKE_SOURCE_DIR}/lib)

# Define the Swift build configuration (Debug or Release)
# TODO: debug/release
set(SWIFT_BUILD_CONFIGURATION debug)

# Determine the path to the built library
set(SWIFT_BUILD_DIR ${SWIFT_PACKAGE_PATH}/.build/${SWIFT_BUILD_CONFIGURATION})
set(SWIFT_LIB ${SWIFT_BUILD_DIR}/libParallelSum.a)

# Expand the include directories for the Swift package
set(INCLUDE_ARGS "")
foreach(path ${pybind11_INCLUDE_DIRS})
    list(APPEND INCLUDE_ARGS "-Xcxx")
    list(APPEND INCLUDE_ARGS "-I${path}")
endforeach()

# Add a custom command to build the Swift library
add_custom_command(
    OUTPUT ${SWIFT_LIB}
    COMMAND swift build -c ${SWIFT_BUILD_CONFIGURATION} ${INCLUDE_ARGS}
    WORKING_DIRECTORY ${SWIFT_PACKAGE_PATH}
    COMMENT "Building Swift Package"
)

# Add a custom target that depends on the output of the custom command
add_custom_target(swift_build DEPENDS ${SWIFT_LIB})

# Include the headers from the Swift package (C++ code)
include_directories(${SWIFT_PACKAGE_PATH}/Sources/ParallelSum)

# Add the built library as an imported target
add_library(ParallelSum STATIC IMPORTED GLOBAL)
set_target_properties(ParallelSum PROPERTIES
    IMPORTED_LOCATION ${SWIFT_LIB}
)

# Ensure that the ParallelSum library depends on swift_build
add_dependencies(ParallelSum swift_build)

# Create the Python module
pybind11_add_module(_parallel_sum
    python/parallel_sum/parallel_sum.cpp
)

# Ensure the Python module depends on the ParallelSum library
add_dependencies(_parallel_sum ParallelSum)

# Link the imported library to the Python module
target_link_libraries(_parallel_sum PRIVATE ParallelSum)

# Install the Python module into the package directory
install(TARGETS _parallel_sum
        LIBRARY DESTINATION parallel_sum  # Install into 'parallel_sum' package
)
