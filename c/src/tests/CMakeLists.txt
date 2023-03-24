set(TYPES_TEST types-test)
add_executable(${TYPES_TEST} types_test.c)

set(CONV_TEST  conv-test)
add_executable(${CONV_TEST} conv_test.c)

install(TARGETS ${TYPES_TEST} ${CONV_TEST} DESTINATION bin)
