set(TYPES_TEST types-test)
add_executable(${TYPES_TEST} types_test.c)
install(TARGETS ${TYPES_TEST} DESTINATION bin)

set(CONV_TEST conv-test)
add_executable(${CONV_TEST} conv_test.c)
install(TARGETS ${CONV_TEST} DESTINATION bin)

set(TIMER_TEST timer-test)
add_executable(${TIMER_TEST} timer_test.c)
target_link_libraries(${TIMER_TEST} rt pthread)
install(TARGETS ${TIMER_TEST} DESTINATION bin)
