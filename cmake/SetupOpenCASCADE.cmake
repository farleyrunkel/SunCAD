# Copyright [2024] SunCAD


set(OpenCASCADE_DIR "E:/Projects/Project-EchoCAD/OCCT-7_8_1-install/cmake")
# Find OpenCASCADE package
find_package(OpenCASCADE REQUIRED)
if(OpenCASCADE_FOUND)
	message(STATUS "OpenCASCADE found")
	message(STATUS "OpenCASCADE include directory: ${OpenCASCADE_INCLUDE_DIR}")
	message(STATUS "OpenCASCADE binary directory: ${OpenCASCADE_BINARY_DIR}")
else()
	message(FATAL_ERROR "OpenCASCADE not found")
endif()

# Use CMake's built-in shared library suffix variable
file(GLOB OpenCASCADE_BINS "${OpenCASCADE_BINARY_DIR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Install the OpenCASCADE shared libraries
install(FILES ${OpenCASCADE_BINS}
    DESTINATION ${CMAKE_INSTALL_BINDIR}                 # Install libraries to the library directory
)