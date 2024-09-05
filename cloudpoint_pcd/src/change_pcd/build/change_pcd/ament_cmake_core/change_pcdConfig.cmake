# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_change_pcd_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED change_pcd_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(change_pcd_FOUND FALSE)
  elseif(NOT change_pcd_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(change_pcd_FOUND FALSE)
  endif()
  return()
endif()
set(_change_pcd_CONFIG_INCLUDED TRUE)

# output package information
if(NOT change_pcd_FIND_QUIETLY)
  message(STATUS "Found change_pcd: 0.0.0 (${change_pcd_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'change_pcd' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${change_pcd_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(change_pcd_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${change_pcd_DIR}/${_extra}")
endforeach()
