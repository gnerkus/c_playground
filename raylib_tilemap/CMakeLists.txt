# raylib tilemap loader example
cmake_minimum_required(VERSION 3.15)
project(tilemap)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
# Raylib
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Raylib Tileson
find_package(raylib-tileson 4.2.1 QUIET) # QUIET or REQUIRED
if (NOT raylib-tileson_FOUND) # If there's none, fetch and build raylib-tileson
  include(FetchContent)
  FetchContent_Declare(
    raylib-tileson
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/RobLoach/raylib-tileson/archive/refs/heads/master.tar.gz
  )
  FetchContent_GetProperties(raylib-tileson)
  if (NOT raylib-tileson_POPULATED) # Have we downloaded raylib-tileson yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib-tileson)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} tilemap_loader.c)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib raylib-tileson)

# Resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "Debug/resources/")

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()