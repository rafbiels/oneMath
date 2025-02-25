/***************************************************************************
*  Copyright (C) Codeplay Software Limited
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  For your convenience, a copy of the License has been included in this
*  repository.
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
**************************************************************************/

#ifndef _ONEMATH_RNG_OPENRNG_HPP_
#define _ONEMATH_RNG_OPENRNG_HPP_

#include "oneapi/math/rng/detail/mklcpu/onemath_rng_mklcpu.hpp"

namespace oneapi::math::rng {
// OpenRNG implements the Intel MKL interface and the oneMath OpenRNG backend
// uses the MKL CPU implementation directly by just aliasing the namespace.
namespace openrng = mklcpu;
} // namespace oneapi::math::rng

#endif //_ONEMATH_RNG_OPENRNG_HPP_
