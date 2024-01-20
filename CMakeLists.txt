cmake_minimum_required(VERSION 3.20)

project(CTF)

# shared - not implemented
# add_library(CTF-shared SHARED libCTF/Source/CTF.c libCTF/Source/CTF.h)
# target_compile_definitions(CTF PUBLIC CTF_SHARED)

# static
add_library(CTF-static STATIC libCTF/Source/CTF.c libCTF/Source/CTF.h)
target_compile_definitions(CTF-static PUBLIC LIBCTF_STATIC)
target_include_directories(CTF-static PUBLIC libCTF/Source)

add_executable(CTFCreate CTFCreate/Source/Main.c)
target_link_libraries(CTFCreate PRIVATE CTF-static)
target_include_directories(CTFCreate PRIVATE CTFCreate/Libs/stb)
target_link_libraries(CTFCreate PRIVATE m)