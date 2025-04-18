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
set(sdkVersion 2.1.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(contador_decrescente C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(contador_decrescente 
    contador_decrescente.c
    inc/ssd1306_i2c.c
    # Adicione outros arquivos fonte aqui se necessário
)

pico_set_program_name(contador_decrescente "contador_decrescente")
pico_set_program_version(contador_decrescente "0.1")

# Configuração de saída serial
pico_enable_stdio_uart(contador_decrescente 0)
pico_enable_stdio_usb(contador_decrescente 1)

# Configurações para o display OLED
# Adiciona o diretório de includes
target_include_directories(contador_decrescente PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc  # Pasta onde está ssd1306_i2c.h
    ${PICO_SDK_PATH}/src/rp2_common/hardware_i2c/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
)

# Bibliotecas necessárias
target_link_libraries(contador_decrescente
    pico_stdlib
    pico_stdio_usb       # Para printf() via USB
    hardware_i2c         # Biblioteca I2C da Pico
    hardware_gpio        # Para controle de GPIO
    # Adicione outras bibliotecas específicas do OLED se necessário
)

# Adiciona definições de compilação se necessário
target_compile_definitions(contador_decrescente PRIVATE
    PICO_DEFAULT_I2C_SDA_PIN=14
    PICO_DEFAULT_I2C_SCL_PIN=15
)

pico_add_extra_outputs(contador_decrescente)