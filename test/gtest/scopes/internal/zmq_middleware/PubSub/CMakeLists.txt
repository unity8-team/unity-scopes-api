configure_file(Zmq.ini.in Zmq.ini)

add_definitions(-DTEST_DIR="${CMAKE_CURRENT_BINARY_DIR}")
add_executable(PubSub_test PubSub_test.cpp)
target_link_libraries(PubSub_test ${LIBS} ${TESTLIBS})

add_test(PubSub PubSub_test)
