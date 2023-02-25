cmake_minimum_required(VERSION 2.8.12)
project(libxmlexample)

add_definitions("-std=c++20")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# Create a custom target to copy XML files to binary directory
add_custom_target(copy_xml_files ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/xml ${CMAKE_CURRENT_BINARY_DIR}/bin/xml
  COMMENT "Copying XML files to binary directory"
)

# Add dependency on the copy_xml_files target to my_executable
add_dependencies(${PROJECT_NAME} copy_xml_files)