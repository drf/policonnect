include_directories(
      ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
)


set(policonnect_helper_SRCS
    policonnecthelper.cpp
    main.cpp
)

qt4_add_dbus_adaptor(policonnect_helper_SRCS
    it.polimi.policonnecthelper.xml
    policonnecthelper.h
    PoliconnectHelper
)

automoc4_add_executable(policonnect-helper
    ${policonnect_helper_SRCS}
    ${policonnect_helper_MOC_SRCS}
)

target_link_libraries(policonnect-helper
    ${QT_QTCORE_LIBRARY}
    ${QT_DBUS_LIBRARY}
    ${POLKITQT-1_CORE_LIBRARY}
)

install(TARGETS policonnect-helper DESTINATION ${LIBEXEC_INSTALL_DIR})

dbus_add_activation_system_service(it.polimi.policonnecthelper.service.in)

install(FILES it.polimi.policonnecthelper.conf DESTINATION /etc/dbus-1/system.d)
install(FILES it.polimi.policonnect.policy DESTINATION ${POLKITQT-1_POLICY_FILES_INSTALL_DIR})
