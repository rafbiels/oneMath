#==========================================================================
#  Copyright (C) Codeplay Software Limited
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  For your convenience, a copy of the License has been included in this
#  repository.
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================

find_package(OpenRNG)

set(LIB_NAME onemath_rng_openrng)
set(LIB_OBJ ${LIB_NAME}_obj)

# OpenRNG implements the Intel MKL RNG API, so we use the oneMath MKL CPU RNG
# backend source code directly to compile with OpenRNG headers and libraries
set(MKL_RNG_CPU_SOURCE_DIR ../mklcpu)
set(SOURCES ${MKL_RNG_CPU_SOURCE_DIR}/cpu_common.hpp
  ${MKL_RNG_CPU_SOURCE_DIR}/philox4x32x10.cpp
  ${MKL_RNG_CPU_SOURCE_DIR}/mrg32k3a.cpp
  $<$<BOOL:${BUILD_SHARED_LIBS}>: ${MKL_RNG_CPU_SOURCE_DIR}/mkl_rng_cpu_wrappers.cpp>
)

add_library(${LIB_NAME})
add_deprecated_library(${LIB_NAME})
add_library(${LIB_OBJ} OBJECT ${SOURCES})
add_dependencies(onemath_backend_libs_rng ${LIB_NAME})
target_include_directories(${LIB_OBJ}
  PUBLIC  ${ONEMATH_INCLUDE_DIRS}
  PRIVATE ${PROJECT_SOURCE_DIR}/src/include
          ${PROJECT_SOURCE_DIR}/src
          ${CMAKE_BINARY_DIR}/bin
          ${ONEMATH_GENERATED_INCLUDE_PATH}
)

target_compile_options(${LIB_OBJ} PRIVATE ${ONEMATH_BUILD_COPT})
if (USE_ADD_SYCL_TO_TARGET_INTEGRATION)
  add_sycl_to_target(TARGET ${LIB_OBJ} SOURCES ${SOURCES})
endif()
target_link_libraries(${LIB_OBJ} PUBLIC ONEMATH::SYCL::SYCL ONEMATH::OpenRNG::OpenRNG)
target_include_directories(${LIB_OBJ} SYSTEM PRIVATE ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(${LIB_OBJ} PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(${LIB_NAME} PUBLIC ${LIB_OBJ} ONEMATH::OpenRNG::OpenRNG)
target_include_directories(${LIB_NAME} PUBLIC ${ONEMATH_INCLUDE_DIRS})

list(APPEND ONEMATH_RNG_OPENRNG_SHARED_LIB_DEPS ONEMATH::SYCL::SYCL)
list(APPEND ONEMATH_RNG_OPENRNG_SHARED_LIB_DEPS ONEMATH::OpenRNG::OpenRNG)

# Set oneMath libraries as not transitive for dynamic
if(BUILD_SHARED_LIBS)
  set_target_properties(${LIB_NAME} PROPERTIES
    INTERFACE_LINK_LIBRARIES "${ONEMATH_RNG_OPENRNG_SHARED_LIB_DEPS}"
  )
endif()

# Add major version to the library
set_target_properties(${LIB_NAME} PROPERTIES
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Add dependencies rpath to the library
list(APPEND CMAKE_BUILD_RPATH $<TARGET_FILE_DIR:${LIB_NAME}>)

# Add the library to install package
install(TARGETS ${LIB_OBJ} EXPORT oneMathTargets)
install(TARGETS ${LIB_NAME} EXPORT oneMathTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)
