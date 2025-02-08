cmake_minimum_required(VERSION 3.5)

project(DoublePendulumSimulation VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AUTOMOC を有効にして、Q_OBJECT マクロがあるファイルから moc ファイルを自動生成
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/simulation.cpp
    src/simulationworker.cpp
)

set(HEADER_FILES
    src/mainwindow.h
    src/simulation.h
    src/simulationworker.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
