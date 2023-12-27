if (EMIL_INCLUDE_FATFS)
    add_subdirectory(fatfs)
endif()

if (EMIL_INCLUDE_LITTLEFS)
    add_subdirectory(littlefs)
endif()