CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(applibs C)

set(AZURE_SPHERE_REMOTE ON CACHE  BOOL "ENABLE AZURE SPHERE REMOTE" FORCE )

################################################################################
# Source groups
################################################################################
set(Source
    "comms_manager.c"
    "src/adc.c"
    "src/gpio.c"
    "src/i2c.c"
    "src/log.c"
    "src/pwm.c"
    "src/remotex.c"
    "src/spi.c"
    "src/storage.c"
    "src/uart.c"
)
source_group("Source" FILES ${Source})

set(ALL_FILES
    ${Source}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

# https://github.com/sadiquealy/GCC_Mocking
# https://titanwolf.org/Network/Articles/Article?AID=b6e0ae3e-3300-4627-afa6-5627f22c6298

target_link_libraries (${PROJECT_NAME} gcc_s c "-Wl,--wrap=close -Wl,--wrap=read -Wl,--wrap=write -Wl,--wrap=lseek")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/HardwareDefinitions/inc")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/HardwareDefinitions/inc/hw")

target_compile_definitions(${PROJECT_NAME} PUBLIC AZURE_SPHERE_REMOTE)
