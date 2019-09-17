
# Global cmake target responsible for the generation of all the cpp headers
add_custom_target(generate-headers)

# Fonction that generate cpp header files from dia files using dia2code.
# Dia files must contain only one namespace and must be named by this
# namespace.
#
# Arguments:
#
# namespace
#   Name of the dia file. Must also be the name of the namespace contained
#   inside the dia file.
#
# output
#   Name of the output directory where the cpp header should be generated.
#   This directory should exist inside the "src" folder of the project root.
#
function(generate_dia_header namespace output)
  # Path to the .dia file used to generate the cpp headers
  set(dia_file "${PROJECT_SOURCE_DIR}/src/${namespace}.dia")
  # Path to the output directory
  set(output_dir "${PROJECT_SOURCE_DIR}/src/${output}")

  # Stamp file that take care of the dependency chain
  set(stamp ${CMAKE_CURRENT_BINARY_DIR}/generate_header_${namespace}.stamp)

  # Custom command that generate the cpp headers and create the stamp file
  add_custom_command(
    OUTPUT ${stamp}
    COMMAND $<TARGET_FILE:dia2code> -ns ${namespace} -d ${output_dir} -t cpp ${dia_file}
    COMMAND ${CMAKE_COMMAND} -E touch ${stamp}
    DEPENDS ${dia_file}
    )

  # Create cmake intermediate target to generate the cpp headers
  add_custom_target(generate-header-${namespace} DEPENDS ${stamp})

  # Add the intermediate target as a dependency of the global cmake target for header
  # generation.
  add_dependencies(generate-headers generate-header-${namespace})
endfunction()

# vim: set sw=2 sts=2 et:

