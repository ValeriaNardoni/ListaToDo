cmake_minimum_required(VERSION 3.9)
project(Esame_Programmazione_Lista_ToDo)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
include_directories(.)
add_subdirectory(test)

include_directories(/test)

add_executable(Esame_Programmazione_Lista_ToDo
        main.cpp
        mainWindow.cpp
        mainWindow.h
        mainWindow.ui
        ListToDo.cpp
        ListToDo.h
        ListToDo.ui
        Board.cpp
        Board.h
        Board.ui
        task.cpp
        task.h
        Important.cpp
        Important.h
        Important.ui)

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)