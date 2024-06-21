set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        #ViewModels
        gameviewmodel.h
        gameviewmodel.cpp

        #Views
        gameboardview.h
        gameboardview.cpp
        snakeview.h
        snakeview.cpp
)

qt_add_library(AwesomeQtSnakeLib
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
target_link_libraries(AwesomeQtSnakeLib PRIVATE
    snakecore
    Qt${QT_VERSION_MAJOR}::Widgets
)
target_include_directories(AwesomeQtSnakeLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AwesomeQtSnake
        MANUAL_FINALIZATION
        main.cpp
    )
else()
    add_executable(AwesomeQtSnake
        main.cpp
    )
endif()

target_link_libraries(AwesomeQtSnake PRIVATE
    AwesomeQtSnakeLib
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AwesomeQtSnake)
endif()
set_target_properties(AwesomeQtSnake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AwesomeQtSnake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_target(AwesomeQtSnakeLib)
    qt_finalize_executable(AwesomeQtSnake)
endif()
