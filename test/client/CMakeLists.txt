
set(TEST_SFML_LIBS
  sfml-graphics
  sfml-network
  sfml-system
  sfml-window
  )

# List of test functions
add_custom_test(client_dummy
  TEST_LIBRARIES ${TEST_SFML_LIBS}
  TEST_INCLUDES ${SFML_INCLUDE_DIR}
  )

# vim: set sw=2 sts=2 et:

