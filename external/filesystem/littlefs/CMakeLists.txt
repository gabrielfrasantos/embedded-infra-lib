FetchContent_Declare(
    littlefs
    GIT_REPOSITORY https://github.com/littlefs-project/littlefs
    GIT_TAG v2.8.2
)

FetchContent_MakeAvailable(littlefs)

add_library(filesystem.littlefs ${EMIL_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(filesystem.littlefs PUBLIC
    "$<BUILD_INTERFACE:${fatfs_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(filesystem.littlefs PRIVATE
    ${littlefs_SOURCE_DIR}/lfs.h
    ${littlefs_SOURCE_DIR}/lfs.c
    ${littlefs_SOURCE_DIR}/lfs_util.h
    ${littlefs_SOURCE_DIR}/lfs_util.c
)

emil_exclude_from_clang_format(filesystem.littlefs)
