cmake_minimum_required(VERSION 3.28)
project(GameProject VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(GIT_EXECUTABLE "C:/Dev/prerequisites/MSYS2/usr/bin/git.exe")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")
add_executable(GameProject ${SOURCES})

target_link_libraries(GameProject PRIVATE sfml-graphics sfml-audio)
target_include_directories(GameProject PUBLIC "src/include")
target_compile_features(GameProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET GameProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:GameProject>
        VERBATIM)
endif()

install(TARGETS GameProject)