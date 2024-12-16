
set(SARibbonBar_DIR "E:/Binaries/SARibbon-2.2.6/bin_qt6.5.3_MSVC_x64/lib/cmake/SARibbonBar")

find_package(SARibbonBar REQUIRED)

get_filename_component(BASE_PATH "${SARibbonBar_INCLUDE_DIR}" DIRECTORY)

message("SARibbonBar_INCLUDE_DIR is: ${SARibbonBar_INCLUDE_DIR}")

# 定义 bin 路径
set(SARibbonBar_BINARY_DIR "${BASE_PATH}/../bin")

# 输出结果
message("SARibbonBar_BINARY_DIR is: ${SARibbonBar_BINARY_DIR}")

# Use CMake's built-in shared library suffix variable
file(GLOB SARibbonBar_BINS "${SARibbonBar_BINARY_DIR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Install the OpenCASCADE shared libraries
install(FILES ${SARibbonBar_BINS}
    DESTINATION ${CMAKE_INSTALL_BINDIR}                 # Install libraries to the library directory
)
