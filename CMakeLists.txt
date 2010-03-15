project(policonnect)

cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(QT_MIN_VERSION "4.5.0")

include(InstallSettings)

macro(dbus_add_activation_system_service _sources)
    pkg_search_module( DBUS dbus-1 )
    foreach (_i ${_sources})
        get_filename_component(_service_file ${_i} ABSOLUTE)
        string(REGEX REPLACE "\\.service.*$" ".service" _output_file ${_i})
        set(_target ${CMAKE_CURRENT_BINARY_DIR}/${_output_file})
        configure_file(${_service_file} ${_target})
        install(FILES ${_target} DESTINATION ${DBUS_PREFIX}/share/dbus-1/system-services )
    endforeach (_i ${ARGN})
endmacro(dbus_add_activation_system_service _sources)

find_package(Qt4 REQUIRED)
find_package(Automoc4 REQUIRED)
find_package(PolkitQt-1 REQUIRED)

message(${POLKITQT-1_INCLUDE_DIR})

include_directories(
      ${CMAKE_CURRENT_BINARY_DIR}
      ${POLKITQT-1_INCLUDE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_SOURCE_DIR}
      ${CMAKE_BINARY_DIR}
      ${QT_INCLUDES}
)

add_subdirectory(helper)
add_subdirectory(icons)

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
    ${POLKITQT-1_GUI_LIBRARY}
)

install(TARGETS policonnect         DESTINATION ${BIN_INSTALL_DIR}      )
install(FILES   policonnect.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )

### Source tarball autogeneration ###
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-1.0)
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

