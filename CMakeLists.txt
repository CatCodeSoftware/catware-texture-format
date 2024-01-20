cmake_minimum_required(VERSION 3.20)

project(libCTF)

# shared - not implemented
# add_library(CTF-shared SHARED libCTF/Source/CTF.c libCTF/Source/CTF.h)
# target_compile_definitions(CTF PUBLIC CTF_SHARED)

# static
add_library(CTF-static STATIC libCTF/Source/CTF.c libCTF/Source/CTF.h)
target_compile_definitions(CTF-static PUBLIC LIBCTF_STATIC)
target_include_directories(CTF-static PUBLIC libCTF/Source)

add_executable(Test CTFTest/Source/Main.c)
target_link_libraries(Test PRIVATE CTF-static)

add_subdirectory(CTFTest/Libs/SDL)
target_link_libraries(Test PRIVATE SDL2-static)
target_include_directories(Test PRIVATE CTFTest/Libs/SDL/include CTFTest/Libs/stb)