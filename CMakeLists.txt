cmake_minimum_required(VERSION 3.20)

project(libCTF)

# shared - not implemented
# add_library(CTF-shared SHARED libCTF/Source/CTF.c libCTF/Source/CTF.h)
# target_compile_definitions(CTF PUBLIC CTF_SHARED)

# static
add_library(CTF-static STATIC libCTF/Source/CTF.c libCTF/Source/CTF.h)
target_compile_definitions(CTF-static PUBLIC CTF_STATIC)

add_executable(Test Test/Source/Main.c)
target_link_libraries(Test PRIVATE CTF-static)