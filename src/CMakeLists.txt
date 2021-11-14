set(S4_FS_INCLUDE ${CMAKE_CURRENT_LIST_DIR})

# gather source files list
file(GLOB_RECURSE S4_FS_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    ${S4_FS_INCLUDE}/*.cpp 
    ${S4_FS_INCLUDE}/*.hpp 
    ${S4_FS_INCLUDE}/*.hpp)
GenerateSourceGoups("${S4_FS_SRCS}")

add_library(${S4_FS_TARGET} INTERFACE ${S4_FS_SRCS})
target_compile_features(${S4_FS_TARGET} INTERFACE cxx_std_20)
target_include_directories(${S4_FS_TARGET} INTERFACE ${S4_FS_INCLUDE})