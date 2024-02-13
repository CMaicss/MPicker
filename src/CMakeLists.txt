set(SOURCES
        main.cpp
        screencover.h screencover.cpp
        pickermanager.h pickermanager.cpp
        utils.cpp utils.h
        trayicon.h trayicon.cpp
        shortcutwidget.h shortcutwidget.cpp
        ../images/images.qrc
)
if (WIN32)
    set(CMAKE_CXX_FLAGS "-mwindows")
    add_executable(MPicker ${SOURCES} ../icon.rc)
else()
    add_executable(MPicker ${SOURCES})
endif()
target_link_libraries(MPicker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
