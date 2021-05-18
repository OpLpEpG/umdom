# Find Zephyr. This also loads Zephyr's build system.
cmake_minimum_required(VERSION 3.20.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(umdom_bluepill)
# Add your source file to the "app" target. This must come after
# find_package(Zephyr) which defines the target.
# add_subdirectory(src/driver)

file(GLOB app_sources 
    src/*.c 
    # src/process_sensor.c
    src/objdict/CO_OD.c
    src/*/*/*c
    )

target_sources(app PRIVATE ${app_sources})
zephyr_include_directories(src/objdict)
