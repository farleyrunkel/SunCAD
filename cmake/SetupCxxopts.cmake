
set(cxxopts_DIR "E:/Scoop/apps/vcpkg/current/installed/x64-windows/share/cxxopts")
# cmd> vcpkg install cxxopts
find_package(cxxopts REQUIRED)

if(cxxopts_FOUND)
	message(STATUS "cxxopts found: ${cxxopts_DIR}")
else()
	message(FATAL_ERROR "cxxopts not found")
endif()