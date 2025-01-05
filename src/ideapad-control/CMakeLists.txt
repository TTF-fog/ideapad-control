cmake_minimum_required(VERSION 3.1)
project(ideapad-control VERSION 0.1)

add_executable(ideapad-control "main.cpp")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../ ${CMAKE_CURRENT_SOURCE_DIR}/../../example_build EXCLUDE_FROM_ALL)
target_link_libraries(ideapad-control tray)

target_compile_features(ideapad-control PUBLIC cxx_std_17)
set_target_properties(ideapad-control PROPERTIES CMAKE_CXX_STANDARD 17)
set_target_properties(ideapad-control PROPERTIES CMAKE_CXX_EXTENSIONS Off)
set_target_properties(ideapad-control PROPERTIES CMAKE_CXX_STANDARD_REQUIRED On)
set_target_properties(ideapad-control PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ideapad-control PROPERTIES PROJECT_NAME ${PROJECT_NAME})