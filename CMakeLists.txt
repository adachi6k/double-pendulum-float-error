cmake_minimum_required(VERSION 3.5)

# プロジェクト名とバージョン
project(DoublePendulumSimulation VERSION 1.0)

# C++11 を利用
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AUTOMOC を有効にする（moc の自動実行）
set(CMAKE_AUTOMOC ON)

# Qt5 Widgets モジュールの検索
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# ソースファイルとヘッダファイルを指定（src/ 配下に配置）
set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/simulation.cpp
)

set(HEADER_FILES
    src/mainwindow.h
    src/simulation.h
)

# 実行ファイルの生成
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Qt5 Widgets ライブラリをリンク
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
