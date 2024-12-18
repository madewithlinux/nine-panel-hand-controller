# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(nine-panel-hand-controller C CXX ASM)
add_library(common_stuff INTERFACE)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(src/)
target_sources(common_stuff INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/reset_interface.c
    ${CMAKE_CURRENT_LIST_DIR}/src/reset_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/src/tusb_config.h
    ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.c
    ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.h
)

# Add the standard library to the build
# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(common_stuff INTERFACE
    pico_stdlib
    pico_stdio_usb
    hardware_timer
    tinyusb_device
    tinyusb_board
)

# Add the standard include files to the build, and Make sure TinyUSB can find tusb_config.h
target_include_directories(common_stuff INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
  ${CMAKE_CURRENT_LIST_DIR}/src
)

add_compile_options(-Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
)
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()



#########################################
### individual targets for different configurations

add_executable(nine-panel-hand-controller)
target_link_libraries(nine-panel-hand-controller common_stuff)
target_compile_definitions(nine-panel-hand-controller PRIVATE
    PLAYER_NUMBER=1
)
pico_add_extra_outputs(nine-panel-hand-controller)
pico_set_binary_type(nine-panel-hand-controller copy_to_ram)


add_executable(nine-panel-hand-controller-wasd)
target_link_libraries(nine-panel-hand-controller-wasd common_stuff)
target_compile_definitions(nine-panel-hand-controller-wasd PRIVATE
    KEYMAP_LAYOUT=KEYMAP_WASD
)
pico_add_extra_outputs(nine-panel-hand-controller-wasd)
pico_set_binary_type(nine-panel-hand-controller-wasd copy_to_ram)


add_executable(nine-panel-hand-controller-numpad)
target_link_libraries(nine-panel-hand-controller-numpad common_stuff)
target_compile_definitions(nine-panel-hand-controller-numpad PRIVATE
    KEYMAP_LAYOUT=KEYMAP_NUMPAD
)
pico_add_extra_outputs(nine-panel-hand-controller-numpad)
pico_set_binary_type(nine-panel-hand-controller-numpad copy_to_ram)


add_executable(nine-panel-hand-controller-arrows)
target_link_libraries(nine-panel-hand-controller-arrows common_stuff)
target_compile_definitions(nine-panel-hand-controller-arrows PRIVATE
    KEYMAP_LAYOUT=KEYMAP_ARROWS
)
pico_add_extra_outputs(nine-panel-hand-controller-arrows)
pico_set_binary_type(nine-panel-hand-controller-arrows copy_to_ram)
