cmake_minimum_required(VERSION 3.15...3.26)

project(nanobind_example LANGUAGES CXX)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()
set(CMAKE_CXX_STANDARD 20)
# Try to import all Python components potentially needed by nanobind
find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

# We are now ready to compile the actual extension module
nanobind_add_module(
  # Name of the extension
  nanobind_example_ext

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Build libnanobind statically and merge it into the
  # extension (which itself remains a shared library)
  #
  # If your project builds multiple extensions, you can
  # replace this flag by NB_SHARED to conserve space by
  # reusing a shared libnanobind across libraries
  NB_STATIC

  # Source code goes here
  src/nanobind_example/nanobind_example_ext.cpp
)


# Help cmake find pybind11 installed as Python package
execute_process(
  COMMAND "${Python3_EXECUTABLE}" "-c"
  "import pybind11; print(pybind11.get_cmake_dir())"
  OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
  RESULT_VARIABLE PYBIND11_COMMAND_RESULT
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT PYBIND11_COMMAND_RESULT)
  message(STATUS "Found pybind11 cmake directory at ${PYBIND11_CMAKE_DIR}")
endif() 

find_package(
  pybind11
  2.9.1
  REQUIRED
  CONFIG
  HINTS
  ${PYBIND11_CMAKE_DIR}
  ${PYBIND11_DIR}
  ${PYBIND11_ROOT}
  $ENV{PYBIND11_DIR}
  $ENV{PYBIND11_ROOT}
)

# We are now ready to compile the actual extension module
pybind11_add_module(
  # Name of the extension
  pybind11_example_ext
  MODULE
  src/nanobind_example/pybind11_example_ext.cpp
)


# Install directive for scikit-build-core
install(TARGETS nanobind_example_ext pybind11_example_ext LIBRARY DESTINATION nanobind_example)
