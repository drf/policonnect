cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(QT_MIN_VERSION "4.4.0")

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
      ${CMAKE_CURRENT_SOURCE_DIR}/includes
      ${QT_INCLUDES}
)

set(policonnect_SRCS
    main.cpp
    mainwindow.cpp
)

set(policonnect_UI_H
    mainwindow.ui
)

qt4_wrap_ui(policonnect_UI_H ${policonnect_UI})
automoc4_add_executable(policonnect ${policonnect_SRCS} ${policonnect_UI})

target_link_libraries(policonnect
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${POLKITQT_LIBRARIES}
)

install(TARGETS policonnect DESTINATION ${BIN_INSTALL_DIR} )

