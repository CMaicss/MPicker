set(SOURCES
        main.cpp
        screencover.h screencover.cpp
        pickermanager.h pickermanager.cpp
        utils.cpp utils.h
        trayicon.h trayicon.cpp
        ../images/images.qrc
)
add_executable(MPicker ${SOURCES})
target_link_libraries(MPicker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
