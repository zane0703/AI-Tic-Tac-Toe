cmake_minimum_required(VERSION 3.16)

project(Tic-Tac-Toe VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
        Tic-Tac-Toe.c
        Tic-Tac-Toe.h
        tictactoe3x3form.hpp tictactoe3x3form.cpp tictactoe3x3form.ui
        tictactoe4x4form.hpp tictactoe4x4form.cpp tictactoe4x4form.ui
        Tic-Tac-Toe-4x4.h
        Tic-Tac-Toe-4x4.c
)
if(WIN32)
    enable_language(RC)
    set(APP_ICON_RESOURCE  ${CMAKE_CURRENT_SOURCE_DIR}/appico.rc )
endif()
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Tic-Tac-Toe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
         ${APP_ICON_RESOURCE}
         tictactoe3x3form.hpp tictactoe3x3form.cpp tictactoe3x3form.ui
         tictactoe4x4form.hpp tictactoe4x4form.cpp tictactoe4x4form.ui
        Tic-Tac-Toe-4x4.h
        Tic-Tac-Toe-4x4.c

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qtTest APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Tic-Tac-Toe SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Tic-Tac-Toe
            ${PROJECT_SOURCES}
             ${APP_ICON_RESOURCE}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()



target_link_libraries(Tic-Tac-Toe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Tic-Tac-Toe)
endif()
set_target_properties(Tic-Tac-Toe PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Tic-Tac-Toe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Tic-Tac-Toe)
endif()
