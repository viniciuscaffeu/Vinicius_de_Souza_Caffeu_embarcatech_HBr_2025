add_executable(run_tests
    test_temp_sensor.c
    unity/unity.c
    ../src/temp_sensor.c
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/unity
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(run_tests pico_stdlib)
pico_enable_stdio_uart(run_tests 1)
