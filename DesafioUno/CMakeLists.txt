cmake_minimum_required(VERSION 3.19)
project(tetrisactualizadooo LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(tetrisactualizadooo
    main.cpp
    tablero.h tablero.cpp
    juego.h juego.cpp
)

target_link_libraries(tetrisactualizadooo
    PRIVATE
        Qt::Core
)

install(TARGETS tetrisactualizadooo
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
