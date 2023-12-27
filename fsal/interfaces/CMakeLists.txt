add_library(fsal.interfaces ${HAL_TI_EXCLUDE_FROM_ALL} INTERFACE)

target_link_libraries(fsal.interfaces INTERFACE
    infra.util
)

target_sources(fsal.interfaces INTERFACE
    Directory.hpp
    File.hpp
)
