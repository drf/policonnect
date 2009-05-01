project(policonnect)

cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(QT_MIN_VERSION "4.5.0")

include(FindQt4)
include(FindPolkitQt)
include(InstallSettings)

find_package(Qt4 REQUIRED)
find_package(Automoc4 REQUIRED)
set(POLKITQT_MIN_VERSION 0.9.2)
find_package(PolkitQt REQUIRED)

include_directories(
      ${CMAKE_CURRENT_BINARY_DIR}
      ${POLKITQT_INCLUDE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_SOURCE_DIR}
      ${CMAKE_BINARY_DIR}
      ${QT_INCLUDES}
)

add_subdirectory(helper)

CONFIGURE_FILE(
       "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/cmake_uninstall.cmake.in"
       "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
       IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

set(policonnect_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_wrap_ui(policonnect_UIS
    mainwindow.ui
)

qt4_add_resources(qtsourceview_RC_SRCS
    policonnect.qrc
)

automoc4_add_executable(policonnect ${policonnect_SRCS} ${policonnect_UIS} ${qtsourceview_RC_SRCS})

target_link_libraries(policonnect
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${POLKITQT_LIBRARIES}
)

install(TARGETS policonnect DESTINATION ${BIN_INSTALL_DIR} )

