# Find Zephyr. This also loads Zephyr's build system.
cmake_minimum_required(VERSION 3.20.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(umdom_bluepill)
# Add your source file to the "app" target. This must come after
add_subdirectory(src/driver)

file(GLOB app_sources 
    src/*.c 
    src/objdict/CO_OD.c
    )

target_sources(app PRIVATE ${app_sources})
zephyr_include_directories(src/objdict)
