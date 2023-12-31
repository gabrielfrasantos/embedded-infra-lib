add_library(fsal.fatfs ${EMIL_EXCLUDE_FROM_ALL} STATIC)

target_link_libraries(fsal.fatfs PUBLIC
    fsal.interfaces
    filesystem.fatfs
    hal.interfaces
)

target_sources(fsal.fatfs PRIVATE
    FileFatFs.cpp
    FileFatFs.hpp
    DirectoryFatFs.cpp
    DirectoryFatFs.hpp
    DriverFatFs.cpp
    DriverFatFs.hpp
)
