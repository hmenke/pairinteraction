include(FindPackageHandleStandardArgs)

if(NOT PYTHON_EXECUTABLE)
  find_package(PythonInterp 3)
endif()

function(FIND_SPHINX_LIBRARY name library)
  if(NOT SPHINX_${name}_FOUND)
    execute_process(
      COMMAND "${PYTHON_EXECUTABLE}" -c
      "from ${library} import main; print('TRUE')"
      OUTPUT_VARIABLE FOUND
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET)
    set("SPHINX_${name}_FOUND" ${FOUND} PARENT_SCOPE)
    set("SPHINX_${name}_LIBRARY" ${library} PARENT_SCOPE)
  endif()
endfunction()

if(PYTHON_EXECUTABLE)
  # find sphinx-build
  FIND_SPHINX_LIBRARY("BUILD" "sphinx")
  FIND_SPHINX_LIBRARY("BUILD" "sphinx.cmd.build")

  # find sphinx-apidoc
  FIND_SPHINX_LIBRARY("APIDOC" "sphinx.apidoc")
  FIND_SPHINX_LIBRARY("APIDOC" "sphinx.ext.apidoc")

  # Get the version
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
    "import sphinx; print(sphinx.__version__)"
    OUTPUT_VARIABLE SPHINX_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET)

else()
  message(STATUS "Python not found, not finding Sphinx")
endif()

find_package_handle_standard_args(Sphinx 
    REQUIRED_VARS SPHINX_BUILD_FOUND SPHINX_APIDOC_FOUND
    VERSION_VAR SPHINX_VERSION
)
 
mark_as_advanced(SPHINX_BUILD_LIBRARY SPHINX_APIDOC_LIBRARY)
