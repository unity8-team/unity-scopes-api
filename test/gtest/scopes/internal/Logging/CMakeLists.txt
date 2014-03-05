add_executable(
    Logging_test
    Logging_test.cpp
)

target_link_libraries(
    Logging_test
    ${TESTLIBS}
)

add_test(
    Logging
    Logging_test
)
