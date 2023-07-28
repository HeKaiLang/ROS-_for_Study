# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_cpp04_prarm_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED cpp04_prarm_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(cpp04_prarm_FOUND FALSE)
  elseif(NOT cpp04_prarm_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(cpp04_prarm_FOUND FALSE)
  endif()
  return()
endif()
set(_cpp04_prarm_CONFIG_INCLUDED TRUE)

# output package information
if(NOT cpp04_prarm_FIND_QUIETLY)
  message(STATUS "Found cpp04_prarm: 0.0.0 (${cpp04_prarm_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'cpp04_prarm' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${cpp04_prarm_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(cpp04_prarm_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${cpp04_prarm_DIR}/${_extra}")
endforeach()
