cmake_minimum_required(VERSION 3.5)

project(BachelorWork LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/properties.cpp
        src/utils/copy_path.cpp
        src/utils/dir_size.cpp
        src/utils/navigation.cpp
        src/utils/search_filter.cpp
        src/utils/create_unit.cpp
        src/utils/filename.cpp
        src/utils/rename_unit.cpp
        src/utils/copypaste.cpp
        src/utils/delete_unit.cpp
        src/utils/swap_drives.cpp
        src/propertieswindow.cpp
        include/mainwindow.h
        include/global.h
        include/utils/copy_path.h
        include/utils/dir_size.h
        include/utils/navigation.h
        include/utils/search_filter.h
        include/utils/create_unit.h
        include/utils/filename.h
        include/utils/rename_unit.h
        include/utils/copypaste.h
        include/utils/delete_unit.h
        include/utils/swap_drives.h
        include/properties.h
        include/propertieswindow.h
        ui/mainwindow.ui
        resources/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BachelorWork
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(BachelorWork SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(BachelorWork
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BachelorWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
