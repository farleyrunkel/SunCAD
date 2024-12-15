

set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/SunCAD.cc)

# add executable target
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)


# 根据不同平台设置链接器选项
if(WIN32)
    # Windows 平台：设置为 Windows 应用程序，避免控制台窗口
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
elseif(APPLE)
    # macOS 平台：特定的链接器标志（如果需要）
    target_link_options(${PROJECT_NAME} PRIVATE "-framework Cocoa")
elseif(UNIX)
    # Linux 平台：例如启用 pthreads
    target_link_options(${PROJECT_NAME} PRIVATE "-pthread")
endif()


if(CMAKE_SUNCAD_HAS_WXWIDGETS)
	target_link_libraries(${PROJECT_NAME} PRIVATE imp_wxwidgets)
endif()
