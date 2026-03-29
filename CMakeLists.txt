cmake_minimum_required(VERSION 3.16)
project(RBACSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/models/Person.cpp
    src/utils/Tools.cpp
    src/editor/Editor.cpp
    src/controllers/AuthController.cpp
    src/controllers/AdminController.cpp
    src/controllers/WorkerController.cpp
    src/views/MenuView.cpp
    src/views/TableView.cpp
)

add_executable(rbac-system ${SOURCES})

target_include_directories(rbac-system PRIVATE include)

# ncurses — Linux only
find_package(Curses REQUIRED)
target_link_libraries(rbac-system PRIVATE ${CURSES_LIBRARIES})
target_include_directories(rbac-system PRIVATE ${CURSES_INCLUDE_DIR})