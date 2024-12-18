
set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/SunCAD.cc)
set(PROJECT_RESOURCES ${CMAKE_SOURCE_DIR}/res/SunCAD.qrc)

# Recursively find all source and header files
file(GLOB SUB_DIRECTORY_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*/*.h"
    "${CMAKE_SOURCE_DIR}/src/*/*.cc"
    "${CMAKE_SOURCE_DIR}/src/*/*/*.h"
    "${CMAKE_SOURCE_DIR}/src/*/*/*.cc"
)

list(APPEND PROJECT_SOURCES ${SUB_DIRECTORY_SOURCES})

# add executable target
qt_add_executable(SunCAD
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core5Compat)

target_link_libraries(${PROJECT_NAME} PRIVATE SARibbonBar::SARibbonBar)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts::cxxopts)
target_link_libraries(${PROJECT_NAME} PRIVATE ads::qtadvanceddocking-qt6)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

# Link OpenCASCADE libraries
foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} PRIVATE debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(${PROJECT_NAME} PRIVATE optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SunCAD)
endif()
set_target_properties(SunCAD PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install the target executable/library (SunCAD)
include(GNUInstallDirs)

# Install the executable or runtime (if Windows, RUNTIME is used)
install(TARGETS SunCAD
    BUNDLE DESTINATION .                                # For macOS app bundles (if applicable)
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}         # Shared libraries on Linux/macOS
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}         # Executables and Windows DLLs
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SunCAD)
endif()
