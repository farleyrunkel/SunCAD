# Copyright [2024] SunCAD


set(qtadvanceddocking-qt6_DIR "E:/Sources/Qt-Advanced-Docking-System/out/install/x64-Debug/lib/cmake/qtadvanceddocking-qt6")

find_package(qtadvanceddocking-qt6 REQUIRED)


# 定义 bin 路径
set(qtadvanceddocking_BINARY_DIR "${qtadvanceddocking-qt6_DIR}/../../../bin")

# 输出结果
message("qtadvanceddocking_BINARY_DIR is: ${qtadvanceddocking_BINARY_DIR}")

# Use CMake's built-in shared library suffix variable
file(GLOB qtadvanceddocking_BINS "${qtadvanceddocking_BINARY_DIR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Install the OpenCASCADE shared libraries
install(FILES ${qtadvanceddocking_BINS}
    DESTINATION ${CMAKE_INSTALL_BINDIR}                 # Install libraries to the library directory
)
