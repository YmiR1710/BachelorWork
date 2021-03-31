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
find_package(Qt5Charts REQUIRED)

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
        src/utils/config_parser.cpp
        src/propertieswindow.cpp
        src/statisticswidget.cpp
        src/utils/statistics.cpp
        src/utils/cloud_drives.cpp
        src/donutbreakdownchart.cpp
        src/mainslice.cpp
        src/discview.cpp
        src/cloud_drive_entity.cpp
        src/clouddrivewidget.cpp
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
        include/utils/config_parser.h
        include/utils/cloud_drives.h
        include/properties.h
        include/propertieswindow.h
        include/statisticswidget.h
        include/panels.h
        include/themes.h
        include/donutbreakdownchart.h
        include/mainslice.h
        include/discview.h
        include/utils/statistics.h
        include/clouddrivewidget.h
        include/cloud_drive_entity.h
        ui/mainwindow.ui
        ui/statisticswidget.ui
        ui/discview.ui
        ui/clouddrivewidget.ui
        resources/resources.qrc
        config/.config
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qExplorer
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qExplorer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qExplorer
            ${PROJECT_SOURCES}
        )
    endif()
endif()
#set_target_properties(qExplorer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
target_link_libraries(qExplorer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Charts)
