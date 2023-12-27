FetchContent_Declare(
    fatfs
    URL http://elm-chan.org/fsw/ff/arc/ff15.zip
)

FetchContent_MakeAvailable(fatfs)

add_library(filesystem.fatfs ${EMIL_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(filesystem.fatfs PUBLIC
    "$<BUILD_INTERFACE:${fatfs_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (NOT FATFS_CONFIG_FILE_DIRECTORY)
    set(FATFS_CONFIG_FILE_DIRECTORY "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>")
    message(WARNING "FatFS: ffconf.h not defined! Using the default version. Use the variable FATFS_CONFIG_FILE_DIRECTORY to use your custom file.")
endif()

target_sources(filesystem.fatfs PRIVATE
    ${fatfs_SOURCE_DIR}/source/ff.h
    ${fatfs_SOURCE_DIR}/source/ff.c
    ${fatfs_SOURCE_DIR}/source/ffsystem.c
    ${fatfs_SOURCE_DIR}/source/ffunicode.c
    ${FATFS_CONFIG_FILE_DIRECTORY}/ffconf.h
)

emil_exclude_from_clang_format(filesystem.fatfs)
