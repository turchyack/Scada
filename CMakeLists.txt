cmake_minimum_required(VERSION 3.16)
project(scada-lite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)  # Включаем автоматический moc

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_resources(RESOURCES resources.qrc)

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core/Tag.cpp
    src/core/Tag.h
    src/core/TagManager.cpp
    src/core/TagManager.h
    ${RESOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

