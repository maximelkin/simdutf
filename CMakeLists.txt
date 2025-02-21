cmake_minimum_required(VERSION 3.15)

project(simdutf
  DESCRIPTION "Fast Unicode validation, transcoding and processing"
  LANGUAGES CXX 
  VERSION 1.0.0
)

set(SIMDUTF_LIB_VERSION "1.0.1" CACHE STRING "simdutf library version")
set(SIMDUTF_LIB_SOVERSION "1" CACHE STRING "simdutf library soversion")

include(GNUInstallDirs)
include(cmake/simdutf-flags.cmake)

set(SIMDUTF_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)



if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
  message(STATUS "The benchmark tool requires GCC 8.0 or better.")
else()
  add_subdirectory(benchmarks)
endif()


# ---- Install rules ----
add_library(simdutf::simdutf ALIAS simdutf)

set_target_properties(
    simdutf PROPERTIES
    VERSION "${SIMDUTF_LIB_VERSION}"
    SOVERSION "${SIMDUTF_LIB_SOVERSION}"
    WINDOWS_EXPORT_ALL_SYMBOLS YES
)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(
    FILES include/simdutf.h
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT simdutf_Development
)

install(
    DIRECTORY include/simdutf
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT simdutf_Development
)

install(
    TARGETS simdutf
    EXPORT simdutfTargets
    RUNTIME COMPONENT simdutf_Runtime
    LIBRARY COMPONENT simdutf_Runtime
    NAMELINK_COMPONENT simdutf_Development
    ARCHIVE COMPONENT simdutf_Development
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

configure_file(cmake/simdutf-config.cmake.in simdutf-config.cmake @ONLY)

write_basic_package_version_file(
    simdutf-config-version.cmake
    COMPATIBILITY SameMinorVersion
)

set(
    SIMDUTF_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/simdutf"
    CACHE STRING "CMake package config location relative to the install prefix"
)
mark_as_advanced(SIMDUTF_INSTALL_CMAKEDIR)

install(
    FILES
    "${PROJECT_BINARY_DIR}/simdutf-config.cmake"
    "${PROJECT_BINARY_DIR}/simdutf-config-version.cmake"
    DESTINATION "${SIMDUTF_INSTALL_CMAKEDIR}"
    COMPONENT simdutf_Development
)

install(
    EXPORT simdutfTargets
    NAMESPACE simdutf::
    DESTINATION "${SIMDUTF_INSTALL_CMAKEDIR}"
    COMPONENT example_Development
)

#
# CPack
#
if(is_top_project)
  set(CPACK_PACKAGE_VENDOR "Daniel Lemire")
  set(CPACK_PACKAGE_CONTACT "lemire@gmail.com")
  set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE-MIT")
  set(CPACK_RPM_PACKAGE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE-MIT")
  set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
  set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
  include(CPack)
endif()

# ----
