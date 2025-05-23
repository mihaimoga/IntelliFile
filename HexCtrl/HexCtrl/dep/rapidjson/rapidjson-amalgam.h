
// Begin file: istreamwrapper.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ISTREAMWRAPPER_H_
#define RAPIDJSON_ISTREAMWRAPPER_H_


// Begin file: stream.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.


// Begin file: rapidjson.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_RAPIDJSON_H_
#define RAPIDJSON_RAPIDJSON_H_

/*!\file rapidjson.h
    \brief common definitions and configuration

    \see RAPIDJSON_CONFIG
 */

/*! \defgroup RAPIDJSON_CONFIG RapidJSON configuration
    \brief Configuration macros for library features

    Some RapidJSON features are configurable to adapt the library to a wide
    variety of platforms, environments and usage scenarios.  Most of the
    features can be configured in terms of overridden or predefined
    preprocessor macros at compile-time.

    Some additional customization is available in the \ref RAPIDJSON_ERRORS APIs.

    \note These macros should be given on the compiler command-line
          (where applicable)  to avoid inconsistent values when compiling
          different translation units of a single application.
 */

#include <cstdlib>  // malloc(), realloc(), free(), size_t
#include <cstring>  // memset(), memcpy(), memmove(), memcmp()

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_VERSION_STRING
//
// ALWAYS synchronize the following 3 macros with corresponding variables in /CMakeLists.txt.
//

//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
// token stringification
#define RAPIDJSON_STRINGIFY(x) RAPIDJSON_DO_STRINGIFY(x)
#define RAPIDJSON_DO_STRINGIFY(x) #x

// token concatenation
#define RAPIDJSON_JOIN(X, Y) RAPIDJSON_DO_JOIN(X, Y)
#define RAPIDJSON_DO_JOIN(X, Y) RAPIDJSON_DO_JOIN2(X, Y)
#define RAPIDJSON_DO_JOIN2(X, Y) X##Y
//!@endcond

/*! \def RAPIDJSON_MAJOR_VERSION
    \ingroup RAPIDJSON_CONFIG
    \brief Major version of RapidJSON in integer.
*/
/*! \def RAPIDJSON_MINOR_VERSION
    \ingroup RAPIDJSON_CONFIG
    \brief Minor version of RapidJSON in integer.
*/
/*! \def RAPIDJSON_PATCH_VERSION
    \ingroup RAPIDJSON_CONFIG
    \brief Patch version of RapidJSON in integer.
*/
/*! \def RAPIDJSON_VERSION_STRING
    \ingroup RAPIDJSON_CONFIG
    \brief Version of RapidJSON in "<major>.<minor>.<patch>" string format.
*/
#define RAPIDJSON_MAJOR_VERSION 1
#define RAPIDJSON_MINOR_VERSION 1
#define RAPIDJSON_PATCH_VERSION 0
#define RAPIDJSON_VERSION_STRING \
    RAPIDJSON_STRINGIFY(RAPIDJSON_MAJOR_VERSION.RAPIDJSON_MINOR_VERSION.RAPIDJSON_PATCH_VERSION)

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_NAMESPACE_(BEGIN|END)
/*! \def RAPIDJSON_NAMESPACE
    \ingroup RAPIDJSON_CONFIG
    \brief   provide custom rapidjson namespace

    In order to avoid symbol clashes and/or "One Definition Rule" errors
    between multiple inclusions of (different versions of) RapidJSON in
    a single binary, users can customize the name of the main RapidJSON
    namespace.

    In case of a single nesting level, defining \c RAPIDJSON_NAMESPACE
    to a custom name (e.g. \c MyRapidJSON) is sufficient.  If multiple
    levels are needed, both \ref RAPIDJSON_NAMESPACE_BEGIN and \ref
    RAPIDJSON_NAMESPACE_END need to be defined as well:

    \code
    // in some .cpp file
    #define RAPIDJSON_NAMESPACE my::rapidjson
    #define RAPIDJSON_NAMESPACE_BEGIN namespace my { namespace rapidjson {
    #define RAPIDJSON_NAMESPACE_END   } }
    #include "rapidjson/..."
    \endcode

    \see rapidjson
 */
/*! \def RAPIDJSON_NAMESPACE_BEGIN
    \ingroup RAPIDJSON_CONFIG
    \brief   provide custom rapidjson namespace (opening expression)
    \see RAPIDJSON_NAMESPACE
*/
/*! \def RAPIDJSON_NAMESPACE_END
    \ingroup RAPIDJSON_CONFIG
    \brief   provide custom rapidjson namespace (closing expression)
    \see RAPIDJSON_NAMESPACE
*/
#ifndef RAPIDJSON_NAMESPACE
#define RAPIDJSON_NAMESPACE rapidjson
#endif
#ifndef RAPIDJSON_NAMESPACE_BEGIN
#define RAPIDJSON_NAMESPACE_BEGIN namespace RAPIDJSON_NAMESPACE {
#endif
#ifndef RAPIDJSON_NAMESPACE_END
#define RAPIDJSON_NAMESPACE_END }
#endif

///////////////////////////////////////////////////////////////////////////////
// __cplusplus macro

//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN

#if defined(_MSC_VER)
#define RAPIDJSON_CPLUSPLUS _MSVC_LANG
#else
#define RAPIDJSON_CPLUSPLUS __cplusplus
#endif

//!@endcond

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_HAS_STDSTRING

#ifndef RAPIDJSON_HAS_STDSTRING
#ifdef RAPIDJSON_DOXYGEN_RUNNING
#define RAPIDJSON_HAS_STDSTRING 1 // force generation of documentation
#else
#define RAPIDJSON_HAS_STDSTRING 0 // no std::string support by default
#endif
/*! \def RAPIDJSON_HAS_STDSTRING
    \ingroup RAPIDJSON_CONFIG
    \brief Enable RapidJSON support for \c std::string

    By defining this preprocessor symbol to \c 1, several convenience functions for using
    \ref rapidjson::GenericValue with \c std::string are enabled, especially
    for construction and comparison.

    \hideinitializer
*/
#endif // !defined(RAPIDJSON_HAS_STDSTRING)

#if RAPIDJSON_HAS_STDSTRING
#include <string>
#endif // RAPIDJSON_HAS_STDSTRING

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_USE_MEMBERSMAP

/*! \def RAPIDJSON_USE_MEMBERSMAP
    \ingroup RAPIDJSON_CONFIG
    \brief Enable RapidJSON support for object members handling in a \c std::multimap

    By defining this preprocessor symbol to \c 1, \ref rapidjson::GenericValue object
    members are stored in a \c std::multimap for faster lookup and deletion times, a
    trade off with a slightly slower insertion time and a small object allocat(or)ed
    memory overhead.

    \hideinitializer
*/
#ifndef RAPIDJSON_USE_MEMBERSMAP
#define RAPIDJSON_USE_MEMBERSMAP 0 // not by default
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_NO_INT64DEFINE

/*! \def RAPIDJSON_NO_INT64DEFINE
    \ingroup RAPIDJSON_CONFIG
    \brief Use external 64-bit integer types.

    RapidJSON requires the 64-bit integer types \c int64_t and  \c uint64_t types
    to be available at global scope.

    If users have their own definition, define RAPIDJSON_NO_INT64DEFINE to
    prevent RapidJSON from defining its own types.
*/
#ifndef RAPIDJSON_NO_INT64DEFINE
//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
#if defined(_MSC_VER) && (_MSC_VER < 1800) // Visual Studio 2013

// Begin file: msinttypes/stdint.h
// ISO C9x  compliant stdint.h for Microsoft Visual Studio
// Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124 
// 
//  Copyright (c) 2006-2013 Alexander Chemeris
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//   1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
// 
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
// 
//   3. Neither the name of the product nor the names of its contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
///////////////////////////////////////////////////////////////////////////////

// The above software in this distribution may have been modified by 
// THL A29 Limited ("Tencent Modifications"). 
// All Tencent Modifications are Copyright (C) 2015 THL A29 Limited.

#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_STDINT_H_ // [
#define _MSC_STDINT_H_

#if _MSC_VER > 1000
#pragma once
#endif

// miloyip: Originally Visual Studio 2010 uses its own stdint.h. However it generates warning with INT64_C(), so change to use this file for vs2010.
#if _MSC_VER >= 1600 // [
#include <stdint.h>

#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) // [   See footnote 224 at page 260

#undef INT8_C
#undef INT16_C
#undef INT32_C
#undef INT64_C
#undef UINT8_C
#undef UINT16_C
#undef UINT32_C
#undef UINT64_C

// 7.18.4.1 Macros for minimum-width integer constants

#define INT8_C(val)  val##i8
#define INT16_C(val) val##i16
#define INT32_C(val) val##i32
#define INT64_C(val) val##i64

#define UINT8_C(val)  val##ui8
#define UINT16_C(val) val##ui16
#define UINT32_C(val) val##ui32
#define UINT64_C(val) val##ui64

// 7.18.4.2 Macros for greatest-width integer constants
// These #ifndef's are needed to prevent collisions with <boost/cstdint.hpp>.
// Check out Issue 9 for the details.
#ifndef INTMAX_C //   [
#  define INTMAX_C   INT64_C
#endif // INTMAX_C    ]
#ifndef UINTMAX_C //  [
#  define UINTMAX_C  UINT64_C
#endif // UINTMAX_C   ]

#endif // __STDC_CONSTANT_MACROS ]

#else // ] _MSC_VER >= 1700 [

#include <limits.h>

// For Visual Studio 6 in C++ mode and for many Visual Studio versions when
// compiling for ARM we have to wrap <wchar.h> include with 'extern "C++" {}'
// or compiler would give many errors like this:
//   error C2733: second C linkage of overloaded function 'wmemchr' not allowed
#if defined(__cplusplus) && !defined(_M_ARM)
extern "C" {
#endif
#  include <wchar.h>
#if defined(__cplusplus) && !defined(_M_ARM)
}
#endif

// Define _W64 macros to mark types changing their size, like intptr_t.
#ifndef _W64
#  if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#     define _W64 __w64
#  else
#     define _W64
#  endif
#endif


// 7.18.1 Integer types

// 7.18.1.1 Exact-width integer types

// Visual Studio 6 and Embedded Visual C++ 4 doesn't
// realize that, e.g. char has the same size as __int8
// so we give up on __intX for them.
#if (_MSC_VER < 1300)
   typedef signed char       int8_t;
   typedef signed short      int16_t;
   typedef signed int        int32_t;
   typedef unsigned char     uint8_t;
   typedef unsigned short    uint16_t;
   typedef unsigned int      uint32_t;
#else
   typedef signed __int8     int8_t;
   typedef signed __int16    int16_t;
   typedef signed __int32    int32_t;
   typedef unsigned __int8   uint8_t;
   typedef unsigned __int16  uint16_t;
   typedef unsigned __int32  uint32_t;
#endif
typedef signed __int64       int64_t;
typedef unsigned __int64     uint64_t;


// 7.18.1.2 Minimum-width integer types
typedef int8_t    int_least8_t;
typedef int16_t   int_least16_t;
typedef int32_t   int_least32_t;
typedef int64_t   int_least64_t;
typedef uint8_t   uint_least8_t;
typedef uint16_t  uint_least16_t;
typedef uint32_t  uint_least32_t;
typedef uint64_t  uint_least64_t;

// 7.18.1.3 Fastest minimum-width integer types
typedef int8_t    int_fast8_t;
typedef int16_t   int_fast16_t;
typedef int32_t   int_fast32_t;
typedef int64_t   int_fast64_t;
typedef uint8_t   uint_fast8_t;
typedef uint16_t  uint_fast16_t;
typedef uint32_t  uint_fast32_t;
typedef uint64_t  uint_fast64_t;

// 7.18.1.4 Integer types capable of holding object pointers
#ifdef _WIN64 // [
   typedef signed __int64    intptr_t;
   typedef unsigned __int64  uintptr_t;
#else // _WIN64 ][
   typedef _W64 signed int   intptr_t;
   typedef _W64 unsigned int uintptr_t;
#endif // _WIN64 ]

// 7.18.1.5 Greatest-width integer types
typedef int64_t   intmax_t;
typedef uint64_t  uintmax_t;


// 7.18.2 Limits of specified-width integer types

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) // [   See footnote 220 at page 257 and footnote 221 at page 259

// 7.18.2.1 Limits of exact-width integer types
#define INT8_MIN     ((int8_t)_I8_MIN)
#define INT8_MAX     _I8_MAX
#define INT16_MIN    ((int16_t)_I16_MIN)
#define INT16_MAX    _I16_MAX
#define INT32_MIN    ((int32_t)_I32_MIN)
#define INT32_MAX    _I32_MAX
#define INT64_MIN    ((int64_t)_I64_MIN)
#define INT64_MAX    _I64_MAX
#define UINT8_MAX    _UI8_MAX
#define UINT16_MAX   _UI16_MAX
#define UINT32_MAX   _UI32_MAX
#define UINT64_MAX   _UI64_MAX

// 7.18.2.2 Limits of minimum-width integer types
#define INT_LEAST8_MIN    INT8_MIN
#define INT_LEAST8_MAX    INT8_MAX
#define INT_LEAST16_MIN   INT16_MIN
#define INT_LEAST16_MAX   INT16_MAX
#define INT_LEAST32_MIN   INT32_MIN
#define INT_LEAST32_MAX   INT32_MAX
#define INT_LEAST64_MIN   INT64_MIN
#define INT_LEAST64_MAX   INT64_MAX
#define UINT_LEAST8_MAX   UINT8_MAX
#define UINT_LEAST16_MAX  UINT16_MAX
#define UINT_LEAST32_MAX  UINT32_MAX
#define UINT_LEAST64_MAX  UINT64_MAX

// 7.18.2.3 Limits of fastest minimum-width integer types
#define INT_FAST8_MIN    INT8_MIN
#define INT_FAST8_MAX    INT8_MAX
#define INT_FAST16_MIN   INT16_MIN
#define INT_FAST16_MAX   INT16_MAX
#define INT_FAST32_MIN   INT32_MIN
#define INT_FAST32_MAX   INT32_MAX
#define INT_FAST64_MIN   INT64_MIN
#define INT_FAST64_MAX   INT64_MAX
#define UINT_FAST8_MAX   UINT8_MAX
#define UINT_FAST16_MAX  UINT16_MAX
#define UINT_FAST32_MAX  UINT32_MAX
#define UINT_FAST64_MAX  UINT64_MAX

// 7.18.2.4 Limits of integer types capable of holding object pointers
#ifdef _WIN64 // [
#  define INTPTR_MIN   INT64_MIN
#  define INTPTR_MAX   INT64_MAX
#  define UINTPTR_MAX  UINT64_MAX
#else // _WIN64 ][
#  define INTPTR_MIN   INT32_MIN
#  define INTPTR_MAX   INT32_MAX
#  define UINTPTR_MAX  UINT32_MAX
#endif // _WIN64 ]

// 7.18.2.5 Limits of greatest-width integer types
#define INTMAX_MIN   INT64_MIN
#define INTMAX_MAX   INT64_MAX
#define UINTMAX_MAX  UINT64_MAX

// 7.18.3 Limits of other integer types

#ifdef _WIN64 // [
#  define PTRDIFF_MIN  _I64_MIN
#  define PTRDIFF_MAX  _I64_MAX
#else  // _WIN64 ][
#  define PTRDIFF_MIN  _I32_MIN
#  define PTRDIFF_MAX  _I32_MAX
#endif  // _WIN64 ]

#define SIG_ATOMIC_MIN  INT_MIN
#define SIG_ATOMIC_MAX  INT_MAX

#ifndef SIZE_MAX // [
#  ifdef _WIN64 // [
#     define SIZE_MAX  _UI64_MAX
#  else // _WIN64 ][
#     define SIZE_MAX  _UI32_MAX
#  endif // _WIN64 ]
#endif // SIZE_MAX ]

// WCHAR_MIN and WCHAR_MAX are also defined in <wchar.h>
#ifndef WCHAR_MIN // [
#  define WCHAR_MIN  0
#endif  // WCHAR_MIN ]
#ifndef WCHAR_MAX // [
#  define WCHAR_MAX  _UI16_MAX
#endif  // WCHAR_MAX ]

#define WINT_MIN  0
#define WINT_MAX  _UI16_MAX

#endif // __STDC_LIMIT_MACROS ]


// 7.18.4 Limits of other integer types

#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) // [   See footnote 224 at page 260

// 7.18.4.1 Macros for minimum-width integer constants

#define INT8_C(val)  val##i8
#define INT16_C(val) val##i16
#define INT32_C(val) val##i32
#define INT64_C(val) val##i64

#define UINT8_C(val)  val##ui8
#define UINT16_C(val) val##ui16
#define UINT32_C(val) val##ui32
#define UINT64_C(val) val##ui64

// 7.18.4.2 Macros for greatest-width integer constants
// These #ifndef's are needed to prevent collisions with <boost/cstdint.hpp>.
// Check out Issue 9 for the details.
#ifndef INTMAX_C //   [
#  define INTMAX_C   INT64_C
#endif // INTMAX_C    ]
#ifndef UINTMAX_C //  [
#  define UINTMAX_C  UINT64_C
#endif // UINTMAX_C   ]

#endif // __STDC_CONSTANT_MACROS ]

#endif // _MSC_VER >= 1600 ]

#endif // _MSC_STDINT_H_ ]

// End file:msinttypes/stdint.h


// Begin file: msinttypes/inttypes.h
// ISO C9x  compliant inttypes.h for Microsoft Visual Studio
// Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124 
// 
//  Copyright (c) 2006-2013 Alexander Chemeris
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//   1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
// 
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
// 
//   3. Neither the name of the product nor the names of its contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
///////////////////////////////////////////////////////////////////////////////

// The above software in this distribution may have been modified by 
// THL A29 Limited ("Tencent Modifications"). 
// All Tencent Modifications are Copyright (C) 2015 THL A29 Limited.

#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_INTTYPES_H_ // [
#define _MSC_INTTYPES_H_

#if _MSC_VER > 1000
#pragma once
#endif


// Begin file: stdint.h
// already included
// End file:stdint.h


// miloyip: VC supports inttypes.h since VC2013
#if _MSC_VER >= 1800
#include <inttypes.h>
#else

// 7.8 Format conversion of integer types

typedef struct {
   intmax_t quot;
   intmax_t rem;
} imaxdiv_t;

// 7.8.1 Macros for format specifiers

#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) // [   See footnote 185 at page 198

// The fprintf macros for signed integers are:
#define PRId8       "d"
#define PRIi8       "i"
#define PRIdLEAST8  "d"
#define PRIiLEAST8  "i"
#define PRIdFAST8   "d"
#define PRIiFAST8   "i"

#define PRId16       "hd"
#define PRIi16       "hi"
#define PRIdLEAST16  "hd"
#define PRIiLEAST16  "hi"
#define PRIdFAST16   "hd"
#define PRIiFAST16   "hi"

#define PRId32       "I32d"
#define PRIi32       "I32i"
#define PRIdLEAST32  "I32d"
#define PRIiLEAST32  "I32i"
#define PRIdFAST32   "I32d"
#define PRIiFAST32   "I32i"

#define PRId64       "I64d"
#define PRIi64       "I64i"
#define PRIdLEAST64  "I64d"
#define PRIiLEAST64  "I64i"
#define PRIdFAST64   "I64d"
#define PRIiFAST64   "I64i"

#define PRIdMAX     "I64d"
#define PRIiMAX     "I64i"

#define PRIdPTR     "Id"
#define PRIiPTR     "Ii"

// The fprintf macros for unsigned integers are:
#define PRIo8       "o"
#define PRIu8       "u"
#define PRIx8       "x"
#define PRIX8       "X"
#define PRIoLEAST8  "o"
#define PRIuLEAST8  "u"
#define PRIxLEAST8  "x"
#define PRIXLEAST8  "X"
#define PRIoFAST8   "o"
#define PRIuFAST8   "u"
#define PRIxFAST8   "x"
#define PRIXFAST8   "X"

#define PRIo16       "ho"
#define PRIu16       "hu"
#define PRIx16       "hx"
#define PRIX16       "hX"
#define PRIoLEAST16  "ho"
#define PRIuLEAST16  "hu"
#define PRIxLEAST16  "hx"
#define PRIXLEAST16  "hX"
#define PRIoFAST16   "ho"
#define PRIuFAST16   "hu"
#define PRIxFAST16   "hx"
#define PRIXFAST16   "hX"

#define PRIo32       "I32o"
#define PRIu32       "I32u"
#define PRIx32       "I32x"
#define PRIX32       "I32X"
#define PRIoLEAST32  "I32o"
#define PRIuLEAST32  "I32u"
#define PRIxLEAST32  "I32x"
#define PRIXLEAST32  "I32X"
#define PRIoFAST32   "I32o"
#define PRIuFAST32   "I32u"
#define PRIxFAST32   "I32x"
#define PRIXFAST32   "I32X"

#define PRIo64       "I64o"
#define PRIu64       "I64u"
#define PRIx64       "I64x"
#define PRIX64       "I64X"
#define PRIoLEAST64  "I64o"
#define PRIuLEAST64  "I64u"
#define PRIxLEAST64  "I64x"
#define PRIXLEAST64  "I64X"
#define PRIoFAST64   "I64o"
#define PRIuFAST64   "I64u"
#define PRIxFAST64   "I64x"
#define PRIXFAST64   "I64X"

#define PRIoMAX     "I64o"
#define PRIuMAX     "I64u"
#define PRIxMAX     "I64x"
#define PRIXMAX     "I64X"

#define PRIoPTR     "Io"
#define PRIuPTR     "Iu"
#define PRIxPTR     "Ix"
#define PRIXPTR     "IX"

// The fscanf macros for signed integers are:
#define SCNd8       "d"
#define SCNi8       "i"
#define SCNdLEAST8  "d"
#define SCNiLEAST8  "i"
#define SCNdFAST8   "d"
#define SCNiFAST8   "i"

#define SCNd16       "hd"
#define SCNi16       "hi"
#define SCNdLEAST16  "hd"
#define SCNiLEAST16  "hi"
#define SCNdFAST16   "hd"
#define SCNiFAST16   "hi"

#define SCNd32       "ld"
#define SCNi32       "li"
#define SCNdLEAST32  "ld"
#define SCNiLEAST32  "li"
#define SCNdFAST32   "ld"
#define SCNiFAST32   "li"

#define SCNd64       "I64d"
#define SCNi64       "I64i"
#define SCNdLEAST64  "I64d"
#define SCNiLEAST64  "I64i"
#define SCNdFAST64   "I64d"
#define SCNiFAST64   "I64i"

#define SCNdMAX     "I64d"
#define SCNiMAX     "I64i"

#ifdef _WIN64 // [
#  define SCNdPTR     "I64d"
#  define SCNiPTR     "I64i"
#else  // _WIN64 ][
#  define SCNdPTR     "ld"
#  define SCNiPTR     "li"
#endif  // _WIN64 ]

// The fscanf macros for unsigned integers are:
#define SCNo8       "o"
#define SCNu8       "u"
#define SCNx8       "x"
#define SCNX8       "X"
#define SCNoLEAST8  "o"
#define SCNuLEAST8  "u"
#define SCNxLEAST8  "x"
#define SCNXLEAST8  "X"
#define SCNoFAST8   "o"
#define SCNuFAST8   "u"
#define SCNxFAST8   "x"
#define SCNXFAST8   "X"

#define SCNo16       "ho"
#define SCNu16       "hu"
#define SCNx16       "hx"
#define SCNX16       "hX"
#define SCNoLEAST16  "ho"
#define SCNuLEAST16  "hu"
#define SCNxLEAST16  "hx"
#define SCNXLEAST16  "hX"
#define SCNoFAST16   "ho"
#define SCNuFAST16   "hu"
#define SCNxFAST16   "hx"
#define SCNXFAST16   "hX"

#define SCNo32       "lo"
#define SCNu32       "lu"
#define SCNx32       "lx"
#define SCNX32       "lX"
#define SCNoLEAST32  "lo"
#define SCNuLEAST32  "lu"
#define SCNxLEAST32  "lx"
#define SCNXLEAST32  "lX"
#define SCNoFAST32   "lo"
#define SCNuFAST32   "lu"
#define SCNxFAST32   "lx"
#define SCNXFAST32   "lX"

#define SCNo64       "I64o"
#define SCNu64       "I64u"
#define SCNx64       "I64x"
#define SCNX64       "I64X"
#define SCNoLEAST64  "I64o"
#define SCNuLEAST64  "I64u"
#define SCNxLEAST64  "I64x"
#define SCNXLEAST64  "I64X"
#define SCNoFAST64   "I64o"
#define SCNuFAST64   "I64u"
#define SCNxFAST64   "I64x"
#define SCNXFAST64   "I64X"

#define SCNoMAX     "I64o"
#define SCNuMAX     "I64u"
#define SCNxMAX     "I64x"
#define SCNXMAX     "I64X"

#ifdef _WIN64 // [
#  define SCNoPTR     "I64o"
#  define SCNuPTR     "I64u"
#  define SCNxPTR     "I64x"
#  define SCNXPTR     "I64X"
#else  // _WIN64 ][
#  define SCNoPTR     "lo"
#  define SCNuPTR     "lu"
#  define SCNxPTR     "lx"
#  define SCNXPTR     "lX"
#endif  // _WIN64 ]

#endif // __STDC_FORMAT_MACROS ]

// 7.8.2 Functions for greatest-width integer types

// 7.8.2.1 The imaxabs function
#define imaxabs _abs64

// 7.8.2.2 The imaxdiv function

// This is modified version of div() function from Microsoft's div.c found
// in %MSVC.NET%\crt\src\div.c
#ifdef STATIC_IMAXDIV // [
static
#else // STATIC_IMAXDIV ][
_inline
#endif // STATIC_IMAXDIV ]
imaxdiv_t __cdecl imaxdiv(intmax_t numer, intmax_t denom)
{
   imaxdiv_t result;

   result.quot = numer / denom;
   result.rem = numer % denom;

   if (numer < 0 && result.rem > 0) {
      // did division wrong; must fix up
      ++result.quot;
      result.rem -= denom;
   }

   return result;
}

// 7.8.2.3 The strtoimax and strtoumax functions
#define strtoimax _strtoi64
#define strtoumax _strtoui64

// 7.8.2.4 The wcstoimax and wcstoumax functions
#define wcstoimax _wcstoi64
#define wcstoumax _wcstoui64

#endif // _MSC_VER >= 1800

#endif // _MSC_INTTYPES_H_ ]

// End file:msinttypes/inttypes.h

#else
// Other compilers should have this.
#include <stdint.h>
#include <inttypes.h>
#endif
//!@endcond
#ifdef RAPIDJSON_DOXYGEN_RUNNING
#define RAPIDJSON_NO_INT64DEFINE
#endif
#endif // RAPIDJSON_NO_INT64TYPEDEF

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_FORCEINLINE

#ifndef RAPIDJSON_FORCEINLINE
//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
#if defined(_MSC_VER) && defined(NDEBUG)
#define RAPIDJSON_FORCEINLINE __forceinline
#elif defined(__GNUC__) && __GNUC__ >= 4 && defined(NDEBUG)
#define RAPIDJSON_FORCEINLINE __attribute__((always_inline))
#else
#define RAPIDJSON_FORCEINLINE
#endif
//!@endcond
#endif // RAPIDJSON_FORCEINLINE

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_ENDIAN
#define RAPIDJSON_LITTLEENDIAN  0   //!< Little endian machine
#define RAPIDJSON_BIGENDIAN     1   //!< Big endian machine

//! Endianness of the machine.
/*!
    \def RAPIDJSON_ENDIAN
    \ingroup RAPIDJSON_CONFIG

    GCC 4.6 provided macro for detecting endianness of the target machine. But other
    compilers may not have this. User can define RAPIDJSON_ENDIAN to either
    \ref RAPIDJSON_LITTLEENDIAN or \ref RAPIDJSON_BIGENDIAN.

    Default detection implemented with reference to
    \li https://gcc.gnu.org/onlinedocs/gcc-4.6.0/cpp/Common-Predefined-Macros.html
    \li http://www.boost.org/doc/libs/1_42_0/boost/detail/endian.hpp
*/
#ifndef RAPIDJSON_ENDIAN
// Detect with GCC 4.6's macro
#  ifdef __BYTE_ORDER__
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#      define RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN
#    elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#      define RAPIDJSON_ENDIAN RAPIDJSON_BIGENDIAN
#    else
#      error Unknown machine endianness detected. User needs to define RAPIDJSON_ENDIAN.
#    endif // __BYTE_ORDER__
// Detect with GLIBC's endian.h
#  elif defined(__GLIBC__)
#    include <endian.h>
#    if (__BYTE_ORDER == __LITTLE_ENDIAN)
#      define RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN
#    elif (__BYTE_ORDER == __BIG_ENDIAN)
#      define RAPIDJSON_ENDIAN RAPIDJSON_BIGENDIAN
#    else
#      error Unknown machine endianness detected. User needs to define RAPIDJSON_ENDIAN.
#   endif // __GLIBC__
// Detect with _LITTLE_ENDIAN and _BIG_ENDIAN macro
#  elif defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)
#    define RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN
#  elif defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)
#    define RAPIDJSON_ENDIAN RAPIDJSON_BIGENDIAN
// Detect with architecture macros
#  elif defined(__sparc) || defined(__sparc__) || defined(_POWER) || defined(__powerpc__) || defined(__ppc__) || defined(__ppc64__) || defined(__hpux) || defined(__hppa) || defined(_MIPSEB) || defined(_POWER) || defined(__s390__)
#    define RAPIDJSON_ENDIAN RAPIDJSON_BIGENDIAN
#  elif defined(__i386__) || defined(__alpha__) || defined(__ia64) || defined(__ia64__) || defined(_M_IX86) || defined(_M_IA64) || defined(_M_ALPHA) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) || defined(_M_X64) || defined(__bfin__)
#    define RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN
#  elif defined(_MSC_VER) && (defined(_M_ARM) || defined(_M_ARM64))
#    define RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN
#  elif defined(RAPIDJSON_DOXYGEN_RUNNING)
#    define RAPIDJSON_ENDIAN
#  else
#    error Unknown machine endianness detected. User needs to define RAPIDJSON_ENDIAN.
#  endif
#endif // RAPIDJSON_ENDIAN

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_64BIT

//! Whether using 64-bit architecture
#ifndef RAPIDJSON_64BIT
#if defined(__LP64__) || (defined(__x86_64__) && defined(__ILP32__)) || defined(_WIN64) || defined(__EMSCRIPTEN__)
#define RAPIDJSON_64BIT 1
#else
#define RAPIDJSON_64BIT 0
#endif
#endif // RAPIDJSON_64BIT

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_ALIGN

//! Data alignment of the machine.
/*! \ingroup RAPIDJSON_CONFIG
    \param x pointer to align

    Some machines require strict data alignment. The default is 8 bytes.
    User can customize by defining the RAPIDJSON_ALIGN function macro.
*/
#ifndef RAPIDJSON_ALIGN
#define RAPIDJSON_ALIGN(x) (((x) + static_cast<size_t>(7u)) & ~static_cast<size_t>(7u))
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_UINT64_C2

//! Construct a 64-bit literal by a pair of 32-bit integer.
/*!
    64-bit literal with or without ULL suffix is prone to compiler warnings.
    UINT64_C() is C macro which cause compilation problems.
    Use this macro to define 64-bit constants by a pair of 32-bit integer.
*/
#ifndef RAPIDJSON_UINT64_C2
#define RAPIDJSON_UINT64_C2(high32, low32) ((static_cast<uint64_t>(high32) << 32) | static_cast<uint64_t>(low32))
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_48BITPOINTER_OPTIMIZATION

//! Use only lower 48-bit address for some pointers.
/*!
    \ingroup RAPIDJSON_CONFIG

    This optimization uses the fact that current X86-64 architecture only implement lower 48-bit virtual address.
    The higher 16-bit can be used for storing other data.
    \c GenericValue uses this optimization to reduce its size form 24 bytes to 16 bytes in 64-bit architecture.
*/
#ifndef RAPIDJSON_48BITPOINTER_OPTIMIZATION
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#define RAPIDJSON_48BITPOINTER_OPTIMIZATION 1
#else
#define RAPIDJSON_48BITPOINTER_OPTIMIZATION 0
#endif
#endif // RAPIDJSON_48BITPOINTER_OPTIMIZATION

#if RAPIDJSON_48BITPOINTER_OPTIMIZATION == 1
#if RAPIDJSON_64BIT != 1
#error RAPIDJSON_48BITPOINTER_OPTIMIZATION can only be set to 1 when RAPIDJSON_64BIT=1
#endif
#define RAPIDJSON_SETPOINTER(type, p, x) (p = reinterpret_cast<type *>((reinterpret_cast<uintptr_t>(p) & static_cast<uintptr_t>(RAPIDJSON_UINT64_C2(0xFFFF0000, 0x00000000))) | reinterpret_cast<uintptr_t>(reinterpret_cast<const void*>(x))))
#define RAPIDJSON_GETPOINTER(type, p) (reinterpret_cast<type *>(reinterpret_cast<uintptr_t>(p) & static_cast<uintptr_t>(RAPIDJSON_UINT64_C2(0x0000FFFF, 0xFFFFFFFF))))
#else
#define RAPIDJSON_SETPOINTER(type, p, x) (p = (x))
#define RAPIDJSON_GETPOINTER(type, p) (p)
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_SSE2/RAPIDJSON_SSE42/RAPIDJSON_NEON/RAPIDJSON_SIMD

/*! \def RAPIDJSON_SIMD
    \ingroup RAPIDJSON_CONFIG
    \brief Enable SSE2/SSE4.2/Neon optimization.

    RapidJSON supports optimized implementations for some parsing operations
    based on the SSE2, SSE4.2 or NEon SIMD extensions on modern Intel
    or ARM compatible processors.

    To enable these optimizations, three different symbols can be defined;
    \code
    // Enable SSE2 optimization.
    #define RAPIDJSON_SSE2

    // Enable SSE4.2 optimization.
    #define RAPIDJSON_SSE42
    \endcode

    // Enable ARM Neon optimization.
    #define RAPIDJSON_NEON
    \endcode

    \c RAPIDJSON_SSE42 takes precedence over SSE2, if both are defined.

    If any of these symbols is defined, RapidJSON defines the macro
    \c RAPIDJSON_SIMD to indicate the availability of the optimized code.
*/
#if defined(RAPIDJSON_SSE2) || defined(RAPIDJSON_SSE42) \
    || defined(RAPIDJSON_NEON) || defined(RAPIDJSON_DOXYGEN_RUNNING)
#define RAPIDJSON_SIMD
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_NO_SIZETYPEDEFINE

#ifndef RAPIDJSON_NO_SIZETYPEDEFINE
/*! \def RAPIDJSON_NO_SIZETYPEDEFINE
    \ingroup RAPIDJSON_CONFIG
    \brief User-provided \c SizeType definition.

    In order to avoid using 32-bit size types for indexing strings and arrays,
    define this preprocessor symbol and provide the type rapidjson::SizeType
    before including RapidJSON:
    \code
    #define RAPIDJSON_NO_SIZETYPEDEFINE
    namespace rapidjson { typedef ::std::size_t SizeType; }
    #include "rapidjson/..."
    \endcode

    \see rapidjson::SizeType
*/
#ifdef RAPIDJSON_DOXYGEN_RUNNING
#define RAPIDJSON_NO_SIZETYPEDEFINE
#endif
RAPIDJSON_NAMESPACE_BEGIN
//! Size type (for string lengths, array sizes, etc.)
/*! RapidJSON uses 32-bit array/string indices even on 64-bit platforms,
    instead of using \c size_t. Users may override the SizeType by defining
    \ref RAPIDJSON_NO_SIZETYPEDEFINE.
*/
typedef unsigned SizeType;
RAPIDJSON_NAMESPACE_END
#endif

// always import std::size_t to rapidjson namespace
RAPIDJSON_NAMESPACE_BEGIN
using std::size_t;
RAPIDJSON_NAMESPACE_END

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_ASSERT

//! Assertion.
/*! \ingroup RAPIDJSON_CONFIG
    By default, rapidjson uses C \c assert() for internal assertions.
    User can override it by defining RAPIDJSON_ASSERT(x) macro.

    \note Parsing errors are handled and can be customized by the
          \ref RAPIDJSON_ERRORS APIs.
*/
#ifndef RAPIDJSON_ASSERT
#include <cassert>
#define RAPIDJSON_ASSERT(x) assert(x)
#endif // RAPIDJSON_ASSERT

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_STATIC_ASSERT

// Prefer C++11 static_assert, if available
#ifndef RAPIDJSON_STATIC_ASSERT
#if RAPIDJSON_CPLUSPLUS >= 201103L || ( defined(_MSC_VER) && _MSC_VER >= 1800 )
#define RAPIDJSON_STATIC_ASSERT(x) \
   static_assert(x, RAPIDJSON_STRINGIFY(x))
#endif // C++11
#endif // RAPIDJSON_STATIC_ASSERT

// Adopt C++03 implementation from boost
#ifndef RAPIDJSON_STATIC_ASSERT
#ifndef __clang__
//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
#endif
RAPIDJSON_NAMESPACE_BEGIN
template <bool x> struct STATIC_ASSERTION_FAILURE;
template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
template <size_t x> struct StaticAssertTest {};
RAPIDJSON_NAMESPACE_END

#if defined(__GNUC__) || defined(__clang__)
#define RAPIDJSON_STATIC_ASSERT_UNUSED_ATTRIBUTE __attribute__((unused))
#else
#define RAPIDJSON_STATIC_ASSERT_UNUSED_ATTRIBUTE 
#endif
#ifndef __clang__
//!@endcond
#endif

/*! \def RAPIDJSON_STATIC_ASSERT
    \brief (Internal) macro to check for conditions at compile-time
    \param x compile-time condition
    \hideinitializer
 */
#define RAPIDJSON_STATIC_ASSERT(x) \
    typedef ::RAPIDJSON_NAMESPACE::StaticAssertTest< \
      sizeof(::RAPIDJSON_NAMESPACE::STATIC_ASSERTION_FAILURE<bool(x) >)> \
    RAPIDJSON_JOIN(StaticAssertTypedef, __LINE__) RAPIDJSON_STATIC_ASSERT_UNUSED_ATTRIBUTE
#endif // RAPIDJSON_STATIC_ASSERT

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_LIKELY, RAPIDJSON_UNLIKELY

//! Compiler branching hint for expression with high probability to be true.
/*!
    \ingroup RAPIDJSON_CONFIG
    \param x Boolean expression likely to be true.
*/
#ifndef RAPIDJSON_LIKELY
#if defined(__GNUC__) || defined(__clang__)
#define RAPIDJSON_LIKELY(x) __builtin_expect(!!(x), 1)
#else
#define RAPIDJSON_LIKELY(x) (x)
#endif
#endif

//! Compiler branching hint for expression with low probability to be true.
/*!
    \ingroup RAPIDJSON_CONFIG
    \param x Boolean expression unlikely to be true.
*/
#ifndef RAPIDJSON_UNLIKELY
#if defined(__GNUC__) || defined(__clang__)
#define RAPIDJSON_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define RAPIDJSON_UNLIKELY(x) (x)
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
// Helpers

//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN

#define RAPIDJSON_MULTILINEMACRO_BEGIN do {
#define RAPIDJSON_MULTILINEMACRO_END \
} while((void)0, 0)

// adopted from Boost
#define RAPIDJSON_VERSION_CODE(x,y,z) \
  (((x)*100000) + ((y)*100) + (z))

#if defined(__has_builtin)
#define RAPIDJSON_HAS_BUILTIN(x) __has_builtin(x)
#else
#define RAPIDJSON_HAS_BUILTIN(x) 0
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_DIAG_PUSH/POP, RAPIDJSON_DIAG_OFF

#if defined(__GNUC__)
#define RAPIDJSON_GNUC \
    RAPIDJSON_VERSION_CODE(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)
#endif

#if defined(__clang__) || (defined(RAPIDJSON_GNUC) && RAPIDJSON_GNUC >= RAPIDJSON_VERSION_CODE(4,2,0))

#define RAPIDJSON_PRAGMA(x) _Pragma(RAPIDJSON_STRINGIFY(x))
#define RAPIDJSON_DIAG_PRAGMA(x) RAPIDJSON_PRAGMA(GCC diagnostic x)
#define RAPIDJSON_DIAG_OFF(x) \
    RAPIDJSON_DIAG_PRAGMA(ignored RAPIDJSON_STRINGIFY(RAPIDJSON_JOIN(-W,x)))

// push/pop support in Clang and GCC>=4.6
#if defined(__clang__) || (defined(RAPIDJSON_GNUC) && RAPIDJSON_GNUC >= RAPIDJSON_VERSION_CODE(4,6,0))
#define RAPIDJSON_DIAG_PUSH RAPIDJSON_DIAG_PRAGMA(push)
#define RAPIDJSON_DIAG_POP  RAPIDJSON_DIAG_PRAGMA(pop)
#else // GCC >= 4.2, < 4.6
#define RAPIDJSON_DIAG_PUSH /* ignored */
#define RAPIDJSON_DIAG_POP /* ignored */
#endif

#elif defined(_MSC_VER)

// pragma (MSVC specific)
#define RAPIDJSON_PRAGMA(x) __pragma(x)
#define RAPIDJSON_DIAG_PRAGMA(x) RAPIDJSON_PRAGMA(warning(x))

#define RAPIDJSON_DIAG_OFF(x) RAPIDJSON_DIAG_PRAGMA(disable: x)
#define RAPIDJSON_DIAG_PUSH RAPIDJSON_DIAG_PRAGMA(push)
#define RAPIDJSON_DIAG_POP  RAPIDJSON_DIAG_PRAGMA(pop)

#else

#define RAPIDJSON_DIAG_OFF(x) /* ignored */
#define RAPIDJSON_DIAG_PUSH   /* ignored */
#define RAPIDJSON_DIAG_POP    /* ignored */

#endif // RAPIDJSON_DIAG_*

///////////////////////////////////////////////////////////////////////////////
// C++11 features

#ifndef RAPIDJSON_HAS_CXX11
#define RAPIDJSON_HAS_CXX11 (RAPIDJSON_CPLUSPLUS >= 201103L)
#endif

#ifndef RAPIDJSON_HAS_CXX11_RVALUE_REFS
#if RAPIDJSON_HAS_CXX11
#define RAPIDJSON_HAS_CXX11_RVALUE_REFS 1
#elif defined(__clang__)
#if __has_feature(cxx_rvalue_references) && \
    (defined(_MSC_VER) || defined(_LIBCPP_VERSION) || defined(__GLIBCXX__) && __GLIBCXX__ >= 20080306)
#define RAPIDJSON_HAS_CXX11_RVALUE_REFS 1
#else
#define RAPIDJSON_HAS_CXX11_RVALUE_REFS 0
#endif
#elif (defined(RAPIDJSON_GNUC) && (RAPIDJSON_GNUC >= RAPIDJSON_VERSION_CODE(4,3,0)) && defined(__GXX_EXPERIMENTAL_CXX0X__)) || \
      (defined(_MSC_VER) && _MSC_VER >= 1600) || \
      (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5140 && defined(__GXX_EXPERIMENTAL_CXX0X__))

#define RAPIDJSON_HAS_CXX11_RVALUE_REFS 1
#else
#define RAPIDJSON_HAS_CXX11_RVALUE_REFS 0
#endif
#endif // RAPIDJSON_HAS_CXX11_RVALUE_REFS

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
#include <utility> // std::move
#endif

#ifndef RAPIDJSON_HAS_CXX11_NOEXCEPT
#if RAPIDJSON_HAS_CXX11
#define RAPIDJSON_HAS_CXX11_NOEXCEPT 1
#elif defined(__clang__)
#define RAPIDJSON_HAS_CXX11_NOEXCEPT __has_feature(cxx_noexcept)
#elif (defined(RAPIDJSON_GNUC) && (RAPIDJSON_GNUC >= RAPIDJSON_VERSION_CODE(4,6,0)) && defined(__GXX_EXPERIMENTAL_CXX0X__)) || \
    (defined(_MSC_VER) && _MSC_VER >= 1900) || \
    (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5140 && defined(__GXX_EXPERIMENTAL_CXX0X__))
#define RAPIDJSON_HAS_CXX11_NOEXCEPT 1
#else
#define RAPIDJSON_HAS_CXX11_NOEXCEPT 0
#endif
#endif
#ifndef RAPIDJSON_NOEXCEPT
#if RAPIDJSON_HAS_CXX11_NOEXCEPT
#define RAPIDJSON_NOEXCEPT noexcept
#else
#define RAPIDJSON_NOEXCEPT throw()
#endif // RAPIDJSON_HAS_CXX11_NOEXCEPT
#endif

// no automatic detection, yet
#ifndef RAPIDJSON_HAS_CXX11_TYPETRAITS
#if (defined(_MSC_VER) && _MSC_VER >= 1700)
#define RAPIDJSON_HAS_CXX11_TYPETRAITS 1
#else
#define RAPIDJSON_HAS_CXX11_TYPETRAITS 0
#endif
#endif

#ifndef RAPIDJSON_HAS_CXX11_RANGE_FOR
#if defined(__clang__)
#define RAPIDJSON_HAS_CXX11_RANGE_FOR __has_feature(cxx_range_for)
#elif (defined(RAPIDJSON_GNUC) && (RAPIDJSON_GNUC >= RAPIDJSON_VERSION_CODE(4,6,0)) && defined(__GXX_EXPERIMENTAL_CXX0X__)) || \
      (defined(_MSC_VER) && _MSC_VER >= 1700) || \
      (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5140 && defined(__GXX_EXPERIMENTAL_CXX0X__))
#define RAPIDJSON_HAS_CXX11_RANGE_FOR 1
#else
#define RAPIDJSON_HAS_CXX11_RANGE_FOR 0
#endif
#endif // RAPIDJSON_HAS_CXX11_RANGE_FOR

///////////////////////////////////////////////////////////////////////////////
// C++17 features

#ifndef RAPIDJSON_HAS_CXX17
#define RAPIDJSON_HAS_CXX17 (RAPIDJSON_CPLUSPLUS >= 201703L)
#endif

#if RAPIDJSON_HAS_CXX17
# define RAPIDJSON_DELIBERATE_FALLTHROUGH [[fallthrough]]
#elif defined(__has_cpp_attribute)
# if __has_cpp_attribute(clang::fallthrough)
#  define RAPIDJSON_DELIBERATE_FALLTHROUGH [[clang::fallthrough]]
# elif __has_cpp_attribute(fallthrough)
#  define RAPIDJSON_DELIBERATE_FALLTHROUGH __attribute__((fallthrough))
# else
#  define RAPIDJSON_DELIBERATE_FALLTHROUGH
# endif
#else
# define RAPIDJSON_DELIBERATE_FALLTHROUGH
#endif

//!@endcond

//! Assertion (in non-throwing contexts).
 /*! \ingroup RAPIDJSON_CONFIG
    Some functions provide a \c noexcept guarantee, if the compiler supports it.
    In these cases, the \ref RAPIDJSON_ASSERT macro cannot be overridden to
    throw an exception.  This macro adds a separate customization point for
    such cases.

    Defaults to C \c assert() (as \ref RAPIDJSON_ASSERT), if \c noexcept is
    supported, and to \ref RAPIDJSON_ASSERT otherwise.
 */

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_NOEXCEPT_ASSERT

#ifndef RAPIDJSON_NOEXCEPT_ASSERT
#ifdef RAPIDJSON_ASSERT_THROWS
#include <cassert>
#define RAPIDJSON_NOEXCEPT_ASSERT(x) assert(x)
#else
#define RAPIDJSON_NOEXCEPT_ASSERT(x) RAPIDJSON_ASSERT(x)
#endif // RAPIDJSON_ASSERT_THROWS
#endif // RAPIDJSON_NOEXCEPT_ASSERT

///////////////////////////////////////////////////////////////////////////////
// malloc/realloc/free

#ifndef RAPIDJSON_MALLOC
///! customization point for global \c malloc
#define RAPIDJSON_MALLOC(size) std::malloc(size)
#endif
#ifndef RAPIDJSON_REALLOC
///! customization point for global \c realloc
#define RAPIDJSON_REALLOC(ptr, new_size) std::realloc(ptr, new_size)
#endif
#ifndef RAPIDJSON_FREE
///! customization point for global \c free
#define RAPIDJSON_FREE(ptr) std::free(ptr)
#endif

///////////////////////////////////////////////////////////////////////////////
// new/delete

#ifndef RAPIDJSON_NEW
///! customization point for global \c new
#define RAPIDJSON_NEW(TypeName) new TypeName
#endif
#ifndef RAPIDJSON_DELETE
///! customization point for global \c delete
#define RAPIDJSON_DELETE(x) delete x
#endif

///////////////////////////////////////////////////////////////////////////////
// Type

/*! \namespace rapidjson
    \brief main RapidJSON namespace
    \see RAPIDJSON_NAMESPACE
*/
RAPIDJSON_NAMESPACE_BEGIN

//! Type of JSON value
enum Type {
    kNullType = 0,      //!< null
    kFalseType = 1,     //!< false
    kTrueType = 2,      //!< true
    kObjectType = 3,    //!< object
    kArrayType = 4,     //!< array
    kStringType = 5,    //!< string
    kNumberType = 6     //!< number
};

RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_RAPIDJSON_H_

// End file:rapidjson.h


#ifndef RAPIDJSON_STREAM_H_
#define RAPIDJSON_STREAM_H_


// Begin file: encodings.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ENCODINGS_H_
#define RAPIDJSON_ENCODINGS_H_


// Begin file: rapidjson.h
// already included
// End file:rapidjson.h


#if defined(_MSC_VER) && !defined(__clang__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4244) // conversion from 'type1' to 'type2', possible loss of data
RAPIDJSON_DIAG_OFF(4702)  // unreachable code
#elif defined(__GNUC__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++)
RAPIDJSON_DIAG_OFF(overflow)
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// Encoding

/*! \class rapidjson::Encoding
    \brief Concept for encoding of Unicode characters.

\code
concept Encoding {
    typename Ch;    //! Type of character. A "character" is actually a code unit in unicode's definition.

    enum { supportUnicode = 1 }; // or 0 if not supporting unicode

    //! \brief Encode a Unicode codepoint to an output stream.
    //! \param os Output stream.
    //! \param codepoint An unicode codepoint, ranging from 0x0 to 0x10FFFF inclusively.
    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint);

    //! \brief Decode a Unicode codepoint from an input stream.
    //! \param is Input stream.
    //! \param codepoint Output of the unicode codepoint.
    //! \return true if a valid codepoint can be decoded from the stream.
    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint);

    //! \brief Validate one Unicode codepoint from an encoded stream.
    //! \param is Input stream to obtain codepoint.
    //! \param os Output for copying one codepoint.
    //! \return true if it is valid.
    //! \note This function just validating and copying the codepoint without actually decode it.
    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os);

    // The following functions are deal with byte streams.

    //! Take a character from input byte stream, skip BOM if exist.
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is);

    //! Take a character from input byte stream.
    template <typename InputByteStream>
    static Ch Take(InputByteStream& is);

    //! Put BOM to output byte stream.
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os);

    //! Put a character to output byte stream.
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, Ch c);
};
\endcode
*/

///////////////////////////////////////////////////////////////////////////////
// UTF8

//! UTF-8 encoding.
/*! http://en.wikipedia.org/wiki/UTF-8
    http://tools.ietf.org/html/rfc3629
    \tparam CharType Code unit for storing 8-bit UTF-8 data. Default is char.
    \note implements Encoding concept
*/
template<typename CharType = char>
struct UTF8 {
    typedef CharType Ch;

    enum { supportUnicode = 1 };

    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        if (codepoint <= 0x7F) 
            os.Put(static_cast<Ch>(codepoint & 0xFF));
        else if (codepoint <= 0x7FF) {
            os.Put(static_cast<Ch>(0xC0 | ((codepoint >> 6) & 0xFF)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint & 0x3F))));
        }
        else if (codepoint <= 0xFFFF) {
            os.Put(static_cast<Ch>(0xE0 | ((codepoint >> 12) & 0xFF)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint >> 6) & 0x3F)));
            os.Put(static_cast<Ch>(0x80 | (codepoint & 0x3F)));
        }
        else {
            RAPIDJSON_ASSERT(codepoint <= 0x10FFFF);
            os.Put(static_cast<Ch>(0xF0 | ((codepoint >> 18) & 0xFF)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint >> 12) & 0x3F)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint >> 6) & 0x3F)));
            os.Put(static_cast<Ch>(0x80 | (codepoint & 0x3F)));
        }
    }

    template<typename OutputStream>
    static void EncodeUnsafe(OutputStream& os, unsigned codepoint) {
        if (codepoint <= 0x7F) 
            PutUnsafe(os, static_cast<Ch>(codepoint & 0xFF));
        else if (codepoint <= 0x7FF) {
            PutUnsafe(os, static_cast<Ch>(0xC0 | ((codepoint >> 6) & 0xFF)));
            PutUnsafe(os, static_cast<Ch>(0x80 | ((codepoint & 0x3F))));
        }
        else if (codepoint <= 0xFFFF) {
            PutUnsafe(os, static_cast<Ch>(0xE0 | ((codepoint >> 12) & 0xFF)));
            PutUnsafe(os, static_cast<Ch>(0x80 | ((codepoint >> 6) & 0x3F)));
            PutUnsafe(os, static_cast<Ch>(0x80 | (codepoint & 0x3F)));
        }
        else {
            RAPIDJSON_ASSERT(codepoint <= 0x10FFFF);
            PutUnsafe(os, static_cast<Ch>(0xF0 | ((codepoint >> 18) & 0xFF)));
            PutUnsafe(os, static_cast<Ch>(0x80 | ((codepoint >> 12) & 0x3F)));
            PutUnsafe(os, static_cast<Ch>(0x80 | ((codepoint >> 6) & 0x3F)));
            PutUnsafe(os, static_cast<Ch>(0x80 | (codepoint & 0x3F)));
        }
    }

    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
#define RAPIDJSON_COPY() c = is.Take(); *codepoint = (*codepoint << 6) | (static_cast<unsigned char>(c) & 0x3Fu)
#define RAPIDJSON_TRANS(mask) result &= ((GetRange(static_cast<unsigned char>(c)) & mask) != 0)
#define RAPIDJSON_TAIL() RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x70)
        typename InputStream::Ch c = is.Take();
        if (!(c & 0x80)) {
            *codepoint = static_cast<unsigned char>(c);
            return true;
        }

        unsigned char type = GetRange(static_cast<unsigned char>(c));
        if (type >= 32) {
            *codepoint = 0;
        } else {
            *codepoint = (0xFFu >> type) & static_cast<unsigned char>(c);
        }
        bool result = true;
        switch (type) {
        case 2: RAPIDJSON_TAIL(); return result;
        case 3: RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        case 4: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x50); RAPIDJSON_TAIL(); return result;
        case 5: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x10); RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        case 6: RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        case 10: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x20); RAPIDJSON_TAIL(); return result;
        case 11: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x60); RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        default: return false;
        }
#undef RAPIDJSON_COPY
#undef RAPIDJSON_TRANS
#undef RAPIDJSON_TAIL
    }

    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
#define RAPIDJSON_COPY() os.Put(c = is.Take())
#define RAPIDJSON_TRANS(mask) result &= ((GetRange(static_cast<unsigned char>(c)) & mask) != 0)
#define RAPIDJSON_TAIL() RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x70)
        Ch c;
        RAPIDJSON_COPY();
        if (!(c & 0x80))
            return true;

        bool result = true;
        switch (GetRange(static_cast<unsigned char>(c))) {
        case 2: RAPIDJSON_TAIL(); return result;
        case 3: RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        case 4: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x50); RAPIDJSON_TAIL(); return result;
        case 5: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x10); RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        case 6: RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        case 10: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x20); RAPIDJSON_TAIL(); return result;
        case 11: RAPIDJSON_COPY(); RAPIDJSON_TRANS(0x60); RAPIDJSON_TAIL(); RAPIDJSON_TAIL(); return result;
        default: return false;
        }
#undef RAPIDJSON_COPY
#undef RAPIDJSON_TRANS
#undef RAPIDJSON_TAIL
    }

    static unsigned char GetRange(unsigned char c) {
        // Referring to DFA of http://bjoern.hoehrmann.de/utf-8/decoder/dfa/
        // With new mapping 1 -> 0x10, 7 -> 0x20, 9 -> 0x40, such that AND operation can test multiple types.
        static const unsigned char type[] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
            0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
            0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
            0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
            8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
            10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,
        };
        return type[c];
    }

    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        typename InputByteStream::Ch c = Take(is);
        if (static_cast<unsigned char>(c) != 0xEFu) return c;
        c = is.Take();
        if (static_cast<unsigned char>(c) != 0xBBu) return c;
        c = is.Take();
        if (static_cast<unsigned char>(c) != 0xBFu) return c;
        c = is.Take();
        return c;
    }

    template <typename InputByteStream>
    static Ch Take(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        return static_cast<Ch>(is.Take());
    }

    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(0xEFu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xBBu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xBFu));
    }

    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, Ch c) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(c));
    }
};

///////////////////////////////////////////////////////////////////////////////
// UTF16

//! UTF-16 encoding.
/*! http://en.wikipedia.org/wiki/UTF-16
    http://tools.ietf.org/html/rfc2781
    \tparam CharType Type for storing 16-bit UTF-16 data. Default is wchar_t. C++11 may use char16_t instead.
    \note implements Encoding concept

    \note For in-memory access, no need to concern endianness. The code units and code points are represented by CPU's endianness.
    For streaming, use UTF16LE and UTF16BE, which handle endianness.
*/
template<typename CharType = wchar_t>
struct UTF16 {
    typedef CharType Ch;
    RAPIDJSON_STATIC_ASSERT(sizeof(Ch) >= 2);

    enum { supportUnicode = 1 };

    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputStream::Ch) >= 2);
        if (codepoint <= 0xFFFF) {
            RAPIDJSON_ASSERT(codepoint < 0xD800 || codepoint > 0xDFFF); // Code point itself cannot be surrogate pair 
            os.Put(static_cast<typename OutputStream::Ch>(codepoint));
        }
        else {
            RAPIDJSON_ASSERT(codepoint <= 0x10FFFF);
            unsigned v = codepoint - 0x10000;
            os.Put(static_cast<typename OutputStream::Ch>((v >> 10) | 0xD800));
            os.Put(static_cast<typename OutputStream::Ch>((v & 0x3FF) | 0xDC00));
        }
    }


    template<typename OutputStream>
    static void EncodeUnsafe(OutputStream& os, unsigned codepoint) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputStream::Ch) >= 2);
        if (codepoint <= 0xFFFF) {
            RAPIDJSON_ASSERT(codepoint < 0xD800 || codepoint > 0xDFFF); // Code point itself cannot be surrogate pair 
            PutUnsafe(os, static_cast<typename OutputStream::Ch>(codepoint));
        }
        else {
            RAPIDJSON_ASSERT(codepoint <= 0x10FFFF);
            unsigned v = codepoint - 0x10000;
            PutUnsafe(os, static_cast<typename OutputStream::Ch>((v >> 10) | 0xD800));
            PutUnsafe(os, static_cast<typename OutputStream::Ch>((v & 0x3FF) | 0xDC00));
        }
    }

    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputStream::Ch) >= 2);
        typename InputStream::Ch c = is.Take();
        if (c < 0xD800 || c > 0xDFFF) {
            *codepoint = static_cast<unsigned>(c);
            return true;
        }
        else if (c <= 0xDBFF) {
            *codepoint = (static_cast<unsigned>(c) & 0x3FF) << 10;
            c = is.Take();
            *codepoint |= (static_cast<unsigned>(c) & 0x3FF);
            *codepoint += 0x10000;
            return c >= 0xDC00 && c <= 0xDFFF;
        }
        return false;
    }

    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputStream::Ch) >= 2);
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputStream::Ch) >= 2);
        typename InputStream::Ch c;
        os.Put(static_cast<typename OutputStream::Ch>(c = is.Take()));
        if (c < 0xD800 || c > 0xDFFF)
            return true;
        else if (c <= 0xDBFF) {
            os.Put(c = is.Take());
            return c >= 0xDC00 && c <= 0xDFFF;
        }
        return false;
    }
};

//! UTF-16 little endian encoding.
template<typename CharType = wchar_t>
struct UTF16LE : UTF16<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        CharType c = Take(is);
        return static_cast<uint16_t>(c) == 0xFEFFu ? Take(is) : c;
    }

    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        unsigned c = static_cast<uint8_t>(is.Take());
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 8;
        return static_cast<CharType>(c);
    }

    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFEu));
    }

    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(static_cast<unsigned>(c) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>((static_cast<unsigned>(c) >> 8) & 0xFFu));
    }
};

//! UTF-16 big endian encoding.
template<typename CharType = wchar_t>
struct UTF16BE : UTF16<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        CharType c = Take(is);
        return static_cast<uint16_t>(c) == 0xFEFFu ? Take(is) : c;
    }

    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        unsigned c = static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 8;
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take()));
        return static_cast<CharType>(c);
    }

    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFEu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFFu));
    }

    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>((static_cast<unsigned>(c) >> 8) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>(static_cast<unsigned>(c) & 0xFFu));
    }
};

///////////////////////////////////////////////////////////////////////////////
// UTF32

//! UTF-32 encoding. 
/*! http://en.wikipedia.org/wiki/UTF-32
    \tparam CharType Type for storing 32-bit UTF-32 data. Default is unsigned. C++11 may use char32_t instead.
    \note implements Encoding concept

    \note For in-memory access, no need to concern endianness. The code units and code points are represented by CPU's endianness.
    For streaming, use UTF32LE and UTF32BE, which handle endianness.
*/
template<typename CharType = unsigned>
struct UTF32 {
    typedef CharType Ch;
    RAPIDJSON_STATIC_ASSERT(sizeof(Ch) >= 4);

    enum { supportUnicode = 1 };

    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputStream::Ch) >= 4);
        RAPIDJSON_ASSERT(codepoint <= 0x10FFFF);
        os.Put(codepoint);
    }

    template<typename OutputStream>
    static void EncodeUnsafe(OutputStream& os, unsigned codepoint) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputStream::Ch) >= 4);
        RAPIDJSON_ASSERT(codepoint <= 0x10FFFF);
        PutUnsafe(os, codepoint);
    }

    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputStream::Ch) >= 4);
        Ch c = is.Take();
        *codepoint = c;
        return c <= 0x10FFFF;
    }

    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputStream::Ch) >= 4);
        Ch c;
        os.Put(c = is.Take());
        return c <= 0x10FFFF;
    }
};

//! UTF-32 little endian enocoding.
template<typename CharType = unsigned>
struct UTF32LE : UTF32<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        CharType c = Take(is);
        return static_cast<uint32_t>(c) == 0x0000FEFFu ? Take(is) : c;
    }

    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        unsigned c = static_cast<uint8_t>(is.Take());
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 8;
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 16;
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 24;
        return static_cast<CharType>(c);
    }

    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFEu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0x00u));
        os.Put(static_cast<typename OutputByteStream::Ch>(0x00u));
    }

    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(c & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>((c >> 8) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>((c >> 16) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>((c >> 24) & 0xFFu));
    }
};

//! UTF-32 big endian encoding.
template<typename CharType = unsigned>
struct UTF32BE : UTF32<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        CharType c = Take(is);
        return static_cast<uint32_t>(c) == 0x0000FEFFu ? Take(is) : c; 
    }

    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        unsigned c = static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 24;
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 16;
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take())) << 8;
        c |= static_cast<unsigned>(static_cast<uint8_t>(is.Take()));
        return static_cast<CharType>(c);
    }

    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(0x00u));
        os.Put(static_cast<typename OutputByteStream::Ch>(0x00u));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFEu));
        os.Put(static_cast<typename OutputByteStream::Ch>(0xFFu));
    }

    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>((c >> 24) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>((c >> 16) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>((c >> 8) & 0xFFu));
        os.Put(static_cast<typename OutputByteStream::Ch>(c & 0xFFu));
    }
};

///////////////////////////////////////////////////////////////////////////////
// ASCII

//! ASCII encoding.
/*! http://en.wikipedia.org/wiki/ASCII
    \tparam CharType Code unit for storing 7-bit ASCII data. Default is char.
    \note implements Encoding concept
*/
template<typename CharType = char>
struct ASCII {
    typedef CharType Ch;

    enum { supportUnicode = 0 };

    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        RAPIDJSON_ASSERT(codepoint <= 0x7F);
        os.Put(static_cast<Ch>(codepoint & 0xFF));
    }

    template<typename OutputStream>
    static void EncodeUnsafe(OutputStream& os, unsigned codepoint) {
        RAPIDJSON_ASSERT(codepoint <= 0x7F);
        PutUnsafe(os, static_cast<Ch>(codepoint & 0xFF));
    }

    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        uint8_t c = static_cast<uint8_t>(is.Take());
        *codepoint = c;
        return c <= 0X7F;
    }

    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        uint8_t c = static_cast<uint8_t>(is.Take());
        os.Put(static_cast<typename OutputStream::Ch>(c));
        return c <= 0x7F;
    }

    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        uint8_t c = static_cast<uint8_t>(Take(is));
        return static_cast<Ch>(c);
    }

    template <typename InputByteStream>
    static Ch Take(InputByteStream& is) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
        return static_cast<Ch>(is.Take());
    }

    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        (void)os;
    }

    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, Ch c) {
        RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
        os.Put(static_cast<typename OutputByteStream::Ch>(c));
    }
};

///////////////////////////////////////////////////////////////////////////////
// AutoUTF

//! Runtime-specified UTF encoding type of a stream.
enum UTFType {
    kUTF8 = 0,      //!< UTF-8.
    kUTF16LE = 1,   //!< UTF-16 little endian.
    kUTF16BE = 2,   //!< UTF-16 big endian.
    kUTF32LE = 3,   //!< UTF-32 little endian.
    kUTF32BE = 4    //!< UTF-32 big endian.
};

//! Dynamically select encoding according to stream's runtime-specified UTF encoding type.
/*! \note This class can be used with AutoUTFInputtStream and AutoUTFOutputStream, which provides GetType().
*/
template<typename CharType>
struct AutoUTF {
    typedef CharType Ch;

    enum { supportUnicode = 1 };

#define RAPIDJSON_ENCODINGS_FUNC(x) UTF8<Ch>::x, UTF16LE<Ch>::x, UTF16BE<Ch>::x, UTF32LE<Ch>::x, UTF32BE<Ch>::x

    template<typename OutputStream>
    static RAPIDJSON_FORCEINLINE void Encode(OutputStream& os, unsigned codepoint) {
        typedef void (*EncodeFunc)(OutputStream&, unsigned);
        static const EncodeFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(Encode) };
        (*f[os.GetType()])(os, codepoint);
    }

    template<typename OutputStream>
    static RAPIDJSON_FORCEINLINE void EncodeUnsafe(OutputStream& os, unsigned codepoint) {
        typedef void (*EncodeFunc)(OutputStream&, unsigned);
        static const EncodeFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(EncodeUnsafe) };
        (*f[os.GetType()])(os, codepoint);
    }

    template <typename InputStream>
    static RAPIDJSON_FORCEINLINE bool Decode(InputStream& is, unsigned* codepoint) {
        typedef bool (*DecodeFunc)(InputStream&, unsigned*);
        static const DecodeFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(Decode) };
        return (*f[is.GetType()])(is, codepoint);
    }

    template <typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool Validate(InputStream& is, OutputStream& os) {
        typedef bool (*ValidateFunc)(InputStream&, OutputStream&);
        static const ValidateFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(Validate) };
        return (*f[is.GetType()])(is, os);
    }

#undef RAPIDJSON_ENCODINGS_FUNC
};

///////////////////////////////////////////////////////////////////////////////
// Transcoder

//! Encoding conversion.
template<typename SourceEncoding, typename TargetEncoding>
struct Transcoder {
    //! Take one Unicode codepoint from source encoding, convert it to target encoding and put it to the output stream.
    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool Transcode(InputStream& is, OutputStream& os) {
        unsigned codepoint;
        if (!SourceEncoding::Decode(is, &codepoint))
            return false;
        TargetEncoding::Encode(os, codepoint);
        return true;
    }

    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool TranscodeUnsafe(InputStream& is, OutputStream& os) {
        unsigned codepoint;
        if (!SourceEncoding::Decode(is, &codepoint))
            return false;
        TargetEncoding::EncodeUnsafe(os, codepoint);
        return true;
    }

    //! Validate one Unicode codepoint from an encoded stream.
    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool Validate(InputStream& is, OutputStream& os) {
        return Transcode(is, os);   // Since source/target encoding is different, must transcode.
    }
};

// Forward declaration.
template<typename Stream>
inline void PutUnsafe(Stream& stream, typename Stream::Ch c);

//! Specialization of Transcoder with same source and target encoding.
template<typename Encoding>
struct Transcoder<Encoding, Encoding> {
    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool Transcode(InputStream& is, OutputStream& os) {
        os.Put(is.Take());  // Just copy one code unit. This semantic is different from primary template class.
        return true;
    }
    
    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool TranscodeUnsafe(InputStream& is, OutputStream& os) {
        PutUnsafe(os, is.Take());  // Just copy one code unit. This semantic is different from primary template class.
        return true;
    }
    
    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE bool Validate(InputStream& is, OutputStream& os) {
        return Encoding::Validate(is, os);  // source/target encoding are the same
    }
};

RAPIDJSON_NAMESPACE_END

#if defined(__GNUC__) || (defined(_MSC_VER) && !defined(__clang__))
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_ENCODINGS_H_

// End file:encodings.h


RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//  Stream

/*! \class rapidjson::Stream
    \brief Concept for reading and writing characters.

    For read-only stream, no need to implement PutBegin(), Put(), Flush() and PutEnd().

    For write-only stream, only need to implement Put() and Flush().

\code
concept Stream {
    typename Ch;    //!< Character type of the stream.

    //! Read the current character from stream without moving the read cursor.
    Ch Peek() const;

    //! Read the current character from stream and moving the read cursor to next character.
    Ch Take();

    //! Get the current read cursor.
    //! \return Number of characters read from start.
    size_t Tell();

    //! Begin writing operation at the current read pointer.
    //! \return The begin writer pointer.
    Ch* PutBegin();

    //! Write a character.
    void Put(Ch c);

    //! Flush the buffer.
    void Flush();

    //! End the writing operation.
    //! \param begin The begin write pointer returned by PutBegin().
    //! \return Number of characters written.
    size_t PutEnd(Ch* begin);
}
\endcode
*/

//! Provides additional information for stream.
/*!
    By using traits pattern, this type provides a default configuration for stream.
    For custom stream, this type can be specialized for other configuration.
    See TEST(Reader, CustomStringStream) in readertest.cpp for example.
*/
template<typename Stream>
struct StreamTraits {
    //! Whether to make local copy of stream for optimization during parsing.
    /*!
        By default, for safety, streams do not use local copy optimization.
        Stream that can be copied fast should specialize this, like StreamTraits<StringStream>.
    */
    enum { copyOptimization = 0 };
};

//! Reserve n characters for writing to a stream.
template<typename Stream>
inline void PutReserve(Stream& stream, size_t count) {
    (void)stream;
    (void)count;
}

//! Write character to a stream, presuming buffer is reserved.
template<typename Stream>
inline void PutUnsafe(Stream& stream, typename Stream::Ch c) {
    stream.Put(c);
}

//! Put N copies of a character to a stream.
template<typename Stream, typename Ch>
inline void PutN(Stream& stream, Ch c, size_t n) {
    PutReserve(stream, n);
    for (size_t i = 0; i < n; i++)
        PutUnsafe(stream, c);
}

///////////////////////////////////////////////////////////////////////////////
// GenericStreamWrapper

//! A Stream Wrapper
/*! \tThis string stream is a wrapper for any stream by just forwarding any
    \treceived message to the origin stream.
    \note implements Stream concept
*/

#if defined(_MSC_VER) && _MSC_VER <= 1800
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4702)  // unreachable code
RAPIDJSON_DIAG_OFF(4512)  // assignment operator could not be generated
#endif

template <typename InputStream, typename Encoding = UTF8<> >
class GenericStreamWrapper {
public:
    typedef typename Encoding::Ch Ch;
    GenericStreamWrapper(InputStream& is): is_(is) {}

    Ch Peek() const { return is_.Peek(); }
    Ch Take() { return is_.Take(); }
    size_t Tell() { return is_.Tell(); }
    Ch* PutBegin() { return is_.PutBegin(); }
    void Put(Ch ch) { is_.Put(ch); }
    void Flush() { is_.Flush(); }
    size_t PutEnd(Ch* ch) { return is_.PutEnd(ch); }

    // wrapper for MemoryStream
    const Ch* Peek4() const { return is_.Peek4(); }

    // wrapper for AutoUTFInputStream
    UTFType GetType() const { return is_.GetType(); }
    bool HasBOM() const { return is_.HasBOM(); }

protected:
    InputStream& is_;
};

#if defined(_MSC_VER) && _MSC_VER <= 1800
RAPIDJSON_DIAG_POP
#endif

///////////////////////////////////////////////////////////////////////////////
// StringStream

//! Read-only string stream.
/*! \note implements Stream concept
*/
template <typename Encoding>
struct GenericStringStream {
    typedef typename Encoding::Ch Ch;

    GenericStringStream(const Ch *src) : src_(src), head_(src) {}

    Ch Peek() const { return *src_; }
    Ch Take() { return *src_++; }
    size_t Tell() const { return static_cast<size_t>(src_ - head_); }

    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    void Put(Ch) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

    const Ch* src_;     //!< Current read position.
    const Ch* head_;    //!< Original head of the string.
};

template <typename Encoding>
struct StreamTraits<GenericStringStream<Encoding> > {
    enum { copyOptimization = 1 };
};

//! String stream with UTF8 encoding.
typedef GenericStringStream<UTF8<> > StringStream;

///////////////////////////////////////////////////////////////////////////////
// InsituStringStream

//! A read-write string stream.
/*! This string stream is particularly designed for in-situ parsing.
    \note implements Stream concept
*/
template <typename Encoding>
struct GenericInsituStringStream {
    typedef typename Encoding::Ch Ch;

    GenericInsituStringStream(Ch *src) : src_(src), dst_(0), head_(src) {}

    // Read
    Ch Peek() { return *src_; }
    Ch Take() { return *src_++; }
    size_t Tell() { return static_cast<size_t>(src_ - head_); }

    // Write
    void Put(Ch c) { RAPIDJSON_ASSERT(dst_ != 0); *dst_++ = c; }

    Ch* PutBegin() { return dst_ = src_; }
    size_t PutEnd(Ch* begin) { return static_cast<size_t>(dst_ - begin); }
    void Flush() {}

    Ch* Push(size_t count) { Ch* begin = dst_; dst_ += count; return begin; }
    void Pop(size_t count) { dst_ -= count; }

    Ch* src_;
    Ch* dst_;
    Ch* head_;
};

template <typename Encoding>
struct StreamTraits<GenericInsituStringStream<Encoding> > {
    enum { copyOptimization = 1 };
};

//! Insitu string stream with UTF8 encoding.
typedef GenericInsituStringStream<UTF8<> > InsituStringStream;

RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_STREAM_H_

// End file:stream.h

#include <iosfwd>
#include <ios>

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4351) // new behavior: elements of array 'array' will be default initialized
#endif

RAPIDJSON_NAMESPACE_BEGIN

//! Wrapper of \c std::basic_istream into RapidJSON's Stream concept.
/*!
    The classes can be wrapped including but not limited to:

    - \c std::istringstream
    - \c std::stringstream
    - \c std::wistringstream
    - \c std::wstringstream
    - \c std::ifstream
    - \c std::fstream
    - \c std::wifstream
    - \c std::wfstream

    \tparam StreamType Class derived from \c std::basic_istream.
*/
   
template <typename StreamType>
class BasicIStreamWrapper {
public:
    typedef typename StreamType::char_type Ch;

    //! Constructor.
    /*!
        \param stream stream opened for read.
    */
    BasicIStreamWrapper(StreamType &stream) : stream_(stream), buffer_(peekBuffer_), bufferSize_(4), bufferLast_(0), current_(buffer_), readCount_(0), count_(0), eof_(false) { 
        Read();
    }

    //! Constructor.
    /*!
        \param stream stream opened for read.
        \param buffer user-supplied buffer.
        \param bufferSize size of buffer in bytes. Must >=4 bytes.
    */
    BasicIStreamWrapper(StreamType &stream, char* buffer, size_t bufferSize) : stream_(stream), buffer_(buffer), bufferSize_(bufferSize), bufferLast_(0), current_(buffer_), readCount_(0), count_(0), eof_(false) { 
        RAPIDJSON_ASSERT(bufferSize >= 4);
        Read();
    }

    Ch Peek() const { return *current_; }
    Ch Take() { Ch c = *current_; Read(); return c; }
    size_t Tell() const { return count_ + static_cast<size_t>(current_ - buffer_); }

    // Not implemented
    void Put(Ch) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); } 
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

    // For encoding detection only.
    const Ch* Peek4() const {
        return (current_ + 4 - !eof_ <= bufferLast_) ? current_ : 0;
    }

private:
    BasicIStreamWrapper();
    BasicIStreamWrapper(const BasicIStreamWrapper&);
    BasicIStreamWrapper& operator=(const BasicIStreamWrapper&);

    void Read() {
        if (current_ < bufferLast_)
            ++current_;
        else if (!eof_) {
            count_ += readCount_;
            readCount_ = bufferSize_;
            bufferLast_ = buffer_ + readCount_ - 1;
            current_ = buffer_;

            if (!stream_.read(buffer_, static_cast<std::streamsize>(bufferSize_))) {
                readCount_ = static_cast<size_t>(stream_.gcount());
                *(bufferLast_ = buffer_ + readCount_) = '\0';
                eof_ = true;
            }
        }
    }

    StreamType &stream_;
    Ch peekBuffer_[4], *buffer_;
    size_t bufferSize_;
    Ch *bufferLast_;
    Ch *current_;
    size_t readCount_;
    size_t count_;  //!< Number of characters read
    bool eof_;
};

typedef BasicIStreamWrapper<std::istream> IStreamWrapper;
typedef BasicIStreamWrapper<std::wistream> WIStreamWrapper;

#if defined(__clang__) || defined(_MSC_VER)
RAPIDJSON_DIAG_POP
#endif

RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_ISTREAMWRAPPER_H_

// End file:istreamwrapper.h


// Begin file: schema.h
// Tencent is pleased to support the open source community by making RapidJSON available->
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip-> All rights reserved->
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License-> You may obtain a copy of the License at
//
// http://opensource->org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied-> See the License for the
// specific language governing permissions and limitations under the License->

#ifndef RAPIDJSON_SCHEMA_H_
#define RAPIDJSON_SCHEMA_H_


// Begin file: document.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_DOCUMENT_H_
#define RAPIDJSON_DOCUMENT_H_

/*! \file document.h */


// Begin file: reader.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_READER_H_
#define RAPIDJSON_READER_H_

/*! \file reader.h */


// Begin file: allocators.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ALLOCATORS_H_
#define RAPIDJSON_ALLOCATORS_H_


// Begin file: rapidjson.h
// already included
// End file:rapidjson.h


// Begin file: internal/meta.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_INTERNAL_META_H_
#define RAPIDJSON_INTERNAL_META_H_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


#ifdef __GNUC__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++)
#endif

#if defined(_MSC_VER) && !defined(__clang__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(6334)
#endif

#if RAPIDJSON_HAS_CXX11_TYPETRAITS
#include <type_traits>
#endif

//@cond RAPIDJSON_INTERNAL
RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

// Helper to wrap/convert arbitrary types to void, useful for arbitrary type matching
template <typename T> struct Void { typedef void Type; };

///////////////////////////////////////////////////////////////////////////////
// BoolType, TrueType, FalseType
//
template <bool Cond> struct BoolType {
    static const bool Value = Cond;
    typedef BoolType Type;
};
typedef BoolType<true> TrueType;
typedef BoolType<false> FalseType;


///////////////////////////////////////////////////////////////////////////////
// SelectIf, BoolExpr, NotExpr, AndExpr, OrExpr
//

template <bool C> struct SelectIfImpl { template <typename T1, typename T2> struct Apply { typedef T1 Type; }; };
template <> struct SelectIfImpl<false> { template <typename T1, typename T2> struct Apply { typedef T2 Type; }; };
template <bool C, typename T1, typename T2> struct SelectIfCond : SelectIfImpl<C>::template Apply<T1,T2> {};
template <typename C, typename T1, typename T2> struct SelectIf : SelectIfCond<C::Value, T1, T2> {};

template <bool Cond1, bool Cond2> struct AndExprCond : FalseType {};
template <> struct AndExprCond<true, true> : TrueType {};
template <bool Cond1, bool Cond2> struct OrExprCond : TrueType {};
template <> struct OrExprCond<false, false> : FalseType {};

template <typename C> struct BoolExpr : SelectIf<C,TrueType,FalseType>::Type {};
template <typename C> struct NotExpr  : SelectIf<C,FalseType,TrueType>::Type {};
template <typename C1, typename C2> struct AndExpr : AndExprCond<C1::Value, C2::Value>::Type {};
template <typename C1, typename C2> struct OrExpr  : OrExprCond<C1::Value, C2::Value>::Type {};


///////////////////////////////////////////////////////////////////////////////
// AddConst, MaybeAddConst, RemoveConst
template <typename T> struct AddConst { typedef const T Type; };
template <bool Constify, typename T> struct MaybeAddConst : SelectIfCond<Constify, const T, T> {};
template <typename T> struct RemoveConst { typedef T Type; };
template <typename T> struct RemoveConst<const T> { typedef T Type; };


///////////////////////////////////////////////////////////////////////////////
// IsSame, IsConst, IsMoreConst, IsPointer
//
template <typename T, typename U> struct IsSame : FalseType {};
template <typename T> struct IsSame<T, T> : TrueType {};

template <typename T> struct IsConst : FalseType {};
template <typename T> struct IsConst<const T> : TrueType {};

template <typename CT, typename T>
struct IsMoreConst
    : AndExpr<IsSame<typename RemoveConst<CT>::Type, typename RemoveConst<T>::Type>,
              BoolType<IsConst<CT>::Value >= IsConst<T>::Value> >::Type {};

template <typename T> struct IsPointer : FalseType {};
template <typename T> struct IsPointer<T*> : TrueType {};

///////////////////////////////////////////////////////////////////////////////
// IsBaseOf
//
#if RAPIDJSON_HAS_CXX11_TYPETRAITS

template <typename B, typename D> struct IsBaseOf
    : BoolType< ::std::is_base_of<B,D>::value> {};

#else // simplified version adopted from Boost

template<typename B, typename D> struct IsBaseOfImpl {
    RAPIDJSON_STATIC_ASSERT(sizeof(B) != 0);
    RAPIDJSON_STATIC_ASSERT(sizeof(D) != 0);

    typedef char (&Yes)[1];
    typedef char (&No) [2];

    template <typename T>
    static Yes Check(const D*, T);
    static No  Check(const B*, int);

    struct Host {
        operator const B*() const;
        operator const D*();
    };

    enum { Value = (sizeof(Check(Host(), 0)) == sizeof(Yes)) };
};

template <typename B, typename D> struct IsBaseOf
    : OrExpr<IsSame<B, D>, BoolExpr<IsBaseOfImpl<B, D> > >::Type {};

#endif // RAPIDJSON_HAS_CXX11_TYPETRAITS


//////////////////////////////////////////////////////////////////////////
// EnableIf / DisableIf
//
template <bool Condition, typename T = void> struct EnableIfCond  { typedef T Type; };
template <typename T> struct EnableIfCond<false, T> { /* empty */ };

template <bool Condition, typename T = void> struct DisableIfCond { typedef T Type; };
template <typename T> struct DisableIfCond<true, T> { /* empty */ };

template <typename Condition, typename T = void>
struct EnableIf : EnableIfCond<Condition::Value, T> {};

template <typename Condition, typename T = void>
struct DisableIf : DisableIfCond<Condition::Value, T> {};

// SFINAE helpers
struct SfinaeTag {};
template <typename T> struct RemoveSfinaeTag;
template <typename T> struct RemoveSfinaeTag<SfinaeTag&(*)(T)> { typedef T Type; };

#define RAPIDJSON_REMOVEFPTR_(type) \
    typename ::RAPIDJSON_NAMESPACE::internal::RemoveSfinaeTag \
        < ::RAPIDJSON_NAMESPACE::internal::SfinaeTag&(*) type>::Type

#define RAPIDJSON_ENABLEIF(cond) \
    typename ::RAPIDJSON_NAMESPACE::internal::EnableIf \
        <RAPIDJSON_REMOVEFPTR_(cond)>::Type * = NULL

#define RAPIDJSON_DISABLEIF(cond) \
    typename ::RAPIDJSON_NAMESPACE::internal::DisableIf \
        <RAPIDJSON_REMOVEFPTR_(cond)>::Type * = NULL

#define RAPIDJSON_ENABLEIF_RETURN(cond,returntype) \
    typename ::RAPIDJSON_NAMESPACE::internal::EnableIf \
        <RAPIDJSON_REMOVEFPTR_(cond), \
         RAPIDJSON_REMOVEFPTR_(returntype)>::Type

#define RAPIDJSON_DISABLEIF_RETURN(cond,returntype) \
    typename ::RAPIDJSON_NAMESPACE::internal::DisableIf \
        <RAPIDJSON_REMOVEFPTR_(cond), \
         RAPIDJSON_REMOVEFPTR_(returntype)>::Type

} // namespace internal
RAPIDJSON_NAMESPACE_END
//@endcond

#if defined(_MSC_VER) && !defined(__clang__)
RAPIDJSON_DIAG_POP
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_INTERNAL_META_H_

// End file:internal/meta.h


#include <memory>
#include <limits>

#if RAPIDJSON_HAS_CXX11
#include <type_traits>
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// Allocator

/*! \class rapidjson::Allocator
    \brief Concept for allocating, resizing and freeing memory block.
    
    Note that Malloc() and Realloc() are non-static but Free() is static.
    
    So if an allocator need to support Free(), it needs to put its pointer in 
    the header of memory block.

\code
concept Allocator {
    static const bool kNeedFree;    //!< Whether this allocator needs to call Free().

    // Allocate a memory block.
    // \param size of the memory block in bytes.
    // \returns pointer to the memory block.
    void* Malloc(size_t size);

    // Resize a memory block.
    // \param originalPtr The pointer to current memory block. Null pointer is permitted.
    // \param originalSize The current size in bytes. (Design issue: since some allocator may not book-keep this, explicitly pass to it can save memory.)
    // \param newSize the new size in bytes.
    void* Realloc(void* originalPtr, size_t originalSize, size_t newSize);

    // Free a memory block.
    // \param pointer to the memory block. Null pointer is permitted.
    static void Free(void *ptr);
};
\endcode
*/


/*! \def RAPIDJSON_ALLOCATOR_DEFAULT_CHUNK_CAPACITY
    \ingroup RAPIDJSON_CONFIG
    \brief User-defined kDefaultChunkCapacity definition.

    User can define this as any \c size that is a power of 2.
*/

#ifndef RAPIDJSON_ALLOCATOR_DEFAULT_CHUNK_CAPACITY
#define RAPIDJSON_ALLOCATOR_DEFAULT_CHUNK_CAPACITY (64 * 1024)
#endif


///////////////////////////////////////////////////////////////////////////////
// CrtAllocator

//! C-runtime library allocator.
/*! This class is just wrapper for standard C library memory routines.
    \note implements Allocator concept
*/
class CrtAllocator {
public:
    static const bool kNeedFree = true;
    void* Malloc(size_t size) { 
        if (size) //  behavior of malloc(0) is implementation defined.
            return RAPIDJSON_MALLOC(size);
        else
            return NULL; // standardize to returning NULL.
    }
    void* Realloc(void* originalPtr, size_t originalSize, size_t newSize) {
        (void)originalSize;
        if (newSize == 0) {
            RAPIDJSON_FREE(originalPtr);
            return NULL;
        }
        return RAPIDJSON_REALLOC(originalPtr, newSize);
    }
    static void Free(void *ptr) RAPIDJSON_NOEXCEPT { RAPIDJSON_FREE(ptr); }

    bool operator==(const CrtAllocator&) const RAPIDJSON_NOEXCEPT {
        return true;
    }
    bool operator!=(const CrtAllocator&) const RAPIDJSON_NOEXCEPT {
        return false;
    }
};

///////////////////////////////////////////////////////////////////////////////
// MemoryPoolAllocator

//! Default memory allocator used by the parser and DOM.
/*! This allocator allocate memory blocks from pre-allocated memory chunks. 

    It does not free memory blocks. And Realloc() only allocate new memory.

    The memory chunks are allocated by BaseAllocator, which is CrtAllocator by default.

    User may also supply a buffer as the first chunk.

    If the user-buffer is full then additional chunks are allocated by BaseAllocator.

    The user-buffer is not deallocated by this allocator.

    \tparam BaseAllocator the allocator type for allocating memory chunks. Default is CrtAllocator.
    \note implements Allocator concept
*/
template <typename BaseAllocator = CrtAllocator>
class MemoryPoolAllocator {
    //! Chunk header for perpending to each chunk.
    /*! Chunks are stored as a singly linked list.
    */
    struct ChunkHeader {
        size_t capacity;    //!< Capacity of the chunk in bytes (excluding the header itself).
        size_t size;        //!< Current size of allocated memory in bytes.
        ChunkHeader *next;  //!< Next chunk in the linked list.
    };

    struct SharedData {
        ChunkHeader *chunkHead;  //!< Head of the chunk linked-list. Only the head chunk serves allocation.
        BaseAllocator* ownBaseAllocator; //!< base allocator created by this object.
        size_t refcount;
        bool ownBuffer;
    };

    static const size_t SIZEOF_SHARED_DATA = RAPIDJSON_ALIGN(sizeof(SharedData));
    static const size_t SIZEOF_CHUNK_HEADER = RAPIDJSON_ALIGN(sizeof(ChunkHeader));

    static inline ChunkHeader *GetChunkHead(SharedData *shared)
    {
        return reinterpret_cast<ChunkHeader*>(reinterpret_cast<uint8_t*>(shared) + SIZEOF_SHARED_DATA);
    }
    static inline uint8_t *GetChunkBuffer(SharedData *shared)
    {
        return reinterpret_cast<uint8_t*>(shared->chunkHead) + SIZEOF_CHUNK_HEADER;
    }

    static const size_t kDefaultChunkCapacity = RAPIDJSON_ALLOCATOR_DEFAULT_CHUNK_CAPACITY; //!< Default chunk capacity.

public:
    static const bool kNeedFree = false;    //!< Tell users that no need to call Free() with this allocator. (concept Allocator)
    static const bool kRefCounted = true;   //!< Tell users that this allocator is reference counted on copy

    //! Constructor with chunkSize.
    /*! \param chunkSize The size of memory chunk. The default is kDefaultChunkSize.
        \param baseAllocator The allocator for allocating memory chunks.
    */
    explicit
    MemoryPoolAllocator(size_t chunkSize = kDefaultChunkCapacity, BaseAllocator* baseAllocator = 0) : 
        chunk_capacity_(chunkSize),
        baseAllocator_(baseAllocator ? baseAllocator : RAPIDJSON_NEW(BaseAllocator)()),
        shared_(static_cast<SharedData*>(baseAllocator_ ? baseAllocator_->Malloc(SIZEOF_SHARED_DATA + SIZEOF_CHUNK_HEADER) : 0))
    {
        RAPIDJSON_ASSERT(baseAllocator_ != 0);
        RAPIDJSON_ASSERT(shared_ != 0);
        if (baseAllocator) {
            shared_->ownBaseAllocator = 0;
        }
        else {
            shared_->ownBaseAllocator = baseAllocator_;
        }
        shared_->chunkHead = GetChunkHead(shared_);
        shared_->chunkHead->capacity = 0;
        shared_->chunkHead->size = 0;
        shared_->chunkHead->next = 0;
        shared_->ownBuffer = true;
        shared_->refcount = 1;
    }

    //! Constructor with user-supplied buffer.
    /*! The user buffer will be used firstly. When it is full, memory pool allocates new chunk with chunk size.

        The user buffer will not be deallocated when this allocator is destructed.

        \param buffer User supplied buffer.
        \param size Size of the buffer in bytes. It must at least larger than sizeof(ChunkHeader).
        \param chunkSize The size of memory chunk. The default is kDefaultChunkSize.
        \param baseAllocator The allocator for allocating memory chunks.
    */
    MemoryPoolAllocator(void *buffer, size_t size, size_t chunkSize = kDefaultChunkCapacity, BaseAllocator* baseAllocator = 0) :
        chunk_capacity_(chunkSize),
        baseAllocator_(baseAllocator),
        shared_(static_cast<SharedData*>(AlignBuffer(buffer, size)))
    {
        RAPIDJSON_ASSERT(size >= SIZEOF_SHARED_DATA + SIZEOF_CHUNK_HEADER);
        shared_->chunkHead = GetChunkHead(shared_);
        shared_->chunkHead->capacity = size - SIZEOF_SHARED_DATA - SIZEOF_CHUNK_HEADER;
        shared_->chunkHead->size = 0;
        shared_->chunkHead->next = 0;
        shared_->ownBaseAllocator = 0;
        shared_->ownBuffer = false;
        shared_->refcount = 1;
    }

    MemoryPoolAllocator(const MemoryPoolAllocator& rhs) RAPIDJSON_NOEXCEPT :
        chunk_capacity_(rhs.chunk_capacity_),
        baseAllocator_(rhs.baseAllocator_),
        shared_(rhs.shared_)
    {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        ++shared_->refcount;
    }
    MemoryPoolAllocator& operator=(const MemoryPoolAllocator& rhs) RAPIDJSON_NOEXCEPT
    {
        RAPIDJSON_NOEXCEPT_ASSERT(rhs.shared_->refcount > 0);
        ++rhs.shared_->refcount;
        this->~MemoryPoolAllocator();
        baseAllocator_ = rhs.baseAllocator_;
        chunk_capacity_ = rhs.chunk_capacity_;
        shared_ = rhs.shared_;
        return *this;
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    MemoryPoolAllocator(MemoryPoolAllocator&& rhs) RAPIDJSON_NOEXCEPT :
        chunk_capacity_(rhs.chunk_capacity_),
        baseAllocator_(rhs.baseAllocator_),
        shared_(rhs.shared_)
    {
        RAPIDJSON_NOEXCEPT_ASSERT(rhs.shared_->refcount > 0);
        rhs.shared_ = 0;
    }
    MemoryPoolAllocator& operator=(MemoryPoolAllocator&& rhs) RAPIDJSON_NOEXCEPT
    {
        RAPIDJSON_NOEXCEPT_ASSERT(rhs.shared_->refcount > 0);
        this->~MemoryPoolAllocator();
        baseAllocator_ = rhs.baseAllocator_;
        chunk_capacity_ = rhs.chunk_capacity_;
        shared_ = rhs.shared_;
        rhs.shared_ = 0;
        return *this;
    }
#endif

    //! Destructor.
    /*! This deallocates all memory chunks, excluding the user-supplied buffer.
    */
    ~MemoryPoolAllocator() RAPIDJSON_NOEXCEPT {
        if (!shared_) {
            // do nothing if moved
            return;
        }
        if (shared_->refcount > 1) {
            --shared_->refcount;
            return;
        }
        Clear();
        BaseAllocator *a = shared_->ownBaseAllocator;
        if (shared_->ownBuffer) {
            baseAllocator_->Free(shared_);
        }
        RAPIDJSON_DELETE(a);
    }

    //! Deallocates all memory chunks, excluding the first/user one.
    void Clear() RAPIDJSON_NOEXCEPT {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        for (;;) {
            ChunkHeader* c = shared_->chunkHead;
            if (!c->next) {
                break;
            }
            shared_->chunkHead = c->next;
            baseAllocator_->Free(c);
        }
        shared_->chunkHead->size = 0;
    }

    //! Computes the total capacity of allocated memory chunks.
    /*! \return total capacity in bytes.
    */
    size_t Capacity() const RAPIDJSON_NOEXCEPT {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        size_t capacity = 0;
        for (ChunkHeader* c = shared_->chunkHead; c != 0; c = c->next)
            capacity += c->capacity;
        return capacity;
    }

    //! Computes the memory blocks allocated.
    /*! \return total used bytes.
    */
    size_t Size() const RAPIDJSON_NOEXCEPT {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        size_t size = 0;
        for (ChunkHeader* c = shared_->chunkHead; c != 0; c = c->next)
            size += c->size;
        return size;
    }

    //! Whether the allocator is shared.
    /*! \return true or false.
    */
    bool Shared() const RAPIDJSON_NOEXCEPT {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        return shared_->refcount > 1;
    }

    //! Allocates a memory block. (concept Allocator)
    void* Malloc(size_t size) {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        if (!size)
            return NULL;

        size = RAPIDJSON_ALIGN(size);
        if (RAPIDJSON_UNLIKELY(shared_->chunkHead->size + size > shared_->chunkHead->capacity))
            if (!AddChunk(chunk_capacity_ > size ? chunk_capacity_ : size))
                return NULL;

        void *buffer = GetChunkBuffer(shared_) + shared_->chunkHead->size;
        shared_->chunkHead->size += size;
        return buffer;
    }

    //! Resizes a memory block (concept Allocator)
    void* Realloc(void* originalPtr, size_t originalSize, size_t newSize) {
        if (originalPtr == 0)
            return Malloc(newSize);

        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        if (newSize == 0)
            return NULL;

        originalSize = RAPIDJSON_ALIGN(originalSize);
        newSize = RAPIDJSON_ALIGN(newSize);

        // Do not shrink if new size is smaller than original
        if (originalSize >= newSize)
            return originalPtr;

        // Simply expand it if it is the last allocation and there is sufficient space
        if (originalPtr == GetChunkBuffer(shared_) + shared_->chunkHead->size - originalSize) {
            size_t increment = static_cast<size_t>(newSize - originalSize);
            if (shared_->chunkHead->size + increment <= shared_->chunkHead->capacity) {
                shared_->chunkHead->size += increment;
                return originalPtr;
            }
        }

        // Realloc process: allocate and copy memory, do not free original buffer.
        if (void* newBuffer = Malloc(newSize)) {
            if (originalSize)
                std::memcpy(newBuffer, originalPtr, originalSize);
            return newBuffer;
        }
        else
            return NULL;
    }

    //! Frees a memory block (concept Allocator)
    static void Free(void *ptr) RAPIDJSON_NOEXCEPT { (void)ptr; } // Do nothing

    //! Compare (equality) with another MemoryPoolAllocator
    bool operator==(const MemoryPoolAllocator& rhs) const RAPIDJSON_NOEXCEPT {
        RAPIDJSON_NOEXCEPT_ASSERT(shared_->refcount > 0);
        RAPIDJSON_NOEXCEPT_ASSERT(rhs.shared_->refcount > 0);
        return shared_ == rhs.shared_;
    }
    //! Compare (inequality) with another MemoryPoolAllocator
    bool operator!=(const MemoryPoolAllocator& rhs) const RAPIDJSON_NOEXCEPT {
        return !operator==(rhs);
    }

private:
    //! Creates a new chunk.
    /*! \param capacity Capacity of the chunk in bytes.
        \return true if success.
    */
    bool AddChunk(size_t capacity) {
        if (!baseAllocator_)
            shared_->ownBaseAllocator = baseAllocator_ = RAPIDJSON_NEW(BaseAllocator)();
        if (ChunkHeader* chunk = static_cast<ChunkHeader*>(baseAllocator_->Malloc(SIZEOF_CHUNK_HEADER + capacity))) {
            chunk->capacity = capacity;
            chunk->size = 0;
            chunk->next = shared_->chunkHead;
            shared_->chunkHead = chunk;
            return true;
        }
        else
            return false;
    }

    static inline void* AlignBuffer(void* buf, size_t &size)
    {
        RAPIDJSON_NOEXCEPT_ASSERT(buf != 0);
        const uintptr_t mask = sizeof(void*) - 1;
        const uintptr_t ubuf = reinterpret_cast<uintptr_t>(buf);
        if (RAPIDJSON_UNLIKELY(ubuf & mask)) {
            const uintptr_t abuf = (ubuf + mask) & ~mask;
            RAPIDJSON_ASSERT(size >= abuf - ubuf);
            buf = reinterpret_cast<void*>(abuf);
            size -= abuf - ubuf;
        }
        return buf;
    }

    size_t chunk_capacity_;     //!< The minimum capacity of chunk when they are allocated.
    BaseAllocator* baseAllocator_;  //!< base allocator for allocating memory chunks.
    SharedData *shared_;        //!< The shared data of the allocator
};

namespace internal {
    template<typename, typename = void>
    struct IsRefCounted :
        public FalseType
    { };
    template<typename T>
    struct IsRefCounted<T, typename internal::EnableIfCond<T::kRefCounted>::Type> :
        public TrueType
    { };
}

template<typename T, typename A>
inline T* Realloc(A& a, T* old_p, size_t old_n, size_t new_n)
{
    RAPIDJSON_NOEXCEPT_ASSERT(old_n <= (std::numeric_limits<size_t>::max)() / sizeof(T) && new_n <= (std::numeric_limits<size_t>::max)() / sizeof(T));
    return static_cast<T*>(a.Realloc(old_p, old_n * sizeof(T), new_n * sizeof(T)));
}

template<typename T, typename A>
inline T *Malloc(A& a, size_t n = 1)
{
    return Realloc<T, A>(a, NULL, 0, n);
}

template<typename T, typename A>
inline void Free(A& a, T *p, size_t n = 1)
{
    static_cast<void>(Realloc<T, A>(a, p, n, 0));
}

#ifdef __GNUC__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++) // std::allocator can safely be inherited
#endif

template <typename T, typename BaseAllocator = CrtAllocator>
class StdAllocator :
    public std::allocator<T>
{
    typedef std::allocator<T> allocator_type;
#if RAPIDJSON_HAS_CXX11
    typedef std::allocator_traits<allocator_type> traits_type;
#else
    typedef allocator_type traits_type;
#endif

public:
    typedef BaseAllocator BaseAllocatorType;

    StdAllocator() RAPIDJSON_NOEXCEPT :
        allocator_type(),
        baseAllocator_()
    { }

    StdAllocator(const StdAllocator& rhs) RAPIDJSON_NOEXCEPT :
        allocator_type(rhs),
        baseAllocator_(rhs.baseAllocator_)
    { }

    template<typename U>
    StdAllocator(const StdAllocator<U, BaseAllocator>& rhs) RAPIDJSON_NOEXCEPT :
        allocator_type(rhs),
        baseAllocator_(rhs.baseAllocator_)
    { }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    StdAllocator(StdAllocator&& rhs) RAPIDJSON_NOEXCEPT :
        allocator_type(std::move(rhs)),
        baseAllocator_(std::move(rhs.baseAllocator_))
    { }
#endif
#if RAPIDJSON_HAS_CXX11
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
#endif

    /* implicit */
    StdAllocator(const BaseAllocator& baseAllocator) RAPIDJSON_NOEXCEPT :
        allocator_type(),
        baseAllocator_(baseAllocator)
    { }

    ~StdAllocator() RAPIDJSON_NOEXCEPT
    { }

    template<typename U>
    struct rebind {
        typedef StdAllocator<U, BaseAllocator> other;
    };

    typedef typename traits_type::size_type         size_type;
    typedef typename traits_type::difference_type   difference_type;

    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::pointer           pointer;
    typedef typename traits_type::const_pointer     const_pointer;

#if RAPIDJSON_HAS_CXX11

    typedef typename std::add_lvalue_reference<value_type>::type &reference;
    typedef typename std::add_lvalue_reference<typename std::add_const<value_type>::type>::type &const_reference;

    pointer address(reference r) const RAPIDJSON_NOEXCEPT
    {
        return std::addressof(r);
    }
    const_pointer address(const_reference r) const RAPIDJSON_NOEXCEPT
    {
        return std::addressof(r);
    }

    size_type max_size() const RAPIDJSON_NOEXCEPT
    {
        return traits_type::max_size(*this);
    }

    template <typename ...Args>
    void construct(pointer p, Args&&... args)
    {
        traits_type::construct(*this, p, std::forward<Args>(args)...);
    }
    void destroy(pointer p)
    {
        traits_type::destroy(*this, p);
    }

#else // !RAPIDJSON_HAS_CXX11

    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;

    pointer address(reference r) const RAPIDJSON_NOEXCEPT
    {
        return allocator_type::address(r);
    }
    const_pointer address(const_reference r) const RAPIDJSON_NOEXCEPT
    {
        return allocator_type::address(r);
    }

    size_type max_size() const RAPIDJSON_NOEXCEPT
    {
        return allocator_type::max_size();
    }

    void construct(pointer p, const_reference r)
    {
        allocator_type::construct(p, r);
    }
    void destroy(pointer p)
    {
        allocator_type::destroy(p);
    }

#endif // !RAPIDJSON_HAS_CXX11

    template <typename U>
    U* allocate(size_type n = 1, const void* = 0)
    {
        return RAPIDJSON_NAMESPACE::Malloc<U>(baseAllocator_, n);
    }
    template <typename U>
    void deallocate(U* p, size_type n = 1)
    {
        RAPIDJSON_NAMESPACE::Free<U>(baseAllocator_, p, n);
    }

    pointer allocate(size_type n = 1, const void* = 0)
    {
        return allocate<value_type>(n);
    }
    void deallocate(pointer p, size_type n = 1)
    {
        deallocate<value_type>(p, n);
    }

#if RAPIDJSON_HAS_CXX11
    using is_always_equal = std::is_empty<BaseAllocator>;
#endif

    template<typename U>
    bool operator==(const StdAllocator<U, BaseAllocator>& rhs) const RAPIDJSON_NOEXCEPT
    {
        return baseAllocator_ == rhs.baseAllocator_;
    }
    template<typename U>
    bool operator!=(const StdAllocator<U, BaseAllocator>& rhs) const RAPIDJSON_NOEXCEPT
    {
        return !operator==(rhs);
    }

    //! rapidjson Allocator concept
    static const bool kNeedFree = BaseAllocator::kNeedFree;
    static const bool kRefCounted = internal::IsRefCounted<BaseAllocator>::Value;
    void* Malloc(size_t size)
    {
        return baseAllocator_.Malloc(size);
    }
    void* Realloc(void* originalPtr, size_t originalSize, size_t newSize)
    {
        return baseAllocator_.Realloc(originalPtr, originalSize, newSize);
    }
    static void Free(void *ptr) RAPIDJSON_NOEXCEPT
    {
        BaseAllocator::Free(ptr);
    }

private:
    template <typename, typename>
    friend class StdAllocator; // access to StdAllocator<!T>.*

    BaseAllocator baseAllocator_;
};

#if !RAPIDJSON_HAS_CXX17 // std::allocator<void> deprecated in C++17
template <typename BaseAllocator>
class StdAllocator<void, BaseAllocator> :
    public std::allocator<void>
{
    typedef std::allocator<void> allocator_type;

public:
    typedef BaseAllocator BaseAllocatorType;

    StdAllocator() RAPIDJSON_NOEXCEPT :
        allocator_type(),
        baseAllocator_()
    { }

    StdAllocator(const StdAllocator& rhs) RAPIDJSON_NOEXCEPT :
        allocator_type(rhs),
        baseAllocator_(rhs.baseAllocator_)
    { }

    template<typename U>
    StdAllocator(const StdAllocator<U, BaseAllocator>& rhs) RAPIDJSON_NOEXCEPT :
        allocator_type(rhs),
        baseAllocator_(rhs.baseAllocator_)
    { }

    /* implicit */
    StdAllocator(const BaseAllocator& baseAllocator) RAPIDJSON_NOEXCEPT :
        allocator_type(),
        baseAllocator_(baseAllocator)
    { }

    ~StdAllocator() RAPIDJSON_NOEXCEPT
    { }

    template<typename U>
    struct rebind {
        typedef StdAllocator<U, BaseAllocator> other;
    };

    typedef typename allocator_type::value_type value_type;

private:
    template <typename, typename>
    friend class StdAllocator; // access to StdAllocator<!T>.*

    BaseAllocator baseAllocator_;
};
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_POP
#endif

RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_ENCODINGS_H_

// End file:allocators.h


// Begin file: stream.h
// already included
// End file:stream.h


// Begin file: encodedstream.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ENCODEDSTREAM_H_
#define RAPIDJSON_ENCODEDSTREAM_H_


// Begin file: stream.h
// already included
// End file:stream.h


// Begin file: memorystream.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_MEMORYSTREAM_H_
#define RAPIDJSON_MEMORYSTREAM_H_


// Begin file: stream.h
// already included
// End file:stream.h


#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(unreachable-code)
RAPIDJSON_DIAG_OFF(missing-noreturn)
#endif

RAPIDJSON_NAMESPACE_BEGIN

//! Represents an in-memory input byte stream.
/*!
    This class is mainly for being wrapped by EncodedInputStream or AutoUTFInputStream.

    It is similar to FileReadBuffer but the source is an in-memory buffer instead of a file.

    Differences between MemoryStream and StringStream:
    1. StringStream has encoding but MemoryStream is a byte stream.
    2. MemoryStream needs size of the source buffer and the buffer don't need to be null terminated. StringStream assume null-terminated string as source.
    3. MemoryStream supports Peek4() for encoding detection. StringStream is specified with an encoding so it should not have Peek4().
    \note implements Stream concept
*/
struct MemoryStream {
    typedef char Ch; // byte

    MemoryStream(const Ch *src, size_t size) : src_(src), begin_(src), end_(src + size), size_(size) {}

    Ch Peek() const { return RAPIDJSON_UNLIKELY(src_ == end_) ? '\0' : *src_; }
    Ch Take() { return RAPIDJSON_UNLIKELY(src_ == end_) ? '\0' : *src_++; }
    size_t Tell() const { return static_cast<size_t>(src_ - begin_); }

    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    void Put(Ch) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

    // For encoding detection only.
    const Ch* Peek4() const {
        return Tell() + 4 <= size_ ? src_ : 0;
    }

    const Ch* src_;     //!< Current read position.
    const Ch* begin_;   //!< Original head of the string.
    const Ch* end_;     //!< End of stream.
    size_t size_;       //!< Size of the stream.
};

RAPIDJSON_NAMESPACE_END

#ifdef __clang__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_MEMORYBUFFER_H_

// End file:memorystream.h


#ifdef __GNUC__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++)
#endif

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
#endif

RAPIDJSON_NAMESPACE_BEGIN

//! Input byte stream wrapper with a statically bound encoding.
/*!
    \tparam Encoding The interpretation of encoding of the stream. Either UTF8, UTF16LE, UTF16BE, UTF32LE, UTF32BE.
    \tparam InputByteStream Type of input byte stream. For example, FileReadStream.
*/
template <typename Encoding, typename InputByteStream>
class EncodedInputStream {
    RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
public:
    typedef typename Encoding::Ch Ch;

    EncodedInputStream(InputByteStream& is) : is_(is) { 
        current_ = Encoding::TakeBOM(is_);
    }

    Ch Peek() const { return current_; }
    Ch Take() { Ch c = current_; current_ = Encoding::Take(is_); return c; }
    size_t Tell() const { return is_.Tell(); }

    // Not implemented
    void Put(Ch) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); } 
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

private:
    EncodedInputStream(const EncodedInputStream&);
    EncodedInputStream& operator=(const EncodedInputStream&);

    InputByteStream& is_;
    Ch current_;
};

//! Specialized for UTF8 MemoryStream.
template <>
class EncodedInputStream<UTF8<>, MemoryStream> {
public:
    typedef UTF8<>::Ch Ch;

    EncodedInputStream(MemoryStream& is) : is_(is) {
        if (static_cast<unsigned char>(is_.Peek()) == 0xEFu) is_.Take();
        if (static_cast<unsigned char>(is_.Peek()) == 0xBBu) is_.Take();
        if (static_cast<unsigned char>(is_.Peek()) == 0xBFu) is_.Take();
    }
    Ch Peek() const { return is_.Peek(); }
    Ch Take() { return is_.Take(); }
    size_t Tell() const { return is_.Tell(); }

    // Not implemented
    void Put(Ch) {}
    void Flush() {} 
    Ch* PutBegin() { return 0; }
    size_t PutEnd(Ch*) { return 0; }

    MemoryStream& is_;

private:
    EncodedInputStream(const EncodedInputStream&);
    EncodedInputStream& operator=(const EncodedInputStream&);
};

//! Output byte stream wrapper with statically bound encoding.
/*!
    \tparam Encoding The interpretation of encoding of the stream. Either UTF8, UTF16LE, UTF16BE, UTF32LE, UTF32BE.
    \tparam OutputByteStream Type of input byte stream. For example, FileWriteStream.
*/
template <typename Encoding, typename OutputByteStream>
class EncodedOutputStream {
    RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
public:
    typedef typename Encoding::Ch Ch;

    EncodedOutputStream(OutputByteStream& os, bool putBOM = true) : os_(os) { 
        if (putBOM)
            Encoding::PutBOM(os_);
    }

    void Put(Ch c) { Encoding::Put(os_, c);  }
    void Flush() { os_.Flush(); }

    // Not implemented
    Ch Peek() const { RAPIDJSON_ASSERT(false); return 0;}
    Ch Take() { RAPIDJSON_ASSERT(false); return 0;}
    size_t Tell() const { RAPIDJSON_ASSERT(false);  return 0; }
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

private:
    EncodedOutputStream(const EncodedOutputStream&);
    EncodedOutputStream& operator=(const EncodedOutputStream&);

    OutputByteStream& os_;
};

#define RAPIDJSON_ENCODINGS_FUNC(x) UTF8<Ch>::x, UTF16LE<Ch>::x, UTF16BE<Ch>::x, UTF32LE<Ch>::x, UTF32BE<Ch>::x

//! Input stream wrapper with dynamically bound encoding and automatic encoding detection.
/*!
    \tparam CharType Type of character for reading.
    \tparam InputByteStream type of input byte stream to be wrapped.
*/
template <typename CharType, typename InputByteStream>
class AutoUTFInputStream {
    RAPIDJSON_STATIC_ASSERT(sizeof(typename InputByteStream::Ch) == 1);
public:
    typedef CharType Ch;

    //! Constructor.
    /*!
        \param is input stream to be wrapped.
        \param type UTF encoding type if it is not detected from the stream.
    */
    AutoUTFInputStream(InputByteStream& is, UTFType type = kUTF8) : is_(&is), type_(type), hasBOM_(false) {
        RAPIDJSON_ASSERT(type >= kUTF8 && type <= kUTF32BE);        
        DetectType();
        static const TakeFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(Take) };
        takeFunc_ = f[type_];
        current_ = takeFunc_(*is_);
    }

    UTFType GetType() const { return type_; }
    bool HasBOM() const { return hasBOM_; }

    Ch Peek() const { return current_; }
    Ch Take() { Ch c = current_; current_ = takeFunc_(*is_); return c; }
    size_t Tell() const { return is_->Tell(); }

    // Not implemented
    void Put(Ch) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); } 
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

private:
    AutoUTFInputStream(const AutoUTFInputStream&);
    AutoUTFInputStream& operator=(const AutoUTFInputStream&);

    // Detect encoding type with BOM or RFC 4627
    void DetectType() {
        // BOM (Byte Order Mark):
        // 00 00 FE FF  UTF-32BE
        // FF FE 00 00  UTF-32LE
        // FE FF        UTF-16BE
        // FF FE        UTF-16LE
        // EF BB BF     UTF-8

        const unsigned char* c = reinterpret_cast<const unsigned char *>(is_->Peek4());
        if (!c)
            return;

        unsigned bom = static_cast<unsigned>(c[0] | (c[1] << 8) | (c[2] << 16) | (c[3] << 24));
        hasBOM_ = false;
        if (bom == 0xFFFE0000)                  { type_ = kUTF32BE; hasBOM_ = true; is_->Take(); is_->Take(); is_->Take(); is_->Take(); }
        else if (bom == 0x0000FEFF)             { type_ = kUTF32LE; hasBOM_ = true; is_->Take(); is_->Take(); is_->Take(); is_->Take(); }
        else if ((bom & 0xFFFF) == 0xFFFE)      { type_ = kUTF16BE; hasBOM_ = true; is_->Take(); is_->Take();                           }
        else if ((bom & 0xFFFF) == 0xFEFF)      { type_ = kUTF16LE; hasBOM_ = true; is_->Take(); is_->Take();                           }
        else if ((bom & 0xFFFFFF) == 0xBFBBEF)  { type_ = kUTF8;    hasBOM_ = true; is_->Take(); is_->Take(); is_->Take();              }

        // RFC 4627: Section 3
        // "Since the first two characters of a JSON text will always be ASCII
        // characters [RFC0020], it is possible to determine whether an octet
        // stream is UTF-8, UTF-16 (BE or LE), or UTF-32 (BE or LE) by looking
        // at the pattern of nulls in the first four octets."
        // 00 00 00 xx  UTF-32BE
        // 00 xx 00 xx  UTF-16BE
        // xx 00 00 00  UTF-32LE
        // xx 00 xx 00  UTF-16LE
        // xx xx xx xx  UTF-8

        if (!hasBOM_) {
            int pattern = (c[0] ? 1 : 0) | (c[1] ? 2 : 0) | (c[2] ? 4 : 0) | (c[3] ? 8 : 0);
            switch (pattern) {
            case 0x08: type_ = kUTF32BE; break;
            case 0x0A: type_ = kUTF16BE; break;
            case 0x01: type_ = kUTF32LE; break;
            case 0x05: type_ = kUTF16LE; break;
            case 0x0F: type_ = kUTF8;    break;
            default: break; // Use type defined by user.
            }
        }

        // Runtime check whether the size of character type is sufficient. It only perform checks with assertion.
        if (type_ == kUTF16LE || type_ == kUTF16BE) RAPIDJSON_ASSERT(sizeof(Ch) >= 2);
        if (type_ == kUTF32LE || type_ == kUTF32BE) RAPIDJSON_ASSERT(sizeof(Ch) >= 4);
    }

    typedef Ch (*TakeFunc)(InputByteStream& is);
    InputByteStream* is_;
    UTFType type_;
    Ch current_;
    TakeFunc takeFunc_;
    bool hasBOM_;
};

//! Output stream wrapper with dynamically bound encoding and automatic encoding detection.
/*!
    \tparam CharType Type of character for writing.
    \tparam OutputByteStream type of output byte stream to be wrapped.
*/
template <typename CharType, typename OutputByteStream>
class AutoUTFOutputStream {
    RAPIDJSON_STATIC_ASSERT(sizeof(typename OutputByteStream::Ch) == 1);
public:
    typedef CharType Ch;

    //! Constructor.
    /*!
        \param os output stream to be wrapped.
        \param type UTF encoding type.
        \param putBOM Whether to write BOM at the beginning of the stream.
    */
    AutoUTFOutputStream(OutputByteStream& os, UTFType type, bool putBOM) : os_(&os), type_(type) {
        RAPIDJSON_ASSERT(type >= kUTF8 && type <= kUTF32BE);

        // Runtime check whether the size of character type is sufficient. It only perform checks with assertion.
        if (type_ == kUTF16LE || type_ == kUTF16BE) RAPIDJSON_ASSERT(sizeof(Ch) >= 2);
        if (type_ == kUTF32LE || type_ == kUTF32BE) RAPIDJSON_ASSERT(sizeof(Ch) >= 4);

        static const PutFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(Put) };
        putFunc_ = f[type_];

        if (putBOM)
            PutBOM();
    }

    UTFType GetType() const { return type_; }

    void Put(Ch c) { putFunc_(*os_, c); }
    void Flush() { os_->Flush(); } 

    // Not implemented
    Ch Peek() const { RAPIDJSON_ASSERT(false); return 0;}
    Ch Take() { RAPIDJSON_ASSERT(false); return 0;}
    size_t Tell() const { RAPIDJSON_ASSERT(false); return 0; }
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

private:
    AutoUTFOutputStream(const AutoUTFOutputStream&);
    AutoUTFOutputStream& operator=(const AutoUTFOutputStream&);

    void PutBOM() { 
        typedef void (*PutBOMFunc)(OutputByteStream&);
        static const PutBOMFunc f[] = { RAPIDJSON_ENCODINGS_FUNC(PutBOM) };
        f[type_](*os_);
    }

    typedef void (*PutFunc)(OutputByteStream&, Ch);

    OutputByteStream* os_;
    UTFType type_;
    PutFunc putFunc_;
};

#undef RAPIDJSON_ENCODINGS_FUNC

RAPIDJSON_NAMESPACE_END

#ifdef __clang__
RAPIDJSON_DIAG_POP
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_FILESTREAM_H_

// End file:encodedstream.h


// Begin file: internal/clzll.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_CLZLL_H_
#define RAPIDJSON_CLZLL_H_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


#if defined(_MSC_VER) && !defined(UNDER_CE)
#include <intrin.h>
#if defined(_WIN64)
#pragma intrinsic(_BitScanReverse64)
#else
#pragma intrinsic(_BitScanReverse)
#endif
#endif

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

inline uint32_t clzll(uint64_t x) {
    // Passing 0 to __builtin_clzll is UB in GCC and results in an
    // infinite loop in the software implementation.
    RAPIDJSON_ASSERT(x != 0);

#if defined(_MSC_VER) && !defined(UNDER_CE)
    unsigned long r = 0;
#if defined(_WIN64)
    _BitScanReverse64(&r, x);
#else
    // Scan the high 32 bits.
    if (_BitScanReverse(&r, static_cast<uint32_t>(x >> 32)))
        return 63 - (r + 32);

    // Scan the low 32 bits.
    _BitScanReverse(&r, static_cast<uint32_t>(x & 0xFFFFFFFF));
#endif // _WIN64

    return 63 - r;
#elif (defined(__GNUC__) && __GNUC__ >= 4) || RAPIDJSON_HAS_BUILTIN(__builtin_clzll)
    // __builtin_clzll wrapper
    return static_cast<uint32_t>(__builtin_clzll(x));
#else
    // naive version
    uint32_t r = 0;
    while (!(x & (static_cast<uint64_t>(1) << 63))) {
        x <<= 1;
        ++r;
    }

    return r;
#endif // _MSC_VER
}

#define RAPIDJSON_CLZLL RAPIDJSON_NAMESPACE::internal::clzll

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_CLZLL_H_

// End file:internal/clzll.h


// Begin file: internal/meta.h
// already included
// End file:internal/meta.h


// Begin file: internal/stack.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_INTERNAL_STACK_H_
#define RAPIDJSON_INTERNAL_STACK_H_


// Begin file: ../allocators.h
// already included
// End file:../allocators.h


// Begin file: swap.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_INTERNAL_SWAP_H_
#define RAPIDJSON_INTERNAL_SWAP_H_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


#if defined(__clang__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(c++98-compat)
#endif

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

//! Custom swap() to avoid dependency on C++ <algorithm> header
/*! \tparam T Type of the arguments to swap, should be instantiated with primitive C++ types only.
    \note This has the same semantics as std::swap().
*/
template <typename T>
inline void Swap(T& a, T& b) RAPIDJSON_NOEXCEPT {
    T tmp = a;
        a = b;
        b = tmp;
}

} // namespace internal
RAPIDJSON_NAMESPACE_END

#if defined(__clang__)
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_INTERNAL_SWAP_H_

// End file:swap.h

#include <cstddef>

#if defined(__clang__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(c++98-compat)
#endif

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

///////////////////////////////////////////////////////////////////////////////
// Stack

//! A type-unsafe stack for storing different types of data.
/*! \tparam Allocator Allocator for allocating stack memory.
*/
template <typename Allocator>
class Stack {
public:
    // Optimization note: Do not allocate memory for stack_ in constructor.
    // Do it lazily when first Push() -> Expand() -> Resize().
    Stack(Allocator* allocator, size_t stackCapacity) : allocator_(allocator), ownAllocator_(0), stack_(0), stackTop_(0), stackEnd_(0), initialCapacity_(stackCapacity) {
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    Stack(Stack&& rhs)
        : allocator_(rhs.allocator_),
          ownAllocator_(rhs.ownAllocator_),
          stack_(rhs.stack_),
          stackTop_(rhs.stackTop_),
          stackEnd_(rhs.stackEnd_),
          initialCapacity_(rhs.initialCapacity_)
    {
        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.stack_ = 0;
        rhs.stackTop_ = 0;
        rhs.stackEnd_ = 0;
        rhs.initialCapacity_ = 0;
    }
#endif

    ~Stack() {
        Destroy();
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    Stack& operator=(Stack&& rhs) {
        if (&rhs != this)
        {
            Destroy();

            allocator_ = rhs.allocator_;
            ownAllocator_ = rhs.ownAllocator_;
            stack_ = rhs.stack_;
            stackTop_ = rhs.stackTop_;
            stackEnd_ = rhs.stackEnd_;
            initialCapacity_ = rhs.initialCapacity_;

            rhs.allocator_ = 0;
            rhs.ownAllocator_ = 0;
            rhs.stack_ = 0;
            rhs.stackTop_ = 0;
            rhs.stackEnd_ = 0;
            rhs.initialCapacity_ = 0;
        }
        return *this;
    }
#endif

    void Swap(Stack& rhs) RAPIDJSON_NOEXCEPT {
        internal::Swap(allocator_, rhs.allocator_);
        internal::Swap(ownAllocator_, rhs.ownAllocator_);
        internal::Swap(stack_, rhs.stack_);
        internal::Swap(stackTop_, rhs.stackTop_);
        internal::Swap(stackEnd_, rhs.stackEnd_);
        internal::Swap(initialCapacity_, rhs.initialCapacity_);
    }

    void Clear() { stackTop_ = stack_; }

    void ShrinkToFit() { 
        if (Empty()) {
            // If the stack is empty, completely deallocate the memory.
            Allocator::Free(stack_); // NOLINT (+clang-analyzer-unix.Malloc)
            stack_ = 0;
            stackTop_ = 0;
            stackEnd_ = 0;
        }
        else
            Resize(GetSize());
    }

    // Optimization note: try to minimize the size of this function for force inline.
    // Expansion is run very infrequently, so it is moved to another (probably non-inline) function.
    template<typename T>
    RAPIDJSON_FORCEINLINE void Reserve(size_t count = 1) {
         // Expand the stack if needed
        if (RAPIDJSON_UNLIKELY(static_cast<std::ptrdiff_t>(sizeof(T) * count) > (stackEnd_ - stackTop_)))
            Expand<T>(count);
    }

    template<typename T>
    RAPIDJSON_FORCEINLINE T* Push(size_t count = 1) {
        Reserve<T>(count);
        return PushUnsafe<T>(count);
    }

    template<typename T>
    RAPIDJSON_FORCEINLINE T* PushUnsafe(size_t count = 1) {
        RAPIDJSON_ASSERT(stackTop_);
        RAPIDJSON_ASSERT(static_cast<std::ptrdiff_t>(sizeof(T) * count) <= (stackEnd_ - stackTop_));
        T* ret = reinterpret_cast<T*>(stackTop_);
        stackTop_ += sizeof(T) * count;
        return ret;
    }

    template<typename T>
    T* Pop(size_t count) {
        RAPIDJSON_ASSERT(GetSize() >= count * sizeof(T));
        stackTop_ -= count * sizeof(T);
        return reinterpret_cast<T*>(stackTop_);
    }

    template<typename T>
    T* Top() { 
        RAPIDJSON_ASSERT(GetSize() >= sizeof(T));
        return reinterpret_cast<T*>(stackTop_ - sizeof(T));
    }

    template<typename T>
    const T* Top() const {
        RAPIDJSON_ASSERT(GetSize() >= sizeof(T));
        return reinterpret_cast<T*>(stackTop_ - sizeof(T));
    }

    template<typename T>
    T* End() { return reinterpret_cast<T*>(stackTop_); }

    template<typename T>
    const T* End() const { return reinterpret_cast<T*>(stackTop_); }

    template<typename T>
    T* Bottom() { return reinterpret_cast<T*>(stack_); }

    template<typename T>
    const T* Bottom() const { return reinterpret_cast<T*>(stack_); }

    bool HasAllocator() const {
        return allocator_ != 0;
    }

    Allocator& GetAllocator() {
        RAPIDJSON_ASSERT(allocator_);
        return *allocator_;
    }

    bool Empty() const { return stackTop_ == stack_; }
    size_t GetSize() const { return static_cast<size_t>(stackTop_ - stack_); }
    size_t GetCapacity() const { return static_cast<size_t>(stackEnd_ - stack_); }

private:
    template<typename T>
    void Expand(size_t count) {
        // Only expand the capacity if the current stack exists. Otherwise just create a stack with initial capacity.
        size_t newCapacity;
        if (stack_ == 0) {
            if (!allocator_)
                ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();
            newCapacity = initialCapacity_;
        } else {
            newCapacity = GetCapacity();
            newCapacity += (newCapacity + 1) / 2;
        }
        size_t newSize = GetSize() + sizeof(T) * count;
        if (newCapacity < newSize)
            newCapacity = newSize;

        Resize(newCapacity);
    }

    void Resize(size_t newCapacity) {
        const size_t size = GetSize();  // Backup the current size
        stack_ = static_cast<char*>(allocator_->Realloc(stack_, GetCapacity(), newCapacity));
        stackTop_ = stack_ + size;
        stackEnd_ = stack_ + newCapacity;
    }

    void Destroy() {
        Allocator::Free(stack_);
        RAPIDJSON_DELETE(ownAllocator_); // Only delete if it is owned by the stack
    }

    // Prohibit copy constructor & assignment operator.
    Stack(const Stack&);
    Stack& operator=(const Stack&);

    Allocator* allocator_;
    Allocator* ownAllocator_;
    char *stack_;
    char *stackTop_;
    char *stackEnd_;
    size_t initialCapacity_;
};

} // namespace internal
RAPIDJSON_NAMESPACE_END

#if defined(__clang__)
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_STACK_H_

// End file:internal/stack.h


// Begin file: internal/strtod.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_STRTOD_
#define RAPIDJSON_STRTOD_


// Begin file: ieee754.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_IEEE754_
#define RAPIDJSON_IEEE754_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

class Double {
public:
    Double() {}
    Double(double d) : d_(d) {}
    Double(uint64_t u) : u_(u) {}

    double Value() const { return d_; }
    uint64_t Uint64Value() const { return u_; }

    double NextPositiveDouble() const {
        RAPIDJSON_ASSERT(!Sign());
        return Double(u_ + 1).Value();
    }

    bool Sign() const { return (u_ & kSignMask) != 0; }
    uint64_t Significand() const { return u_ & kSignificandMask; }
    int Exponent() const { return static_cast<int>(((u_ & kExponentMask) >> kSignificandSize) - kExponentBias); }

    bool IsNan() const { return (u_ & kExponentMask) == kExponentMask && Significand() != 0; }
    bool IsInf() const { return (u_ & kExponentMask) == kExponentMask && Significand() == 0; }
    bool IsNanOrInf() const { return (u_ & kExponentMask) == kExponentMask; }
    bool IsNormal() const { return (u_ & kExponentMask) != 0 || Significand() == 0; }
    bool IsZero() const { return (u_ & (kExponentMask | kSignificandMask)) == 0; }

    uint64_t IntegerSignificand() const { return IsNormal() ? Significand() | kHiddenBit : Significand(); }
    int IntegerExponent() const { return (IsNormal() ? Exponent() : kDenormalExponent) - kSignificandSize; }
    uint64_t ToBias() const { return (u_ & kSignMask) ? ~u_ + 1 : u_ | kSignMask; }

    static int EffectiveSignificandSize(int order) {
        if (order >= -1021)
            return 53;
        else if (order <= -1074)
            return 0;
        else
            return order + 1074;
    }

private:
    static const int kSignificandSize = 52;
    static const int kExponentBias = 0x3FF;
    static const int kDenormalExponent = 1 - kExponentBias;
    static const uint64_t kSignMask = RAPIDJSON_UINT64_C2(0x80000000, 0x00000000);
    static const uint64_t kExponentMask = RAPIDJSON_UINT64_C2(0x7FF00000, 0x00000000);
    static const uint64_t kSignificandMask = RAPIDJSON_UINT64_C2(0x000FFFFF, 0xFFFFFFFF);
    static const uint64_t kHiddenBit = RAPIDJSON_UINT64_C2(0x00100000, 0x00000000);

    union {
        double d_;
        uint64_t u_;
    };
};

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_IEEE754_

// End file:ieee754.h


// Begin file: biginteger.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_BIGINTEGER_H_
#define RAPIDJSON_BIGINTEGER_H_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) && defined(_M_AMD64)
#include <intrin.h> // for _umul128
#if !defined(_ARM64EC_)
#pragma intrinsic(_umul128)
#else
#pragma comment(lib,"softintrin")
#endif
#endif

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

class BigInteger {
public:
    typedef uint64_t Type;

    BigInteger(const BigInteger& rhs) : count_(rhs.count_) {
        std::memcpy(digits_, rhs.digits_, count_ * sizeof(Type));
    }

    explicit BigInteger(uint64_t u) : count_(1) {
        digits_[0] = u;
    }

    template<typename Ch>
    BigInteger(const Ch* decimals, size_t length) : count_(1) {
        RAPIDJSON_ASSERT(length > 0);
        digits_[0] = 0;
        size_t i = 0;
        const size_t kMaxDigitPerIteration = 19;  // 2^64 = 18446744073709551616 > 10^19
        while (length >= kMaxDigitPerIteration) {
            AppendDecimal64(decimals + i, decimals + i + kMaxDigitPerIteration);
            length -= kMaxDigitPerIteration;
            i += kMaxDigitPerIteration;
        }

        if (length > 0)
            AppendDecimal64(decimals + i, decimals + i + length);
    }
    
    BigInteger& operator=(const BigInteger &rhs)
    {
        if (this != &rhs) {
            count_ = rhs.count_;
            std::memcpy(digits_, rhs.digits_, count_ * sizeof(Type));
        }
        return *this;
    }
    
    BigInteger& operator=(uint64_t u) {
        digits_[0] = u;            
        count_ = 1;
        return *this;
    }

    BigInteger& operator+=(uint64_t u) {
        Type backup = digits_[0];
        digits_[0] += u;
        for (size_t i = 0; i < count_ - 1; i++) {
            if (digits_[i] >= backup)
                return *this; // no carry
            backup = digits_[i + 1];
            digits_[i + 1] += 1;
        }

        // Last carry
        if (digits_[count_ - 1] < backup)
            PushBack(1);

        return *this;
    }

    BigInteger& operator*=(uint64_t u) {
        if (u == 0) return *this = 0;
        if (u == 1) return *this;
        if (*this == 1) return *this = u;

        uint64_t k = 0;
        for (size_t i = 0; i < count_; i++) {
            uint64_t hi;
            digits_[i] = MulAdd64(digits_[i], u, k, &hi);
            k = hi;
        }
        
        if (k > 0)
            PushBack(k);

        return *this;
    }

    BigInteger& operator*=(uint32_t u) {
        if (u == 0) return *this = 0;
        if (u == 1) return *this;
        if (*this == 1) return *this = u;

        uint64_t k = 0;
        for (size_t i = 0; i < count_; i++) {
            const uint64_t c = digits_[i] >> 32;
            const uint64_t d = digits_[i] & 0xFFFFFFFF;
            const uint64_t uc = u * c;
            const uint64_t ud = u * d;
            const uint64_t p0 = ud + k;
            const uint64_t p1 = uc + (p0 >> 32);
            digits_[i] = (p0 & 0xFFFFFFFF) | (p1 << 32);
            k = p1 >> 32;
        }
        
        if (k > 0)
            PushBack(k);

        return *this;
    }

    BigInteger& operator<<=(size_t shift) {
        if (IsZero() || shift == 0) return *this;

        size_t offset = shift / kTypeBit;
        size_t interShift = shift % kTypeBit;
        RAPIDJSON_ASSERT(count_ + offset <= kCapacity);

        if (interShift == 0) {
            std::memmove(digits_ + offset, digits_, count_ * sizeof(Type));
            count_ += offset;
        }
        else {
            digits_[count_] = 0;
            for (size_t i = count_; i > 0; i--)
                digits_[i + offset] = (digits_[i] << interShift) | (digits_[i - 1] >> (kTypeBit - interShift));
            digits_[offset] = digits_[0] << interShift;
            count_ += offset;
            if (digits_[count_])
                count_++;
        }

        std::memset(digits_, 0, offset * sizeof(Type));

        return *this;
    }

    bool operator==(const BigInteger& rhs) const {
        return count_ == rhs.count_ && std::memcmp(digits_, rhs.digits_, count_ * sizeof(Type)) == 0;
    }

    bool operator==(const Type rhs) const {
        return count_ == 1 && digits_[0] == rhs;
    }

    BigInteger& MultiplyPow5(unsigned exp) {
        static const uint32_t kPow5[12] = {
            5,
            5 * 5,
            5 * 5 * 5,
            5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5
        };
        if (exp == 0) return *this;
        for (; exp >= 27; exp -= 27) *this *= RAPIDJSON_UINT64_C2(0X6765C793, 0XFA10079D); // 5^27
        for (; exp >= 13; exp -= 13) *this *= static_cast<uint32_t>(1220703125u); // 5^13
        if (exp > 0)                 *this *= kPow5[exp - 1];
        return *this;
    }

    // Compute absolute difference of this and rhs.
    // Assume this != rhs
    bool Difference(const BigInteger& rhs, BigInteger* out) const {
        int cmp = Compare(rhs);
        RAPIDJSON_ASSERT(cmp != 0);
        const BigInteger *a, *b;  // Makes a > b
        bool ret;
        if (cmp < 0) { a = &rhs; b = this; ret = true; }
        else         { a = this; b = &rhs; ret = false; }

        Type borrow = 0;
        for (size_t i = 0; i < a->count_; i++) {
            Type d = a->digits_[i] - borrow;
            if (i < b->count_)
                d -= b->digits_[i];
            borrow = (d > a->digits_[i]) ? 1 : 0;
            out->digits_[i] = d;
            if (d != 0)
                out->count_ = i + 1;
        }

        return ret;
    }

    int Compare(const BigInteger& rhs) const {
        if (count_ != rhs.count_)
            return count_ < rhs.count_ ? -1 : 1;

        for (size_t i = count_; i-- > 0;)
            if (digits_[i] != rhs.digits_[i])
                return digits_[i] < rhs.digits_[i] ? -1 : 1;

        return 0;
    }

    size_t GetCount() const { return count_; }
    Type GetDigit(size_t index) const { RAPIDJSON_ASSERT(index < count_); return digits_[index]; }
    bool IsZero() const { return count_ == 1 && digits_[0] == 0; }

private:
    template<typename Ch>
    void AppendDecimal64(const Ch* begin, const Ch* end) {
        uint64_t u = ParseUint64(begin, end);
        if (IsZero())
            *this = u;
        else {
            unsigned exp = static_cast<unsigned>(end - begin);
            (MultiplyPow5(exp) <<= exp) += u;   // *this = *this * 10^exp + u
        }
    }

    void PushBack(Type digit) {
        RAPIDJSON_ASSERT(count_ < kCapacity);
        digits_[count_++] = digit;
    }

    template<typename Ch>
    static uint64_t ParseUint64(const Ch* begin, const Ch* end) {
        uint64_t r = 0;
        for (const Ch* p = begin; p != end; ++p) {
            RAPIDJSON_ASSERT(*p >= Ch('0') && *p <= Ch('9'));
            r = r * 10u + static_cast<unsigned>(*p - Ch('0'));
        }
        return r;
    }

    // Assume a * b + k < 2^128
    static uint64_t MulAdd64(uint64_t a, uint64_t b, uint64_t k, uint64_t* outHigh) {
#if defined(_MSC_VER) && defined(_M_AMD64)
        uint64_t low = _umul128(a, b, outHigh) + k;
        if (low < k)
            (*outHigh)++;
        return low;
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__x86_64__)
        __extension__ typedef unsigned __int128 uint128;
        uint128 p = static_cast<uint128>(a) * static_cast<uint128>(b);
        p += k;
        *outHigh = static_cast<uint64_t>(p >> 64);
        return static_cast<uint64_t>(p);
#else
        const uint64_t a0 = a & 0xFFFFFFFF, a1 = a >> 32, b0 = b & 0xFFFFFFFF, b1 = b >> 32;
        uint64_t x0 = a0 * b0, x1 = a0 * b1, x2 = a1 * b0, x3 = a1 * b1;
        x1 += (x0 >> 32); // can't give carry
        x1 += x2;
        if (x1 < x2)
            x3 += (static_cast<uint64_t>(1) << 32);
        uint64_t lo = (x1 << 32) + (x0 & 0xFFFFFFFF);
        uint64_t hi = x3 + (x1 >> 32);

        lo += k;
        if (lo < k)
            hi++;
        *outHigh = hi;
        return lo;
#endif
    }

    static const size_t kBitCount = 3328;  // 64bit * 54 > 10^1000
    static const size_t kCapacity = kBitCount / sizeof(Type);
    static const size_t kTypeBit = sizeof(Type) * 8;

    Type digits_[kCapacity];
    size_t count_;
};

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_BIGINTEGER_H_

// End file:biginteger.h


// Begin file: diyfp.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// This is a C++ header-only implementation of Grisu2 algorithm from the publication:
// Loitsch, Florian. "Printing floating-point numbers quickly and accurately with
// integers." ACM Sigplan Notices 45.6 (2010): 233-243.

#ifndef RAPIDJSON_DIYFP_H_
#define RAPIDJSON_DIYFP_H_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


// Begin file: clzll.h
// already included
// End file:clzll.h

#include <limits>

#if defined(_MSC_VER) && defined(_M_AMD64) && !defined(__INTEL_COMPILER)
#include <intrin.h>
#if !defined(_ARM64EC_)
#pragma intrinsic(_umul128)
#else
#pragma comment(lib,"softintrin")
#endif
#endif

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

#ifdef __GNUC__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++)
#endif

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
#endif

struct DiyFp {
    DiyFp() : f(), e() {}

    DiyFp(uint64_t fp, int exp) : f(fp), e(exp) {}

    explicit DiyFp(double d) {
        union {
            double d;
            uint64_t u64;
        } u = { d };

        int biased_e = static_cast<int>((u.u64 & kDpExponentMask) >> kDpSignificandSize);
        uint64_t significand = (u.u64 & kDpSignificandMask);
        if (biased_e != 0) {
            f = significand + kDpHiddenBit;
            e = biased_e - kDpExponentBias;
        }
        else {
            f = significand;
            e = kDpMinExponent + 1;
        }
    }

    DiyFp operator-(const DiyFp& rhs) const {
        return DiyFp(f - rhs.f, e);
    }

    DiyFp operator*(const DiyFp& rhs) const {
#if defined(_MSC_VER) && defined(_M_AMD64)
        uint64_t h;
        uint64_t l = _umul128(f, rhs.f, &h);
        if (l & (uint64_t(1) << 63)) // rounding
            h++;
        return DiyFp(h, e + rhs.e + 64);
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__x86_64__)
        __extension__ typedef unsigned __int128 uint128;
        uint128 p = static_cast<uint128>(f) * static_cast<uint128>(rhs.f);
        uint64_t h = static_cast<uint64_t>(p >> 64);
        uint64_t l = static_cast<uint64_t>(p);
        if (l & (uint64_t(1) << 63)) // rounding
            h++;
        return DiyFp(h, e + rhs.e + 64);
#else
        const uint64_t M32 = 0xFFFFFFFF;
        const uint64_t a = f >> 32;
        const uint64_t b = f & M32;
        const uint64_t c = rhs.f >> 32;
        const uint64_t d = rhs.f & M32;
        const uint64_t ac = a * c;
        const uint64_t bc = b * c;
        const uint64_t ad = a * d;
        const uint64_t bd = b * d;
        uint64_t tmp = (bd >> 32) + (ad & M32) + (bc & M32);
        tmp += 1U << 31;  /// mult_round
        return DiyFp(ac + (ad >> 32) + (bc >> 32) + (tmp >> 32), e + rhs.e + 64);
#endif
    }

    DiyFp Normalize() const {
        int s = static_cast<int>(clzll(f));
        return DiyFp(f << s, e - s);
    }

    DiyFp NormalizeBoundary() const {
        DiyFp res = *this;
        while (!(res.f & (kDpHiddenBit << 1))) {
            res.f <<= 1;
            res.e--;
        }
        res.f <<= (kDiySignificandSize - kDpSignificandSize - 2);
        res.e = res.e - (kDiySignificandSize - kDpSignificandSize - 2);
        return res;
    }

    void NormalizedBoundaries(DiyFp* minus, DiyFp* plus) const {
        DiyFp pl = DiyFp((f << 1) + 1, e - 1).NormalizeBoundary();
        DiyFp mi = (f == kDpHiddenBit) ? DiyFp((f << 2) - 1, e - 2) : DiyFp((f << 1) - 1, e - 1);
        mi.f <<= mi.e - pl.e;
        mi.e = pl.e;
        *plus = pl;
        *minus = mi;
    }

    double ToDouble() const {
        union {
            double d;
            uint64_t u64;
        }u;
        RAPIDJSON_ASSERT(f <= kDpHiddenBit + kDpSignificandMask);
        if (e < kDpDenormalExponent) {
            // Underflow.
            return 0.0;
        }
        if (e >= kDpMaxExponent) {
            // Overflow.
            return std::numeric_limits<double>::infinity();
        }
        const uint64_t be = (e == kDpDenormalExponent && (f & kDpHiddenBit) == 0) ? 0 :
            static_cast<uint64_t>(e + kDpExponentBias);
        u.u64 = (f & kDpSignificandMask) | (be << kDpSignificandSize);
        return u.d;
    }

    static const int kDiySignificandSize = 64;
    static const int kDpSignificandSize = 52;
    static const int kDpExponentBias = 0x3FF + kDpSignificandSize;
    static const int kDpMaxExponent = 0x7FF - kDpExponentBias;
    static const int kDpMinExponent = -kDpExponentBias;
    static const int kDpDenormalExponent = -kDpExponentBias + 1;
    static const uint64_t kDpExponentMask = RAPIDJSON_UINT64_C2(0x7FF00000, 0x00000000);
    static const uint64_t kDpSignificandMask = RAPIDJSON_UINT64_C2(0x000FFFFF, 0xFFFFFFFF);
    static const uint64_t kDpHiddenBit = RAPIDJSON_UINT64_C2(0x00100000, 0x00000000);

    uint64_t f;
    int e;
};

inline DiyFp GetCachedPowerByIndex(size_t index) {
    // 10^-348, 10^-340, ..., 10^340
    static const uint64_t kCachedPowers_F[] = {
        RAPIDJSON_UINT64_C2(0xfa8fd5a0, 0x081c0288), RAPIDJSON_UINT64_C2(0xbaaee17f, 0xa23ebf76),
        RAPIDJSON_UINT64_C2(0x8b16fb20, 0x3055ac76), RAPIDJSON_UINT64_C2(0xcf42894a, 0x5dce35ea),
        RAPIDJSON_UINT64_C2(0x9a6bb0aa, 0x55653b2d), RAPIDJSON_UINT64_C2(0xe61acf03, 0x3d1a45df),
        RAPIDJSON_UINT64_C2(0xab70fe17, 0xc79ac6ca), RAPIDJSON_UINT64_C2(0xff77b1fc, 0xbebcdc4f),
        RAPIDJSON_UINT64_C2(0xbe5691ef, 0x416bd60c), RAPIDJSON_UINT64_C2(0x8dd01fad, 0x907ffc3c),
        RAPIDJSON_UINT64_C2(0xd3515c28, 0x31559a83), RAPIDJSON_UINT64_C2(0x9d71ac8f, 0xada6c9b5),
        RAPIDJSON_UINT64_C2(0xea9c2277, 0x23ee8bcb), RAPIDJSON_UINT64_C2(0xaecc4991, 0x4078536d),
        RAPIDJSON_UINT64_C2(0x823c1279, 0x5db6ce57), RAPIDJSON_UINT64_C2(0xc2109436, 0x4dfb5637),
        RAPIDJSON_UINT64_C2(0x9096ea6f, 0x3848984f), RAPIDJSON_UINT64_C2(0xd77485cb, 0x25823ac7),
        RAPIDJSON_UINT64_C2(0xa086cfcd, 0x97bf97f4), RAPIDJSON_UINT64_C2(0xef340a98, 0x172aace5),
        RAPIDJSON_UINT64_C2(0xb23867fb, 0x2a35b28e), RAPIDJSON_UINT64_C2(0x84c8d4df, 0xd2c63f3b),
        RAPIDJSON_UINT64_C2(0xc5dd4427, 0x1ad3cdba), RAPIDJSON_UINT64_C2(0x936b9fce, 0xbb25c996),
        RAPIDJSON_UINT64_C2(0xdbac6c24, 0x7d62a584), RAPIDJSON_UINT64_C2(0xa3ab6658, 0x0d5fdaf6),
        RAPIDJSON_UINT64_C2(0xf3e2f893, 0xdec3f126), RAPIDJSON_UINT64_C2(0xb5b5ada8, 0xaaff80b8),
        RAPIDJSON_UINT64_C2(0x87625f05, 0x6c7c4a8b), RAPIDJSON_UINT64_C2(0xc9bcff60, 0x34c13053),
        RAPIDJSON_UINT64_C2(0x964e858c, 0x91ba2655), RAPIDJSON_UINT64_C2(0xdff97724, 0x70297ebd),
        RAPIDJSON_UINT64_C2(0xa6dfbd9f, 0xb8e5b88f), RAPIDJSON_UINT64_C2(0xf8a95fcf, 0x88747d94),
        RAPIDJSON_UINT64_C2(0xb9447093, 0x8fa89bcf), RAPIDJSON_UINT64_C2(0x8a08f0f8, 0xbf0f156b),
        RAPIDJSON_UINT64_C2(0xcdb02555, 0x653131b6), RAPIDJSON_UINT64_C2(0x993fe2c6, 0xd07b7fac),
        RAPIDJSON_UINT64_C2(0xe45c10c4, 0x2a2b3b06), RAPIDJSON_UINT64_C2(0xaa242499, 0x697392d3),
        RAPIDJSON_UINT64_C2(0xfd87b5f2, 0x8300ca0e), RAPIDJSON_UINT64_C2(0xbce50864, 0x92111aeb),
        RAPIDJSON_UINT64_C2(0x8cbccc09, 0x6f5088cc), RAPIDJSON_UINT64_C2(0xd1b71758, 0xe219652c),
        RAPIDJSON_UINT64_C2(0x9c400000, 0x00000000), RAPIDJSON_UINT64_C2(0xe8d4a510, 0x00000000),
        RAPIDJSON_UINT64_C2(0xad78ebc5, 0xac620000), RAPIDJSON_UINT64_C2(0x813f3978, 0xf8940984),
        RAPIDJSON_UINT64_C2(0xc097ce7b, 0xc90715b3), RAPIDJSON_UINT64_C2(0x8f7e32ce, 0x7bea5c70),
        RAPIDJSON_UINT64_C2(0xd5d238a4, 0xabe98068), RAPIDJSON_UINT64_C2(0x9f4f2726, 0x179a2245),
        RAPIDJSON_UINT64_C2(0xed63a231, 0xd4c4fb27), RAPIDJSON_UINT64_C2(0xb0de6538, 0x8cc8ada8),
        RAPIDJSON_UINT64_C2(0x83c7088e, 0x1aab65db), RAPIDJSON_UINT64_C2(0xc45d1df9, 0x42711d9a),
        RAPIDJSON_UINT64_C2(0x924d692c, 0xa61be758), RAPIDJSON_UINT64_C2(0xda01ee64, 0x1a708dea),
        RAPIDJSON_UINT64_C2(0xa26da399, 0x9aef774a), RAPIDJSON_UINT64_C2(0xf209787b, 0xb47d6b85),
        RAPIDJSON_UINT64_C2(0xb454e4a1, 0x79dd1877), RAPIDJSON_UINT64_C2(0x865b8692, 0x5b9bc5c2),
        RAPIDJSON_UINT64_C2(0xc83553c5, 0xc8965d3d), RAPIDJSON_UINT64_C2(0x952ab45c, 0xfa97a0b3),
        RAPIDJSON_UINT64_C2(0xde469fbd, 0x99a05fe3), RAPIDJSON_UINT64_C2(0xa59bc234, 0xdb398c25),
        RAPIDJSON_UINT64_C2(0xf6c69a72, 0xa3989f5c), RAPIDJSON_UINT64_C2(0xb7dcbf53, 0x54e9bece),
        RAPIDJSON_UINT64_C2(0x88fcf317, 0xf22241e2), RAPIDJSON_UINT64_C2(0xcc20ce9b, 0xd35c78a5),
        RAPIDJSON_UINT64_C2(0x98165af3, 0x7b2153df), RAPIDJSON_UINT64_C2(0xe2a0b5dc, 0x971f303a),
        RAPIDJSON_UINT64_C2(0xa8d9d153, 0x5ce3b396), RAPIDJSON_UINT64_C2(0xfb9b7cd9, 0xa4a7443c),
        RAPIDJSON_UINT64_C2(0xbb764c4c, 0xa7a44410), RAPIDJSON_UINT64_C2(0x8bab8eef, 0xb6409c1a),
        RAPIDJSON_UINT64_C2(0xd01fef10, 0xa657842c), RAPIDJSON_UINT64_C2(0x9b10a4e5, 0xe9913129),
        RAPIDJSON_UINT64_C2(0xe7109bfb, 0xa19c0c9d), RAPIDJSON_UINT64_C2(0xac2820d9, 0x623bf429),
        RAPIDJSON_UINT64_C2(0x80444b5e, 0x7aa7cf85), RAPIDJSON_UINT64_C2(0xbf21e440, 0x03acdd2d),
        RAPIDJSON_UINT64_C2(0x8e679c2f, 0x5e44ff8f), RAPIDJSON_UINT64_C2(0xd433179d, 0x9c8cb841),
        RAPIDJSON_UINT64_C2(0x9e19db92, 0xb4e31ba9), RAPIDJSON_UINT64_C2(0xeb96bf6e, 0xbadf77d9),
        RAPIDJSON_UINT64_C2(0xaf87023b, 0x9bf0ee6b)
    };
    static const int16_t kCachedPowers_E[] = {
        -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007,  -980,
        -954,  -927,  -901,  -874,  -847,  -821,  -794,  -768,  -741,  -715,
        -688,  -661,  -635,  -608,  -582,  -555,  -529,  -502,  -475,  -449,
        -422,  -396,  -369,  -343,  -316,  -289,  -263,  -236,  -210,  -183,
        -157,  -130,  -103,   -77,   -50,   -24,     3,    30,    56,    83,
        109,   136,   162,   189,   216,   242,   269,   295,   322,   348,
        375,   402,   428,   455,   481,   508,   534,   561,   588,   614,
        641,   667,   694,   720,   747,   774,   800,   827,   853,   880,
        907,   933,   960,   986,  1013,  1039,  1066
    };
    RAPIDJSON_ASSERT(index < 87);
    return DiyFp(kCachedPowers_F[index], kCachedPowers_E[index]);
}

inline DiyFp GetCachedPower(int e, int* K) {

    //int k = static_cast<int>(ceil((-61 - e) * 0.30102999566398114)) + 374;
    double dk = (-61 - e) * 0.30102999566398114 + 347;  // dk must be positive, so can do ceiling in positive
    int k = static_cast<int>(dk);
    if (dk - k > 0.0)
        k++;

    unsigned index = static_cast<unsigned>((k >> 3) + 1);
    *K = -(-348 + static_cast<int>(index << 3));    // decimal exponent no need lookup table

    return GetCachedPowerByIndex(index);
}

inline DiyFp GetCachedPower10(int exp, int *outExp) {
    RAPIDJSON_ASSERT(exp >= -348);
    unsigned index = static_cast<unsigned>(exp + 348) / 8u;
    *outExp = -348 + static_cast<int>(index) * 8;
    return GetCachedPowerByIndex(index);
}

#ifdef __GNUC__
RAPIDJSON_DIAG_POP
#endif

#ifdef __clang__
RAPIDJSON_DIAG_POP
RAPIDJSON_DIAG_OFF(padded)
#endif

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_DIYFP_H_

// End file:diyfp.h


// Begin file: pow10.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_POW10_
#define RAPIDJSON_POW10_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

//! Computes integer powers of 10 in double (10.0^n).
/*! This function uses lookup table for fast and accurate results.
    \param n non-negative exponent. Must <= 308.
    \return 10.0^n
*/
inline double Pow10(int n) {
    static const double e[] = { // 1e-0...1e308: 309 * 8 bytes = 2472 bytes
        1e+0,  
        1e+1,  1e+2,  1e+3,  1e+4,  1e+5,  1e+6,  1e+7,  1e+8,  1e+9,  1e+10, 1e+11, 1e+12, 1e+13, 1e+14, 1e+15, 1e+16, 1e+17, 1e+18, 1e+19, 1e+20, 
        1e+21, 1e+22, 1e+23, 1e+24, 1e+25, 1e+26, 1e+27, 1e+28, 1e+29, 1e+30, 1e+31, 1e+32, 1e+33, 1e+34, 1e+35, 1e+36, 1e+37, 1e+38, 1e+39, 1e+40,
        1e+41, 1e+42, 1e+43, 1e+44, 1e+45, 1e+46, 1e+47, 1e+48, 1e+49, 1e+50, 1e+51, 1e+52, 1e+53, 1e+54, 1e+55, 1e+56, 1e+57, 1e+58, 1e+59, 1e+60,
        1e+61, 1e+62, 1e+63, 1e+64, 1e+65, 1e+66, 1e+67, 1e+68, 1e+69, 1e+70, 1e+71, 1e+72, 1e+73, 1e+74, 1e+75, 1e+76, 1e+77, 1e+78, 1e+79, 1e+80,
        1e+81, 1e+82, 1e+83, 1e+84, 1e+85, 1e+86, 1e+87, 1e+88, 1e+89, 1e+90, 1e+91, 1e+92, 1e+93, 1e+94, 1e+95, 1e+96, 1e+97, 1e+98, 1e+99, 1e+100,
        1e+101,1e+102,1e+103,1e+104,1e+105,1e+106,1e+107,1e+108,1e+109,1e+110,1e+111,1e+112,1e+113,1e+114,1e+115,1e+116,1e+117,1e+118,1e+119,1e+120,
        1e+121,1e+122,1e+123,1e+124,1e+125,1e+126,1e+127,1e+128,1e+129,1e+130,1e+131,1e+132,1e+133,1e+134,1e+135,1e+136,1e+137,1e+138,1e+139,1e+140,
        1e+141,1e+142,1e+143,1e+144,1e+145,1e+146,1e+147,1e+148,1e+149,1e+150,1e+151,1e+152,1e+153,1e+154,1e+155,1e+156,1e+157,1e+158,1e+159,1e+160,
        1e+161,1e+162,1e+163,1e+164,1e+165,1e+166,1e+167,1e+168,1e+169,1e+170,1e+171,1e+172,1e+173,1e+174,1e+175,1e+176,1e+177,1e+178,1e+179,1e+180,
        1e+181,1e+182,1e+183,1e+184,1e+185,1e+186,1e+187,1e+188,1e+189,1e+190,1e+191,1e+192,1e+193,1e+194,1e+195,1e+196,1e+197,1e+198,1e+199,1e+200,
        1e+201,1e+202,1e+203,1e+204,1e+205,1e+206,1e+207,1e+208,1e+209,1e+210,1e+211,1e+212,1e+213,1e+214,1e+215,1e+216,1e+217,1e+218,1e+219,1e+220,
        1e+221,1e+222,1e+223,1e+224,1e+225,1e+226,1e+227,1e+228,1e+229,1e+230,1e+231,1e+232,1e+233,1e+234,1e+235,1e+236,1e+237,1e+238,1e+239,1e+240,
        1e+241,1e+242,1e+243,1e+244,1e+245,1e+246,1e+247,1e+248,1e+249,1e+250,1e+251,1e+252,1e+253,1e+254,1e+255,1e+256,1e+257,1e+258,1e+259,1e+260,
        1e+261,1e+262,1e+263,1e+264,1e+265,1e+266,1e+267,1e+268,1e+269,1e+270,1e+271,1e+272,1e+273,1e+274,1e+275,1e+276,1e+277,1e+278,1e+279,1e+280,
        1e+281,1e+282,1e+283,1e+284,1e+285,1e+286,1e+287,1e+288,1e+289,1e+290,1e+291,1e+292,1e+293,1e+294,1e+295,1e+296,1e+297,1e+298,1e+299,1e+300,
        1e+301,1e+302,1e+303,1e+304,1e+305,1e+306,1e+307,1e+308
    };
    RAPIDJSON_ASSERT(n >= 0 && n <= 308);
    return e[n];
}

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_POW10_

// End file:pow10.h

#include <climits>
#include <limits>

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

inline double FastPath(double significand, int exp) {
    if (exp < -308)
        return 0.0;
    else if (exp >= 0)
        return significand * internal::Pow10(exp);
    else
        return significand / internal::Pow10(-exp);
}

inline double StrtodNormalPrecision(double d, int p) {
    if (p < -308) {
        // Prevent expSum < -308, making Pow10(p) = 0
        d = FastPath(d, -308);
        d = FastPath(d, p + 308);
    }
    else
        d = FastPath(d, p);
    return d;
}

template <typename T>
inline T Min3(T a, T b, T c) {
    T m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}

inline int CheckWithinHalfULP(double b, const BigInteger& d, int dExp) {
    const Double db(b);
    const uint64_t bInt = db.IntegerSignificand();
    const int bExp = db.IntegerExponent();
    const int hExp = bExp - 1;

    int dS_Exp2 = 0, dS_Exp5 = 0, bS_Exp2 = 0, bS_Exp5 = 0, hS_Exp2 = 0, hS_Exp5 = 0;

    // Adjust for decimal exponent
    if (dExp >= 0) {
        dS_Exp2 += dExp;
        dS_Exp5 += dExp;
    }
    else {
        bS_Exp2 -= dExp;
        bS_Exp5 -= dExp;
        hS_Exp2 -= dExp;
        hS_Exp5 -= dExp;
    }

    // Adjust for binary exponent
    if (bExp >= 0)
        bS_Exp2 += bExp;
    else {
        dS_Exp2 -= bExp;
        hS_Exp2 -= bExp;
    }

    // Adjust for half ulp exponent
    if (hExp >= 0)
        hS_Exp2 += hExp;
    else {
        dS_Exp2 -= hExp;
        bS_Exp2 -= hExp;
    }

    // Remove common power of two factor from all three scaled values
    int common_Exp2 = Min3(dS_Exp2, bS_Exp2, hS_Exp2);
    dS_Exp2 -= common_Exp2;
    bS_Exp2 -= common_Exp2;
    hS_Exp2 -= common_Exp2;

    BigInteger dS = d;
    dS.MultiplyPow5(static_cast<unsigned>(dS_Exp5)) <<= static_cast<unsigned>(dS_Exp2);

    BigInteger bS(bInt);
    bS.MultiplyPow5(static_cast<unsigned>(bS_Exp5)) <<= static_cast<unsigned>(bS_Exp2);

    BigInteger hS(1);
    hS.MultiplyPow5(static_cast<unsigned>(hS_Exp5)) <<= static_cast<unsigned>(hS_Exp2);

    BigInteger delta(0);
    dS.Difference(bS, &delta);

    return delta.Compare(hS);
}

inline bool StrtodFast(double d, int p, double* result) {
    // Use fast path for string-to-double conversion if possible
    // see http://www.exploringbinary.com/fast-path-decimal-to-floating-point-conversion/
    if (p > 22  && p < 22 + 16) {
        // Fast Path Cases In Disguise
        d *= internal::Pow10(p - 22);
        p = 22;
    }

    if (p >= -22 && p <= 22 && d <= 9007199254740991.0) { // 2^53 - 1
        *result = FastPath(d, p);
        return true;
    }
    else
        return false;
}

// Compute an approximation and see if it is within 1/2 ULP
template<typename Ch>
inline bool StrtodDiyFp(const Ch* decimals, int dLen, int dExp, double* result) {
    uint64_t significand = 0;
    int i = 0;   // 2^64 - 1 = 18446744073709551615, 1844674407370955161 = 0x1999999999999999    
    for (; i < dLen; i++) {
        if (significand  >  RAPIDJSON_UINT64_C2(0x19999999, 0x99999999) ||
            (significand == RAPIDJSON_UINT64_C2(0x19999999, 0x99999999) && decimals[i] > Ch('5')))
            break;
        significand = significand * 10u + static_cast<unsigned>(decimals[i] - Ch('0'));
    }
    
    if (i < dLen && decimals[i] >= Ch('5')) // Rounding
        significand++;

    int remaining = dLen - i;
    const int kUlpShift = 3;
    const int kUlp = 1 << kUlpShift;
    int64_t error = (remaining == 0) ? 0 : kUlp / 2;

    DiyFp v(significand, 0);
    v = v.Normalize();
    error <<= -v.e;

    dExp += remaining;

    int actualExp;
    DiyFp cachedPower = GetCachedPower10(dExp, &actualExp);
    if (actualExp != dExp) {
        static const DiyFp kPow10[] = {
            DiyFp(RAPIDJSON_UINT64_C2(0xa0000000, 0x00000000), -60),  // 10^1
            DiyFp(RAPIDJSON_UINT64_C2(0xc8000000, 0x00000000), -57),  // 10^2
            DiyFp(RAPIDJSON_UINT64_C2(0xfa000000, 0x00000000), -54),  // 10^3
            DiyFp(RAPIDJSON_UINT64_C2(0x9c400000, 0x00000000), -50),  // 10^4
            DiyFp(RAPIDJSON_UINT64_C2(0xc3500000, 0x00000000), -47),  // 10^5
            DiyFp(RAPIDJSON_UINT64_C2(0xf4240000, 0x00000000), -44),  // 10^6
            DiyFp(RAPIDJSON_UINT64_C2(0x98968000, 0x00000000), -40)   // 10^7
        };
        int adjustment = dExp - actualExp;
        RAPIDJSON_ASSERT(adjustment >= 1 && adjustment < 8);
        v = v * kPow10[adjustment - 1];
        if (dLen + adjustment > 19) // has more digits than decimal digits in 64-bit
            error += kUlp / 2;
    }

    v = v * cachedPower;

    error += kUlp + (error == 0 ? 0 : 1);

    const int oldExp = v.e;
    v = v.Normalize();
    error <<= oldExp - v.e;

    const int effectiveSignificandSize = Double::EffectiveSignificandSize(64 + v.e);
    int precisionSize = 64 - effectiveSignificandSize;
    if (precisionSize + kUlpShift >= 64) {
        int scaleExp = (precisionSize + kUlpShift) - 63;
        v.f >>= scaleExp;
        v.e += scaleExp; 
        error = (error >> scaleExp) + 1 + kUlp;
        precisionSize -= scaleExp;
    }

    DiyFp rounded(v.f >> precisionSize, v.e + precisionSize);
    const uint64_t precisionBits = (v.f & ((uint64_t(1) << precisionSize) - 1)) * kUlp;
    const uint64_t halfWay = (uint64_t(1) << (precisionSize - 1)) * kUlp;
    if (precisionBits >= halfWay + static_cast<unsigned>(error)) {
        rounded.f++;
        if (rounded.f & (DiyFp::kDpHiddenBit << 1)) { // rounding overflows mantissa (issue #340)
            rounded.f >>= 1;
            rounded.e++;
        }
    }

    *result = rounded.ToDouble();

    return halfWay - static_cast<unsigned>(error) >= precisionBits || precisionBits >= halfWay + static_cast<unsigned>(error);
}

template<typename Ch>
inline double StrtodBigInteger(double approx, const Ch* decimals, int dLen, int dExp) {
    RAPIDJSON_ASSERT(dLen >= 0);
    const BigInteger dInt(decimals, static_cast<unsigned>(dLen));
    Double a(approx);
    int cmp = CheckWithinHalfULP(a.Value(), dInt, dExp);
    if (cmp < 0)
        return a.Value();  // within half ULP
    else if (cmp == 0) {
        // Round towards even
        if (a.Significand() & 1)
            return a.NextPositiveDouble();
        else
            return a.Value();
    }
    else // adjustment
        return a.NextPositiveDouble();
}

template<typename Ch>
inline double StrtodFullPrecision(double d, int p, const Ch* decimals, size_t length, size_t decimalPosition, int exp) {
    RAPIDJSON_ASSERT(d >= 0.0);
    RAPIDJSON_ASSERT(length >= 1);

    double result = 0.0;
    if (StrtodFast(d, p, &result))
        return result;

    RAPIDJSON_ASSERT(length <= INT_MAX);
    int dLen = static_cast<int>(length);

    RAPIDJSON_ASSERT(length >= decimalPosition);
    RAPIDJSON_ASSERT(length - decimalPosition <= INT_MAX);
    int dExpAdjust = static_cast<int>(length - decimalPosition);

    RAPIDJSON_ASSERT(exp >= INT_MIN + dExpAdjust);
    int dExp = exp - dExpAdjust;

    // Make sure length+dExp does not overflow
    RAPIDJSON_ASSERT(dExp <= INT_MAX - dLen);

    // Trim leading zeros
    while (dLen > 0 && *decimals == '0') {
        dLen--;
        decimals++;
    }

    // Trim trailing zeros
    while (dLen > 0 && decimals[dLen - 1] == '0') {
        dLen--;
        dExp++;
    }

    if (dLen == 0) { // Buffer only contains zeros.
        return 0.0;
    }

    // Trim right-most digits
    const int kMaxDecimalDigit = 767 + 1;
    if (dLen > kMaxDecimalDigit) {
        dExp += dLen - kMaxDecimalDigit;
        dLen = kMaxDecimalDigit;
    }

    // If too small, underflow to zero.
    // Any x <= 10^-324 is interpreted as zero.
    if (dLen + dExp <= -324)
        return 0.0;

    // If too large, overflow to infinity.
    // Any x >= 10^309 is interpreted as +infinity.
    if (dLen + dExp > 309)
        return std::numeric_limits<double>::infinity();

    if (StrtodDiyFp(decimals, dLen, dExp, &result))
        return result;

    // Use approximation from StrtodDiyFp and make adjustment with BigInteger comparison
    return StrtodBigInteger(result, decimals, dLen, dExp);
}

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_STRTOD_

// End file:internal/strtod.h

#include <limits>

#if defined(RAPIDJSON_SIMD) && defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(_BitScanForward)
#endif
#ifdef RAPIDJSON_SSE42
#include <nmmintrin.h>
#elif defined(RAPIDJSON_SSE2)
#include <emmintrin.h>
#elif defined(RAPIDJSON_NEON)
#include <arm_neon.h>
#endif

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(old-style-cast)
RAPIDJSON_DIAG_OFF(padded)
RAPIDJSON_DIAG_OFF(switch-enum)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4127)  // conditional expression is constant
RAPIDJSON_DIAG_OFF(4702)  // unreachable code
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++)
#endif

//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
#define RAPIDJSON_NOTHING /* deliberately empty */
#ifndef RAPIDJSON_PARSE_ERROR_EARLY_RETURN
#define RAPIDJSON_PARSE_ERROR_EARLY_RETURN(value) \
    RAPIDJSON_MULTILINEMACRO_BEGIN \
    if (RAPIDJSON_UNLIKELY(HasParseError())) { return value; } \
    RAPIDJSON_MULTILINEMACRO_END
#endif
#define RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID \
    RAPIDJSON_PARSE_ERROR_EARLY_RETURN(RAPIDJSON_NOTHING)
//!@endcond

/*! \def RAPIDJSON_PARSE_ERROR_NORETURN
    \ingroup RAPIDJSON_ERRORS
    \brief Macro to indicate a parse error.
    \param parseErrorCode \ref rapidjson::ParseErrorCode of the error
    \param offset  position of the error in JSON input (\c size_t)

    This macros can be used as a customization point for the internal
    error handling mechanism of RapidJSON.

    A common usage model is to throw an exception instead of requiring the
    caller to explicitly check the \ref rapidjson::GenericReader::Parse's
    return value:

    \code
    #define RAPIDJSON_PARSE_ERROR_NORETURN(parseErrorCode,offset) \
       throw ParseException(parseErrorCode, #parseErrorCode, offset)

    #include <stdexcept>               // std::runtime_error
    #include "rapidjson/error/error.h" // rapidjson::ParseResult

    struct ParseException : std::runtime_error, rapidjson::ParseResult {
      ParseException(rapidjson::ParseErrorCode code, const char* msg, size_t offset)
        : std::runtime_error(msg), ParseResult(code, offset) {}
    };

    #include "rapidjson/reader.h"
    \endcode

    \see RAPIDJSON_PARSE_ERROR, rapidjson::GenericReader::Parse
 */
#ifndef RAPIDJSON_PARSE_ERROR_NORETURN
#define RAPIDJSON_PARSE_ERROR_NORETURN(parseErrorCode, offset) \
    RAPIDJSON_MULTILINEMACRO_BEGIN \
    RAPIDJSON_ASSERT(!HasParseError()); /* Error can only be assigned once */ \
    SetParseError(parseErrorCode, offset); \
    RAPIDJSON_MULTILINEMACRO_END
#endif

/*! \def RAPIDJSON_PARSE_ERROR
    \ingroup RAPIDJSON_ERRORS
    \brief (Internal) macro to indicate and handle a parse error.
    \param parseErrorCode \ref rapidjson::ParseErrorCode of the error
    \param offset  position of the error in JSON input (\c size_t)

    Invokes RAPIDJSON_PARSE_ERROR_NORETURN and stops the parsing.

    \see RAPIDJSON_PARSE_ERROR_NORETURN
    \hideinitializer
 */
#ifndef RAPIDJSON_PARSE_ERROR
#define RAPIDJSON_PARSE_ERROR(parseErrorCode, offset) \
    RAPIDJSON_MULTILINEMACRO_BEGIN \
    RAPIDJSON_PARSE_ERROR_NORETURN(parseErrorCode, offset); \
    RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID; \
    RAPIDJSON_MULTILINEMACRO_END
#endif


// Begin file: error/error.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ERROR_ERROR_H_
#define RAPIDJSON_ERROR_ERROR_H_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
#endif

/*! \file error.h */

/*! \defgroup RAPIDJSON_ERRORS RapidJSON error handling */

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_ERROR_CHARTYPE

//! Character type of error messages.
/*! \ingroup RAPIDJSON_ERRORS
    The default character type is \c char.
    On Windows, user can define this macro as \c TCHAR for supporting both
    unicode/non-unicode settings.
*/
#ifndef RAPIDJSON_ERROR_CHARTYPE
#define RAPIDJSON_ERROR_CHARTYPE char
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_ERROR_STRING

//! Macro for converting string literal to \ref RAPIDJSON_ERROR_CHARTYPE[].
/*! \ingroup RAPIDJSON_ERRORS
    By default this conversion macro does nothing.
    On Windows, user can define this macro as \c _T(x) for supporting both
    unicode/non-unicode settings.
*/
#ifndef RAPIDJSON_ERROR_STRING
#define RAPIDJSON_ERROR_STRING(x) x
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// ParseErrorCode

//! Error code of parsing.
/*! \ingroup RAPIDJSON_ERRORS
    \see GenericReader::Parse, GenericReader::GetParseErrorCode
*/
enum ParseErrorCode {
    kParseErrorNone = 0,                        //!< No error.

    kParseErrorDocumentEmpty,                   //!< The document is empty.
    kParseErrorDocumentRootNotSingular,         //!< The document root must not follow by other values.

    kParseErrorValueInvalid,                    //!< Invalid value.

    kParseErrorObjectMissName,                  //!< Missing a name for object member.
    kParseErrorObjectMissColon,                 //!< Missing a colon after a name of object member.
    kParseErrorObjectMissCommaOrCurlyBracket,   //!< Missing a comma or '}' after an object member.

    kParseErrorArrayMissCommaOrSquareBracket,   //!< Missing a comma or ']' after an array element.

    kParseErrorStringUnicodeEscapeInvalidHex,   //!< Incorrect hex digit after \\u escape in string.
    kParseErrorStringUnicodeSurrogateInvalid,   //!< The surrogate pair in string is invalid.
    kParseErrorStringEscapeInvalid,             //!< Invalid escape character in string.
    kParseErrorStringMissQuotationMark,         //!< Missing a closing quotation mark in string.
    kParseErrorStringInvalidEncoding,           //!< Invalid encoding in string.

    kParseErrorNumberTooBig,                    //!< Number too big to be stored in double.
    kParseErrorNumberMissFraction,              //!< Miss fraction part in number.
    kParseErrorNumberMissExponent,              //!< Miss exponent in number.

    kParseErrorTermination,                     //!< Parsing was terminated.
    kParseErrorUnspecificSyntaxError            //!< Unspecific syntax error.
};

//! Result of parsing (wraps ParseErrorCode)
/*!
    \ingroup RAPIDJSON_ERRORS
    \code
        Document doc;
        ParseResult ok = doc.Parse("[42]");
        if (!ok) {
            fprintf(stderr, "JSON parse error: %s (%u)",
                    GetParseError_En(ok.Code()), ok.Offset());
            exit(EXIT_FAILURE);
        }
    \endcode
    \see GenericReader::Parse, GenericDocument::Parse
*/
struct ParseResult {
    //!! Unspecified boolean type
    typedef bool (ParseResult::*BooleanType)() const;
public:
    //! Default constructor, no error.
    ParseResult() : code_(kParseErrorNone), offset_(0) {}
    //! Constructor to set an error.
    ParseResult(ParseErrorCode code, size_t offset) : code_(code), offset_(offset) {}

    //! Get the error code.
    ParseErrorCode Code() const { return code_; }
    //! Get the error offset, if \ref IsError(), 0 otherwise.
    size_t Offset() const { return offset_; }

    //! Explicit conversion to \c bool, returns \c true, iff !\ref IsError().
    operator BooleanType() const { return !IsError() ? &ParseResult::IsError : NULL; }
    //! Whether the result is an error.
    bool IsError() const { return code_ != kParseErrorNone; }

    bool operator==(const ParseResult& that) const { return code_ == that.code_; }
    bool operator==(ParseErrorCode code) const { return code_ == code; }
    friend bool operator==(ParseErrorCode code, const ParseResult & err) { return code == err.code_; }

    bool operator!=(const ParseResult& that) const { return !(*this == that); }
    bool operator!=(ParseErrorCode code) const { return !(*this == code); }
    friend bool operator!=(ParseErrorCode code, const ParseResult & err) { return err != code; }

    //! Reset error code.
    void Clear() { Set(kParseErrorNone); }
    //! Update error code and offset.
    void Set(ParseErrorCode code, size_t offset = 0) { code_ = code; offset_ = offset; }

private:
    ParseErrorCode code_;
    size_t offset_;
};

//! Function pointer type of GetParseError().
/*! \ingroup RAPIDJSON_ERRORS

    This is the prototype for \c GetParseError_X(), where \c X is a locale.
    User can dynamically change locale in runtime, e.g.:
\code
    GetParseErrorFunc GetParseError = GetParseError_En; // or whatever
    const RAPIDJSON_ERROR_CHARTYPE* s = GetParseError(document.GetParseErrorCode());
\endcode
*/
typedef const RAPIDJSON_ERROR_CHARTYPE* (*GetParseErrorFunc)(ParseErrorCode);

///////////////////////////////////////////////////////////////////////////////
// ValidateErrorCode

//! Error codes when validating.
/*! \ingroup RAPIDJSON_ERRORS
    \see GenericSchemaValidator
*/
enum ValidateErrorCode {
    kValidateErrors    = -1,                   //!< Top level error code when kValidateContinueOnErrorsFlag set.
    kValidateErrorNone = 0,                    //!< No error.

    kValidateErrorMultipleOf,                  //!< Number is not a multiple of the 'multipleOf' value.
    kValidateErrorMaximum,                     //!< Number is greater than the 'maximum' value.
    kValidateErrorExclusiveMaximum,            //!< Number is greater than or equal to the 'maximum' value.
    kValidateErrorMinimum,                     //!< Number is less than the 'minimum' value.
    kValidateErrorExclusiveMinimum,            //!< Number is less than or equal to the 'minimum' value.

    kValidateErrorMaxLength,                   //!< String is longer than the 'maxLength' value.
    kValidateErrorMinLength,                   //!< String is longer than the 'maxLength' value.
    kValidateErrorPattern,                     //!< String does not match the 'pattern' regular expression.

    kValidateErrorMaxItems,                    //!< Array is longer than the 'maxItems' value.
    kValidateErrorMinItems,                    //!< Array is shorter than the 'minItems' value.
    kValidateErrorUniqueItems,                 //!< Array has duplicate items but 'uniqueItems' is true.
    kValidateErrorAdditionalItems,             //!< Array has additional items that are not allowed by the schema.

    kValidateErrorMaxProperties,               //!< Object has more members than 'maxProperties' value.
    kValidateErrorMinProperties,               //!< Object has less members than 'minProperties' value.
    kValidateErrorRequired,                    //!< Object is missing one or more members required by the schema.
    kValidateErrorAdditionalProperties,        //!< Object has additional members that are not allowed by the schema.
    kValidateErrorPatternProperties,           //!< See other errors.
    kValidateErrorDependencies,                //!< Object has missing property or schema dependencies.

    kValidateErrorEnum,                        //!< Property has a value that is not one of its allowed enumerated values.
    kValidateErrorType,                        //!< Property has a type that is not allowed by the schema.

    kValidateErrorOneOf,                       //!< Property did not match any of the sub-schemas specified by 'oneOf'.
    kValidateErrorOneOfMatch,                  //!< Property matched more than one of the sub-schemas specified by 'oneOf'.
    kValidateErrorAllOf,                       //!< Property did not match all of the sub-schemas specified by 'allOf'.
    kValidateErrorAnyOf,                       //!< Property did not match any of the sub-schemas specified by 'anyOf'.
    kValidateErrorNot,                         //!< Property matched the sub-schema specified by 'not'.

    kValidateErrorReadOnly,                    //!< Property is read-only but has been provided when validation is for writing
    kValidateErrorWriteOnly                    //!< Property is write-only but has been provided when validation is for reading
};

//! Function pointer type of GetValidateError().
/*! \ingroup RAPIDJSON_ERRORS

    This is the prototype for \c GetValidateError_X(), where \c X is a locale.
    User can dynamically change locale in runtime, e.g.:
\code
    GetValidateErrorFunc GetValidateError = GetValidateError_En; // or whatever
    const RAPIDJSON_ERROR_CHARTYPE* s = GetValidateError(validator.GetInvalidSchemaCode());
\endcode
*/
typedef const RAPIDJSON_ERROR_CHARTYPE* (*GetValidateErrorFunc)(ValidateErrorCode);

///////////////////////////////////////////////////////////////////////////////
// SchemaErrorCode

//! Error codes when validating.
/*! \ingroup RAPIDJSON_ERRORS
    \see GenericSchemaValidator
*/
enum SchemaErrorCode {
    kSchemaErrorNone = 0,                      //!< No error.

    kSchemaErrorStartUnknown,                  //!< Pointer to start of schema does not resolve to a location in the document
    kSchemaErrorRefPlainName,                  //!< $ref fragment must be a JSON pointer
    kSchemaErrorRefInvalid,                    //!< $ref must not be an empty string
    kSchemaErrorRefPointerInvalid,             //!< $ref fragment is not a valid JSON pointer at offset
    kSchemaErrorRefUnknown,                    //!< $ref does not resolve to a location in the target document
    kSchemaErrorRefCyclical,                   //!< $ref is cyclical
    kSchemaErrorRefNoRemoteProvider,           //!< $ref is remote but there is no remote provider
    kSchemaErrorRefNoRemoteSchema,             //!< $ref is remote but the remote provider did not return a schema
    kSchemaErrorRegexInvalid,                  //!< Invalid regular expression in 'pattern' or 'patternProperties'
    kSchemaErrorSpecUnknown,                   //!< JSON schema draft or OpenAPI version is not recognized
    kSchemaErrorSpecUnsupported,               //!< JSON schema draft or OpenAPI version is not supported
    kSchemaErrorSpecIllegal,                   //!< Both JSON schema draft and OpenAPI version found in document
    kSchemaErrorReadOnlyAndWriteOnly           //!< Property must not be both 'readOnly' and 'writeOnly'
};

//! Function pointer type of GetSchemaError().
/*! \ingroup RAPIDJSON_ERRORS

    This is the prototype for \c GetSchemaError_X(), where \c X is a locale.
    User can dynamically change locale in runtime, e.g.:
\code
    GetSchemaErrorFunc GetSchemaError = GetSchemaError_En; // or whatever
    const RAPIDJSON_ERROR_CHARTYPE* s = GetSchemaError(validator.GetInvalidSchemaCode());
\endcode
*/
typedef const RAPIDJSON_ERROR_CHARTYPE* (*GetSchemaErrorFunc)(SchemaErrorCode);

///////////////////////////////////////////////////////////////////////////////
// PointerParseErrorCode

//! Error code of JSON pointer parsing.
/*! \ingroup RAPIDJSON_ERRORS
    \see GenericPointer::GenericPointer, GenericPointer::GetParseErrorCode
*/
enum PointerParseErrorCode {
    kPointerParseErrorNone = 0,                     //!< The parse is successful

    kPointerParseErrorTokenMustBeginWithSolidus,    //!< A token must begin with a '/'
    kPointerParseErrorInvalidEscape,                //!< Invalid escape
    kPointerParseErrorInvalidPercentEncoding,       //!< Invalid percent encoding in URI fragment
    kPointerParseErrorCharacterMustPercentEncode    //!< A character must percent encoded in URI fragment
};

//! Function pointer type of GetPointerParseError().
/*! \ingroup RAPIDJSON_ERRORS

    This is the prototype for \c GetPointerParseError_X(), where \c X is a locale.
    User can dynamically change locale in runtime, e.g.:
\code
    GetPointerParseErrorFunc GetPointerParseError = GetPointerParseError_En; // or whatever
    const RAPIDJSON_ERROR_CHARTYPE* s = GetPointerParseError(pointer.GetParseErrorCode());
\endcode
*/
typedef const RAPIDJSON_ERROR_CHARTYPE* (*GetPointerParseErrorFunc)(PointerParseErrorCode);


RAPIDJSON_NAMESPACE_END

#ifdef __clang__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_ERROR_ERROR_H_

// End file:error/error.h


RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// ParseFlag

/*! \def RAPIDJSON_PARSE_DEFAULT_FLAGS
    \ingroup RAPIDJSON_CONFIG
    \brief User-defined kParseDefaultFlags definition.

    User can define this as any \c ParseFlag combinations.
*/
#ifndef RAPIDJSON_PARSE_DEFAULT_FLAGS
#define RAPIDJSON_PARSE_DEFAULT_FLAGS kParseNoFlags
#endif

//! Combination of parseFlags
/*! \see Reader::Parse, Document::Parse, Document::ParseInsitu, Document::ParseStream
 */
enum ParseFlag {
    kParseNoFlags = 0,              //!< No flags are set.
    kParseInsituFlag = 1,           //!< In-situ(destructive) parsing.
    kParseValidateEncodingFlag = 2, //!< Validate encoding of JSON strings.
    kParseIterativeFlag = 4,        //!< Iterative(constant complexity in terms of function call stack size) parsing.
    kParseStopWhenDoneFlag = 8,     //!< After parsing a complete JSON root from stream, stop further processing the rest of stream. When this flag is used, parser will not generate kParseErrorDocumentRootNotSingular error.
    kParseFullPrecisionFlag = 16,   //!< Parse number in full precision (but slower).
    kParseCommentsFlag = 32,        //!< Allow one-line (//) and multi-line (/**/) comments.
    kParseNumbersAsStringsFlag = 64,    //!< Parse all numbers (ints/doubles) as strings.
    kParseTrailingCommasFlag = 128, //!< Allow trailing commas at the end of objects and arrays.
    kParseNanAndInfFlag = 256,      //!< Allow parsing NaN, Inf, Infinity, -Inf and -Infinity as doubles.
    kParseEscapedApostropheFlag = 512,  //!< Allow escaped apostrophe in strings.
    kParseDefaultFlags = RAPIDJSON_PARSE_DEFAULT_FLAGS  //!< Default parse flags. Can be customized by defining RAPIDJSON_PARSE_DEFAULT_FLAGS
};

///////////////////////////////////////////////////////////////////////////////
// Handler

/*! \class rapidjson::Handler
    \brief Concept for receiving events from GenericReader upon parsing.
    The functions return true if no error occurs. If they return false,
    the event publisher should terminate the process.
\code
concept Handler {
    typename Ch;

    bool Null();
    bool Bool(bool b);
    bool Int(int i);
    bool Uint(unsigned i);
    bool Int64(int64_t i);
    bool Uint64(uint64_t i);
    bool Double(double d);
    /// enabled via kParseNumbersAsStringsFlag, string is not null-terminated (use length)
    bool RawNumber(const Ch* str, SizeType length, bool copy);
    bool String(const Ch* str, SizeType length, bool copy);
    bool StartObject();
    bool Key(const Ch* str, SizeType length, bool copy);
    bool EndObject(SizeType memberCount);
    bool StartArray();
    bool EndArray(SizeType elementCount);
};
\endcode
*/
///////////////////////////////////////////////////////////////////////////////
// BaseReaderHandler

//! Default implementation of Handler.
/*! This can be used as base class of any reader handler.
    \note implements Handler concept
*/
template<typename Encoding = UTF8<>, typename Derived = void>
struct BaseReaderHandler {
    typedef typename Encoding::Ch Ch;

    typedef typename internal::SelectIf<internal::IsSame<Derived, void>, BaseReaderHandler, Derived>::Type Override;

    bool Default() { return true; }
    bool Null() { return static_cast<Override&>(*this).Default(); }
    bool Bool(bool) { return static_cast<Override&>(*this).Default(); }
    bool Int(int) { return static_cast<Override&>(*this).Default(); }
    bool Uint(unsigned) { return static_cast<Override&>(*this).Default(); }
    bool Int64(int64_t) { return static_cast<Override&>(*this).Default(); }
    bool Uint64(uint64_t) { return static_cast<Override&>(*this).Default(); }
    bool Double(double) { return static_cast<Override&>(*this).Default(); }
    /// enabled via kParseNumbersAsStringsFlag, string is not null-terminated (use length)
    bool RawNumber(const Ch* str, SizeType len, bool copy) { return static_cast<Override&>(*this).String(str, len, copy); }
    bool String(const Ch*, SizeType, bool) { return static_cast<Override&>(*this).Default(); }
    bool StartObject() { return static_cast<Override&>(*this).Default(); }
    bool Key(const Ch* str, SizeType len, bool copy) { return static_cast<Override&>(*this).String(str, len, copy); }
    bool EndObject(SizeType) { return static_cast<Override&>(*this).Default(); }
    bool StartArray() { return static_cast<Override&>(*this).Default(); }
    bool EndArray(SizeType) { return static_cast<Override&>(*this).Default(); }
};

///////////////////////////////////////////////////////////////////////////////
// StreamLocalCopy

namespace internal {

template<typename Stream, int = StreamTraits<Stream>::copyOptimization>
class StreamLocalCopy;

//! Do copy optimization.
template<typename Stream>
class StreamLocalCopy<Stream, 1> {
public:
    StreamLocalCopy(Stream& original) : s(original), original_(original) {}
    ~StreamLocalCopy() { original_ = s; }

    Stream s;

private:
    StreamLocalCopy& operator=(const StreamLocalCopy&) /* = delete */;

    Stream& original_;
};

//! Keep reference.
template<typename Stream>
class StreamLocalCopy<Stream, 0> {
public:
    StreamLocalCopy(Stream& original) : s(original) {}

    Stream& s;

private:
    StreamLocalCopy& operator=(const StreamLocalCopy&) /* = delete */;
};

} // namespace internal

///////////////////////////////////////////////////////////////////////////////
// SkipWhitespace

//! Skip the JSON white spaces in a stream.
/*! \param is A input stream for skipping white spaces.
    \note This function has SSE2/SSE4.2 specialization.
*/
template<typename InputStream>
void SkipWhitespace(InputStream& is) {
    internal::StreamLocalCopy<InputStream> copy(is);
    InputStream& s(copy.s);

    typename InputStream::Ch c;
    while ((c = s.Peek()) == ' ' || c == '\n' || c == '\r' || c == '\t')
        s.Take();
}

inline const char* SkipWhitespace(const char* p, const char* end) {
    while (p != end && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t'))
        ++p;
    return p;
}

#ifdef RAPIDJSON_SSE42
//! Skip whitespace with SSE 4.2 pcmpistrm instruction, testing 16 8-byte characters at once.
inline const char *SkipWhitespace_SIMD(const char* p) {
    // Fast return for single non-whitespace
    if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
        ++p;
    else
        return p;

    // 16-byte align to the next boundary
    const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
    while (p != nextAligned)
        if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
            ++p;
        else
            return p;

    // The rest of string using SIMD
    static const char whitespace[16] = " \n\r\t";
    const __m128i w = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespace[0]));

    for (;; p += 16) {
        const __m128i s = _mm_load_si128(reinterpret_cast<const __m128i *>(p));
        const int r = _mm_cmpistri(w, s, _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_LEAST_SIGNIFICANT | _SIDD_NEGATIVE_POLARITY);
        if (r != 16)    // some of characters is non-whitespace
            return p + r;
    }
}

inline const char *SkipWhitespace_SIMD(const char* p, const char* end) {
    // Fast return for single non-whitespace
    if (p != end && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t'))
        ++p;
    else
        return p;

    // The middle of string using SIMD
    static const char whitespace[16] = " \n\r\t";
    const __m128i w = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespace[0]));

    for (; p <= end - 16; p += 16) {
        const __m128i s = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
        const int r = _mm_cmpistri(w, s, _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_LEAST_SIGNIFICANT | _SIDD_NEGATIVE_POLARITY);
        if (r != 16)    // some of characters is non-whitespace
            return p + r;
    }

    return SkipWhitespace(p, end);
}

#elif defined(RAPIDJSON_SSE2)

//! Skip whitespace with SSE2 instructions, testing 16 8-byte characters at once.
inline const char *SkipWhitespace_SIMD(const char* p) {
    // Fast return for single non-whitespace
    if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
        ++p;
    else
        return p;

    // 16-byte align to the next boundary
    const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
    while (p != nextAligned)
        if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
            ++p;
        else
            return p;

    // The rest of string
    #define C16(c) { c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c }
    static const char whitespaces[4][16] = { C16(' '), C16('\n'), C16('\r'), C16('\t') };
    #undef C16

    const __m128i w0 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[0][0]));
    const __m128i w1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[1][0]));
    const __m128i w2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[2][0]));
    const __m128i w3 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[3][0]));

    for (;; p += 16) {
        const __m128i s = _mm_load_si128(reinterpret_cast<const __m128i *>(p));
        __m128i x = _mm_cmpeq_epi8(s, w0);
        x = _mm_or_si128(x, _mm_cmpeq_epi8(s, w1));
        x = _mm_or_si128(x, _mm_cmpeq_epi8(s, w2));
        x = _mm_or_si128(x, _mm_cmpeq_epi8(s, w3));
        unsigned short r = static_cast<unsigned short>(~_mm_movemask_epi8(x));
        if (r != 0) {   // some of characters may be non-whitespace
#ifdef _MSC_VER         // Find the index of first non-whitespace
            unsigned long offset;
            _BitScanForward(&offset, r);
            return p + offset;
#else
            return p + __builtin_ffs(r) - 1;
#endif
        }
    }
}

inline const char *SkipWhitespace_SIMD(const char* p, const char* end) {
    // Fast return for single non-whitespace
    if (p != end && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t'))
        ++p;
    else
        return p;

    // The rest of string
    #define C16(c) { c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c }
    static const char whitespaces[4][16] = { C16(' '), C16('\n'), C16('\r'), C16('\t') };
    #undef C16

    const __m128i w0 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[0][0]));
    const __m128i w1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[1][0]));
    const __m128i w2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[2][0]));
    const __m128i w3 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&whitespaces[3][0]));

    for (; p <= end - 16; p += 16) {
        const __m128i s = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
        __m128i x = _mm_cmpeq_epi8(s, w0);
        x = _mm_or_si128(x, _mm_cmpeq_epi8(s, w1));
        x = _mm_or_si128(x, _mm_cmpeq_epi8(s, w2));
        x = _mm_or_si128(x, _mm_cmpeq_epi8(s, w3));
        unsigned short r = static_cast<unsigned short>(~_mm_movemask_epi8(x));
        if (r != 0) {   // some of characters may be non-whitespace
#ifdef _MSC_VER         // Find the index of first non-whitespace
            unsigned long offset;
            _BitScanForward(&offset, r);
            return p + offset;
#else
            return p + __builtin_ffs(r) - 1;
#endif
        }
    }

    return SkipWhitespace(p, end);
}

#elif defined(RAPIDJSON_NEON)

//! Skip whitespace with ARM Neon instructions, testing 16 8-byte characters at once.
inline const char *SkipWhitespace_SIMD(const char* p) {
    // Fast return for single non-whitespace
    if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
        ++p;
    else
        return p;

    // 16-byte align to the next boundary
    const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
    while (p != nextAligned)
        if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
            ++p;
        else
            return p;

    const uint8x16_t w0 = vmovq_n_u8(' ');
    const uint8x16_t w1 = vmovq_n_u8('\n');
    const uint8x16_t w2 = vmovq_n_u8('\r');
    const uint8x16_t w3 = vmovq_n_u8('\t');

    for (;; p += 16) {
        const uint8x16_t s = vld1q_u8(reinterpret_cast<const uint8_t *>(p));
        uint8x16_t x = vceqq_u8(s, w0);
        x = vorrq_u8(x, vceqq_u8(s, w1));
        x = vorrq_u8(x, vceqq_u8(s, w2));
        x = vorrq_u8(x, vceqq_u8(s, w3));

        x = vmvnq_u8(x);                       // Negate
        x = vrev64q_u8(x);                     // Rev in 64
        uint64_t low = vgetq_lane_u64(vreinterpretq_u64_u8(x), 0);   // extract
        uint64_t high = vgetq_lane_u64(vreinterpretq_u64_u8(x), 1);  // extract

        if (low == 0) {
            if (high != 0) {
                uint32_t lz = internal::clzll(high);
                return p + 8 + (lz >> 3);
            }
        } else {
            uint32_t lz = internal::clzll(low);
            return p + (lz >> 3);
        }
    }
}

inline const char *SkipWhitespace_SIMD(const char* p, const char* end) {
    // Fast return for single non-whitespace
    if (p != end && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t'))
        ++p;
    else
        return p;

    const uint8x16_t w0 = vmovq_n_u8(' ');
    const uint8x16_t w1 = vmovq_n_u8('\n');
    const uint8x16_t w2 = vmovq_n_u8('\r');
    const uint8x16_t w3 = vmovq_n_u8('\t');

    for (; p <= end - 16; p += 16) {
        const uint8x16_t s = vld1q_u8(reinterpret_cast<const uint8_t *>(p));
        uint8x16_t x = vceqq_u8(s, w0);
        x = vorrq_u8(x, vceqq_u8(s, w1));
        x = vorrq_u8(x, vceqq_u8(s, w2));
        x = vorrq_u8(x, vceqq_u8(s, w3));

        x = vmvnq_u8(x);                       // Negate
        x = vrev64q_u8(x);                     // Rev in 64
        uint64_t low = vgetq_lane_u64(vreinterpretq_u64_u8(x), 0);   // extract
        uint64_t high = vgetq_lane_u64(vreinterpretq_u64_u8(x), 1);  // extract

        if (low == 0) {
            if (high != 0) {
                uint32_t lz = internal::clzll(high);
                return p + 8 + (lz >> 3);
            }
        } else {
            uint32_t lz = internal::clzll(low);
            return p + (lz >> 3);
        }
    }

    return SkipWhitespace(p, end);
}

#endif // RAPIDJSON_NEON

#ifdef RAPIDJSON_SIMD
//! Template function specialization for InsituStringStream
template<> inline void SkipWhitespace(InsituStringStream& is) {
    is.src_ = const_cast<char*>(SkipWhitespace_SIMD(is.src_));
}

//! Template function specialization for StringStream
template<> inline void SkipWhitespace(StringStream& is) {
    is.src_ = SkipWhitespace_SIMD(is.src_);
}

template<> inline void SkipWhitespace(EncodedInputStream<UTF8<>, MemoryStream>& is) {
    is.is_.src_ = SkipWhitespace_SIMD(is.is_.src_, is.is_.end_);
}
#endif // RAPIDJSON_SIMD

///////////////////////////////////////////////////////////////////////////////
// GenericReader

//! SAX-style JSON parser. Use \ref Reader for UTF8 encoding and default allocator.
/*! GenericReader parses JSON text from a stream, and send events synchronously to an
    object implementing Handler concept.

    It needs to allocate a stack for storing a single decoded string during
    non-destructive parsing.

    For in-situ parsing, the decoded string is directly written to the source
    text string, no temporary buffer is required.

    A GenericReader object can be reused for parsing multiple JSON text.

    \tparam SourceEncoding Encoding of the input stream.
    \tparam TargetEncoding Encoding of the parse output.
    \tparam StackAllocator Allocator type for stack.
*/
template <typename SourceEncoding, typename TargetEncoding, typename StackAllocator = CrtAllocator>
class GenericReader {
public:
    typedef typename SourceEncoding::Ch Ch; //!< SourceEncoding character type

    //! Constructor.
    /*! \param stackAllocator Optional allocator for allocating stack memory. (Only use for non-destructive parsing)
        \param stackCapacity stack capacity in bytes for storing a single decoded string.  (Only use for non-destructive parsing)
    */
    GenericReader(StackAllocator* stackAllocator = 0, size_t stackCapacity = kDefaultStackCapacity) :
        stack_(stackAllocator, stackCapacity), parseResult_(), state_(IterativeParsingStartState) {}

    //! Parse JSON text.
    /*! \tparam parseFlags Combination of \ref ParseFlag.
        \tparam InputStream Type of input stream, implementing Stream concept.
        \tparam Handler Type of handler, implementing Handler concept.
        \param is Input stream to be parsed.
        \param handler The handler to receive events.
        \return Whether the parsing is successful.
    */
    template <unsigned parseFlags, typename InputStream, typename Handler>
    ParseResult Parse(InputStream& is, Handler& handler) {
        if (parseFlags & kParseIterativeFlag)
            return IterativeParse<parseFlags>(is, handler);

        parseResult_.Clear();

        ClearStackOnExit scope(*this);

        SkipWhitespaceAndComments<parseFlags>(is);
        RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);

        if (RAPIDJSON_UNLIKELY(is.Peek() == '\0')) {
            RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorDocumentEmpty, is.Tell());
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);
        }
        else {
            ParseValue<parseFlags>(is, handler);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);

            if (!(parseFlags & kParseStopWhenDoneFlag)) {
                SkipWhitespaceAndComments<parseFlags>(is);
                RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);

                if (RAPIDJSON_UNLIKELY(is.Peek() != '\0')) {
                    RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorDocumentRootNotSingular, is.Tell());
                    RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);
                }
            }
        }

        return parseResult_;
    }

    //! Parse JSON text (with \ref kParseDefaultFlags)
    /*! \tparam InputStream Type of input stream, implementing Stream concept
        \tparam Handler Type of handler, implementing Handler concept.
        \param is Input stream to be parsed.
        \param handler The handler to receive events.
        \return Whether the parsing is successful.
    */
    template <typename InputStream, typename Handler>
    ParseResult Parse(InputStream& is, Handler& handler) {
        return Parse<kParseDefaultFlags>(is, handler);
    }

    //! Initialize JSON text token-by-token parsing
    /*!
     */
    void IterativeParseInit() {
        parseResult_.Clear();
        state_ = IterativeParsingStartState;
    }

    //! Parse one token from JSON text
    /*! \tparam InputStream Type of input stream, implementing Stream concept
        \tparam Handler Type of handler, implementing Handler concept.
        \param is Input stream to be parsed.
        \param handler The handler to receive events.
        \return Whether the parsing is successful.
     */
    template <unsigned parseFlags, typename InputStream, typename Handler>
    bool IterativeParseNext(InputStream& is, Handler& handler) {
        while (RAPIDJSON_LIKELY(is.Peek() != '\0')) {
            SkipWhitespaceAndComments<parseFlags>(is);

            Token t = Tokenize(is.Peek());
            IterativeParsingState n = Predict(state_, t);
            IterativeParsingState d = Transit<parseFlags>(state_, t, n, is, handler);

            // If we've finished or hit an error...
            if (RAPIDJSON_UNLIKELY(IsIterativeParsingCompleteState(d))) {
                // Report errors.
                if (d == IterativeParsingErrorState) {
                    HandleError(state_, is);
                    return false;
                }

                // Transition to the finish state.
                RAPIDJSON_ASSERT(d == IterativeParsingFinishState);
                state_ = d;

                // If StopWhenDone is not set...
                if (!(parseFlags & kParseStopWhenDoneFlag)) {
                    // ... and extra non-whitespace data is found...
                    SkipWhitespaceAndComments<parseFlags>(is);
                    if (is.Peek() != '\0') {
                        // ... this is considered an error.
                        HandleError(state_, is);
                        return false;
                    }
                }

                // Success! We are done!
                return true;
            }

            // Transition to the new state.
            state_ = d;

            // If we parsed anything other than a delimiter, we invoked the handler, so we can return true now.
            if (!IsIterativeParsingDelimiterState(n))
                return true;
        }

        // We reached the end of file.
        stack_.Clear();

        if (state_ != IterativeParsingFinishState) {
            HandleError(state_, is);
            return false;
        }

        return true;
    }

    //! Check if token-by-token parsing JSON text is complete
    /*! \return Whether the JSON has been fully decoded.
     */
    RAPIDJSON_FORCEINLINE bool IterativeParseComplete() const {
        return IsIterativeParsingCompleteState(state_);
    }

    //! Whether a parse error has occurred in the last parsing.
    bool HasParseError() const { return parseResult_.IsError(); }

    //! Get the \ref ParseErrorCode of last parsing.
    ParseErrorCode GetParseErrorCode() const { return parseResult_.Code(); }

    //! Get the position of last parsing error in input, 0 otherwise.
    size_t GetErrorOffset() const { return parseResult_.Offset(); }

protected:
    void SetParseError(ParseErrorCode code, size_t offset) { parseResult_.Set(code, offset); }

private:
    // Prohibit copy constructor & assignment operator.
    GenericReader(const GenericReader&);
    GenericReader& operator=(const GenericReader&);

    void ClearStack() { stack_.Clear(); }

    // clear stack on any exit from ParseStream, e.g. due to exception
    struct ClearStackOnExit {
        explicit ClearStackOnExit(GenericReader& r) : r_(r) {}
        ~ClearStackOnExit() { r_.ClearStack(); }
    private:
        GenericReader& r_;
        ClearStackOnExit(const ClearStackOnExit&);
        ClearStackOnExit& operator=(const ClearStackOnExit&);
    };

    template<unsigned parseFlags, typename InputStream>
    void SkipWhitespaceAndComments(InputStream& is) {
        SkipWhitespace(is);

        if (parseFlags & kParseCommentsFlag) {
            while (RAPIDJSON_UNLIKELY(Consume(is, '/'))) {
                if (Consume(is, '*')) {
                    while (true) {
                        if (RAPIDJSON_UNLIKELY(is.Peek() == '\0'))
                            RAPIDJSON_PARSE_ERROR(kParseErrorUnspecificSyntaxError, is.Tell());
                        else if (Consume(is, '*')) {
                            if (Consume(is, '/'))
                                break;
                        }
                        else
                            is.Take();
                    }
                }
                else if (RAPIDJSON_LIKELY(Consume(is, '/')))
                    while (is.Peek() != '\0' && is.Take() != '\n') {}
                else
                    RAPIDJSON_PARSE_ERROR(kParseErrorUnspecificSyntaxError, is.Tell());

                SkipWhitespace(is);
            }
        }
    }

    // Parse object: { string : value, ... }
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseObject(InputStream& is, Handler& handler) {
        RAPIDJSON_ASSERT(is.Peek() == '{');
        is.Take();  // Skip '{'

        if (RAPIDJSON_UNLIKELY(!handler.StartObject()))
            RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());

        SkipWhitespaceAndComments<parseFlags>(is);
        RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

        if (Consume(is, '}')) {
            if (RAPIDJSON_UNLIKELY(!handler.EndObject(0)))  // empty object
                RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
            return;
        }

        for (SizeType memberCount = 0;;) {
            if (RAPIDJSON_UNLIKELY(is.Peek() != '"'))
                RAPIDJSON_PARSE_ERROR(kParseErrorObjectMissName, is.Tell());

            ParseString<parseFlags>(is, handler, true);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            SkipWhitespaceAndComments<parseFlags>(is);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            if (RAPIDJSON_UNLIKELY(!Consume(is, ':')))
                RAPIDJSON_PARSE_ERROR(kParseErrorObjectMissColon, is.Tell());

            SkipWhitespaceAndComments<parseFlags>(is);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            ParseValue<parseFlags>(is, handler);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            SkipWhitespaceAndComments<parseFlags>(is);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            ++memberCount;

            switch (is.Peek()) {
                case ',':
                    is.Take();
                    SkipWhitespaceAndComments<parseFlags>(is);
                    RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;
                    break;
                case '}':
                    is.Take();
                    if (RAPIDJSON_UNLIKELY(!handler.EndObject(memberCount)))
                        RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
                    return;
                default:
                    RAPIDJSON_PARSE_ERROR(kParseErrorObjectMissCommaOrCurlyBracket, is.Tell()); break; // This useless break is only for making warning and coverage happy
            }

            if (parseFlags & kParseTrailingCommasFlag) {
                if (is.Peek() == '}') {
                    if (RAPIDJSON_UNLIKELY(!handler.EndObject(memberCount)))
                        RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
                    is.Take();
                    return;
                }
            }
        }
    }

    // Parse array: [ value, ... ]
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseArray(InputStream& is, Handler& handler) {
        RAPIDJSON_ASSERT(is.Peek() == '[');
        is.Take();  // Skip '['

        if (RAPIDJSON_UNLIKELY(!handler.StartArray()))
            RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());

        SkipWhitespaceAndComments<parseFlags>(is);
        RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

        if (Consume(is, ']')) {
            if (RAPIDJSON_UNLIKELY(!handler.EndArray(0))) // empty array
                RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
            return;
        }

        for (SizeType elementCount = 0;;) {
            ParseValue<parseFlags>(is, handler);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            ++elementCount;
            SkipWhitespaceAndComments<parseFlags>(is);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;

            if (Consume(is, ',')) {
                SkipWhitespaceAndComments<parseFlags>(is);
                RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;
            }
            else if (Consume(is, ']')) {
                if (RAPIDJSON_UNLIKELY(!handler.EndArray(elementCount)))
                    RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
                return;
            }
            else
                RAPIDJSON_PARSE_ERROR(kParseErrorArrayMissCommaOrSquareBracket, is.Tell());

            if (parseFlags & kParseTrailingCommasFlag) {
                if (is.Peek() == ']') {
                    if (RAPIDJSON_UNLIKELY(!handler.EndArray(elementCount)))
                        RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
                    is.Take();
                    return;
                }
            }
        }
    }

    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseNull(InputStream& is, Handler& handler) {
        RAPIDJSON_ASSERT(is.Peek() == 'n');
        is.Take();

        if (RAPIDJSON_LIKELY(Consume(is, 'u') && Consume(is, 'l') && Consume(is, 'l'))) {
            if (RAPIDJSON_UNLIKELY(!handler.Null()))
                RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
        }
        else
            RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, is.Tell());
    }

    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseTrue(InputStream& is, Handler& handler) {
        RAPIDJSON_ASSERT(is.Peek() == 't');
        is.Take();

        if (RAPIDJSON_LIKELY(Consume(is, 'r') && Consume(is, 'u') && Consume(is, 'e'))) {
            if (RAPIDJSON_UNLIKELY(!handler.Bool(true)))
                RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
        }
        else
            RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, is.Tell());
    }

    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseFalse(InputStream& is, Handler& handler) {
        RAPIDJSON_ASSERT(is.Peek() == 'f');
        is.Take();

        if (RAPIDJSON_LIKELY(Consume(is, 'a') && Consume(is, 'l') && Consume(is, 's') && Consume(is, 'e'))) {
            if (RAPIDJSON_UNLIKELY(!handler.Bool(false)))
                RAPIDJSON_PARSE_ERROR(kParseErrorTermination, is.Tell());
        }
        else
            RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, is.Tell());
    }

    template<typename InputStream>
    RAPIDJSON_FORCEINLINE static bool Consume(InputStream& is, typename InputStream::Ch expect) {
        if (RAPIDJSON_LIKELY(is.Peek() == expect)) {
            is.Take();
            return true;
        }
        else
            return false;
    }

    // Helper function to parse four hexadecimal digits in \uXXXX in ParseString().
    template<typename InputStream>
    unsigned ParseHex4(InputStream& is, size_t escapeOffset) {
        unsigned codepoint = 0;
        for (int i = 0; i < 4; i++) {
            Ch c = is.Peek();
            codepoint <<= 4;
            codepoint += static_cast<unsigned>(c);
            if (c >= '0' && c <= '9')
                codepoint -= '0';
            else if (c >= 'A' && c <= 'F')
                codepoint -= 'A' - 10;
            else if (c >= 'a' && c <= 'f')
                codepoint -= 'a' - 10;
            else {
                RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorStringUnicodeEscapeInvalidHex, escapeOffset);
                RAPIDJSON_PARSE_ERROR_EARLY_RETURN(0);
            }
            is.Take();
        }
        return codepoint;
    }

    template <typename CharType>
    class StackStream {
    public:
        typedef CharType Ch;

        StackStream(internal::Stack<StackAllocator>& stack) : stack_(stack), length_(0) {}
        RAPIDJSON_FORCEINLINE void Put(Ch c) {
            *stack_.template Push<Ch>() = c;
            ++length_;
        }

        RAPIDJSON_FORCEINLINE void* Push(SizeType count) {
            length_ += count;
            return stack_.template Push<Ch>(count);
        }

        size_t Length() const { return length_; }

        Ch* Pop() {
            return stack_.template Pop<Ch>(length_);
        }

    private:
        StackStream(const StackStream&);
        StackStream& operator=(const StackStream&);

        internal::Stack<StackAllocator>& stack_;
        SizeType length_;
    };

    // Parse string and generate String event. Different code paths for kParseInsituFlag.
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseString(InputStream& is, Handler& handler, bool isKey = false) {
        internal::StreamLocalCopy<InputStream> copy(is);
        InputStream& s(copy.s);

        RAPIDJSON_ASSERT(s.Peek() == '\"');
        s.Take();  // Skip '\"'

        bool success = false;
        if (parseFlags & kParseInsituFlag) {
            typename InputStream::Ch *head = s.PutBegin();
            ParseStringToStream<parseFlags, SourceEncoding, SourceEncoding>(s, s);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;
            size_t length = s.PutEnd(head) - 1;
            RAPIDJSON_ASSERT(length <= 0xFFFFFFFF);
            const typename TargetEncoding::Ch* const str = reinterpret_cast<typename TargetEncoding::Ch*>(head);
            success = (isKey ? handler.Key(str, SizeType(length), false) : handler.String(str, SizeType(length), false));
        }
        else {
            StackStream<typename TargetEncoding::Ch> stackStream(stack_);
            ParseStringToStream<parseFlags, SourceEncoding, TargetEncoding>(s, stackStream);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;
            SizeType length = static_cast<SizeType>(stackStream.Length()) - 1;
            const typename TargetEncoding::Ch* const str = stackStream.Pop();
            success = (isKey ? handler.Key(str, length, true) : handler.String(str, length, true));
        }
        if (RAPIDJSON_UNLIKELY(!success))
            RAPIDJSON_PARSE_ERROR(kParseErrorTermination, s.Tell());
    }

    // Parse string to an output is
    // This function handles the prefix/suffix double quotes, escaping, and optional encoding validation.
    template<unsigned parseFlags, typename SEncoding, typename TEncoding, typename InputStream, typename OutputStream>
    RAPIDJSON_FORCEINLINE void ParseStringToStream(InputStream& is, OutputStream& os) {
//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
#define Z16 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        static const char escape[256] = {
            Z16, Z16, 0, 0,'\"', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '/',
            Z16, Z16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'\\', 0, 0, 0,
            0, 0,'\b', 0, 0, 0,'\f', 0, 0, 0, 0, 0, 0, 0,'\n', 0,
            0, 0,'\r', 0,'\t', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            Z16, Z16, Z16, Z16, Z16, Z16, Z16, Z16
        };
#undef Z16
//!@endcond

        for (;;) {
            // Scan and copy string before "\\\"" or < 0x20. This is an optional optimzation.
            if (!(parseFlags & kParseValidateEncodingFlag))
                ScanCopyUnescapedString(is, os);

            Ch c = is.Peek();
            if (RAPIDJSON_UNLIKELY(c == '\\')) {    // Escape
                size_t escapeOffset = is.Tell();    // For invalid escaping, report the initial '\\' as error offset
                is.Take();
                Ch e = is.Peek();
                if ((sizeof(Ch) == 1 || unsigned(e) < 256) && RAPIDJSON_LIKELY(escape[static_cast<unsigned char>(e)])) {
                    is.Take();
                    os.Put(static_cast<typename TEncoding::Ch>(escape[static_cast<unsigned char>(e)]));
                }
                else if ((parseFlags & kParseEscapedApostropheFlag) && RAPIDJSON_LIKELY(e == '\'')) { // Allow escaped apostrophe
                    is.Take();
                    os.Put('\'');
                }
                else if (RAPIDJSON_LIKELY(e == 'u')) {    // Unicode
                    is.Take();
                    unsigned codepoint = ParseHex4(is, escapeOffset);
                    RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;
                    if (RAPIDJSON_UNLIKELY(codepoint >= 0xD800 && codepoint <= 0xDFFF)) {
                        // high surrogate, check if followed by valid low surrogate
                        if (RAPIDJSON_LIKELY(codepoint <= 0xDBFF)) {
                            // Handle UTF-16 surrogate pair
                            if (RAPIDJSON_UNLIKELY(!Consume(is, '\\') || !Consume(is, 'u')))
                                RAPIDJSON_PARSE_ERROR(kParseErrorStringUnicodeSurrogateInvalid, escapeOffset);
                            unsigned codepoint2 = ParseHex4(is, escapeOffset);
                            RAPIDJSON_PARSE_ERROR_EARLY_RETURN_VOID;
                            if (RAPIDJSON_UNLIKELY(codepoint2 < 0xDC00 || codepoint2 > 0xDFFF))
                                RAPIDJSON_PARSE_ERROR(kParseErrorStringUnicodeSurrogateInvalid, escapeOffset);
                            codepoint = (((codepoint - 0xD800) << 10) | (codepoint2 - 0xDC00)) + 0x10000;
                        }
                        // single low surrogate
                        else
                        {
                            RAPIDJSON_PARSE_ERROR(kParseErrorStringUnicodeSurrogateInvalid, escapeOffset);
                        }
                    }
                    TEncoding::Encode(os, codepoint);
                }
                else
                    RAPIDJSON_PARSE_ERROR(kParseErrorStringEscapeInvalid, escapeOffset);
            }
            else if (RAPIDJSON_UNLIKELY(c == '"')) {    // Closing double quote
                is.Take();
                os.Put('\0');   // null-terminate the string
                return;
            }
            else if (RAPIDJSON_UNLIKELY(static_cast<unsigned>(c) < 0x20)) { // RFC 4627: unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
                if (c == '\0')
                    RAPIDJSON_PARSE_ERROR(kParseErrorStringMissQuotationMark, is.Tell());
                else
                    RAPIDJSON_PARSE_ERROR(kParseErrorStringInvalidEncoding, is.Tell());
            }
            else {
                size_t offset = is.Tell();
                if (RAPIDJSON_UNLIKELY((parseFlags & kParseValidateEncodingFlag ?
                    !Transcoder<SEncoding, TEncoding>::Validate(is, os) :
                    !Transcoder<SEncoding, TEncoding>::Transcode(is, os))))
                    RAPIDJSON_PARSE_ERROR(kParseErrorStringInvalidEncoding, offset);
            }
        }
    }

    template<typename InputStream, typename OutputStream>
    static RAPIDJSON_FORCEINLINE void ScanCopyUnescapedString(InputStream&, OutputStream&) {
            // Do nothing for generic version
    }

#if defined(RAPIDJSON_SSE2) || defined(RAPIDJSON_SSE42)
    // StringStream -> StackStream<char>
    static RAPIDJSON_FORCEINLINE void ScanCopyUnescapedString(StringStream& is, StackStream<char>& os) {
        const char* p = is.src_;

        // Scan one by one until alignment (unaligned load may cross page boundary and cause crash)
        const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
        while (p != nextAligned)
            if (RAPIDJSON_UNLIKELY(*p == '\"') || RAPIDJSON_UNLIKELY(*p == '\\') || RAPIDJSON_UNLIKELY(static_cast<unsigned>(*p) < 0x20)) {
                is.src_ = p;
                return;
            }
            else
                os.Put(*p++);

        // The rest of string using SIMD
        static const char dquote[16] = { '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"' };
        static const char bslash[16] = { '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\' };
        static const char space[16]  = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
        const __m128i dq = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&dquote[0]));
        const __m128i bs = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&bslash[0]));
        const __m128i sp = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&space[0]));

        for (;; p += 16) {
            const __m128i s = _mm_load_si128(reinterpret_cast<const __m128i *>(p));
            const __m128i t1 = _mm_cmpeq_epi8(s, dq);
            const __m128i t2 = _mm_cmpeq_epi8(s, bs);
            const __m128i t3 = _mm_cmpeq_epi8(_mm_max_epu8(s, sp), sp); // s < 0x20 <=> max(s, 0x1F) == 0x1F
            const __m128i x = _mm_or_si128(_mm_or_si128(t1, t2), t3);
            unsigned short r = static_cast<unsigned short>(_mm_movemask_epi8(x));
            if (RAPIDJSON_UNLIKELY(r != 0)) {   // some of characters is escaped
                SizeType length;
    #ifdef _MSC_VER         // Find the index of first escaped
                unsigned long offset;
                _BitScanForward(&offset, r);
                length = offset;
    #else
                length = static_cast<SizeType>(__builtin_ffs(r) - 1);
    #endif
                if (length != 0) {
                    char* q = reinterpret_cast<char*>(os.Push(length));
                    for (size_t i = 0; i < length; i++)
                        q[i] = p[i];

                    p += length;
                }
                break;
            }
            _mm_storeu_si128(reinterpret_cast<__m128i *>(os.Push(16)), s);
        }

        is.src_ = p;
    }

    // InsituStringStream -> InsituStringStream
    static RAPIDJSON_FORCEINLINE void ScanCopyUnescapedString(InsituStringStream& is, InsituStringStream& os) {
        RAPIDJSON_ASSERT(&is == &os);
        (void)os;

        if (is.src_ == is.dst_) {
            SkipUnescapedString(is);
            return;
        }

        char* p = is.src_;
        char *q = is.dst_;

        // Scan one by one until alignment (unaligned load may cross page boundary and cause crash)
        const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
        while (p != nextAligned)
            if (RAPIDJSON_UNLIKELY(*p == '\"') || RAPIDJSON_UNLIKELY(*p == '\\') || RAPIDJSON_UNLIKELY(static_cast<unsigned>(*p) < 0x20)) {
                is.src_ = p;
                is.dst_ = q;
                return;
            }
            else
                *q++ = *p++;

        // The rest of string using SIMD
        static const char dquote[16] = { '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"' };
        static const char bslash[16] = { '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\' };
        static const char space[16] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
        const __m128i dq = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&dquote[0]));
        const __m128i bs = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&bslash[0]));
        const __m128i sp = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&space[0]));

        for (;; p += 16, q += 16) {
            const __m128i s = _mm_load_si128(reinterpret_cast<const __m128i *>(p));
            const __m128i t1 = _mm_cmpeq_epi8(s, dq);
            const __m128i t2 = _mm_cmpeq_epi8(s, bs);
            const __m128i t3 = _mm_cmpeq_epi8(_mm_max_epu8(s, sp), sp); // s < 0x20 <=> max(s, 0x1F) == 0x1F
            const __m128i x = _mm_or_si128(_mm_or_si128(t1, t2), t3);
            unsigned short r = static_cast<unsigned short>(_mm_movemask_epi8(x));
            if (RAPIDJSON_UNLIKELY(r != 0)) {   // some of characters is escaped
                size_t length;
#ifdef _MSC_VER         // Find the index of first escaped
                unsigned long offset;
                _BitScanForward(&offset, r);
                length = offset;
#else
                length = static_cast<size_t>(__builtin_ffs(r) - 1);
#endif
                for (const char* pend = p + length; p != pend; )
                    *q++ = *p++;
                break;
            }
            _mm_storeu_si128(reinterpret_cast<__m128i *>(q), s);
        }

        is.src_ = p;
        is.dst_ = q;
    }

    // When read/write pointers are the same for insitu stream, just skip unescaped characters
    static RAPIDJSON_FORCEINLINE void SkipUnescapedString(InsituStringStream& is) {
        RAPIDJSON_ASSERT(is.src_ == is.dst_);
        char* p = is.src_;

        // Scan one by one until alignment (unaligned load may cross page boundary and cause crash)
        const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
        for (; p != nextAligned; p++)
            if (RAPIDJSON_UNLIKELY(*p == '\"') || RAPIDJSON_UNLIKELY(*p == '\\') || RAPIDJSON_UNLIKELY(static_cast<unsigned>(*p) < 0x20)) {
                is.src_ = is.dst_ = p;
                return;
            }

        // The rest of string using SIMD
        static const char dquote[16] = { '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"', '\"' };
        static const char bslash[16] = { '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\', '\\' };
        static const char space[16] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
        const __m128i dq = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&dquote[0]));
        const __m128i bs = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&bslash[0]));
        const __m128i sp = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&space[0]));

        for (;; p += 16) {
            const __m128i s = _mm_load_si128(reinterpret_cast<const __m128i *>(p));
            const __m128i t1 = _mm_cmpeq_epi8(s, dq);
            const __m128i t2 = _mm_cmpeq_epi8(s, bs);
            const __m128i t3 = _mm_cmpeq_epi8(_mm_max_epu8(s, sp), sp); // s < 0x20 <=> max(s, 0x1F) == 0x1F
            const __m128i x = _mm_or_si128(_mm_or_si128(t1, t2), t3);
            unsigned short r = static_cast<unsigned short>(_mm_movemask_epi8(x));
            if (RAPIDJSON_UNLIKELY(r != 0)) {   // some of characters is escaped
                size_t length;
#ifdef _MSC_VER         // Find the index of first escaped
                unsigned long offset;
                _BitScanForward(&offset, r);
                length = offset;
#else
                length = static_cast<size_t>(__builtin_ffs(r) - 1);
#endif
                p += length;
                break;
            }
        }

        is.src_ = is.dst_ = p;
    }
#elif defined(RAPIDJSON_NEON)
    // StringStream -> StackStream<char>
    static RAPIDJSON_FORCEINLINE void ScanCopyUnescapedString(StringStream& is, StackStream<char>& os) {
        const char* p = is.src_;

        // Scan one by one until alignment (unaligned load may cross page boundary and cause crash)
        const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
        while (p != nextAligned)
            if (RAPIDJSON_UNLIKELY(*p == '\"') || RAPIDJSON_UNLIKELY(*p == '\\') || RAPIDJSON_UNLIKELY(static_cast<unsigned>(*p) < 0x20)) {
                is.src_ = p;
                return;
            }
            else
                os.Put(*p++);

        // The rest of string using SIMD
        const uint8x16_t s0 = vmovq_n_u8('"');
        const uint8x16_t s1 = vmovq_n_u8('\\');
        const uint8x16_t s2 = vmovq_n_u8('\b');
        const uint8x16_t s3 = vmovq_n_u8(32);

        for (;; p += 16) {
            const uint8x16_t s = vld1q_u8(reinterpret_cast<const uint8_t *>(p));
            uint8x16_t x = vceqq_u8(s, s0);
            x = vorrq_u8(x, vceqq_u8(s, s1));
            x = vorrq_u8(x, vceqq_u8(s, s2));
            x = vorrq_u8(x, vcltq_u8(s, s3));

            x = vrev64q_u8(x);                     // Rev in 64
            uint64_t low = vgetq_lane_u64(vreinterpretq_u64_u8(x), 0);   // extract
            uint64_t high = vgetq_lane_u64(vreinterpretq_u64_u8(x), 1);  // extract

            SizeType length = 0;
            bool escaped = false;
            if (low == 0) {
                if (high != 0) {
                    uint32_t lz = internal::clzll(high);
                    length = 8 + (lz >> 3);
                    escaped = true;
                }
            } else {
                uint32_t lz = internal::clzll(low);
                length = lz >> 3;
                escaped = true;
            }
            if (RAPIDJSON_UNLIKELY(escaped)) {   // some of characters is escaped
                if (length != 0) {
                    char* q = reinterpret_cast<char*>(os.Push(length));
                    for (size_t i = 0; i < length; i++)
                        q[i] = p[i];

                    p += length;
                }
                break;
            }
            vst1q_u8(reinterpret_cast<uint8_t *>(os.Push(16)), s);
        }

        is.src_ = p;
    }

    // InsituStringStream -> InsituStringStream
    static RAPIDJSON_FORCEINLINE void ScanCopyUnescapedString(InsituStringStream& is, InsituStringStream& os) {
        RAPIDJSON_ASSERT(&is == &os);
        (void)os;

        if (is.src_ == is.dst_) {
            SkipUnescapedString(is);
            return;
        }

        char* p = is.src_;
        char *q = is.dst_;

        // Scan one by one until alignment (unaligned load may cross page boundary and cause crash)
        const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
        while (p != nextAligned)
            if (RAPIDJSON_UNLIKELY(*p == '\"') || RAPIDJSON_UNLIKELY(*p == '\\') || RAPIDJSON_UNLIKELY(static_cast<unsigned>(*p) < 0x20)) {
                is.src_ = p;
                is.dst_ = q;
                return;
            }
            else
                *q++ = *p++;

        // The rest of string using SIMD
        const uint8x16_t s0 = vmovq_n_u8('"');
        const uint8x16_t s1 = vmovq_n_u8('\\');
        const uint8x16_t s2 = vmovq_n_u8('\b');
        const uint8x16_t s3 = vmovq_n_u8(32);

        for (;; p += 16, q += 16) {
            const uint8x16_t s = vld1q_u8(reinterpret_cast<uint8_t *>(p));
            uint8x16_t x = vceqq_u8(s, s0);
            x = vorrq_u8(x, vceqq_u8(s, s1));
            x = vorrq_u8(x, vceqq_u8(s, s2));
            x = vorrq_u8(x, vcltq_u8(s, s3));

            x = vrev64q_u8(x);                     // Rev in 64
            uint64_t low = vgetq_lane_u64(vreinterpretq_u64_u8(x), 0);   // extract
            uint64_t high = vgetq_lane_u64(vreinterpretq_u64_u8(x), 1);  // extract

            SizeType length = 0;
            bool escaped = false;
            if (low == 0) {
                if (high != 0) {
                    uint32_t lz = internal::clzll(high);
                    length = 8 + (lz >> 3);
                    escaped = true;
                }
            } else {
                uint32_t lz = internal::clzll(low);
                length = lz >> 3;
                escaped = true;
            }
            if (RAPIDJSON_UNLIKELY(escaped)) {   // some of characters is escaped
                for (const char* pend = p + length; p != pend; ) {
                    *q++ = *p++;
                }
                break;
            }
            vst1q_u8(reinterpret_cast<uint8_t *>(q), s);
        }

        is.src_ = p;
        is.dst_ = q;
    }

    // When read/write pointers are the same for insitu stream, just skip unescaped characters
    static RAPIDJSON_FORCEINLINE void SkipUnescapedString(InsituStringStream& is) {
        RAPIDJSON_ASSERT(is.src_ == is.dst_);
        char* p = is.src_;

        // Scan one by one until alignment (unaligned load may cross page boundary and cause crash)
        const char* nextAligned = reinterpret_cast<const char*>((reinterpret_cast<size_t>(p) + 15) & static_cast<size_t>(~15));
        for (; p != nextAligned; p++)
            if (RAPIDJSON_UNLIKELY(*p == '\"') || RAPIDJSON_UNLIKELY(*p == '\\') || RAPIDJSON_UNLIKELY(static_cast<unsigned>(*p) < 0x20)) {
                is.src_ = is.dst_ = p;
                return;
            }

        // The rest of string using SIMD
        const uint8x16_t s0 = vmovq_n_u8('"');
        const uint8x16_t s1 = vmovq_n_u8('\\');
        const uint8x16_t s2 = vmovq_n_u8('\b');
        const uint8x16_t s3 = vmovq_n_u8(32);

        for (;; p += 16) {
            const uint8x16_t s = vld1q_u8(reinterpret_cast<uint8_t *>(p));
            uint8x16_t x = vceqq_u8(s, s0);
            x = vorrq_u8(x, vceqq_u8(s, s1));
            x = vorrq_u8(x, vceqq_u8(s, s2));
            x = vorrq_u8(x, vcltq_u8(s, s3));

            x = vrev64q_u8(x);                     // Rev in 64
            uint64_t low = vgetq_lane_u64(vreinterpretq_u64_u8(x), 0);   // extract
            uint64_t high = vgetq_lane_u64(vreinterpretq_u64_u8(x), 1);  // extract

            if (low == 0) {
                if (high != 0) {
                    uint32_t lz = internal::clzll(high);
                    p += 8 + (lz >> 3);
                    break;
                }
            } else {
                uint32_t lz = internal::clzll(low);
                p += lz >> 3;
                break;
            }
        }

        is.src_ = is.dst_ = p;
    }
#endif // RAPIDJSON_NEON

    template<typename InputStream, typename StackCharacter, bool backup, bool pushOnTake>
    class NumberStream;

    template<typename InputStream, typename StackCharacter>
    class NumberStream<InputStream, StackCharacter, false, false> {
    public:
        typedef typename InputStream::Ch Ch;

        NumberStream(GenericReader& reader, InputStream& s) : is(s) { (void)reader;  }

        RAPIDJSON_FORCEINLINE Ch Peek() const { return is.Peek(); }
        RAPIDJSON_FORCEINLINE Ch TakePush() { return is.Take(); }
        RAPIDJSON_FORCEINLINE Ch Take() { return is.Take(); }
        RAPIDJSON_FORCEINLINE void Push(char) {}

        size_t Tell() { return is.Tell(); }
        size_t Length() { return 0; }
        const StackCharacter* Pop() { return 0; }

    protected:
        NumberStream& operator=(const NumberStream&);

        InputStream& is;
    };

    template<typename InputStream, typename StackCharacter>
    class NumberStream<InputStream, StackCharacter, true, false> : public NumberStream<InputStream, StackCharacter, false, false> {
        typedef NumberStream<InputStream, StackCharacter, false, false> Base;
    public:
        NumberStream(GenericReader& reader, InputStream& s) : Base(reader, s), stackStream(reader.stack_) {}

        RAPIDJSON_FORCEINLINE Ch TakePush() {
            stackStream.Put(static_cast<StackCharacter>(Base::is.Peek()));
            return Base::is.Take();
        }

        RAPIDJSON_FORCEINLINE void Push(StackCharacter c) {
            stackStream.Put(c);
        }

        size_t Length() { return stackStream.Length(); }

        const StackCharacter* Pop() {
            stackStream.Put('\0');
            return stackStream.Pop();
        }

    private:
        StackStream<StackCharacter> stackStream;
    };

    template<typename InputStream, typename StackCharacter>
    class NumberStream<InputStream, StackCharacter, true, true> : public NumberStream<InputStream, StackCharacter, true, false> {
        typedef NumberStream<InputStream, StackCharacter, true, false> Base;
    public:
        NumberStream(GenericReader& reader, InputStream& s) : Base(reader, s) {}

        RAPIDJSON_FORCEINLINE Ch Take() { return Base::TakePush(); }
    };

    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseNumber(InputStream& is, Handler& handler) {
        typedef typename internal::SelectIf<internal::BoolType<(parseFlags & kParseNumbersAsStringsFlag) != 0>, typename TargetEncoding::Ch, char>::Type NumberCharacter;

        internal::StreamLocalCopy<InputStream> copy(is);
        NumberStream<InputStream, NumberCharacter,
            ((parseFlags & kParseNumbersAsStringsFlag) != 0) ?
                ((parseFlags & kParseInsituFlag) == 0) :
                ((parseFlags & kParseFullPrecisionFlag) != 0),
            (parseFlags & kParseNumbersAsStringsFlag) != 0 &&
                (parseFlags & kParseInsituFlag) == 0> s(*this, copy.s);

        size_t startOffset = s.Tell();
        double d = 0.0;
        bool useNanOrInf = false;

        // Parse minus
        bool minus = Consume(s, '-');

        // Parse int: zero / ( digit1-9 *DIGIT )
        unsigned i = 0;
        uint64_t i64 = 0;
        bool use64bit = false;
        int significandDigit = 0;
        if (RAPIDJSON_UNLIKELY(s.Peek() == '0')) {
            i = 0;
            s.TakePush();
        }
        else if (RAPIDJSON_LIKELY(s.Peek() >= '1' && s.Peek() <= '9')) {
            i = static_cast<unsigned>(s.TakePush() - '0');

            if (minus)
                while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                    if (RAPIDJSON_UNLIKELY(i >= 214748364)) { // 2^31 = 2147483648
                        if (RAPIDJSON_LIKELY(i != 214748364 || s.Peek() > '8')) {
                            i64 = i;
                            use64bit = true;
                            break;
                        }
                    }
                    i = i * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
            else
                while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                    if (RAPIDJSON_UNLIKELY(i >= 429496729)) { // 2^32 - 1 = 4294967295
                        if (RAPIDJSON_LIKELY(i != 429496729 || s.Peek() > '5')) {
                            i64 = i;
                            use64bit = true;
                            break;
                        }
                    }
                    i = i * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
        }
        // Parse NaN or Infinity here
        else if ((parseFlags & kParseNanAndInfFlag) && RAPIDJSON_LIKELY((s.Peek() == 'I' || s.Peek() == 'N'))) {
            if (Consume(s, 'N')) {
                if (Consume(s, 'a') && Consume(s, 'N')) {
                    d = std::numeric_limits<double>::quiet_NaN();
                    useNanOrInf = true;
                }
            }
            else if (RAPIDJSON_LIKELY(Consume(s, 'I'))) {
                if (Consume(s, 'n') && Consume(s, 'f')) {
                    d = (minus ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity());
                    useNanOrInf = true;

                    if (RAPIDJSON_UNLIKELY(s.Peek() == 'i' && !(Consume(s, 'i') && Consume(s, 'n')
                                                                && Consume(s, 'i') && Consume(s, 't') && Consume(s, 'y')))) {
                        RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, s.Tell());
                    }
                }
            }

            if (RAPIDJSON_UNLIKELY(!useNanOrInf)) {
                RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, s.Tell());
            }
        }
        else
            RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, s.Tell());

        // Parse 64bit int
        bool useDouble = false;
        if (use64bit) {
            if (minus)
                while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                     if (RAPIDJSON_UNLIKELY(i64 >= RAPIDJSON_UINT64_C2(0x0CCCCCCC, 0xCCCCCCCC))) // 2^63 = 9223372036854775808
                        if (RAPIDJSON_LIKELY(i64 != RAPIDJSON_UINT64_C2(0x0CCCCCCC, 0xCCCCCCCC) || s.Peek() > '8')) {
                            d = static_cast<double>(i64);
                            useDouble = true;
                            break;
                        }
                    i64 = i64 * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
            else
                while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                    if (RAPIDJSON_UNLIKELY(i64 >= RAPIDJSON_UINT64_C2(0x19999999, 0x99999999))) // 2^64 - 1 = 18446744073709551615
                        if (RAPIDJSON_LIKELY(i64 != RAPIDJSON_UINT64_C2(0x19999999, 0x99999999) || s.Peek() > '5')) {
                            d = static_cast<double>(i64);
                            useDouble = true;
                            break;
                        }
                    i64 = i64 * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
        }

        // Force double for big integer
        if (useDouble) {
            while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                d = d * 10 + (s.TakePush() - '0');
            }
        }

        // Parse frac = decimal-point 1*DIGIT
        int expFrac = 0;
        size_t decimalPosition;
        if (!useNanOrInf && Consume(s, '.')) {
            decimalPosition = s.Length();

            if (RAPIDJSON_UNLIKELY(!(s.Peek() >= '0' && s.Peek() <= '9')))
                RAPIDJSON_PARSE_ERROR(kParseErrorNumberMissFraction, s.Tell());

            if (!useDouble) {
#if RAPIDJSON_64BIT
                // Use i64 to store significand in 64-bit architecture
                if (!use64bit)
                    i64 = i;

                while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                    if (i64 > RAPIDJSON_UINT64_C2(0x1FFFFF, 0xFFFFFFFF)) // 2^53 - 1 for fast path
                        break;
                    else {
                        i64 = i64 * 10 + static_cast<unsigned>(s.TakePush() - '0');
                        --expFrac;
                        if (i64 != 0)
                            significandDigit++;
                    }
                }

                d = static_cast<double>(i64);
#else
                // Use double to store significand in 32-bit architecture
                d = static_cast<double>(use64bit ? i64 : i);
#endif
                useDouble = true;
            }

            while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                if (significandDigit < 17) {
                    d = d * 10.0 + (s.TakePush() - '0');
                    --expFrac;
                    if (RAPIDJSON_LIKELY(d > 0.0))
                        significandDigit++;
                }
                else
                    s.TakePush();
            }
        }
        else
            decimalPosition = s.Length(); // decimal position at the end of integer.

        // Parse exp = e [ minus / plus ] 1*DIGIT
        int exp = 0;
        if (!useNanOrInf && (Consume(s, 'e') || Consume(s, 'E'))) {
            if (!useDouble) {
                d = static_cast<double>(use64bit ? i64 : i);
                useDouble = true;
            }

            bool expMinus = false;
            if (Consume(s, '+'))
                ;
            else if (Consume(s, '-'))
                expMinus = true;

            if (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                exp = static_cast<int>(s.Take() - '0');
                if (expMinus) {
                    // (exp + expFrac) must not underflow int => we're detecting when -exp gets
                    // dangerously close to INT_MIN (a pessimistic next digit 9 would push it into
                    // underflow territory):
                    //
                    //        -(exp * 10 + 9) + expFrac >= INT_MIN
                    //   <=>  exp <= (expFrac - INT_MIN - 9) / 10
                    RAPIDJSON_ASSERT(expFrac <= 0);
                    int maxExp = (expFrac + 2147483639) / 10;

                    while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                        exp = exp * 10 + static_cast<int>(s.Take() - '0');
                        if (RAPIDJSON_UNLIKELY(exp > maxExp)) {
                            while (RAPIDJSON_UNLIKELY(s.Peek() >= '0' && s.Peek() <= '9'))  // Consume the rest of exponent
                                s.Take();
                        }
                    }
                }
                else {  // positive exp
                    int maxExp = 308 - expFrac;
                    while (RAPIDJSON_LIKELY(s.Peek() >= '0' && s.Peek() <= '9')) {
                        exp = exp * 10 + static_cast<int>(s.Take() - '0');
                        if (RAPIDJSON_UNLIKELY(exp > maxExp))
                            RAPIDJSON_PARSE_ERROR(kParseErrorNumberTooBig, startOffset);
                    }
                }
            }
            else
                RAPIDJSON_PARSE_ERROR(kParseErrorNumberMissExponent, s.Tell());

            if (expMinus)
                exp = -exp;
        }

        // Finish parsing, call event according to the type of number.
        bool cont = true;

        if (parseFlags & kParseNumbersAsStringsFlag) {
            if (parseFlags & kParseInsituFlag) {
                s.Pop();  // Pop stack no matter if it will be used or not.
                typename InputStream::Ch* head = is.PutBegin();
                const size_t length = s.Tell() - startOffset;
                RAPIDJSON_ASSERT(length <= 0xFFFFFFFF);
                // unable to insert the \0 character here, it will erase the comma after this number
                const typename TargetEncoding::Ch* const str = reinterpret_cast<typename TargetEncoding::Ch*>(head);
                cont = handler.RawNumber(str, SizeType(length), false);
            }
            else {
                SizeType numCharsToCopy = static_cast<SizeType>(s.Length());
                GenericStringStream<UTF8<NumberCharacter> > srcStream(s.Pop());
                StackStream<typename TargetEncoding::Ch> dstStream(stack_);
                while (numCharsToCopy--) {
                    Transcoder<UTF8<typename TargetEncoding::Ch>, TargetEncoding>::Transcode(srcStream, dstStream);
                }
                dstStream.Put('\0');
                const typename TargetEncoding::Ch* str = dstStream.Pop();
                const SizeType length = static_cast<SizeType>(dstStream.Length()) - 1;
                cont = handler.RawNumber(str, SizeType(length), true);
            }
        }
        else {
           size_t length = s.Length();
           const NumberCharacter* decimal = s.Pop();  // Pop stack no matter if it will be used or not.

           if (useDouble) {
               int p = exp + expFrac;
               if (parseFlags & kParseFullPrecisionFlag)
                   d = internal::StrtodFullPrecision(d, p, decimal, length, decimalPosition, exp);
               else
                   d = internal::StrtodNormalPrecision(d, p);

               // Use > max, instead of == inf, to fix bogus warning -Wfloat-equal
               if (d > (std::numeric_limits<double>::max)()) {
                   // Overflow
                   // TODO: internal::StrtodX should report overflow (or underflow)
                   RAPIDJSON_PARSE_ERROR(kParseErrorNumberTooBig, startOffset);
               }

               cont = handler.Double(minus ? -d : d);
           }
           else if (useNanOrInf) {
               cont = handler.Double(d);
           }
           else {
               if (use64bit) {
                   if (minus)
                       cont = handler.Int64(static_cast<int64_t>(~i64 + 1));
                   else
                       cont = handler.Uint64(i64);
               }
               else {
                   if (minus)
                       cont = handler.Int(static_cast<int32_t>(~i + 1));
                   else
                       cont = handler.Uint(i);
               }
           }
        }
        if (RAPIDJSON_UNLIKELY(!cont))
            RAPIDJSON_PARSE_ERROR(kParseErrorTermination, startOffset);
    }

    // Parse any JSON value
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseValue(InputStream& is, Handler& handler) {
        switch (is.Peek()) {
            case 'n': ParseNull  <parseFlags>(is, handler); break;
            case 't': ParseTrue  <parseFlags>(is, handler); break;
            case 'f': ParseFalse <parseFlags>(is, handler); break;
            case '"': ParseString<parseFlags>(is, handler); break;
            case '{': ParseObject<parseFlags>(is, handler); break;
            case '[': ParseArray <parseFlags>(is, handler); break;
            default :
                      ParseNumber<parseFlags>(is, handler);
                      break;

        }
    }

    // Iterative Parsing

    // States
    enum IterativeParsingState {
        IterativeParsingFinishState = 0, // sink states at top
        IterativeParsingErrorState,      // sink states at top
        IterativeParsingStartState,

        // Object states
        IterativeParsingObjectInitialState,
        IterativeParsingMemberKeyState,
        IterativeParsingMemberValueState,
        IterativeParsingObjectFinishState,

        // Array states
        IterativeParsingArrayInitialState,
        IterativeParsingElementState,
        IterativeParsingArrayFinishState,

        // Single value state
        IterativeParsingValueState,

        // Delimiter states (at bottom)
        IterativeParsingElementDelimiterState,
        IterativeParsingMemberDelimiterState,
        IterativeParsingKeyValueDelimiterState,

        cIterativeParsingStateCount
    };

    // Tokens
    enum Token {
        LeftBracketToken = 0,
        RightBracketToken,

        LeftCurlyBracketToken,
        RightCurlyBracketToken,

        CommaToken,
        ColonToken,

        StringToken,
        FalseToken,
        TrueToken,
        NullToken,
        NumberToken,

        kTokenCount
    };

    RAPIDJSON_FORCEINLINE Token Tokenize(Ch c) const {

//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
#define N NumberToken
#define N16 N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N
        // Maps from ASCII to Token
        static const unsigned char tokenMap[256] = {
            N16, // 00~0F
            N16, // 10~1F
            N, N, StringToken, N, N, N, N, N, N, N, N, N, CommaToken, N, N, N, // 20~2F
            N, N, N, N, N, N, N, N, N, N, ColonToken, N, N, N, N, N, // 30~3F
            N16, // 40~4F
            N, N, N, N, N, N, N, N, N, N, N, LeftBracketToken, N, RightBracketToken, N, N, // 50~5F
            N, N, N, N, N, N, FalseToken, N, N, N, N, N, N, N, NullToken, N, // 60~6F
            N, N, N, N, TrueToken, N, N, N, N, N, N, LeftCurlyBracketToken, N, RightCurlyBracketToken, N, N, // 70~7F
            N16, N16, N16, N16, N16, N16, N16, N16 // 80~FF
        };
#undef N
#undef N16
//!@endcond

        if (sizeof(Ch) == 1 || static_cast<unsigned>(c) < 256)
            return static_cast<Token>(tokenMap[static_cast<unsigned char>(c)]);
        else
            return NumberToken;
    }

    RAPIDJSON_FORCEINLINE IterativeParsingState Predict(IterativeParsingState state, Token token) const {
        // current state x one lookahead token -> new state
        static const char G[cIterativeParsingStateCount][kTokenCount] = {
            // Finish(sink state)
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            // Error(sink state)
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            // Start
            {
                IterativeParsingArrayInitialState,  // Left bracket
                IterativeParsingErrorState,         // Right bracket
                IterativeParsingObjectInitialState, // Left curly bracket
                IterativeParsingErrorState,         // Right curly bracket
                IterativeParsingErrorState,         // Comma
                IterativeParsingErrorState,         // Colon
                IterativeParsingValueState,         // String
                IterativeParsingValueState,         // False
                IterativeParsingValueState,         // True
                IterativeParsingValueState,         // Null
                IterativeParsingValueState          // Number
            },
            // ObjectInitial
            {
                IterativeParsingErrorState,         // Left bracket
                IterativeParsingErrorState,         // Right bracket
                IterativeParsingErrorState,         // Left curly bracket
                IterativeParsingObjectFinishState,  // Right curly bracket
                IterativeParsingErrorState,         // Comma
                IterativeParsingErrorState,         // Colon
                IterativeParsingMemberKeyState,     // String
                IterativeParsingErrorState,         // False
                IterativeParsingErrorState,         // True
                IterativeParsingErrorState,         // Null
                IterativeParsingErrorState          // Number
            },
            // MemberKey
            {
                IterativeParsingErrorState,             // Left bracket
                IterativeParsingErrorState,             // Right bracket
                IterativeParsingErrorState,             // Left curly bracket
                IterativeParsingErrorState,             // Right curly bracket
                IterativeParsingErrorState,             // Comma
                IterativeParsingKeyValueDelimiterState, // Colon
                IterativeParsingErrorState,             // String
                IterativeParsingErrorState,             // False
                IterativeParsingErrorState,             // True
                IterativeParsingErrorState,             // Null
                IterativeParsingErrorState              // Number
            },
            // MemberValue
            {
                IterativeParsingErrorState,             // Left bracket
                IterativeParsingErrorState,             // Right bracket
                IterativeParsingErrorState,             // Left curly bracket
                IterativeParsingObjectFinishState,      // Right curly bracket
                IterativeParsingMemberDelimiterState,   // Comma
                IterativeParsingErrorState,             // Colon
                IterativeParsingErrorState,             // String
                IterativeParsingErrorState,             // False
                IterativeParsingErrorState,             // True
                IterativeParsingErrorState,             // Null
                IterativeParsingErrorState              // Number
            },
            // ObjectFinish(sink state)
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            // ArrayInitial
            {
                IterativeParsingArrayInitialState,      // Left bracket(push Element state)
                IterativeParsingArrayFinishState,       // Right bracket
                IterativeParsingObjectInitialState,     // Left curly bracket(push Element state)
                IterativeParsingErrorState,             // Right curly bracket
                IterativeParsingErrorState,             // Comma
                IterativeParsingErrorState,             // Colon
                IterativeParsingElementState,           // String
                IterativeParsingElementState,           // False
                IterativeParsingElementState,           // True
                IterativeParsingElementState,           // Null
                IterativeParsingElementState            // Number
            },
            // Element
            {
                IterativeParsingErrorState,             // Left bracket
                IterativeParsingArrayFinishState,       // Right bracket
                IterativeParsingErrorState,             // Left curly bracket
                IterativeParsingErrorState,             // Right curly bracket
                IterativeParsingElementDelimiterState,  // Comma
                IterativeParsingErrorState,             // Colon
                IterativeParsingErrorState,             // String
                IterativeParsingErrorState,             // False
                IterativeParsingErrorState,             // True
                IterativeParsingErrorState,             // Null
                IterativeParsingErrorState              // Number
            },
            // ArrayFinish(sink state)
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            // Single Value (sink state)
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            // ElementDelimiter
            {
                IterativeParsingArrayInitialState,      // Left bracket(push Element state)
                IterativeParsingArrayFinishState,       // Right bracket
                IterativeParsingObjectInitialState,     // Left curly bracket(push Element state)
                IterativeParsingErrorState,             // Right curly bracket
                IterativeParsingErrorState,             // Comma
                IterativeParsingErrorState,             // Colon
                IterativeParsingElementState,           // String
                IterativeParsingElementState,           // False
                IterativeParsingElementState,           // True
                IterativeParsingElementState,           // Null
                IterativeParsingElementState            // Number
            },
            // MemberDelimiter
            {
                IterativeParsingErrorState,         // Left bracket
                IterativeParsingErrorState,         // Right bracket
                IterativeParsingErrorState,         // Left curly bracket
                IterativeParsingObjectFinishState,  // Right curly bracket
                IterativeParsingErrorState,         // Comma
                IterativeParsingErrorState,         // Colon
                IterativeParsingMemberKeyState,     // String
                IterativeParsingErrorState,         // False
                IterativeParsingErrorState,         // True
                IterativeParsingErrorState,         // Null
                IterativeParsingErrorState          // Number
            },
            // KeyValueDelimiter
            {
                IterativeParsingArrayInitialState,      // Left bracket(push MemberValue state)
                IterativeParsingErrorState,             // Right bracket
                IterativeParsingObjectInitialState,     // Left curly bracket(push MemberValue state)
                IterativeParsingErrorState,             // Right curly bracket
                IterativeParsingErrorState,             // Comma
                IterativeParsingErrorState,             // Colon
                IterativeParsingMemberValueState,       // String
                IterativeParsingMemberValueState,       // False
                IterativeParsingMemberValueState,       // True
                IterativeParsingMemberValueState,       // Null
                IterativeParsingMemberValueState        // Number
            },
        }; // End of G

        return static_cast<IterativeParsingState>(G[state][token]);
    }

    // Make an advance in the token stream and state based on the candidate destination state which was returned by Transit().
    // May return a new state on state pop.
    template <unsigned parseFlags, typename InputStream, typename Handler>
    RAPIDJSON_FORCEINLINE IterativeParsingState Transit(IterativeParsingState src, Token token, IterativeParsingState dst, InputStream& is, Handler& handler) {
        (void)token;

        switch (dst) {
        case IterativeParsingErrorState:
            return dst;

        case IterativeParsingObjectInitialState:
        case IterativeParsingArrayInitialState:
        {
            // Push the state(Element or MemeberValue) if we are nested in another array or value of member.
            // In this way we can get the correct state on ObjectFinish or ArrayFinish by frame pop.
            IterativeParsingState n = src;
            if (src == IterativeParsingArrayInitialState || src == IterativeParsingElementDelimiterState)
                n = IterativeParsingElementState;
            else if (src == IterativeParsingKeyValueDelimiterState)
                n = IterativeParsingMemberValueState;
            // Push current state.
            *stack_.template Push<SizeType>(1) = n;
            // Initialize and push the member/element count.
            *stack_.template Push<SizeType>(1) = 0;
            // Call handler
            bool hr = (dst == IterativeParsingObjectInitialState) ? handler.StartObject() : handler.StartArray();
            // On handler short circuits the parsing.
            if (!hr) {
                RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorTermination, is.Tell());
                return IterativeParsingErrorState;
            }
            else {
                is.Take();
                return dst;
            }
        }

        case IterativeParsingMemberKeyState:
            ParseString<parseFlags>(is, handler, true);
            if (HasParseError())
                return IterativeParsingErrorState;
            else
                return dst;

        case IterativeParsingKeyValueDelimiterState:
            RAPIDJSON_ASSERT(token == ColonToken);
            is.Take();
            return dst;

        case IterativeParsingMemberValueState:
            // Must be non-compound value. Or it would be ObjectInitial or ArrayInitial state.
            ParseValue<parseFlags>(is, handler);
            if (HasParseError()) {
                return IterativeParsingErrorState;
            }
            return dst;

        case IterativeParsingElementState:
            // Must be non-compound value. Or it would be ObjectInitial or ArrayInitial state.
            ParseValue<parseFlags>(is, handler);
            if (HasParseError()) {
                return IterativeParsingErrorState;
            }
            return dst;

        case IterativeParsingMemberDelimiterState:
        case IterativeParsingElementDelimiterState:
            is.Take();
            // Update member/element count.
            *stack_.template Top<SizeType>() = *stack_.template Top<SizeType>() + 1;
            return dst;

        case IterativeParsingObjectFinishState:
        {
            // Transit from delimiter is only allowed when trailing commas are enabled
            if (!(parseFlags & kParseTrailingCommasFlag) && src == IterativeParsingMemberDelimiterState) {
                RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorObjectMissName, is.Tell());
                return IterativeParsingErrorState;
            }
            // Get member count.
            SizeType c = *stack_.template Pop<SizeType>(1);
            // If the object is not empty, count the last member.
            if (src == IterativeParsingMemberValueState)
                ++c;
            // Restore the state.
            IterativeParsingState n = static_cast<IterativeParsingState>(*stack_.template Pop<SizeType>(1));
            // Transit to Finish state if this is the topmost scope.
            if (n == IterativeParsingStartState)
                n = IterativeParsingFinishState;
            // Call handler
            bool hr = handler.EndObject(c);
            // On handler short circuits the parsing.
            if (!hr) {
                RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorTermination, is.Tell());
                return IterativeParsingErrorState;
            }
            else {
                is.Take();
                return n;
            }
        }

        case IterativeParsingArrayFinishState:
        {
            // Transit from delimiter is only allowed when trailing commas are enabled
            if (!(parseFlags & kParseTrailingCommasFlag) && src == IterativeParsingElementDelimiterState) {
                RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorValueInvalid, is.Tell());
                return IterativeParsingErrorState;
            }
            // Get element count.
            SizeType c = *stack_.template Pop<SizeType>(1);
            // If the array is not empty, count the last element.
            if (src == IterativeParsingElementState)
                ++c;
            // Restore the state.
            IterativeParsingState n = static_cast<IterativeParsingState>(*stack_.template Pop<SizeType>(1));
            // Transit to Finish state if this is the topmost scope.
            if (n == IterativeParsingStartState)
                n = IterativeParsingFinishState;
            // Call handler
            bool hr = handler.EndArray(c);
            // On handler short circuits the parsing.
            if (!hr) {
                RAPIDJSON_PARSE_ERROR_NORETURN(kParseErrorTermination, is.Tell());
                return IterativeParsingErrorState;
            }
            else {
                is.Take();
                return n;
            }
        }

        default:
            // This branch is for IterativeParsingValueState actually.
            // Use `default:` rather than
            // `case IterativeParsingValueState:` is for code coverage.

            // The IterativeParsingStartState is not enumerated in this switch-case.
            // It is impossible for that case. And it can be caught by following assertion.

            // The IterativeParsingFinishState is not enumerated in this switch-case either.
            // It is a "derivative" state which cannot triggered from Predict() directly.
            // Therefore it cannot happen here. And it can be caught by following assertion.
            RAPIDJSON_ASSERT(dst == IterativeParsingValueState);

            // Must be non-compound value. Or it would be ObjectInitial or ArrayInitial state.
            ParseValue<parseFlags>(is, handler);
            if (HasParseError()) {
                return IterativeParsingErrorState;
            }
            return IterativeParsingFinishState;
        }
    }

    template <typename InputStream>
    void HandleError(IterativeParsingState src, InputStream& is) {
        if (HasParseError()) {
            // Error flag has been set.
            return;
        }

        switch (src) {
        case IterativeParsingStartState:            RAPIDJSON_PARSE_ERROR(kParseErrorDocumentEmpty, is.Tell()); return;
        case IterativeParsingFinishState:           RAPIDJSON_PARSE_ERROR(kParseErrorDocumentRootNotSingular, is.Tell()); return;
        case IterativeParsingObjectInitialState:
        case IterativeParsingMemberDelimiterState:  RAPIDJSON_PARSE_ERROR(kParseErrorObjectMissName, is.Tell()); return;
        case IterativeParsingMemberKeyState:        RAPIDJSON_PARSE_ERROR(kParseErrorObjectMissColon, is.Tell()); return;
        case IterativeParsingMemberValueState:      RAPIDJSON_PARSE_ERROR(kParseErrorObjectMissCommaOrCurlyBracket, is.Tell()); return;
        case IterativeParsingKeyValueDelimiterState:
        case IterativeParsingArrayInitialState:
        case IterativeParsingElementDelimiterState: RAPIDJSON_PARSE_ERROR(kParseErrorValueInvalid, is.Tell()); return;
        default: RAPIDJSON_ASSERT(src == IterativeParsingElementState); RAPIDJSON_PARSE_ERROR(kParseErrorArrayMissCommaOrSquareBracket, is.Tell()); return;
        }
    }

    RAPIDJSON_FORCEINLINE bool IsIterativeParsingDelimiterState(IterativeParsingState s) const {
        return s >= IterativeParsingElementDelimiterState;
    }

    RAPIDJSON_FORCEINLINE bool IsIterativeParsingCompleteState(IterativeParsingState s) const {
        return s <= IterativeParsingErrorState;
    }

    template <unsigned parseFlags, typename InputStream, typename Handler>
    ParseResult IterativeParse(InputStream& is, Handler& handler) {
        parseResult_.Clear();
        ClearStackOnExit scope(*this);
        IterativeParsingState state = IterativeParsingStartState;

        SkipWhitespaceAndComments<parseFlags>(is);
        RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);
        while (is.Peek() != '\0') {
            Token t = Tokenize(is.Peek());
            IterativeParsingState n = Predict(state, t);
            IterativeParsingState d = Transit<parseFlags>(state, t, n, is, handler);

            if (d == IterativeParsingErrorState) {
                HandleError(state, is);
                break;
            }

            state = d;

            // Do not further consume streams if a root JSON has been parsed.
            if ((parseFlags & kParseStopWhenDoneFlag) && state == IterativeParsingFinishState)
                break;

            SkipWhitespaceAndComments<parseFlags>(is);
            RAPIDJSON_PARSE_ERROR_EARLY_RETURN(parseResult_);
        }

        // Handle the end of file.
        if (state != IterativeParsingFinishState)
            HandleError(state, is);

        return parseResult_;
    }

    static const size_t kDefaultStackCapacity = 256;    //!< Default stack capacity in bytes for storing a single decoded string.
    internal::Stack<StackAllocator> stack_;  //!< A stack for storing decoded string temporarily during non-destructive parsing.
    ParseResult parseResult_;
    IterativeParsingState state_;
}; // class GenericReader

//! Reader with UTF8 encoding and default allocator.
typedef GenericReader<UTF8<>, UTF8<> > Reader;

RAPIDJSON_NAMESPACE_END

#if defined(__clang__) || defined(_MSC_VER)
RAPIDJSON_DIAG_POP
#endif


#ifdef __GNUC__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_READER_H_

// End file:reader.h


// Begin file: internal/meta.h
// already included
// End file:internal/meta.h


// Begin file: internal/strfunc.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_INTERNAL_STRFUNC_H_
#define RAPIDJSON_INTERNAL_STRFUNC_H_


// Begin file: ../stream.h
// already included
// End file:../stream.h

#include <cwchar>

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

//! Custom strlen() which works on different character types.
/*! \tparam Ch Character type (e.g. char, wchar_t, short)
    \param s Null-terminated input string.
    \return Number of characters in the string. 
    \note This has the same semantics as strlen(), the return value is not number of Unicode codepoints.
*/
template <typename Ch>
inline SizeType StrLen(const Ch* s) {
    RAPIDJSON_ASSERT(s != 0);
    const Ch* p = s;
    while (*p) ++p;
    return SizeType(p - s);
}

template <>
inline SizeType StrLen(const char* s) {
    return SizeType(std::strlen(s));
}

template <>
inline SizeType StrLen(const wchar_t* s) {
    return SizeType(std::wcslen(s));
}

//! Custom strcmpn() which works on different character types.
/*! \tparam Ch Character type (e.g. char, wchar_t, short)
    \param s1 Null-terminated input string.
    \param s2 Null-terminated input string.
    \return 0 if equal
*/
template<typename Ch>
inline int StrCmp(const Ch* s1, const Ch* s2) {
    RAPIDJSON_ASSERT(s1 != 0);
    RAPIDJSON_ASSERT(s2 != 0);
    while(*s1 && (*s1 == *s2)) { s1++; s2++; }
    return static_cast<unsigned>(*s1) < static_cast<unsigned>(*s2) ? -1 : static_cast<unsigned>(*s1) > static_cast<unsigned>(*s2);
}

//! Returns number of code points in a encoded string.
template<typename Encoding>
bool CountStringCodePoint(const typename Encoding::Ch* s, SizeType length, SizeType* outCount) {
    RAPIDJSON_ASSERT(s != 0);
    RAPIDJSON_ASSERT(outCount != 0);
    GenericStringStream<Encoding> is(s);
    const typename Encoding::Ch* end = s + length;
    SizeType count = 0;
    while (is.src_ < end) {
        unsigned codepoint;
        if (!Encoding::Decode(is, &codepoint))
            return false;
        count++;
    }
    *outCount = count;
    return true;
}

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_INTERNAL_STRFUNC_H_

// End file:internal/strfunc.h


// Begin file: memorystream.h
// already included
// End file:memorystream.h


// Begin file: encodedstream.h
// already included
// End file:encodedstream.h

#include <new>      // placement new
#include <limits>
#ifdef __cpp_lib_three_way_comparison
#include <compare>
#endif

RAPIDJSON_DIAG_PUSH
#ifdef __clang__
RAPIDJSON_DIAG_OFF(padded)
RAPIDJSON_DIAG_OFF(switch-enum)
RAPIDJSON_DIAG_OFF(c++98-compat)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_OFF(4127) // conditional expression is constant
RAPIDJSON_DIAG_OFF(4244) // conversion from kXxxFlags to 'uint16_t', possible loss of data
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_OFF(effc++)
#endif // __GNUC__

#ifdef GetObject
// see https://github.com/Tencent/rapidjson/issues/1448
// a former included windows.h might have defined a macro called GetObject, which affects
// GetObject defined here. This ensures the macro does not get applied
#pragma push_macro("GetObject")
#define RAPIDJSON_WINDOWS_GETOBJECT_WORKAROUND_APPLIED
#undef GetObject
#endif

#ifndef RAPIDJSON_NOMEMBERITERATORCLASS
#include <iterator> // std::random_access_iterator_tag
#endif

#if RAPIDJSON_USE_MEMBERSMAP
#include <map> // std::multimap
#endif

RAPIDJSON_NAMESPACE_BEGIN

// Forward declaration.
template <typename Encoding, typename Allocator>
class GenericValue;

template <typename Encoding, typename Allocator, typename StackAllocator>
class GenericDocument;

/*! \def RAPIDJSON_DEFAULT_ALLOCATOR
    \ingroup RAPIDJSON_CONFIG
    \brief Allows to choose default allocator.

    User can define this to use CrtAllocator or MemoryPoolAllocator.
*/
#ifndef RAPIDJSON_DEFAULT_ALLOCATOR
#define RAPIDJSON_DEFAULT_ALLOCATOR ::RAPIDJSON_NAMESPACE::MemoryPoolAllocator<::RAPIDJSON_NAMESPACE::CrtAllocator>
#endif

/*! \def RAPIDJSON_DEFAULT_STACK_ALLOCATOR
    \ingroup RAPIDJSON_CONFIG
    \brief Allows to choose default stack allocator for Document.

    User can define this to use CrtAllocator or MemoryPoolAllocator.
*/
#ifndef RAPIDJSON_DEFAULT_STACK_ALLOCATOR
#define RAPIDJSON_DEFAULT_STACK_ALLOCATOR ::RAPIDJSON_NAMESPACE::CrtAllocator
#endif

/*! \def RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY
    \ingroup RAPIDJSON_CONFIG
    \brief User defined kDefaultObjectCapacity value.

    User can define this as any natural number.
*/
#ifndef RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY
// number of objects that rapidjson::Value allocates memory for by default
#define RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY 16
#endif

/*! \def RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY
    \ingroup RAPIDJSON_CONFIG
    \brief User defined kDefaultArrayCapacity value.

    User can define this as any natural number.
*/
#ifndef RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY
// number of array elements that rapidjson::Value allocates memory for by default
#define RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY 16
#endif

//! Name-value pair in a JSON object value.
/*!
    This class was internal to GenericValue. It used to be a inner struct.
    But a compiler (IBM XL C/C++ for AIX) have reported to have problem with that so it moved as a namespace scope struct.
    https://code.google.com/p/rapidjson/issues/detail?id=64
*/
template <typename Encoding, typename Allocator> 
class GenericMember {
public:
    GenericValue<Encoding, Allocator> name;     //!< name of member (must be a string)
    GenericValue<Encoding, Allocator> value;    //!< value of member.

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move constructor in C++11
    GenericMember(GenericMember&& rhs) RAPIDJSON_NOEXCEPT
        : name(std::move(rhs.name)),
          value(std::move(rhs.value))
    {
    }

    //! Move assignment in C++11
    GenericMember& operator=(GenericMember&& rhs) RAPIDJSON_NOEXCEPT {
        return *this = static_cast<GenericMember&>(rhs);
    }
#endif

    //! Assignment with move semantics.
    /*! \param rhs Source of the assignment. Its name and value will become a null value after assignment.
    */
    GenericMember& operator=(GenericMember& rhs) RAPIDJSON_NOEXCEPT {
        if (RAPIDJSON_LIKELY(this != &rhs)) {
            name = rhs.name;
            value = rhs.value;
        }
        return *this;
    }

    // swap() for std::sort() and other potential use in STL.
    friend inline void swap(GenericMember& a, GenericMember& b) RAPIDJSON_NOEXCEPT {
        a.name.Swap(b.name);
        a.value.Swap(b.value);
    }

private:
    //! Copy constructor is not permitted.
    GenericMember(const GenericMember& rhs);
};

///////////////////////////////////////////////////////////////////////////////
// GenericMemberIterator

#ifndef RAPIDJSON_NOMEMBERITERATORCLASS

//! (Constant) member iterator for a JSON object value
/*!
    \tparam Const Is this a constant iterator?
    \tparam Encoding    Encoding of the value. (Even non-string values need to have the same encoding in a document)
    \tparam Allocator   Allocator type for allocating memory of object, array and string.

    This class implements a Random Access Iterator for GenericMember elements
    of a GenericValue, see ISO/IEC 14882:2003(E) C++ standard, 24.1 [lib.iterator.requirements].

    \note This iterator implementation is mainly intended to avoid implicit
        conversions from iterator values to \c NULL,
        e.g. from GenericValue::FindMember.

    \note Define \c RAPIDJSON_NOMEMBERITERATORCLASS to fall back to a
        pointer-based implementation, if your platform doesn't provide
        the C++ <iterator> header.

    \see GenericMember, GenericValue::MemberIterator, GenericValue::ConstMemberIterator
 */
template <bool Const, typename Encoding, typename Allocator>
class GenericMemberIterator {

    friend class GenericValue<Encoding,Allocator>;
    template <bool, typename, typename> friend class GenericMemberIterator;

    typedef GenericMember<Encoding,Allocator> PlainType;
    typedef typename internal::MaybeAddConst<Const,PlainType>::Type ValueType;

public:
    //! Iterator type itself
    typedef GenericMemberIterator Iterator;
    //! Constant iterator type
    typedef GenericMemberIterator<true,Encoding,Allocator>  ConstIterator;
    //! Non-constant iterator type
    typedef GenericMemberIterator<false,Encoding,Allocator> NonConstIterator;

    /** \name std::iterator_traits support */
    //@{
    typedef ValueType      value_type;
    typedef ValueType *    pointer;
    typedef ValueType &    reference;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
    //@}

    //! Pointer to (const) GenericMember
    typedef pointer         Pointer;
    //! Reference to (const) GenericMember
    typedef reference       Reference;
    //! Signed integer type (e.g. \c ptrdiff_t)
    typedef difference_type DifferenceType;

    //! Default constructor (singular value)
    /*! Creates an iterator pointing to no element.
        \note All operations, except for comparisons, are undefined on such values.
     */
    GenericMemberIterator() : ptr_() {}

    //! Iterator conversions to more const
    /*!
        \param it (Non-const) iterator to copy from

        Allows the creation of an iterator from another GenericMemberIterator
        that is "less const".  Especially, creating a non-constant iterator
        from a constant iterator are disabled:
        \li const -> non-const (not ok)
        \li const -> const (ok)
        \li non-const -> const (ok)
        \li non-const -> non-const (ok)

        \note If the \c Const template parameter is already \c false, this
            constructor effectively defines a regular copy-constructor.
            Otherwise, the copy constructor is implicitly defined.
    */
    GenericMemberIterator(const NonConstIterator & it) : ptr_(it.ptr_) {}
    Iterator& operator=(const NonConstIterator & it) { ptr_ = it.ptr_; return *this; }

    //! @name stepping
    //@{
    Iterator& operator++(){ ++ptr_; return *this; }
    Iterator& operator--(){ --ptr_; return *this; }
    Iterator  operator++(int){ Iterator old(*this); ++ptr_; return old; }
    Iterator  operator--(int){ Iterator old(*this); --ptr_; return old; }
    //@}

    //! @name increment/decrement
    //@{
    Iterator operator+(DifferenceType n) const { return Iterator(ptr_+n); }
    Iterator operator-(DifferenceType n) const { return Iterator(ptr_-n); }

    Iterator& operator+=(DifferenceType n) { ptr_+=n; return *this; }
    Iterator& operator-=(DifferenceType n) { ptr_-=n; return *this; }
    //@}

    //! @name relations
    //@{
    template <bool Const_> bool operator==(const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ == that.ptr_; }
    template <bool Const_> bool operator!=(const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ != that.ptr_; }
    template <bool Const_> bool operator<=(const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ <= that.ptr_; }
    template <bool Const_> bool operator>=(const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ >= that.ptr_; }
    template <bool Const_> bool operator< (const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ < that.ptr_; }
    template <bool Const_> bool operator> (const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ > that.ptr_; }

#ifdef __cpp_lib_three_way_comparison
    template <bool Const_> std::strong_ordering operator<=>(const GenericMemberIterator<Const_, Encoding, Allocator>& that) const { return ptr_ <=> that.ptr_; }
#endif
    //@}

    //! @name dereference
    //@{
    Reference operator*() const { return *ptr_; }
    Pointer   operator->() const { return ptr_; }
    Reference operator[](DifferenceType n) const { return ptr_[n]; }
    //@}

    //! Distance
    DifferenceType operator-(ConstIterator that) const { return ptr_-that.ptr_; }

private:
    //! Internal constructor from plain pointer
    explicit GenericMemberIterator(Pointer p) : ptr_(p) {}

    Pointer ptr_; //!< raw pointer
};

#else // RAPIDJSON_NOMEMBERITERATORCLASS

// class-based member iterator implementation disabled, use plain pointers

template <bool Const, typename Encoding, typename Allocator>
class GenericMemberIterator;

//! non-const GenericMemberIterator
template <typename Encoding, typename Allocator>
class GenericMemberIterator<false,Encoding,Allocator> {
public:
    //! use plain pointer as iterator type
    typedef GenericMember<Encoding,Allocator>* Iterator;
};
//! const GenericMemberIterator
template <typename Encoding, typename Allocator>
class GenericMemberIterator<true,Encoding,Allocator> {
public:
    //! use plain const pointer as iterator type
    typedef const GenericMember<Encoding,Allocator>* Iterator;
};

#endif // RAPIDJSON_NOMEMBERITERATORCLASS

///////////////////////////////////////////////////////////////////////////////
// GenericStringRef

//! Reference to a constant string (not taking a copy)
/*!
    \tparam CharType character type of the string

    This helper class is used to automatically infer constant string
    references for string literals, especially from \c const \b (!)
    character arrays.

    The main use is for creating JSON string values without copying the
    source string via an \ref Allocator.  This requires that the referenced
    string pointers have a sufficient lifetime, which exceeds the lifetime
    of the associated GenericValue.

    \b Example
    \code
    Value v("foo");   // ok, no need to copy & calculate length
    const char foo[] = "foo";
    v.SetString(foo); // ok

    const char* bar = foo;
    // Value x(bar); // not ok, can't rely on bar's lifetime
    Value x(StringRef(bar)); // lifetime explicitly guaranteed by user
    Value y(StringRef(bar, 3));  // ok, explicitly pass length
    \endcode

    \see StringRef, GenericValue::SetString
*/
template<typename CharType>
struct GenericStringRef {
    typedef CharType Ch; //!< character type of the string

    //! Create string reference from \c const character array
#ifndef __clang__ // -Wdocumentation
    /*!
        This constructor implicitly creates a constant string reference from
        a \c const character array.  It has better performance than
        \ref StringRef(const CharType*) by inferring the string \ref length
        from the array length, and also supports strings containing null
        characters.

        \tparam N length of the string, automatically inferred

        \param str Constant character array, lifetime assumed to be longer
            than the use of the string in e.g. a GenericValue

        \post \ref s == str

        \note Constant complexity.
        \note There is a hidden, private overload to disallow references to
            non-const character arrays to be created via this constructor.
            By this, e.g. function-scope arrays used to be filled via
            \c snprintf are excluded from consideration.
            In such cases, the referenced string should be \b copied to the
            GenericValue instead.
     */
#endif
    template<SizeType N>
    GenericStringRef(const CharType (&str)[N]) RAPIDJSON_NOEXCEPT
        : s(str), length(N-1) {}

    //! Explicitly create string reference from \c const character pointer
#ifndef __clang__ // -Wdocumentation
    /*!
        This constructor can be used to \b explicitly  create a reference to
        a constant string pointer.

        \see StringRef(const CharType*)

        \param str Constant character pointer, lifetime assumed to be longer
            than the use of the string in e.g. a GenericValue

        \post \ref s == str

        \note There is a hidden, private overload to disallow references to
            non-const character arrays to be created via this constructor.
            By this, e.g. function-scope arrays used to be filled via
            \c snprintf are excluded from consideration.
            In such cases, the referenced string should be \b copied to the
            GenericValue instead.
     */
#endif
    explicit GenericStringRef(const CharType* str)
        : s(str), length(NotNullStrLen(str)) {}

    //! Create constant string reference from pointer and length
#ifndef __clang__ // -Wdocumentation
    /*! \param str constant string, lifetime assumed to be longer than the use of the string in e.g. a GenericValue
        \param len length of the string, excluding the trailing NULL terminator

        \post \ref s == str && \ref length == len
        \note Constant complexity.
     */
#endif
    GenericStringRef(const CharType* str, SizeType len)
        : s(RAPIDJSON_LIKELY(str) ? str : emptyString), length(len) { RAPIDJSON_ASSERT(str != 0 || len == 0u); }

    GenericStringRef(const GenericStringRef& rhs) : s(rhs.s), length(rhs.length) {}

    //! implicit conversion to plain CharType pointer
    operator const Ch *() const { return s; }

    const Ch* const s; //!< plain CharType pointer
    const SizeType length; //!< length of the string (excluding the trailing NULL terminator)

private:
    SizeType NotNullStrLen(const CharType* str) {
        RAPIDJSON_ASSERT(str != 0);
        return internal::StrLen(str);
    }

    /// Empty string - used when passing in a NULL pointer
    static const Ch emptyString[];

    //! Disallow construction from non-const array
    template<SizeType N>
    GenericStringRef(CharType (&str)[N]) /* = delete */;
    //! Copy assignment operator not permitted - immutable type
    GenericStringRef& operator=(const GenericStringRef& rhs) /* = delete */;
};

template<typename CharType>
const CharType GenericStringRef<CharType>::emptyString[] = { CharType() };

//! Mark a character pointer as constant string
/*! Mark a plain character pointer as a "string literal".  This function
    can be used to avoid copying a character string to be referenced as a
    value in a JSON GenericValue object, if the string's lifetime is known
    to be valid long enough.
    \tparam CharType Character type of the string
    \param str Constant string, lifetime assumed to be longer than the use of the string in e.g. a GenericValue
    \return GenericStringRef string reference object
    \relatesalso GenericStringRef

    \see GenericValue::GenericValue(StringRefType), GenericValue::operator=(StringRefType), GenericValue::SetString(StringRefType), GenericValue::PushBack(StringRefType, Allocator&), GenericValue::AddMember
*/
template<typename CharType>
inline GenericStringRef<CharType> StringRef(const CharType* str) {
    return GenericStringRef<CharType>(str);
}

//! Mark a character pointer as constant string
/*! Mark a plain character pointer as a "string literal".  This function
    can be used to avoid copying a character string to be referenced as a
    value in a JSON GenericValue object, if the string's lifetime is known
    to be valid long enough.

    This version has better performance with supplied length, and also
    supports string containing null characters.

    \tparam CharType character type of the string
    \param str Constant string, lifetime assumed to be longer than the use of the string in e.g. a GenericValue
    \param length The length of source string.
    \return GenericStringRef string reference object
    \relatesalso GenericStringRef
*/
template<typename CharType>
inline GenericStringRef<CharType> StringRef(const CharType* str, size_t length) {
    return GenericStringRef<CharType>(str, SizeType(length));
}

#if RAPIDJSON_HAS_STDSTRING
//! Mark a string object as constant string
/*! Mark a string object (e.g. \c std::string) as a "string literal".
    This function can be used to avoid copying a string to be referenced as a
    value in a JSON GenericValue object, if the string's lifetime is known
    to be valid long enough.

    \tparam CharType character type of the string
    \param str Constant string, lifetime assumed to be longer than the use of the string in e.g. a GenericValue
    \return GenericStringRef string reference object
    \relatesalso GenericStringRef
    \note Requires the definition of the preprocessor symbol \ref RAPIDJSON_HAS_STDSTRING.
*/
template<typename CharType>
inline GenericStringRef<CharType> StringRef(const std::basic_string<CharType>& str) {
    return GenericStringRef<CharType>(str.data(), SizeType(str.size()));
}
#endif

///////////////////////////////////////////////////////////////////////////////
// GenericValue type traits
namespace internal {

template <typename T, typename Encoding = void, typename Allocator = void>
struct IsGenericValueImpl : FalseType {};

// select candidates according to nested encoding and allocator types
template <typename T> struct IsGenericValueImpl<T, typename Void<typename T::EncodingType>::Type, typename Void<typename T::AllocatorType>::Type>
    : IsBaseOf<GenericValue<typename T::EncodingType, typename T::AllocatorType>, T>::Type {};

// helper to match arbitrary GenericValue instantiations, including derived classes
template <typename T> struct IsGenericValue : IsGenericValueImpl<T>::Type {};

} // namespace internal

///////////////////////////////////////////////////////////////////////////////
// TypeHelper

namespace internal {

template <typename ValueType, typename T>
struct TypeHelper {};

template<typename ValueType> 
struct TypeHelper<ValueType, bool> {
    static bool Is(const ValueType& v) { return v.IsBool(); }
    static bool Get(const ValueType& v) { return v.GetBool(); }
    static ValueType& Set(ValueType& v, bool data) { return v.SetBool(data); }
    static ValueType& Set(ValueType& v, bool data, typename ValueType::AllocatorType&) { return v.SetBool(data); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, int> {
    static bool Is(const ValueType& v) { return v.IsInt(); }
    static int Get(const ValueType& v) { return v.GetInt(); }
    static ValueType& Set(ValueType& v, int data) { return v.SetInt(data); }
    static ValueType& Set(ValueType& v, int data, typename ValueType::AllocatorType&) { return v.SetInt(data); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, unsigned> {
    static bool Is(const ValueType& v) { return v.IsUint(); }
    static unsigned Get(const ValueType& v) { return v.GetUint(); }
    static ValueType& Set(ValueType& v, unsigned data) { return v.SetUint(data); }
    static ValueType& Set(ValueType& v, unsigned data, typename ValueType::AllocatorType&) { return v.SetUint(data); }
};

#ifdef _MSC_VER
RAPIDJSON_STATIC_ASSERT(sizeof(long) == sizeof(int));
template<typename ValueType>
struct TypeHelper<ValueType, long> {
    static bool Is(const ValueType& v) { return v.IsInt(); }
    static long Get(const ValueType& v) { return v.GetInt(); }
    static ValueType& Set(ValueType& v, long data) { return v.SetInt(data); }
    static ValueType& Set(ValueType& v, long data, typename ValueType::AllocatorType&) { return v.SetInt(data); }
};

RAPIDJSON_STATIC_ASSERT(sizeof(unsigned long) == sizeof(unsigned));
template<typename ValueType>
struct TypeHelper<ValueType, unsigned long> {
    static bool Is(const ValueType& v) { return v.IsUint(); }
    static unsigned long Get(const ValueType& v) { return v.GetUint(); }
    static ValueType& Set(ValueType& v, unsigned long data) { return v.SetUint(data); }
    static ValueType& Set(ValueType& v, unsigned long data, typename ValueType::AllocatorType&) { return v.SetUint(data); }
};
#endif

template<typename ValueType> 
struct TypeHelper<ValueType, int64_t> {
    static bool Is(const ValueType& v) { return v.IsInt64(); }
    static int64_t Get(const ValueType& v) { return v.GetInt64(); }
    static ValueType& Set(ValueType& v, int64_t data) { return v.SetInt64(data); }
    static ValueType& Set(ValueType& v, int64_t data, typename ValueType::AllocatorType&) { return v.SetInt64(data); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, uint64_t> {
    static bool Is(const ValueType& v) { return v.IsUint64(); }
    static uint64_t Get(const ValueType& v) { return v.GetUint64(); }
    static ValueType& Set(ValueType& v, uint64_t data) { return v.SetUint64(data); }
    static ValueType& Set(ValueType& v, uint64_t data, typename ValueType::AllocatorType&) { return v.SetUint64(data); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, double> {
    static bool Is(const ValueType& v) { return v.IsDouble(); }
    static double Get(const ValueType& v) { return v.GetDouble(); }
    static ValueType& Set(ValueType& v, double data) { return v.SetDouble(data); }
    static ValueType& Set(ValueType& v, double data, typename ValueType::AllocatorType&) { return v.SetDouble(data); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, float> {
    static bool Is(const ValueType& v) { return v.IsFloat(); }
    static float Get(const ValueType& v) { return v.GetFloat(); }
    static ValueType& Set(ValueType& v, float data) { return v.SetFloat(data); }
    static ValueType& Set(ValueType& v, float data, typename ValueType::AllocatorType&) { return v.SetFloat(data); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, const typename ValueType::Ch*> {
    typedef const typename ValueType::Ch* StringType;
    static bool Is(const ValueType& v) { return v.IsString(); }
    static StringType Get(const ValueType& v) { return v.GetString(); }
    static ValueType& Set(ValueType& v, const StringType data) { return v.SetString(typename ValueType::StringRefType(data)); }
    static ValueType& Set(ValueType& v, const StringType data, typename ValueType::AllocatorType& a) { return v.SetString(data, a); }
};

#if RAPIDJSON_HAS_STDSTRING
template<typename ValueType> 
struct TypeHelper<ValueType, std::basic_string<typename ValueType::Ch> > {
    typedef std::basic_string<typename ValueType::Ch> StringType;
    static bool Is(const ValueType& v) { return v.IsString(); }
    static StringType Get(const ValueType& v) { return StringType(v.GetString(), v.GetStringLength()); }
    static ValueType& Set(ValueType& v, const StringType& data, typename ValueType::AllocatorType& a) { return v.SetString(data, a); }
};
#endif

template<typename ValueType> 
struct TypeHelper<ValueType, typename ValueType::Array> {
    typedef typename ValueType::Array ArrayType;
    static bool Is(const ValueType& v) { return v.IsArray(); }
    static ArrayType Get(ValueType& v) { return v.GetArray(); }
    static ValueType& Set(ValueType& v, ArrayType data) { return v = data; }
    static ValueType& Set(ValueType& v, ArrayType data, typename ValueType::AllocatorType&) { return v = data; }
};

template<typename ValueType> 
struct TypeHelper<ValueType, typename ValueType::ConstArray> {
    typedef typename ValueType::ConstArray ArrayType;
    static bool Is(const ValueType& v) { return v.IsArray(); }
    static ArrayType Get(const ValueType& v) { return v.GetArray(); }
};

template<typename ValueType> 
struct TypeHelper<ValueType, typename ValueType::Object> {
    typedef typename ValueType::Object ObjectType;
    static bool Is(const ValueType& v) { return v.IsObject(); }
    static ObjectType Get(ValueType& v) { return v.GetObject(); }
    static ValueType& Set(ValueType& v, ObjectType data) { return v = data; }
    static ValueType& Set(ValueType& v, ObjectType data, typename ValueType::AllocatorType&) { return v = data; }
};

template<typename ValueType> 
struct TypeHelper<ValueType, typename ValueType::ConstObject> {
    typedef typename ValueType::ConstObject ObjectType;
    static bool Is(const ValueType& v) { return v.IsObject(); }
    static ObjectType Get(const ValueType& v) { return v.GetObject(); }
};

} // namespace internal

// Forward declarations
template <bool, typename> class GenericArray;
template <bool, typename> class GenericObject;

///////////////////////////////////////////////////////////////////////////////
// GenericValue

//! Represents a JSON value. Use Value for UTF8 encoding and default allocator.
/*!
    A JSON value can be one of 7 types. This class is a variant type supporting
    these types.

    Use the Value if UTF8 and default allocator

    \tparam Encoding    Encoding of the value. (Even non-string values need to have the same encoding in a document)
    \tparam Allocator   Allocator type for allocating memory of object, array and string.
*/
template <typename Encoding, typename Allocator = RAPIDJSON_DEFAULT_ALLOCATOR >
class GenericValue {
public:
    //! Name-value pair in an object.
    typedef GenericMember<Encoding, Allocator> Member;
    typedef Encoding EncodingType;                  //!< Encoding type from template parameter.
    typedef Allocator AllocatorType;                //!< Allocator type from template parameter.
    typedef typename Encoding::Ch Ch;               //!< Character type derived from Encoding.
    typedef GenericStringRef<Ch> StringRefType;     //!< Reference to a constant string
    typedef typename GenericMemberIterator<false,Encoding,Allocator>::Iterator MemberIterator;  //!< Member iterator for iterating in object.
    typedef typename GenericMemberIterator<true,Encoding,Allocator>::Iterator ConstMemberIterator;  //!< Constant member iterator for iterating in object.
    typedef GenericValue* ValueIterator;            //!< Value iterator for iterating in array.
    typedef const GenericValue* ConstValueIterator; //!< Constant value iterator for iterating in array.
    typedef GenericValue<Encoding, Allocator> ValueType;    //!< Value type of itself.
    typedef GenericArray<false, ValueType> Array;
    typedef GenericArray<true, ValueType> ConstArray;
    typedef GenericObject<false, ValueType> Object;
    typedef GenericObject<true, ValueType> ConstObject;

    //!@name Constructors and destructor.
    //@{

    //! Default constructor creates a null value.
    GenericValue() RAPIDJSON_NOEXCEPT : data_() { data_.f.flags = kNullFlag; }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move constructor in C++11
    GenericValue(GenericValue&& rhs) RAPIDJSON_NOEXCEPT : data_(rhs.data_) {
        rhs.data_.f.flags = kNullFlag; // give up contents
    }
#endif

private:
    //! Copy constructor is not permitted.
    GenericValue(const GenericValue& rhs);

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Moving from a GenericDocument is not permitted.
    template <typename StackAllocator>
    GenericValue(GenericDocument<Encoding,Allocator,StackAllocator>&& rhs);

    //! Move assignment from a GenericDocument is not permitted.
    template <typename StackAllocator>
    GenericValue& operator=(GenericDocument<Encoding,Allocator,StackAllocator>&& rhs);
#endif

public:

    //! Constructor with JSON value type.
    /*! This creates a Value of specified type with default content.
        \param type Type of the value.
        \note Default content for number is zero.
    */
    explicit GenericValue(Type type) RAPIDJSON_NOEXCEPT : data_() {
        static const uint16_t defaultFlags[] = {
            kNullFlag, kFalseFlag, kTrueFlag, kObjectFlag, kArrayFlag, kShortStringFlag,
            kNumberAnyFlag
        };
        RAPIDJSON_NOEXCEPT_ASSERT(type >= kNullType && type <= kNumberType);
        data_.f.flags = defaultFlags[type];

        // Use ShortString to store empty string.
        if (type == kStringType)
            data_.ss.SetLength(0);
    }

    //! Explicit copy constructor (with allocator)
    /*! Creates a copy of a Value by using the given Allocator
        \tparam SourceAllocator allocator of \c rhs
        \param rhs Value to copy from (read-only)
        \param allocator Allocator for allocating copied elements and buffers. Commonly use GenericDocument::GetAllocator().
        \param copyConstStrings Force copying of constant strings (e.g. referencing an in-situ buffer)
        \see CopyFrom()
    */
    template <typename SourceAllocator>
    GenericValue(const GenericValue<Encoding,SourceAllocator>& rhs, Allocator& allocator, bool copyConstStrings = false) {
        switch (rhs.GetType()) {
        case kObjectType:
            DoCopyMembers(rhs, allocator, copyConstStrings);
            break;
        case kArrayType: {
                SizeType count = rhs.data_.a.size;
                GenericValue* le = reinterpret_cast<GenericValue*>(allocator.Malloc(count * sizeof(GenericValue)));
                const GenericValue<Encoding,SourceAllocator>* re = rhs.GetElementsPointer();
                for (SizeType i = 0; i < count; i++)
                    new (&le[i]) GenericValue(re[i], allocator, copyConstStrings);
                data_.f.flags = kArrayFlag;
                data_.a.size = data_.a.capacity = count;
                SetElementsPointer(le);
            }
            break;
        case kStringType:
            if (rhs.data_.f.flags == kConstStringFlag && !copyConstStrings) {
                data_.f.flags = rhs.data_.f.flags;
                data_  = *reinterpret_cast<const Data*>(&rhs.data_);
            }
            else
                SetStringRaw(StringRef(rhs.GetString(), rhs.GetStringLength()), allocator);
            break;
        default:
            data_.f.flags = rhs.data_.f.flags;
            data_  = *reinterpret_cast<const Data*>(&rhs.data_);
            break;
        }
    }

    //! Constructor for boolean value.
    /*! \param b Boolean value
        \note This constructor is limited to \em real boolean values and rejects
            implicitly converted types like arbitrary pointers.  Use an explicit cast
            to \c bool, if you want to construct a boolean JSON value in such cases.
     */
#ifndef RAPIDJSON_DOXYGEN_RUNNING // hide SFINAE from Doxygen
    template <typename T>
    explicit GenericValue(T b, RAPIDJSON_ENABLEIF((internal::IsSame<bool, T>))) RAPIDJSON_NOEXCEPT  // See #472
#else
    explicit GenericValue(bool b) RAPIDJSON_NOEXCEPT
#endif
        : data_() {
            // safe-guard against failing SFINAE
            RAPIDJSON_STATIC_ASSERT((internal::IsSame<bool,T>::Value));
            data_.f.flags = b ? kTrueFlag : kFalseFlag;
    }

    //! Constructor for int value.
    explicit GenericValue(int i) RAPIDJSON_NOEXCEPT : data_() {
        data_.n.i64 = i;
        data_.f.flags = (i >= 0) ? (kNumberIntFlag | kUintFlag | kUint64Flag) : kNumberIntFlag;
    }

    //! Constructor for unsigned value.
    explicit GenericValue(unsigned u) RAPIDJSON_NOEXCEPT : data_() {
        data_.n.u64 = u; 
        data_.f.flags = (u & 0x80000000) ? kNumberUintFlag : (kNumberUintFlag | kIntFlag | kInt64Flag);
    }

    //! Constructor for int64_t value.
    explicit GenericValue(int64_t i64) RAPIDJSON_NOEXCEPT : data_() {
        data_.n.i64 = i64;
        data_.f.flags = kNumberInt64Flag;
        if (i64 >= 0) {
            data_.f.flags |= kNumberUint64Flag;
            if (!(static_cast<uint64_t>(i64) & RAPIDJSON_UINT64_C2(0xFFFFFFFF, 0x00000000)))
                data_.f.flags |= kUintFlag;
            if (!(static_cast<uint64_t>(i64) & RAPIDJSON_UINT64_C2(0xFFFFFFFF, 0x80000000)))
                data_.f.flags |= kIntFlag;
        }
        else if (i64 >= static_cast<int64_t>(RAPIDJSON_UINT64_C2(0xFFFFFFFF, 0x80000000)))
            data_.f.flags |= kIntFlag;
    }

    //! Constructor for uint64_t value.
    explicit GenericValue(uint64_t u64) RAPIDJSON_NOEXCEPT : data_() {
        data_.n.u64 = u64;
        data_.f.flags = kNumberUint64Flag;
        if (!(u64 & RAPIDJSON_UINT64_C2(0x80000000, 0x00000000)))
            data_.f.flags |= kInt64Flag;
        if (!(u64 & RAPIDJSON_UINT64_C2(0xFFFFFFFF, 0x00000000)))
            data_.f.flags |= kUintFlag;
        if (!(u64 & RAPIDJSON_UINT64_C2(0xFFFFFFFF, 0x80000000)))
            data_.f.flags |= kIntFlag;
    }

    //! Constructor for double value.
    explicit GenericValue(double d) RAPIDJSON_NOEXCEPT : data_() { data_.n.d = d; data_.f.flags = kNumberDoubleFlag; }

    //! Constructor for float value.
    explicit GenericValue(float f) RAPIDJSON_NOEXCEPT : data_() { data_.n.d = static_cast<double>(f); data_.f.flags = kNumberDoubleFlag; }

    //! Constructor for constant string (i.e. do not make a copy of string)
    GenericValue(const Ch* s, SizeType length) RAPIDJSON_NOEXCEPT : data_() { SetStringRaw(StringRef(s, length)); }

    //! Constructor for constant string (i.e. do not make a copy of string)
    explicit GenericValue(StringRefType s) RAPIDJSON_NOEXCEPT : data_() { SetStringRaw(s); }

    //! Constructor for copy-string (i.e. do make a copy of string)
    GenericValue(const Ch* s, SizeType length, Allocator& allocator) : data_() { SetStringRaw(StringRef(s, length), allocator); }

    //! Constructor for copy-string (i.e. do make a copy of string)
    GenericValue(const Ch*s, Allocator& allocator) : data_() { SetStringRaw(StringRef(s), allocator); }

#if RAPIDJSON_HAS_STDSTRING
    //! Constructor for copy-string from a string object (i.e. do make a copy of string)
    /*! \note Requires the definition of the preprocessor symbol \ref RAPIDJSON_HAS_STDSTRING.
     */
    GenericValue(const std::basic_string<Ch>& s, Allocator& allocator) : data_() { SetStringRaw(StringRef(s), allocator); }
#endif

    //! Constructor for Array.
    /*!
        \param a An array obtained by \c GetArray().
        \note \c Array is always pass-by-value.
        \note the source array is moved into this value and the sourec array becomes empty.
    */
    GenericValue(Array a) RAPIDJSON_NOEXCEPT : data_(a.value_.data_) {
        a.value_.data_ = Data();
        a.value_.data_.f.flags = kArrayFlag;
    }

    //! Constructor for Object.
    /*!
        \param o An object obtained by \c GetObject().
        \note \c Object is always pass-by-value.
        \note the source object is moved into this value and the sourec object becomes empty.
    */
    GenericValue(Object o) RAPIDJSON_NOEXCEPT : data_(o.value_.data_) {
        o.value_.data_ = Data();
        o.value_.data_.f.flags = kObjectFlag;
    }

    //! Destructor.
    /*! Need to destruct elements of array, members of object, or copy-string.
    */
    ~GenericValue() {
        // With RAPIDJSON_USE_MEMBERSMAP, the maps need to be destroyed to release
        // their Allocator if it's refcounted (e.g. MemoryPoolAllocator).
        if (Allocator::kNeedFree || (RAPIDJSON_USE_MEMBERSMAP+0 &&
                                     internal::IsRefCounted<Allocator>::Value)) {
            switch(data_.f.flags) {
            case kArrayFlag:
                {
                    GenericValue* e = GetElementsPointer();
                    for (GenericValue* v = e; v != e + data_.a.size; ++v)
                        v->~GenericValue();
                    if (Allocator::kNeedFree) { // Shortcut by Allocator's trait
                        Allocator::Free(e);
                    }
                }
                break;

            case kObjectFlag:
                DoFreeMembers();
                break;

            case kCopyStringFlag:
                if (Allocator::kNeedFree) { // Shortcut by Allocator's trait
                    Allocator::Free(const_cast<Ch*>(GetStringPointer()));
                }
                break;

            default:
                break;  // Do nothing for other types.
            }
        }
    }

    //@}

    //!@name Assignment operators
    //@{

    //! Assignment with move semantics.
    /*! \param rhs Source of the assignment. It will become a null value after assignment.
    */
    GenericValue& operator=(GenericValue& rhs) RAPIDJSON_NOEXCEPT {
        if (RAPIDJSON_LIKELY(this != &rhs)) {
            // Can't destroy "this" before assigning "rhs", otherwise "rhs"
            // could be used after free if it's an sub-Value of "this",
            // hence the temporary danse.
            GenericValue temp;
            temp.RawAssign(rhs);
            this->~GenericValue();
            RawAssign(temp);
        }
        return *this;
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move assignment in C++11
    GenericValue& operator=(GenericValue&& rhs) RAPIDJSON_NOEXCEPT {
        return *this = rhs.Move();
    }
#endif

    //! Assignment of constant string reference (no copy)
    /*! \param str Constant string reference to be assigned
        \note This overload is needed to avoid clashes with the generic primitive type assignment overload below.
        \see GenericStringRef, operator=(T)
    */
    GenericValue& operator=(StringRefType str) RAPIDJSON_NOEXCEPT {
        GenericValue s(str);
        return *this = s;
    }

    //! Assignment with primitive types.
    /*! \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t
        \param value The value to be assigned.

        \note The source type \c T explicitly disallows all pointer types,
            especially (\c const) \ref Ch*.  This helps avoiding implicitly
            referencing character strings with insufficient lifetime, use
            \ref SetString(const Ch*, Allocator&) (for copying) or
            \ref StringRef() (to explicitly mark the pointer as constant) instead.
            All other pointer types would implicitly convert to \c bool,
            use \ref SetBool() instead.
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::IsPointer<T>), (GenericValue&))
    operator=(T value) {
        GenericValue v(value);
        return *this = v;
    }

    //! Deep-copy assignment from Value
    /*! Assigns a \b copy of the Value to the current Value object
        \tparam SourceAllocator Allocator type of \c rhs
        \param rhs Value to copy from (read-only)
        \param allocator Allocator to use for copying
        \param copyConstStrings Force copying of constant strings (e.g. referencing an in-situ buffer)
     */
    template <typename SourceAllocator>
    GenericValue& CopyFrom(const GenericValue<Encoding, SourceAllocator>& rhs, Allocator& allocator, bool copyConstStrings = false) {
        RAPIDJSON_ASSERT(static_cast<void*>(this) != static_cast<void const*>(&rhs));
        this->~GenericValue();
        new (this) GenericValue(rhs, allocator, copyConstStrings);
        return *this;
    }

    //! Exchange the contents of this value with those of other.
    /*!
        \param other Another value.
        \note Constant complexity.
    */
    GenericValue& Swap(GenericValue& other) RAPIDJSON_NOEXCEPT {
        GenericValue temp;
        temp.RawAssign(*this);
        RawAssign(other);
        other.RawAssign(temp);
        return *this;
    }

    //! free-standing swap function helper
    /*!
        Helper function to enable support for common swap implementation pattern based on \c std::swap:
        \code
        void swap(MyClass& a, MyClass& b) {
            using std::swap;
            swap(a.value, b.value);
            // ...
        }
        \endcode
        \see Swap()
     */
    friend inline void swap(GenericValue& a, GenericValue& b) RAPIDJSON_NOEXCEPT { a.Swap(b); }

    //! Prepare Value for move semantics
    /*! \return *this */
    GenericValue& Move() RAPIDJSON_NOEXCEPT { return *this; }
    //@}

    //!@name Equal-to and not-equal-to operators
    //@{
    //! Equal-to operator
    /*!
        \note If an object contains duplicated named member, comparing equality with any object is always \c false.
        \note Complexity is quadratic in Object's member number and linear for the rest (number of all values in the subtree and total lengths of all strings).
    */
    template <typename SourceAllocator>
    bool operator==(const GenericValue<Encoding, SourceAllocator>& rhs) const {
        typedef GenericValue<Encoding, SourceAllocator> RhsType;
        if (GetType() != rhs.GetType())
            return false;

        switch (GetType()) {
        case kObjectType: // Warning: O(n^2) inner-loop
            if (data_.o.size != rhs.data_.o.size)
                return false;           
            for (ConstMemberIterator lhsMemberItr = MemberBegin(); lhsMemberItr != MemberEnd(); ++lhsMemberItr) {
                typename RhsType::ConstMemberIterator rhsMemberItr = rhs.FindMember(lhsMemberItr->name);
                if (rhsMemberItr == rhs.MemberEnd() || (!(lhsMemberItr->value == rhsMemberItr->value)))
                    return false;
            }
            return true;
            
        case kArrayType:
            if (data_.a.size != rhs.data_.a.size)
                return false;
            for (SizeType i = 0; i < data_.a.size; i++)
                if (!((*this)[i] == rhs[i]))
                    return false;
            return true;

        case kStringType:
            return StringEqual(rhs);

        case kNumberType:
            if (IsDouble() || rhs.IsDouble()) {
                double a = GetDouble();     // May convert from integer to double.
                double b = rhs.GetDouble(); // Ditto
                return a >= b && a <= b;    // Prevent -Wfloat-equal
            }
            else
                return data_.n.u64 == rhs.data_.n.u64;

        default:
            return true;
        }
    }

    //! Equal-to operator with const C-string pointer
    bool operator==(const Ch* rhs) const { return *this == GenericValue(StringRef(rhs)); }

#if RAPIDJSON_HAS_STDSTRING
    //! Equal-to operator with string object
    /*! \note Requires the definition of the preprocessor symbol \ref RAPIDJSON_HAS_STDSTRING.
     */
    bool operator==(const std::basic_string<Ch>& rhs) const { return *this == GenericValue(StringRef(rhs)); }
#endif

    //! Equal-to operator with primitive types
    /*! \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t, \c double, \c true, \c false
    */
    template <typename T> RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>,internal::IsGenericValue<T> >), (bool)) operator==(const T& rhs) const { return *this == GenericValue(rhs); }

#ifndef __cpp_impl_three_way_comparison
    //! Not-equal-to operator
    /*! \return !(*this == rhs)
     */
    template <typename SourceAllocator>
    bool operator!=(const GenericValue<Encoding, SourceAllocator>& rhs) const { return !(*this == rhs); }

    //! Not-equal-to operator with const C-string pointer
    bool operator!=(const Ch* rhs) const { return !(*this == rhs); }

    //! Not-equal-to operator with arbitrary types
    /*! \return !(*this == rhs)
     */
    template <typename T> RAPIDJSON_DISABLEIF_RETURN((internal::IsGenericValue<T>), (bool)) operator!=(const T& rhs) const { return !(*this == rhs); }

    //! Equal-to operator with arbitrary types (symmetric version)
    /*! \return (rhs == lhs)
     */
    template <typename T> friend RAPIDJSON_DISABLEIF_RETURN((internal::IsGenericValue<T>), (bool)) operator==(const T& lhs, const GenericValue& rhs) { return rhs == lhs; }

    //! Not-Equal-to operator with arbitrary types (symmetric version)
    /*! \return !(rhs == lhs)
     */
    template <typename T> friend RAPIDJSON_DISABLEIF_RETURN((internal::IsGenericValue<T>), (bool)) operator!=(const T& lhs, const GenericValue& rhs) { return !(rhs == lhs); }
    //@}
#endif

    //!@name Type
    //@{

    Type GetType()  const { return static_cast<Type>(data_.f.flags & kTypeMask); }
    bool IsNull()   const { return data_.f.flags == kNullFlag; }
    bool IsFalse()  const { return data_.f.flags == kFalseFlag; }
    bool IsTrue()   const { return data_.f.flags == kTrueFlag; }
    bool IsBool()   const { return (data_.f.flags & kBoolFlag) != 0; }
    bool IsObject() const { return data_.f.flags == kObjectFlag; }
    bool IsArray()  const { return data_.f.flags == kArrayFlag; }
    bool IsNumber() const { return (data_.f.flags & kNumberFlag) != 0; }
    bool IsInt()    const { return (data_.f.flags & kIntFlag) != 0; }
    bool IsUint()   const { return (data_.f.flags & kUintFlag) != 0; }
    bool IsInt64()  const { return (data_.f.flags & kInt64Flag) != 0; }
    bool IsUint64() const { return (data_.f.flags & kUint64Flag) != 0; }
    bool IsDouble() const { return (data_.f.flags & kDoubleFlag) != 0; }
    bool IsString() const { return (data_.f.flags & kStringFlag) != 0; }

    // Checks whether a number can be losslessly converted to a double.
    bool IsLosslessDouble() const {
        if (!IsNumber()) return false;
        if (IsUint64()) {
            uint64_t u = GetUint64();
            volatile double d = static_cast<double>(u);
            return (d >= 0.0)
                && (d < static_cast<double>((std::numeric_limits<uint64_t>::max)()))
                && (u == static_cast<uint64_t>(d));
        }
        if (IsInt64()) {
            int64_t i = GetInt64();
            volatile double d = static_cast<double>(i);
            return (d >= static_cast<double>((std::numeric_limits<int64_t>::min)()))
                && (d < static_cast<double>((std::numeric_limits<int64_t>::max)()))
                && (i == static_cast<int64_t>(d));
        }
        return true; // double, int, uint are always lossless
    }

    // Checks whether a number is a float (possible lossy).
    bool IsFloat() const  {
        if ((data_.f.flags & kDoubleFlag) == 0)
            return false;
        double d = GetDouble();
        return d >= -3.4028234e38 && d <= 3.4028234e38;
    }
    // Checks whether a number can be losslessly converted to a float.
    bool IsLosslessFloat() const {
        if (!IsNumber()) return false;
        double a = GetDouble();
        if (a < static_cast<double>(-(std::numeric_limits<float>::max)())
                || a > static_cast<double>((std::numeric_limits<float>::max)()))
            return false;
        double b = static_cast<double>(static_cast<float>(a));
        return a >= b && a <= b;    // Prevent -Wfloat-equal
    }

    //@}

    //!@name Null
    //@{

    GenericValue& SetNull() { this->~GenericValue(); new (this) GenericValue(); return *this; }

    //@}

    //!@name Bool
    //@{

    bool GetBool() const { RAPIDJSON_ASSERT(IsBool()); return data_.f.flags == kTrueFlag; }
    //!< Set boolean value
    /*! \post IsBool() == true */
    GenericValue& SetBool(bool b) { this->~GenericValue(); new (this) GenericValue(b); return *this; }

    //@}

    //!@name Object
    //@{

    //! Set this value as an empty object.
    /*! \post IsObject() == true */
    GenericValue& SetObject() { this->~GenericValue(); new (this) GenericValue(kObjectType); return *this; }

    //! Get the number of members in the object.
    SizeType MemberCount() const { RAPIDJSON_ASSERT(IsObject()); return data_.o.size; }

    //! Get the capacity of object.
    SizeType MemberCapacity() const { RAPIDJSON_ASSERT(IsObject()); return data_.o.capacity; }

    //! Check whether the object is empty.
    bool ObjectEmpty() const { RAPIDJSON_ASSERT(IsObject()); return data_.o.size == 0; }

    //! Get a value from an object associated with the name.
    /*! \pre IsObject() == true
        \tparam T Either \c Ch or \c const \c Ch (template used for disambiguation with \ref operator[](SizeType))
        \note In version 0.1x, if the member is not found, this function returns a null value. This makes issue 7.
        Since 0.2, if the name is not correct, it will assert.
        If user is unsure whether a member exists, user should use HasMember() first.
        A better approach is to use FindMember().
        \note Linear time complexity.
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::NotExpr<internal::IsSame<typename internal::RemoveConst<T>::Type, Ch> >),(GenericValue&)) operator[](T* name) {
        GenericValue n(StringRef(name));
        return (*this)[n];
    }
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::NotExpr<internal::IsSame<typename internal::RemoveConst<T>::Type, Ch> >),(const GenericValue&)) operator[](T* name) const { return const_cast<GenericValue&>(*this)[name]; }

    //! Get a value from an object associated with the name.
    /*! \pre IsObject() == true
        \tparam SourceAllocator Allocator of the \c name value

        \note Compared to \ref operator[](T*), this version is faster because it does not need a StrLen().
        And it can also handle strings with embedded null characters.

        \note Linear time complexity.
    */
    template <typename SourceAllocator>
    GenericValue& operator[](const GenericValue<Encoding, SourceAllocator>& name) {
        MemberIterator member = FindMember(name);
        if (member != MemberEnd())
            return member->value;
        else {
            RAPIDJSON_ASSERT(false);    // see above note

#if RAPIDJSON_HAS_CXX11
            // Use thread-local storage to prevent races between threads.
            // Use static buffer and placement-new to prevent destruction, with
            // alignas() to ensure proper alignment.
            alignas(GenericValue) thread_local static char buffer[sizeof(GenericValue)];
            return *new (buffer) GenericValue();
#elif defined(_MSC_VER) && _MSC_VER < 1900
            // There's no way to solve both thread locality and proper alignment
            // simultaneously.
            __declspec(thread) static char buffer[sizeof(GenericValue)];
            return *new (buffer) GenericValue();
#elif defined(__GNUC__) || defined(__clang__)
            // This will generate -Wexit-time-destructors in clang, but that's
            // better than having under-alignment.
            __thread static GenericValue buffer;
            return buffer;
#else
            // Don't know what compiler this is, so don't know how to ensure
            // thread-locality.
            static GenericValue buffer;
            return buffer;
#endif
        }
    }
    template <typename SourceAllocator>
    const GenericValue& operator[](const GenericValue<Encoding, SourceAllocator>& name) const { return const_cast<GenericValue&>(*this)[name]; }

#if RAPIDJSON_HAS_STDSTRING
    //! Get a value from an object associated with name (string object).
    GenericValue& operator[](const std::basic_string<Ch>& name) { return (*this)[GenericValue(StringRef(name))]; }
    const GenericValue& operator[](const std::basic_string<Ch>& name) const { return (*this)[GenericValue(StringRef(name))]; }
#endif

    //! Const member iterator
    /*! \pre IsObject() == true */
    ConstMemberIterator MemberBegin() const { RAPIDJSON_ASSERT(IsObject()); return ConstMemberIterator(GetMembersPointer()); }
    //! Const \em past-the-end member iterator
    /*! \pre IsObject() == true */
    ConstMemberIterator MemberEnd() const   { RAPIDJSON_ASSERT(IsObject()); return ConstMemberIterator(GetMembersPointer() + data_.o.size); }
    //! Member iterator
    /*! \pre IsObject() == true */
    MemberIterator MemberBegin()            { RAPIDJSON_ASSERT(IsObject()); return MemberIterator(GetMembersPointer()); }
    //! \em Past-the-end member iterator
    /*! \pre IsObject() == true */
    MemberIterator MemberEnd()              { RAPIDJSON_ASSERT(IsObject()); return MemberIterator(GetMembersPointer() + data_.o.size); }

    //! Request the object to have enough capacity to store members.
    /*! \param newCapacity  The capacity that the object at least need to have.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \note Linear time complexity.
    */
    GenericValue& MemberReserve(SizeType newCapacity, Allocator &allocator) {
        RAPIDJSON_ASSERT(IsObject());
        DoReserveMembers(newCapacity, allocator);
        return *this;
    }

    //! Check whether a member exists in the object.
    /*!
        \param name Member name to be searched.
        \pre IsObject() == true
        \return Whether a member with that name exists.
        \note It is better to use FindMember() directly if you need the obtain the value as well.
        \note Linear time complexity.
    */
    bool HasMember(const Ch* name) const { return FindMember(name) != MemberEnd(); }

#if RAPIDJSON_HAS_STDSTRING
    //! Check whether a member exists in the object with string object.
    /*!
        \param name Member name to be searched.
        \pre IsObject() == true
        \return Whether a member with that name exists.
        \note It is better to use FindMember() directly if you need the obtain the value as well.
        \note Linear time complexity.
    */
    bool HasMember(const std::basic_string<Ch>& name) const { return FindMember(name) != MemberEnd(); }
#endif

    //! Check whether a member exists in the object with GenericValue name.
    /*!
        This version is faster because it does not need a StrLen(). It can also handle string with null character.
        \param name Member name to be searched.
        \pre IsObject() == true
        \return Whether a member with that name exists.
        \note It is better to use FindMember() directly if you need the obtain the value as well.
        \note Linear time complexity.
    */
    template <typename SourceAllocator>
    bool HasMember(const GenericValue<Encoding, SourceAllocator>& name) const { return FindMember(name) != MemberEnd(); }

    //! Find member by name.
    /*!
        \param name Member name to be searched.
        \pre IsObject() == true
        \return Iterator to member, if it exists.
            Otherwise returns \ref MemberEnd().

        \note Earlier versions of Rapidjson returned a \c NULL pointer, in case
            the requested member doesn't exist. For consistency with e.g.
            \c std::map, this has been changed to MemberEnd() now.
        \note Linear time complexity.
    */
    MemberIterator FindMember(const Ch* name) {
        GenericValue n(StringRef(name));
        return FindMember(n);
    }

    ConstMemberIterator FindMember(const Ch* name) const { return const_cast<GenericValue&>(*this).FindMember(name); }

    //! Find member by name.
    /*!
        This version is faster because it does not need a StrLen(). It can also handle string with null character.
        \param name Member name to be searched.
        \pre IsObject() == true
        \return Iterator to member, if it exists.
            Otherwise returns \ref MemberEnd().

        \note Earlier versions of Rapidjson returned a \c NULL pointer, in case
            the requested member doesn't exist. For consistency with e.g.
            \c std::map, this has been changed to MemberEnd() now.
        \note Linear time complexity.
    */
    template <typename SourceAllocator>
    MemberIterator FindMember(const GenericValue<Encoding, SourceAllocator>& name) {
        RAPIDJSON_ASSERT(IsObject());
        RAPIDJSON_ASSERT(name.IsString());
        return DoFindMember(name);
    }
    template <typename SourceAllocator> ConstMemberIterator FindMember(const GenericValue<Encoding, SourceAllocator>& name) const { return const_cast<GenericValue&>(*this).FindMember(name); }

#if RAPIDJSON_HAS_STDSTRING
    //! Find member by string object name.
    /*!
        \param name Member name to be searched.
        \pre IsObject() == true
        \return Iterator to member, if it exists.
            Otherwise returns \ref MemberEnd().
    */
    MemberIterator FindMember(const std::basic_string<Ch>& name) { return FindMember(GenericValue(StringRef(name))); }
    ConstMemberIterator FindMember(const std::basic_string<Ch>& name) const { return FindMember(GenericValue(StringRef(name))); }
#endif

    //! Add a member (name-value pair) to the object.
    /*! \param name A string value as name of member.
        \param value Value of any type.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \note The ownership of \c name and \c value will be transferred to this object on success.
        \pre  IsObject() && name.IsString()
        \post name.IsNull() && value.IsNull()
        \note Amortized Constant time complexity.
    */
    GenericValue& AddMember(GenericValue& name, GenericValue& value, Allocator& allocator) {
        RAPIDJSON_ASSERT(IsObject());
        RAPIDJSON_ASSERT(name.IsString());
        DoAddMember(name, value, allocator);
        return *this;
    }

    //! Add a constant string value as member (name-value pair) to the object.
    /*! \param name A string value as name of member.
        \param value constant string reference as value of member.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \pre  IsObject()
        \note This overload is needed to avoid clashes with the generic primitive type AddMember(GenericValue&,T,Allocator&) overload below.
        \note Amortized Constant time complexity.
    */
    GenericValue& AddMember(GenericValue& name, StringRefType value, Allocator& allocator) {
        GenericValue v(value);
        return AddMember(name, v, allocator);
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Add a string object as member (name-value pair) to the object.
    /*! \param name A string value as name of member.
        \param value constant string reference as value of member.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \pre  IsObject()
        \note This overload is needed to avoid clashes with the generic primitive type AddMember(GenericValue&,T,Allocator&) overload below.
        \note Amortized Constant time complexity.
    */
    GenericValue& AddMember(GenericValue& name, std::basic_string<Ch>& value, Allocator& allocator) {
        GenericValue v(value, allocator);
        return AddMember(name, v, allocator);
    }
#endif

    //! Add any primitive value as member (name-value pair) to the object.
    /*! \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t
        \param name A string value as name of member.
        \param value Value of primitive type \c T as value of member
        \param allocator Allocator for reallocating memory. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \pre  IsObject()

        \note The source type \c T explicitly disallows all pointer types,
            especially (\c const) \ref Ch*.  This helps avoiding implicitly
            referencing character strings with insufficient lifetime, use
            \ref AddMember(StringRefType, GenericValue&, Allocator&) or \ref
            AddMember(StringRefType, StringRefType, Allocator&).
            All other pointer types would implicitly convert to \c bool,
            use an explicit cast instead, if needed.
        \note Amortized Constant time complexity.
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (GenericValue&))
    AddMember(GenericValue& name, T value, Allocator& allocator) {
        GenericValue v(value);
        return AddMember(name, v, allocator);
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericValue& AddMember(GenericValue&& name, GenericValue&& value, Allocator& allocator) {
        return AddMember(name, value, allocator);
    }
    GenericValue& AddMember(GenericValue&& name, GenericValue& value, Allocator& allocator) {
        return AddMember(name, value, allocator);
    }
    GenericValue& AddMember(GenericValue& name, GenericValue&& value, Allocator& allocator) {
        return AddMember(name, value, allocator);
    }
    GenericValue& AddMember(StringRefType name, GenericValue&& value, Allocator& allocator) {
        GenericValue n(name);
        return AddMember(n, value, allocator);
    }
#endif // RAPIDJSON_HAS_CXX11_RVALUE_REFS


    //! Add a member (name-value pair) to the object.
    /*! \param name A constant string reference as name of member.
        \param value Value of any type.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \note The ownership of \c value will be transferred to this object on success.
        \pre  IsObject()
        \post value.IsNull()
        \note Amortized Constant time complexity.
    */
    GenericValue& AddMember(StringRefType name, GenericValue& value, Allocator& allocator) {
        GenericValue n(name);
        return AddMember(n, value, allocator);
    }

    //! Add a constant string value as member (name-value pair) to the object.
    /*! \param name A constant string reference as name of member.
        \param value constant string reference as value of member.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \pre  IsObject()
        \note This overload is needed to avoid clashes with the generic primitive type AddMember(StringRefType,T,Allocator&) overload below.
        \note Amortized Constant time complexity.
    */
    GenericValue& AddMember(StringRefType name, StringRefType value, Allocator& allocator) {
        GenericValue v(value);
        return AddMember(name, v, allocator);
    }

    //! Add any primitive value as member (name-value pair) to the object.
    /*! \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t
        \param name A constant string reference as name of member.
        \param value Value of primitive type \c T as value of member
        \param allocator Allocator for reallocating memory. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \pre  IsObject()

        \note The source type \c T explicitly disallows all pointer types,
            especially (\c const) \ref Ch*.  This helps avoiding implicitly
            referencing character strings with insufficient lifetime, use
            \ref AddMember(StringRefType, GenericValue&, Allocator&) or \ref
            AddMember(StringRefType, StringRefType, Allocator&).
            All other pointer types would implicitly convert to \c bool,
            use an explicit cast instead, if needed.
        \note Amortized Constant time complexity.
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (GenericValue&))
    AddMember(StringRefType name, T value, Allocator& allocator) {
        GenericValue n(name);
        return AddMember(n, value, allocator);
    }

    //! Remove all members in the object.
    /*! This function do not deallocate memory in the object, i.e. the capacity is unchanged.
        \note Linear time complexity.
    */
    void RemoveAllMembers() {
        RAPIDJSON_ASSERT(IsObject()); 
        DoClearMembers();
    }

    //! Remove a member in object by its name.
    /*! \param name Name of member to be removed.
        \return Whether the member existed.
        \note This function may reorder the object members. Use \ref
            EraseMember(ConstMemberIterator) if you need to preserve the
            relative order of the remaining members.
        \note Linear time complexity.
    */
    bool RemoveMember(const Ch* name) {
        GenericValue n(StringRef(name));
        return RemoveMember(n);
    }

#if RAPIDJSON_HAS_STDSTRING
    bool RemoveMember(const std::basic_string<Ch>& name) { return RemoveMember(GenericValue(StringRef(name))); }
#endif

    template <typename SourceAllocator>
    bool RemoveMember(const GenericValue<Encoding, SourceAllocator>& name) {
        MemberIterator m = FindMember(name);
        if (m != MemberEnd()) {
            RemoveMember(m);
            return true;
        }
        else
            return false;
    }

    //! Remove a member in object by iterator.
    /*! \param m member iterator (obtained by FindMember() or MemberBegin()).
        \return the new iterator after removal.
        \note This function may reorder the object members. Use \ref
            EraseMember(ConstMemberIterator) if you need to preserve the
            relative order of the remaining members.
        \note Constant time complexity.
    */
    MemberIterator RemoveMember(MemberIterator m) {
        RAPIDJSON_ASSERT(IsObject());
        RAPIDJSON_ASSERT(data_.o.size > 0);
        RAPIDJSON_ASSERT(GetMembersPointer() != 0);
        RAPIDJSON_ASSERT(m >= MemberBegin() && m < MemberEnd());
        return DoRemoveMember(m);
    }

    //! Remove a member from an object by iterator.
    /*! \param pos iterator to the member to remove
        \pre IsObject() == true && \ref MemberBegin() <= \c pos < \ref MemberEnd()
        \return Iterator following the removed element.
            If the iterator \c pos refers to the last element, the \ref MemberEnd() iterator is returned.
        \note This function preserves the relative order of the remaining object
            members. If you do not need this, use the more efficient \ref RemoveMember(MemberIterator).
        \note Linear time complexity.
    */
    MemberIterator EraseMember(ConstMemberIterator pos) {
        return EraseMember(pos, pos +1);
    }

    //! Remove members in the range [first, last) from an object.
    /*! \param first iterator to the first member to remove
        \param last  iterator following the last member to remove
        \pre IsObject() == true && \ref MemberBegin() <= \c first <= \c last <= \ref MemberEnd()
        \return Iterator following the last removed element.
        \note This function preserves the relative order of the remaining object
            members.
        \note Linear time complexity.
    */
    MemberIterator EraseMember(ConstMemberIterator first, ConstMemberIterator last) {
        RAPIDJSON_ASSERT(IsObject());
        RAPIDJSON_ASSERT(data_.o.size > 0);
        RAPIDJSON_ASSERT(GetMembersPointer() != 0);
        RAPIDJSON_ASSERT(first >= MemberBegin());
        RAPIDJSON_ASSERT(first <= last);
        RAPIDJSON_ASSERT(last <= MemberEnd());
        return DoEraseMembers(first, last);
    }

    //! Erase a member in object by its name.
    /*! \param name Name of member to be removed.
        \return Whether the member existed.
        \note Linear time complexity.
    */
    bool EraseMember(const Ch* name) {
        GenericValue n(StringRef(name));
        return EraseMember(n);
    }

#if RAPIDJSON_HAS_STDSTRING
    bool EraseMember(const std::basic_string<Ch>& name) { return EraseMember(GenericValue(StringRef(name))); }
#endif

    template <typename SourceAllocator>
    bool EraseMember(const GenericValue<Encoding, SourceAllocator>& name) {
        MemberIterator m = FindMember(name);
        if (m != MemberEnd()) {
            EraseMember(m);
            return true;
        }
        else
            return false;
    }

    Object GetObject() { RAPIDJSON_ASSERT(IsObject()); return Object(*this); }
    Object GetObj() { RAPIDJSON_ASSERT(IsObject()); return Object(*this); }
    ConstObject GetObject() const { RAPIDJSON_ASSERT(IsObject()); return ConstObject(*this); }
    ConstObject GetObj() const { RAPIDJSON_ASSERT(IsObject()); return ConstObject(*this); }

    //@}

    //!@name Array
    //@{

    //! Set this value as an empty array.
    /*! \post IsArray == true */
    GenericValue& SetArray() { this->~GenericValue(); new (this) GenericValue(kArrayType); return *this; }

    //! Get the number of elements in array.
    SizeType Size() const { RAPIDJSON_ASSERT(IsArray()); return data_.a.size; }

    //! Get the capacity of array.
    SizeType Capacity() const { RAPIDJSON_ASSERT(IsArray()); return data_.a.capacity; }

    //! Check whether the array is empty.
    bool Empty() const { RAPIDJSON_ASSERT(IsArray()); return data_.a.size == 0; }

    //! Remove all elements in the array.
    /*! This function do not deallocate memory in the array, i.e. the capacity is unchanged.
        \note Linear time complexity.
    */
    void Clear() {
        RAPIDJSON_ASSERT(IsArray()); 
        GenericValue* e = GetElementsPointer();
        for (GenericValue* v = e; v != e + data_.a.size; ++v)
            v->~GenericValue();
        data_.a.size = 0;
    }

    //! Get an element from array by index.
    /*! \pre IsArray() == true
        \param index Zero-based index of element.
        \see operator[](T*)
    */
    GenericValue& operator[](SizeType index) {
        RAPIDJSON_ASSERT(IsArray());
        RAPIDJSON_ASSERT(index < data_.a.size);
        return GetElementsPointer()[index];
    }
    const GenericValue& operator[](SizeType index) const { return const_cast<GenericValue&>(*this)[index]; }

    //! Element iterator
    /*! \pre IsArray() == true */
    ValueIterator Begin() { RAPIDJSON_ASSERT(IsArray()); return GetElementsPointer(); }
    //! \em Past-the-end element iterator
    /*! \pre IsArray() == true */
    ValueIterator End() { RAPIDJSON_ASSERT(IsArray()); return GetElementsPointer() + data_.a.size; }
    //! Constant element iterator
    /*! \pre IsArray() == true */
    ConstValueIterator Begin() const { return const_cast<GenericValue&>(*this).Begin(); }
    //! Constant \em past-the-end element iterator
    /*! \pre IsArray() == true */
    ConstValueIterator End() const { return const_cast<GenericValue&>(*this).End(); }

    //! Request the array to have enough capacity to store elements.
    /*! \param newCapacity  The capacity that the array at least need to have.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \note Linear time complexity.
    */
    GenericValue& Reserve(SizeType newCapacity, Allocator &allocator) {
        RAPIDJSON_ASSERT(IsArray());
        if (newCapacity > data_.a.capacity) {
            SetElementsPointer(reinterpret_cast<GenericValue*>(allocator.Realloc(GetElementsPointer(), data_.a.capacity * sizeof(GenericValue), newCapacity * sizeof(GenericValue))));
            data_.a.capacity = newCapacity;
        }
        return *this;
    }

    //! Append a GenericValue at the end of the array.
    /*! \param value        Value to be appended.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \pre IsArray() == true
        \post value.IsNull() == true
        \return The value itself for fluent API.
        \note The ownership of \c value will be transferred to this array on success.
        \note If the number of elements to be appended is known, calls Reserve() once first may be more efficient.
        \note Amortized constant time complexity.
    */
    GenericValue& PushBack(GenericValue& value, Allocator& allocator) {
        RAPIDJSON_ASSERT(IsArray());
        if (data_.a.size >= data_.a.capacity)
            Reserve(data_.a.capacity == 0 ? kDefaultArrayCapacity : (data_.a.capacity + (data_.a.capacity + 1) / 2), allocator);
        GetElementsPointer()[data_.a.size++].RawAssign(value);
        return *this;
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericValue& PushBack(GenericValue&& value, Allocator& allocator) {
        return PushBack(value, allocator);
    }
#endif // RAPIDJSON_HAS_CXX11_RVALUE_REFS

    //! Append a constant string reference at the end of the array.
    /*! \param value        Constant string reference to be appended.
        \param allocator    Allocator for reallocating memory. It must be the same one used previously. Commonly use GenericDocument::GetAllocator().
        \pre IsArray() == true
        \return The value itself for fluent API.
        \note If the number of elements to be appended is known, calls Reserve() once first may be more efficient.
        \note Amortized constant time complexity.
        \see GenericStringRef
    */
    GenericValue& PushBack(StringRefType value, Allocator& allocator) {
        return (*this).template PushBack<StringRefType>(value, allocator);
    }

    //! Append a primitive value at the end of the array.
    /*! \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t
        \param value Value of primitive type T to be appended.
        \param allocator    Allocator for reallocating memory. It must be the same one as used before. Commonly use GenericDocument::GetAllocator().
        \pre IsArray() == true
        \return The value itself for fluent API.
        \note If the number of elements to be appended is known, calls Reserve() once first may be more efficient.

        \note The source type \c T explicitly disallows all pointer types,
            especially (\c const) \ref Ch*.  This helps avoiding implicitly
            referencing character strings with insufficient lifetime, use
            \ref PushBack(GenericValue&, Allocator&) or \ref
            PushBack(StringRefType, Allocator&).
            All other pointer types would implicitly convert to \c bool,
            use an explicit cast instead, if needed.
        \note Amortized constant time complexity.
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (GenericValue&))
    PushBack(T value, Allocator& allocator) {
        GenericValue v(value);
        return PushBack(v, allocator);
    }

    //! Remove the last element in the array.
    /*!
        \note Constant time complexity.
    */
    GenericValue& PopBack() {
        RAPIDJSON_ASSERT(IsArray());
        RAPIDJSON_ASSERT(!Empty());
        GetElementsPointer()[--data_.a.size].~GenericValue();
        return *this;
    }

    //! Remove an element of array by iterator.
    /*!
        \param pos iterator to the element to remove
        \pre IsArray() == true && \ref Begin() <= \c pos < \ref End()
        \return Iterator following the removed element. If the iterator pos refers to the last element, the End() iterator is returned.
        \note Linear time complexity.
    */
    ValueIterator Erase(ConstValueIterator pos) {
        return Erase(pos, pos + 1);
    }

    //! Remove elements in the range [first, last) of the array.
    /*!
        \param first iterator to the first element to remove
        \param last  iterator following the last element to remove
        \pre IsArray() == true && \ref Begin() <= \c first <= \c last <= \ref End()
        \return Iterator following the last removed element.
        \note Linear time complexity.
    */
    ValueIterator Erase(ConstValueIterator first, ConstValueIterator last) {
        RAPIDJSON_ASSERT(IsArray());
        RAPIDJSON_ASSERT(data_.a.size > 0);
        RAPIDJSON_ASSERT(GetElementsPointer() != 0);
        RAPIDJSON_ASSERT(first >= Begin());
        RAPIDJSON_ASSERT(first <= last);
        RAPIDJSON_ASSERT(last <= End());
        ValueIterator pos = Begin() + (first - Begin());
        for (ValueIterator itr = pos; itr != last; ++itr)
            itr->~GenericValue();
        std::memmove(static_cast<void*>(pos), last, static_cast<size_t>(End() - last) * sizeof(GenericValue));
        data_.a.size -= static_cast<SizeType>(last - first);
        return pos;
    }

    Array GetArray() { RAPIDJSON_ASSERT(IsArray()); return Array(*this); }
    ConstArray GetArray() const { RAPIDJSON_ASSERT(IsArray()); return ConstArray(*this); }

    //@}

    //!@name Number
    //@{

    int GetInt() const          { RAPIDJSON_ASSERT(data_.f.flags & kIntFlag);   return data_.n.i.i;   }
    unsigned GetUint() const    { RAPIDJSON_ASSERT(data_.f.flags & kUintFlag);  return data_.n.u.u;   }
    int64_t GetInt64() const    { RAPIDJSON_ASSERT(data_.f.flags & kInt64Flag); return data_.n.i64; }
    uint64_t GetUint64() const  { RAPIDJSON_ASSERT(data_.f.flags & kUint64Flag); return data_.n.u64; }

    //! Get the value as double type.
    /*! \note If the value is 64-bit integer type, it may lose precision. Use \c IsLosslessDouble() to check whether the converison is lossless.
    */
    double GetDouble() const {
        RAPIDJSON_ASSERT(IsNumber());
        if ((data_.f.flags & kDoubleFlag) != 0)                return data_.n.d;   // exact type, no conversion.
        if ((data_.f.flags & kIntFlag) != 0)                   return data_.n.i.i; // int -> double
        if ((data_.f.flags & kUintFlag) != 0)                  return data_.n.u.u; // unsigned -> double
        if ((data_.f.flags & kInt64Flag) != 0)                 return static_cast<double>(data_.n.i64); // int64_t -> double (may lose precision)
        RAPIDJSON_ASSERT((data_.f.flags & kUint64Flag) != 0);  return static_cast<double>(data_.n.u64); // uint64_t -> double (may lose precision)
    }

    //! Get the value as float type.
    /*! \note If the value is 64-bit integer type, it may lose precision. Use \c IsLosslessFloat() to check whether the converison is lossless.
    */
    float GetFloat() const {
        return static_cast<float>(GetDouble());
    }

    GenericValue& SetInt(int i)             { this->~GenericValue(); new (this) GenericValue(i);    return *this; }
    GenericValue& SetUint(unsigned u)       { this->~GenericValue(); new (this) GenericValue(u);    return *this; }
    GenericValue& SetInt64(int64_t i64)     { this->~GenericValue(); new (this) GenericValue(i64);  return *this; }
    GenericValue& SetUint64(uint64_t u64)   { this->~GenericValue(); new (this) GenericValue(u64);  return *this; }
    GenericValue& SetDouble(double d)       { this->~GenericValue(); new (this) GenericValue(d);    return *this; }
    GenericValue& SetFloat(float f)         { this->~GenericValue(); new (this) GenericValue(static_cast<double>(f)); return *this; }

    //@}

    //!@name String
    //@{

    const Ch* GetString() const { RAPIDJSON_ASSERT(IsString()); return DataString(data_); }

    //! Get the length of string.
    /*! Since rapidjson permits "\\u0000" in the json string, strlen(v.GetString()) may not equal to v.GetStringLength().
    */
    SizeType GetStringLength() const { RAPIDJSON_ASSERT(IsString()); return DataStringLength(data_); }

    //! Set this value as a string without copying source string.
    /*! This version has better performance with supplied length, and also support string containing null character.
        \param s source string pointer. 
        \param length The length of source string, excluding the trailing null terminator.
        \return The value itself for fluent API.
        \post IsString() == true && GetString() == s && GetStringLength() == length
        \see SetString(StringRefType)
    */
    GenericValue& SetString(const Ch* s, SizeType length) { return SetString(StringRef(s, length)); }

    //! Set this value as a string without copying source string.
    /*! \param s source string reference
        \return The value itself for fluent API.
        \post IsString() == true && GetString() == s && GetStringLength() == s.length
    */
    GenericValue& SetString(StringRefType s) { this->~GenericValue(); SetStringRaw(s); return *this; }

    //! Set this value as a string by copying from source string.
    /*! This version has better performance with supplied length, and also support string containing null character.
        \param s source string. 
        \param length The length of source string, excluding the trailing null terminator.
        \param allocator Allocator for allocating copied buffer. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \post IsString() == true && GetString() != s && strcmp(GetString(),s) == 0 && GetStringLength() == length
    */
    GenericValue& SetString(const Ch* s, SizeType length, Allocator& allocator) { return SetString(StringRef(s, length), allocator); }

    //! Set this value as a string by copying from source string.
    /*! \param s source string. 
        \param allocator Allocator for allocating copied buffer. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \post IsString() == true && GetString() != s && strcmp(GetString(),s) == 0 && GetStringLength() == length
    */
    GenericValue& SetString(const Ch* s, Allocator& allocator) { return SetString(StringRef(s), allocator); }

    //! Set this value as a string by copying from source string.
    /*! \param s source string reference
        \param allocator Allocator for allocating copied buffer. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \post IsString() == true && GetString() != s.s && strcmp(GetString(),s) == 0 && GetStringLength() == length
    */
    GenericValue& SetString(StringRefType s, Allocator& allocator) { this->~GenericValue(); SetStringRaw(s, allocator); return *this; }

#if RAPIDJSON_HAS_STDSTRING
    //! Set this value as a string by copying from source string.
    /*! \param s source string.
        \param allocator Allocator for allocating copied buffer. Commonly use GenericDocument::GetAllocator().
        \return The value itself for fluent API.
        \post IsString() == true && GetString() != s.data() && strcmp(GetString(),s.data() == 0 && GetStringLength() == s.size()
        \note Requires the definition of the preprocessor symbol \ref RAPIDJSON_HAS_STDSTRING.
    */
    GenericValue& SetString(const std::basic_string<Ch>& s, Allocator& allocator) { return SetString(StringRef(s), allocator); }
#endif

    //@}

    //!@name Array
    //@{

    //! Templated version for checking whether this value is type T.
    /*!
        \tparam T Either \c bool, \c int, \c unsigned, \c int64_t, \c uint64_t, \c double, \c float, \c const \c char*, \c std::basic_string<Ch>
    */
    template <typename T>
    bool Is() const { return internal::TypeHelper<ValueType, T>::Is(*this); }

    template <typename T>
    T Get() const { return internal::TypeHelper<ValueType, T>::Get(*this); }

    template <typename T>
    T Get() { return internal::TypeHelper<ValueType, T>::Get(*this); }

    template<typename T>
    ValueType& Set(const T& data) { return internal::TypeHelper<ValueType, T>::Set(*this, data); }

    template<typename T>
    ValueType& Set(const T& data, AllocatorType& allocator) { return internal::TypeHelper<ValueType, T>::Set(*this, data, allocator); }

    //@}

    //! Generate events of this value to a Handler.
    /*! This function adopts the GoF visitor pattern.
        Typical usage is to output this JSON value as JSON text via Writer, which is a Handler.
        It can also be used to deep clone this value via GenericDocument, which is also a Handler.
        \tparam Handler type of handler.
        \param handler An object implementing concept Handler.
    */
    template <typename Handler>
    bool Accept(Handler& handler) const {
        switch(GetType()) {
        case kNullType:     return handler.Null();
        case kFalseType:    return handler.Bool(false);
        case kTrueType:     return handler.Bool(true);

        case kObjectType:
            if (RAPIDJSON_UNLIKELY(!handler.StartObject()))
                return false;
            for (ConstMemberIterator m = MemberBegin(); m != MemberEnd(); ++m) {
                RAPIDJSON_ASSERT(m->name.IsString()); // User may change the type of name by MemberIterator.
                if (RAPIDJSON_UNLIKELY(!handler.Key(m->name.GetString(), m->name.GetStringLength(), (m->name.data_.f.flags & kCopyFlag) != 0)))
                    return false;
                if (RAPIDJSON_UNLIKELY(!m->value.Accept(handler)))
                    return false;
            }
            return handler.EndObject(data_.o.size);

        case kArrayType:
            if (RAPIDJSON_UNLIKELY(!handler.StartArray()))
                return false;
            for (ConstValueIterator v = Begin(); v != End(); ++v)
                if (RAPIDJSON_UNLIKELY(!v->Accept(handler)))
                    return false;
            return handler.EndArray(data_.a.size);
    
        case kStringType:
            return handler.String(GetString(), GetStringLength(), (data_.f.flags & kCopyFlag) != 0);
    
        default:
            RAPIDJSON_ASSERT(GetType() == kNumberType);
            if (IsDouble())         return handler.Double(data_.n.d);
            else if (IsInt())       return handler.Int(data_.n.i.i);
            else if (IsUint())      return handler.Uint(data_.n.u.u);
            else if (IsInt64())     return handler.Int64(data_.n.i64);
            else                    return handler.Uint64(data_.n.u64);
        }
    }

private:
    template <typename, typename> friend class GenericValue;
    template <typename, typename, typename> friend class GenericDocument;

    enum {
        kBoolFlag       = 0x0008,
        kNumberFlag     = 0x0010,
        kIntFlag        = 0x0020,
        kUintFlag       = 0x0040,
        kInt64Flag      = 0x0080,
        kUint64Flag     = 0x0100,
        kDoubleFlag     = 0x0200,
        kStringFlag     = 0x0400,
        kCopyFlag       = 0x0800,
        kInlineStrFlag  = 0x1000,

        // Initial flags of different types.
        kNullFlag = kNullType,
        // These casts are added to suppress the warning on MSVC about bitwise operations between enums of different types.
        kTrueFlag = static_cast<int>(kTrueType) | static_cast<int>(kBoolFlag),
        kFalseFlag = static_cast<int>(kFalseType) | static_cast<int>(kBoolFlag),
        kNumberIntFlag = static_cast<int>(kNumberType) | static_cast<int>(kNumberFlag | kIntFlag | kInt64Flag),
        kNumberUintFlag = static_cast<int>(kNumberType) | static_cast<int>(kNumberFlag | kUintFlag | kUint64Flag | kInt64Flag),
        kNumberInt64Flag = static_cast<int>(kNumberType) | static_cast<int>(kNumberFlag | kInt64Flag),
        kNumberUint64Flag = static_cast<int>(kNumberType) | static_cast<int>(kNumberFlag | kUint64Flag),
        kNumberDoubleFlag = static_cast<int>(kNumberType) | static_cast<int>(kNumberFlag | kDoubleFlag),
        kNumberAnyFlag = static_cast<int>(kNumberType) | static_cast<int>(kNumberFlag | kIntFlag | kInt64Flag | kUintFlag | kUint64Flag | kDoubleFlag),
        kConstStringFlag = static_cast<int>(kStringType) | static_cast<int>(kStringFlag),
        kCopyStringFlag = static_cast<int>(kStringType) | static_cast<int>(kStringFlag | kCopyFlag),
        kShortStringFlag = static_cast<int>(kStringType) | static_cast<int>(kStringFlag | kCopyFlag | kInlineStrFlag),
        kObjectFlag = kObjectType,
        kArrayFlag = kArrayType,

        kTypeMask = 0x07
    };

    static const SizeType kDefaultArrayCapacity = RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY;
    static const SizeType kDefaultObjectCapacity = RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY;

    struct Flag {
#if RAPIDJSON_48BITPOINTER_OPTIMIZATION
        char payload[sizeof(SizeType) * 2 + 6];     // 2 x SizeType + lower 48-bit pointer
#elif RAPIDJSON_64BIT
        char payload[sizeof(SizeType) * 2 + sizeof(void*) + 6]; // 6 padding bytes
#else
        char payload[sizeof(SizeType) * 2 + sizeof(void*) + 2]; // 2 padding bytes
#endif
        uint16_t flags;
    };

    struct String {
        SizeType length;
        SizeType hashcode;  //!< reserved
        const Ch* str;
    };  // 12 bytes in 32-bit mode, 16 bytes in 64-bit mode

    // implementation detail: ShortString can represent zero-terminated strings up to MaxSize chars
    // (excluding the terminating zero) and store a value to determine the length of the contained
    // string in the last character str[LenPos] by storing "MaxSize - length" there. If the string
    // to store has the maximal length of MaxSize then str[LenPos] will be 0 and therefore act as
    // the string terminator as well. For getting the string length back from that value just use
    // "MaxSize - str[LenPos]".
    // This allows to store 13-chars strings in 32-bit mode, 21-chars strings in 64-bit mode,
    // 13-chars strings for RAPIDJSON_48BITPOINTER_OPTIMIZATION=1 inline (for `UTF8`-encoded strings).
    struct ShortString {
        enum { MaxChars = sizeof(static_cast<Flag*>(0)->payload) / sizeof(Ch), MaxSize = MaxChars - 1, LenPos = MaxSize };
        Ch str[MaxChars];

        inline static bool Usable(SizeType len) { return                       (MaxSize >= len); }
        inline void     SetLength(SizeType len) { str[LenPos] = static_cast<Ch>(MaxSize -  len); }
        inline SizeType GetLength() const       { return  static_cast<SizeType>(MaxSize -  str[LenPos]); }
    };  // at most as many bytes as "String" above => 12 bytes in 32-bit mode, 16 bytes in 64-bit mode

    // By using proper binary layout, retrieval of different integer types do not need conversions.
    union Number {
#if RAPIDJSON_ENDIAN == RAPIDJSON_LITTLEENDIAN
        struct I {
            int i;
            char padding[4];
        }i;
        struct U {
            unsigned u;
            char padding2[4];
        }u;
#else
        struct I {
            char padding[4];
            int i;
        }i;
        struct U {
            char padding2[4];
            unsigned u;
        }u;
#endif
        int64_t i64;
        uint64_t u64;
        double d;
    };  // 8 bytes

    struct ObjectData {
        SizeType size;
        SizeType capacity;
        Member* members;
    };  // 12 bytes in 32-bit mode, 16 bytes in 64-bit mode

    struct ArrayData {
        SizeType size;
        SizeType capacity;
        GenericValue* elements;
    };  // 12 bytes in 32-bit mode, 16 bytes in 64-bit mode

    union Data {
        String s;
        ShortString ss;
        Number n;
        ObjectData o;
        ArrayData a;
        Flag f;
    };  // 16 bytes in 32-bit mode, 24 bytes in 64-bit mode, 16 bytes in 64-bit with RAPIDJSON_48BITPOINTER_OPTIMIZATION

    static RAPIDJSON_FORCEINLINE const Ch* DataString(const Data& data) {
        return (data.f.flags & kInlineStrFlag) ? data.ss.str : RAPIDJSON_GETPOINTER(Ch, data.s.str);
    }
    static RAPIDJSON_FORCEINLINE SizeType DataStringLength(const Data& data) {
        return (data.f.flags & kInlineStrFlag) ? data.ss.GetLength() : data.s.length;
    }

    RAPIDJSON_FORCEINLINE const Ch* GetStringPointer() const { return RAPIDJSON_GETPOINTER(Ch, data_.s.str); }
    RAPIDJSON_FORCEINLINE const Ch* SetStringPointer(const Ch* str) { return RAPIDJSON_SETPOINTER(Ch, data_.s.str, str); }
    RAPIDJSON_FORCEINLINE GenericValue* GetElementsPointer() const { return RAPIDJSON_GETPOINTER(GenericValue, data_.a.elements); }
    RAPIDJSON_FORCEINLINE GenericValue* SetElementsPointer(GenericValue* elements) { return RAPIDJSON_SETPOINTER(GenericValue, data_.a.elements, elements); }
    RAPIDJSON_FORCEINLINE Member* GetMembersPointer() const { return RAPIDJSON_GETPOINTER(Member, data_.o.members); }
    RAPIDJSON_FORCEINLINE Member* SetMembersPointer(Member* members) { return RAPIDJSON_SETPOINTER(Member, data_.o.members, members); }

#if RAPIDJSON_USE_MEMBERSMAP

    struct MapTraits {
        struct Less {
            bool operator()(const Data& s1, const Data& s2) const {
                SizeType n1 = DataStringLength(s1), n2 = DataStringLength(s2);
                int cmp = std::memcmp(DataString(s1), DataString(s2), sizeof(Ch) * (n1 < n2 ? n1 : n2));
                return cmp < 0 || (cmp == 0 && n1 < n2);
            }
        };
        typedef std::pair<const Data, SizeType> Pair;
        typedef std::multimap<Data, SizeType, Less, StdAllocator<Pair, Allocator> > Map;
        typedef typename Map::iterator Iterator;
    };
    typedef typename MapTraits::Map         Map;
    typedef typename MapTraits::Less        MapLess;
    typedef typename MapTraits::Pair        MapPair;
    typedef typename MapTraits::Iterator    MapIterator;

    //
    // Layout of the members' map/array, re(al)located according to the needed capacity:
    //
    //    {Map*}<>{capacity}<>{Member[capacity]}<>{MapIterator[capacity]}
    //
    // (where <> stands for the RAPIDJSON_ALIGN-ment, if needed)
    //

    static RAPIDJSON_FORCEINLINE size_t GetMapLayoutSize(SizeType capacity) {
        return RAPIDJSON_ALIGN(sizeof(Map*)) +
               RAPIDJSON_ALIGN(sizeof(SizeType)) +
               RAPIDJSON_ALIGN(capacity * sizeof(Member)) +
               capacity * sizeof(MapIterator);
    }

    static RAPIDJSON_FORCEINLINE SizeType &GetMapCapacity(Map* &map) {
        return *reinterpret_cast<SizeType*>(reinterpret_cast<uintptr_t>(&map) +
                                            RAPIDJSON_ALIGN(sizeof(Map*)));
    }

    static RAPIDJSON_FORCEINLINE Member* GetMapMembers(Map* &map) {
        return reinterpret_cast<Member*>(reinterpret_cast<uintptr_t>(&map) +
                                         RAPIDJSON_ALIGN(sizeof(Map*)) +
                                         RAPIDJSON_ALIGN(sizeof(SizeType)));
    }

    static RAPIDJSON_FORCEINLINE MapIterator* GetMapIterators(Map* &map) {
        return reinterpret_cast<MapIterator*>(reinterpret_cast<uintptr_t>(&map) +
                                              RAPIDJSON_ALIGN(sizeof(Map*)) +
                                              RAPIDJSON_ALIGN(sizeof(SizeType)) +
                                              RAPIDJSON_ALIGN(GetMapCapacity(map) * sizeof(Member)));
    }

    static RAPIDJSON_FORCEINLINE Map* &GetMap(Member* members) {
        RAPIDJSON_ASSERT(members != 0);
        return *reinterpret_cast<Map**>(reinterpret_cast<uintptr_t>(members) -
                                        RAPIDJSON_ALIGN(sizeof(SizeType)) -
                                        RAPIDJSON_ALIGN(sizeof(Map*)));
    }

    // Some compilers' debug mechanisms want all iterators to be destroyed, for their accounting..
    RAPIDJSON_FORCEINLINE MapIterator DropMapIterator(MapIterator& rhs) {
#if RAPIDJSON_HAS_CXX11
        MapIterator ret = std::move(rhs);
#else
        MapIterator ret = rhs;
#endif
        rhs.~MapIterator();
        return ret;
    }

    Map* &DoReallocMap(Map** oldMap, SizeType newCapacity, Allocator& allocator) {
        Map **newMap = static_cast<Map**>(allocator.Malloc(GetMapLayoutSize(newCapacity)));
        GetMapCapacity(*newMap) = newCapacity;
        if (!oldMap) {
            *newMap = new (allocator.Malloc(sizeof(Map))) Map(MapLess(), allocator);
        }
        else {
            *newMap = *oldMap;
            size_t count = (*oldMap)->size();
            std::memcpy(static_cast<void*>(GetMapMembers(*newMap)),
                        static_cast<void*>(GetMapMembers(*oldMap)),
                        count * sizeof(Member));
            MapIterator *oldIt = GetMapIterators(*oldMap),
                        *newIt = GetMapIterators(*newMap);
            while (count--) {
                new (&newIt[count]) MapIterator(DropMapIterator(oldIt[count]));
            }
            Allocator::Free(oldMap);
        }
        return *newMap;
    }

    RAPIDJSON_FORCEINLINE Member* DoAllocMembers(SizeType capacity, Allocator& allocator) {
        return GetMapMembers(DoReallocMap(0, capacity, allocator));
    }

    void DoReserveMembers(SizeType newCapacity, Allocator& allocator) {
        ObjectData& o = data_.o;
        if (newCapacity > o.capacity) {
            Member* oldMembers = GetMembersPointer();
            Map **oldMap = oldMembers ? &GetMap(oldMembers) : 0,
                *&newMap = DoReallocMap(oldMap, newCapacity, allocator);
            RAPIDJSON_SETPOINTER(Member, o.members, GetMapMembers(newMap));
            o.capacity = newCapacity;
        }
    }

    template <typename SourceAllocator>
    MemberIterator DoFindMember(const GenericValue<Encoding, SourceAllocator>& name) {
        if (Member* members = GetMembersPointer()) {
            Map* &map = GetMap(members);
            MapIterator mit = map->find(reinterpret_cast<const Data&>(name.data_));
            if (mit != map->end()) {
                return MemberIterator(&members[mit->second]);
            }
        }
        return MemberEnd();
    }

    void DoClearMembers() {
        if (Member* members = GetMembersPointer()) {
            Map* &map = GetMap(members);
            MapIterator* mit = GetMapIterators(map);
            for (SizeType i = 0; i < data_.o.size; i++) {
                map->erase(DropMapIterator(mit[i]));
                members[i].~Member();
            }
            data_.o.size = 0;
        }
    }

    void DoFreeMembers() {
        if (Member* members = GetMembersPointer()) {
            GetMap(members)->~Map();
            for (SizeType i = 0; i < data_.o.size; i++) {
                members[i].~Member();
            }
            if (Allocator::kNeedFree) { // Shortcut by Allocator's trait
                Map** map = &GetMap(members);
                Allocator::Free(*map);
                Allocator::Free(map);
            }
        }
    }

#else // !RAPIDJSON_USE_MEMBERSMAP

    RAPIDJSON_FORCEINLINE Member* DoAllocMembers(SizeType capacity, Allocator& allocator) {
        return Malloc<Member>(allocator, capacity);
    }

    void DoReserveMembers(SizeType newCapacity, Allocator& allocator) {
        ObjectData& o = data_.o;
        if (newCapacity > o.capacity) {
            Member* newMembers = Realloc<Member>(allocator, GetMembersPointer(), o.capacity, newCapacity);
            RAPIDJSON_SETPOINTER(Member, o.members, newMembers);
            o.capacity = newCapacity;
        }
    }

    template <typename SourceAllocator>
    MemberIterator DoFindMember(const GenericValue<Encoding, SourceAllocator>& name) {
        MemberIterator member = MemberBegin();
        for ( ; member != MemberEnd(); ++member)
            if (name.StringEqual(member->name))
                break;
        return member;
    }

    void DoClearMembers() {
        for (MemberIterator m = MemberBegin(); m != MemberEnd(); ++m)
            m->~Member();
        data_.o.size = 0;
    }

    void DoFreeMembers() {
        for (MemberIterator m = MemberBegin(); m != MemberEnd(); ++m)
            m->~Member();
        Allocator::Free(GetMembersPointer());
    }

#endif // !RAPIDJSON_USE_MEMBERSMAP

    void DoAddMember(GenericValue& name, GenericValue& value, Allocator& allocator) {
        ObjectData& o = data_.o;
        if (o.size >= o.capacity)
            DoReserveMembers(o.capacity ? (o.capacity + (o.capacity + 1) / 2) : kDefaultObjectCapacity, allocator);
        Member* members = GetMembersPointer();
        Member* m = members + o.size;
        m->name.RawAssign(name);
        m->value.RawAssign(value);
#if RAPIDJSON_USE_MEMBERSMAP
        Map* &map = GetMap(members);
        MapIterator* mit = GetMapIterators(map);
        new (&mit[o.size]) MapIterator(map->insert(MapPair(m->name.data_, o.size)));
#endif
        ++o.size;
    }

    MemberIterator DoRemoveMember(MemberIterator m) {
        ObjectData& o = data_.o;
        Member* members = GetMembersPointer();
#if RAPIDJSON_USE_MEMBERSMAP
        Map* &map = GetMap(members);
        MapIterator* mit = GetMapIterators(map);
        SizeType mpos = static_cast<SizeType>(&*m - members);
        map->erase(DropMapIterator(mit[mpos]));
#endif
        MemberIterator last(members + (o.size - 1));
        if (o.size > 1 && m != last) {
#if RAPIDJSON_USE_MEMBERSMAP
            new (&mit[mpos]) MapIterator(DropMapIterator(mit[&*last - members]));
            mit[mpos]->second = mpos;
#endif
            *m = *last; // Move the last one to this place
        }
        else {
            m->~Member(); // Only one left, just destroy
        }
        --o.size;
        return m;
    }

    MemberIterator DoEraseMembers(ConstMemberIterator first, ConstMemberIterator last) {
        ObjectData& o = data_.o;
        MemberIterator beg = MemberBegin(),
                       pos = beg + (first - beg),
                       end = MemberEnd();
#if RAPIDJSON_USE_MEMBERSMAP
        Map* &map = GetMap(GetMembersPointer());
        MapIterator* mit = GetMapIterators(map);
#endif
        for (MemberIterator itr = pos; itr != last; ++itr) {
#if RAPIDJSON_USE_MEMBERSMAP
            map->erase(DropMapIterator(mit[itr - beg]));
#endif
            itr->~Member();
        }
#if RAPIDJSON_USE_MEMBERSMAP
        if (first != last) {
            // Move remaining members/iterators
            MemberIterator next = pos + (last - first);
            for (MemberIterator itr = pos; next != end; ++itr, ++next) {
                std::memcpy(static_cast<void*>(&*itr), &*next, sizeof(Member));
                SizeType mpos = static_cast<SizeType>(itr - beg);
                new (&mit[mpos]) MapIterator(DropMapIterator(mit[next - beg]));
                mit[mpos]->second = mpos;
            }
        }
#else
        std::memmove(static_cast<void*>(&*pos), &*last,
                     static_cast<size_t>(end - last) * sizeof(Member));
#endif
        o.size -= static_cast<SizeType>(last - first);
        return pos;
    }

    template <typename SourceAllocator>
    void DoCopyMembers(const GenericValue<Encoding,SourceAllocator>& rhs, Allocator& allocator, bool copyConstStrings) {
        RAPIDJSON_ASSERT(rhs.GetType() == kObjectType);

        data_.f.flags = kObjectFlag;
        SizeType count = rhs.data_.o.size;
        Member* lm = DoAllocMembers(count, allocator);
        const typename GenericValue<Encoding,SourceAllocator>::Member* rm = rhs.GetMembersPointer();
#if RAPIDJSON_USE_MEMBERSMAP
        Map* &map = GetMap(lm);
        MapIterator* mit = GetMapIterators(map);
#endif
        for (SizeType i = 0; i < count; i++) {
            new (&lm[i].name) GenericValue(rm[i].name, allocator, copyConstStrings);
            new (&lm[i].value) GenericValue(rm[i].value, allocator, copyConstStrings);
#if RAPIDJSON_USE_MEMBERSMAP
            new (&mit[i]) MapIterator(map->insert(MapPair(lm[i].name.data_, i)));
#endif
        }
        data_.o.size = data_.o.capacity = count;
        SetMembersPointer(lm);
    }

    // Initialize this value as array with initial data, without calling destructor.
    void SetArrayRaw(GenericValue* values, SizeType count, Allocator& allocator) {
        data_.f.flags = kArrayFlag;
        if (count) {
            GenericValue* e = static_cast<GenericValue*>(allocator.Malloc(count * sizeof(GenericValue)));
            SetElementsPointer(e);
            std::memcpy(static_cast<void*>(e), values, count * sizeof(GenericValue));
        }
        else
            SetElementsPointer(0);
        data_.a.size = data_.a.capacity = count;
    }

    //! Initialize this value as object with initial data, without calling destructor.
    void SetObjectRaw(Member* members, SizeType count, Allocator& allocator) {
        data_.f.flags = kObjectFlag;
        if (count) {
            Member* m = DoAllocMembers(count, allocator);
            SetMembersPointer(m);
            std::memcpy(static_cast<void*>(m), members, count * sizeof(Member));
#if RAPIDJSON_USE_MEMBERSMAP
            Map* &map = GetMap(m);
            MapIterator* mit = GetMapIterators(map);
            for (SizeType i = 0; i < count; i++) {
                new (&mit[i]) MapIterator(map->insert(MapPair(m[i].name.data_, i)));
            }
#endif
        }
        else
            SetMembersPointer(0);
        data_.o.size = data_.o.capacity = count;
    }

    //! Initialize this value as constant string, without calling destructor.
    void SetStringRaw(StringRefType s) RAPIDJSON_NOEXCEPT {
        data_.f.flags = kConstStringFlag;
        SetStringPointer(s);
        data_.s.length = s.length;
    }

    //! Initialize this value as copy string with initial data, without calling destructor.
    void SetStringRaw(StringRefType s, Allocator& allocator) {
        Ch* str = 0;
        if (ShortString::Usable(s.length)) {
            data_.f.flags = kShortStringFlag;
            data_.ss.SetLength(s.length);
            str = data_.ss.str;
            std::memmove(str, s, s.length * sizeof(Ch));
        } else {
            data_.f.flags = kCopyStringFlag;
            data_.s.length = s.length;
            str = static_cast<Ch *>(allocator.Malloc((s.length + 1) * sizeof(Ch)));
            SetStringPointer(str);
            std::memcpy(str, s, s.length * sizeof(Ch));
        }
        str[s.length] = '\0';
    }

    //! Assignment without calling destructor
    void RawAssign(GenericValue& rhs) RAPIDJSON_NOEXCEPT {
        data_ = rhs.data_;
        // data_.f.flags = rhs.data_.f.flags;
        rhs.data_.f.flags = kNullFlag;
    }

    template <typename SourceAllocator>
    bool StringEqual(const GenericValue<Encoding, SourceAllocator>& rhs) const {
        RAPIDJSON_ASSERT(IsString());
        RAPIDJSON_ASSERT(rhs.IsString());

        const SizeType len1 = GetStringLength();
        const SizeType len2 = rhs.GetStringLength();
        if(len1 != len2) { return false; }

        const Ch* const str1 = GetString();
        const Ch* const str2 = rhs.GetString();
        if(str1 == str2) { return true; } // fast path for constant string

        return (std::memcmp(str1, str2, sizeof(Ch) * len1) == 0);
    }

    Data data_;
};

//! GenericValue with UTF8 encoding
typedef GenericValue<UTF8<> > Value;

///////////////////////////////////////////////////////////////////////////////
// GenericDocument 

//! A document for parsing JSON text as DOM.
/*!
    \note implements Handler concept
    \tparam Encoding Encoding for both parsing and string storage.
    \tparam Allocator Allocator for allocating memory for the DOM
    \tparam StackAllocator Allocator for allocating memory for stack during parsing.
    \warning Although GenericDocument inherits from GenericValue, the API does \b not provide any virtual functions, especially no virtual destructor.  To avoid memory leaks, do not \c delete a GenericDocument object via a pointer to a GenericValue.
*/
template <typename Encoding, typename Allocator = RAPIDJSON_DEFAULT_ALLOCATOR, typename StackAllocator = RAPIDJSON_DEFAULT_STACK_ALLOCATOR >
class GenericDocument : public GenericValue<Encoding, Allocator> {
public:
    typedef typename Encoding::Ch Ch;                       //!< Character type derived from Encoding.
    typedef GenericValue<Encoding, Allocator> ValueType;    //!< Value type of the document.
    typedef Allocator AllocatorType;                        //!< Allocator type from template parameter.
    typedef StackAllocator StackAllocatorType;              //!< StackAllocator type from template parameter.

    //! Constructor
    /*! Creates an empty document of specified type.
        \param type             Mandatory type of object to create.
        \param allocator        Optional allocator for allocating memory.
        \param stackCapacity    Optional initial capacity of stack in bytes.
        \param stackAllocator   Optional allocator for allocating memory for stack.
    */
    explicit GenericDocument(Type type, Allocator* allocator = 0, size_t stackCapacity = kDefaultStackCapacity, StackAllocator* stackAllocator = 0) :
        GenericValue<Encoding, Allocator>(type),  allocator_(allocator), ownAllocator_(0), stack_(stackAllocator, stackCapacity), parseResult_()
    {
        if (!allocator_)
            ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();
    }

    //! Constructor
    /*! Creates an empty document which type is Null. 
        \param allocator        Optional allocator for allocating memory.
        \param stackCapacity    Optional initial capacity of stack in bytes.
        \param stackAllocator   Optional allocator for allocating memory for stack.
    */
    GenericDocument(Allocator* allocator = 0, size_t stackCapacity = kDefaultStackCapacity, StackAllocator* stackAllocator = 0) : 
        allocator_(allocator), ownAllocator_(0), stack_(stackAllocator, stackCapacity), parseResult_()
    {
        if (!allocator_)
            ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move constructor in C++11
    GenericDocument(GenericDocument&& rhs) RAPIDJSON_NOEXCEPT
        : ValueType(std::forward<ValueType>(rhs)), // explicit cast to avoid prohibited move from Document
          allocator_(rhs.allocator_),
          ownAllocator_(rhs.ownAllocator_),
          stack_(std::move(rhs.stack_)),
          parseResult_(rhs.parseResult_)
    {
        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.parseResult_ = ParseResult();
    }
#endif

    ~GenericDocument() {
        // Clear the ::ValueType before ownAllocator is destroyed, ~ValueType()
        // runs last and may access its elements or members which would be freed
        // with an allocator like MemoryPoolAllocator (CrtAllocator does not
        // free its data when destroyed, but MemoryPoolAllocator does).
        if (ownAllocator_) {
            ValueType::SetNull();
        }
        Destroy();
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move assignment in C++11
    GenericDocument& operator=(GenericDocument&& rhs) RAPIDJSON_NOEXCEPT
    {
        // The cast to ValueType is necessary here, because otherwise it would
        // attempt to call GenericValue's templated assignment operator.
        ValueType::operator=(std::forward<ValueType>(rhs));

        // Calling the destructor here would prematurely call stack_'s destructor
        Destroy();

        allocator_ = rhs.allocator_;
        ownAllocator_ = rhs.ownAllocator_;
        stack_ = std::move(rhs.stack_);
        parseResult_ = rhs.parseResult_;

        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.parseResult_ = ParseResult();

        return *this;
    }
#endif

    //! Exchange the contents of this document with those of another.
    /*!
        \param rhs Another document.
        \note Constant complexity.
        \see GenericValue::Swap
    */
    GenericDocument& Swap(GenericDocument& rhs) RAPIDJSON_NOEXCEPT {
        ValueType::Swap(rhs);
        stack_.Swap(rhs.stack_);
        internal::Swap(allocator_, rhs.allocator_);
        internal::Swap(ownAllocator_, rhs.ownAllocator_);
        internal::Swap(parseResult_, rhs.parseResult_);
        return *this;
    }

    // Allow Swap with ValueType.
    // Refer to Effective C++ 3rd Edition/Item 33: Avoid hiding inherited names.
    using ValueType::Swap;

    //! free-standing swap function helper
    /*!
        Helper function to enable support for common swap implementation pattern based on \c std::swap:
        \code
        void swap(MyClass& a, MyClass& b) {
            using std::swap;
            swap(a.doc, b.doc);
            // ...
        }
        \endcode
        \see Swap()
     */
    friend inline void swap(GenericDocument& a, GenericDocument& b) RAPIDJSON_NOEXCEPT { a.Swap(b); }

    //! Populate this document by a generator which produces SAX events.
    /*! \tparam Generator A functor with <tt>bool f(Handler)</tt> prototype.
        \param g Generator functor which sends SAX events to the parameter.
        \return The document itself for fluent API.
    */
    template <typename Generator>
    GenericDocument& Populate(Generator& g) {
        ClearStackOnExit scope(*this);
        if (g(*this)) {
            RAPIDJSON_ASSERT(stack_.GetSize() == sizeof(ValueType)); // Got one and only one root object
            ValueType::operator=(*stack_.template Pop<ValueType>(1));// Move value from stack to document
        }
        return *this;
    }

    //!@name Parse from stream
    //!@{

    //! Parse JSON text from an input stream (with Encoding conversion)
    /*! \tparam parseFlags Combination of \ref ParseFlag.
        \tparam SourceEncoding Encoding of input stream
        \tparam InputStream Type of input stream, implementing Stream concept
        \param is Input stream to be parsed.
        \return The document itself for fluent API.
    */
    template <unsigned parseFlags, typename SourceEncoding, typename InputStream>
    GenericDocument& ParseStream(InputStream& is) {
        GenericReader<SourceEncoding, Encoding, StackAllocator> reader(
            stack_.HasAllocator() ? &stack_.GetAllocator() : 0);
        ClearStackOnExit scope(*this);
        parseResult_ = reader.template Parse<parseFlags>(is, *this);
        if (parseResult_) {
            RAPIDJSON_ASSERT(stack_.GetSize() == sizeof(ValueType)); // Got one and only one root object
            ValueType::operator=(*stack_.template Pop<ValueType>(1));// Move value from stack to document
        }
        return *this;
    }

    //! Parse JSON text from an input stream
    /*! \tparam parseFlags Combination of \ref ParseFlag.
        \tparam InputStream Type of input stream, implementing Stream concept
        \param is Input stream to be parsed.
        \return The document itself for fluent API.
    */
    template <unsigned parseFlags, typename InputStream>
    GenericDocument& ParseStream(InputStream& is) {
        return ParseStream<parseFlags, Encoding, InputStream>(is);
    }

    //! Parse JSON text from an input stream (with \ref kParseDefaultFlags)
    /*! \tparam InputStream Type of input stream, implementing Stream concept
        \param is Input stream to be parsed.
        \return The document itself for fluent API.
    */
    template <typename InputStream>
    GenericDocument& ParseStream(InputStream& is) {
        return ParseStream<kParseDefaultFlags, Encoding, InputStream>(is);
    }
    //!@}

    //!@name Parse in-place from mutable string
    //!@{

    //! Parse JSON text from a mutable string
    /*! \tparam parseFlags Combination of \ref ParseFlag.
        \param str Mutable zero-terminated string to be parsed.
        \return The document itself for fluent API.
    */
    template <unsigned parseFlags>
    GenericDocument& ParseInsitu(Ch* str) {
        GenericInsituStringStream<Encoding> s(str);
        return ParseStream<parseFlags | kParseInsituFlag>(s);
    }

    //! Parse JSON text from a mutable string (with \ref kParseDefaultFlags)
    /*! \param str Mutable zero-terminated string to be parsed.
        \return The document itself for fluent API.
    */
    GenericDocument& ParseInsitu(Ch* str) {
        return ParseInsitu<kParseDefaultFlags>(str);
    }
    //!@}

    //!@name Parse from read-only string
    //!@{

    //! Parse JSON text from a read-only string (with Encoding conversion)
    /*! \tparam parseFlags Combination of \ref ParseFlag (must not contain \ref kParseInsituFlag).
        \tparam SourceEncoding Transcoding from input Encoding
        \param str Read-only zero-terminated string to be parsed.
    */
    template <unsigned parseFlags, typename SourceEncoding>
    GenericDocument& Parse(const typename SourceEncoding::Ch* str) {
        RAPIDJSON_ASSERT(!(parseFlags & kParseInsituFlag));
        GenericStringStream<SourceEncoding> s(str);
        return ParseStream<parseFlags, SourceEncoding>(s);
    }

    //! Parse JSON text from a read-only string
    /*! \tparam parseFlags Combination of \ref ParseFlag (must not contain \ref kParseInsituFlag).
        \param str Read-only zero-terminated string to be parsed.
    */
    template <unsigned parseFlags>
    GenericDocument& Parse(const Ch* str) {
        return Parse<parseFlags, Encoding>(str);
    }

    //! Parse JSON text from a read-only string (with \ref kParseDefaultFlags)
    /*! \param str Read-only zero-terminated string to be parsed.
    */
    GenericDocument& Parse(const Ch* str) {
        return Parse<kParseDefaultFlags>(str);
    }

    template <unsigned parseFlags, typename SourceEncoding>
    GenericDocument& Parse(const typename SourceEncoding::Ch* str, size_t length) {
        RAPIDJSON_ASSERT(!(parseFlags & kParseInsituFlag));
        MemoryStream ms(reinterpret_cast<const char*>(str), length * sizeof(typename SourceEncoding::Ch));
        EncodedInputStream<SourceEncoding, MemoryStream> is(ms);
        ParseStream<parseFlags, SourceEncoding>(is);
        return *this;
    }

    template <unsigned parseFlags>
    GenericDocument& Parse(const Ch* str, size_t length) {
        return Parse<parseFlags, Encoding>(str, length);
    }
    
    GenericDocument& Parse(const Ch* str, size_t length) {
        return Parse<kParseDefaultFlags>(str, length);
    }

#if RAPIDJSON_HAS_STDSTRING
    template <unsigned parseFlags, typename SourceEncoding>
    GenericDocument& Parse(const std::basic_string<typename SourceEncoding::Ch>& str) {
        // c_str() is constant complexity according to standard. Should be faster than Parse(const char*, size_t)
        return Parse<parseFlags, SourceEncoding>(str.c_str());
    }

    template <unsigned parseFlags>
    GenericDocument& Parse(const std::basic_string<Ch>& str) {
        return Parse<parseFlags, Encoding>(str.c_str());
    }

    GenericDocument& Parse(const std::basic_string<Ch>& str) {
        return Parse<kParseDefaultFlags>(str);
    }
#endif // RAPIDJSON_HAS_STDSTRING    

    //!@}

    //!@name Handling parse errors
    //!@{

    //! Whether a parse error has occurred in the last parsing.
    bool HasParseError() const { return parseResult_.IsError(); }

    //! Get the \ref ParseErrorCode of last parsing.
    ParseErrorCode GetParseError() const { return parseResult_.Code(); }

    //! Get the position of last parsing error in input, 0 otherwise.
    size_t GetErrorOffset() const { return parseResult_.Offset(); }

    //! Implicit conversion to get the last parse result
#ifndef __clang // -Wdocumentation
    /*! \return \ref ParseResult of the last parse operation

        \code
          Document doc;
          ParseResult ok = doc.Parse(json);
          if (!ok)
            printf( "JSON parse error: %s (%u)\n", GetParseError_En(ok.Code()), ok.Offset());
        \endcode
     */
#endif
    operator ParseResult() const { return parseResult_; }
    //!@}

    //! Get the allocator of this document.
    Allocator& GetAllocator() {
        RAPIDJSON_ASSERT(allocator_);
        return *allocator_;
    }

    //! Get the capacity of stack in bytes.
    size_t GetStackCapacity() const { return stack_.GetCapacity(); }

private:
    // clear stack on any exit from ParseStream, e.g. due to exception
    struct ClearStackOnExit {
        explicit ClearStackOnExit(GenericDocument& d) : d_(d) {}
        ~ClearStackOnExit() { d_.ClearStack(); }
    private:
        ClearStackOnExit(const ClearStackOnExit&);
        ClearStackOnExit& operator=(const ClearStackOnExit&);
        GenericDocument& d_;
    };

    // callers of the following private Handler functions
    // template <typename,typename,typename> friend class GenericReader; // for parsing
    template <typename, typename> friend class GenericValue; // for deep copying

public:
    // Implementation of Handler
    bool Null() { new (stack_.template Push<ValueType>()) ValueType(); return true; }
    bool Bool(bool b) { new (stack_.template Push<ValueType>()) ValueType(b); return true; }
    bool Int(int i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Uint(unsigned i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Int64(int64_t i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Uint64(uint64_t i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Double(double d) { new (stack_.template Push<ValueType>()) ValueType(d); return true; }

    bool RawNumber(const Ch* str, SizeType length, bool copy) { 
        if (copy) 
            new (stack_.template Push<ValueType>()) ValueType(str, length, GetAllocator());
        else
            new (stack_.template Push<ValueType>()) ValueType(str, length);
        return true;
    }

    bool String(const Ch* str, SizeType length, bool copy) { 
        if (copy) 
            new (stack_.template Push<ValueType>()) ValueType(str, length, GetAllocator());
        else
            new (stack_.template Push<ValueType>()) ValueType(str, length);
        return true;
    }

    bool StartObject() { new (stack_.template Push<ValueType>()) ValueType(kObjectType); return true; }
    
    bool Key(const Ch* str, SizeType length, bool copy) { return String(str, length, copy); }

    bool EndObject(SizeType memberCount) {
        typename ValueType::Member* members = stack_.template Pop<typename ValueType::Member>(memberCount);
        stack_.template Top<ValueType>()->SetObjectRaw(members, memberCount, GetAllocator());
        return true;
    }

    bool StartArray() { new (stack_.template Push<ValueType>()) ValueType(kArrayType); return true; }
    
    bool EndArray(SizeType elementCount) {
        ValueType* elements = stack_.template Pop<ValueType>(elementCount);
        stack_.template Top<ValueType>()->SetArrayRaw(elements, elementCount, GetAllocator());
        return true;
    }

private:
    //! Prohibit copying
    GenericDocument(const GenericDocument&);
    //! Prohibit assignment
    GenericDocument& operator=(const GenericDocument&);

    void ClearStack() {
        if (Allocator::kNeedFree)
            while (stack_.GetSize() > 0)    // Here assumes all elements in stack array are GenericValue (Member is actually 2 GenericValue objects)
                (stack_.template Pop<ValueType>(1))->~ValueType();
        else
            stack_.Clear();
        stack_.ShrinkToFit();
    }

    void Destroy() {
        RAPIDJSON_DELETE(ownAllocator_);
    }

    static const size_t kDefaultStackCapacity = 1024;
    Allocator* allocator_;
    Allocator* ownAllocator_;
    internal::Stack<StackAllocator> stack_;
    ParseResult parseResult_;
};

//! GenericDocument with UTF8 encoding
typedef GenericDocument<UTF8<> > Document;


//! Helper class for accessing Value of array type.
/*!
    Instance of this helper class is obtained by \c GenericValue::GetArray().
    In addition to all APIs for array type, it provides range-based for loop if \c RAPIDJSON_HAS_CXX11_RANGE_FOR=1.
*/
template <bool Const, typename ValueT>
class GenericArray {
public:
    typedef GenericArray<true, ValueT> ConstArray;
    typedef GenericArray<false, ValueT> Array;
    typedef ValueT PlainType;
    typedef typename internal::MaybeAddConst<Const,PlainType>::Type ValueType;
    typedef ValueType* ValueIterator;  // This may be const or non-const iterator
    typedef const ValueT* ConstValueIterator;
    typedef typename ValueType::AllocatorType AllocatorType;
    typedef typename ValueType::StringRefType StringRefType;

    template <typename, typename>
    friend class GenericValue;

    GenericArray(const GenericArray& rhs) : value_(rhs.value_) {}
    GenericArray& operator=(const GenericArray& rhs) { value_ = rhs.value_; return *this; }
    ~GenericArray() {}

    operator ValueType&() const { return value_; }
    SizeType Size() const { return value_.Size(); }
    SizeType Capacity() const { return value_.Capacity(); }
    bool Empty() const { return value_.Empty(); }
    void Clear() const { value_.Clear(); }
    ValueType& operator[](SizeType index) const {  return value_[index]; }
    ValueIterator Begin() const { return value_.Begin(); }
    ValueIterator End() const { return value_.End(); }
    GenericArray Reserve(SizeType newCapacity, AllocatorType &allocator) const { value_.Reserve(newCapacity, allocator); return *this; }
    GenericArray PushBack(ValueType& value, AllocatorType& allocator) const { value_.PushBack(value, allocator); return *this; }
#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericArray PushBack(ValueType&& value, AllocatorType& allocator) const { value_.PushBack(value, allocator); return *this; }
#endif // RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericArray PushBack(StringRefType value, AllocatorType& allocator) const { value_.PushBack(value, allocator); return *this; }
    template <typename T> RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (const GenericArray&)) PushBack(T value, AllocatorType& allocator) const { value_.PushBack(value, allocator); return *this; }
    GenericArray PopBack() const { value_.PopBack(); return *this; }
    ValueIterator Erase(ConstValueIterator pos) const { return value_.Erase(pos); }
    ValueIterator Erase(ConstValueIterator first, ConstValueIterator last) const { return value_.Erase(first, last); }

#if RAPIDJSON_HAS_CXX11_RANGE_FOR
    ValueIterator begin() const { return value_.Begin(); }
    ValueIterator end() const { return value_.End(); }
#endif

private:
    GenericArray();
    GenericArray(ValueType& value) : value_(value) {}
    ValueType& value_;
};

//! Helper class for accessing Value of object type.
/*!
    Instance of this helper class is obtained by \c GenericValue::GetObject().
    In addition to all APIs for array type, it provides range-based for loop if \c RAPIDJSON_HAS_CXX11_RANGE_FOR=1.
*/
template <bool Const, typename ValueT>
class GenericObject {
public:
    typedef GenericObject<true, ValueT> ConstObject;
    typedef GenericObject<false, ValueT> Object;
    typedef ValueT PlainType;
    typedef typename internal::MaybeAddConst<Const,PlainType>::Type ValueType;
    typedef GenericMemberIterator<Const, typename ValueT::EncodingType, typename ValueT::AllocatorType> MemberIterator;  // This may be const or non-const iterator
    typedef GenericMemberIterator<true, typename ValueT::EncodingType, typename ValueT::AllocatorType> ConstMemberIterator;
    typedef typename ValueType::AllocatorType AllocatorType;
    typedef typename ValueType::StringRefType StringRefType;
    typedef typename ValueType::EncodingType EncodingType;
    typedef typename ValueType::Ch Ch;

    template <typename, typename>
    friend class GenericValue;

    GenericObject(const GenericObject& rhs) : value_(rhs.value_) {}
    GenericObject& operator=(const GenericObject& rhs) { value_ = rhs.value_; return *this; }
    ~GenericObject() {}

    operator ValueType&() const { return value_; }
    SizeType MemberCount() const { return value_.MemberCount(); }
    SizeType MemberCapacity() const { return value_.MemberCapacity(); }
    bool ObjectEmpty() const { return value_.ObjectEmpty(); }
    template <typename T> ValueType& operator[](T* name) const { return value_[name]; }
    template <typename SourceAllocator> ValueType& operator[](const GenericValue<EncodingType, SourceAllocator>& name) const { return value_[name]; }
#if RAPIDJSON_HAS_STDSTRING
    ValueType& operator[](const std::basic_string<Ch>& name) const { return value_[name]; }
#endif
    MemberIterator MemberBegin() const { return value_.MemberBegin(); }
    MemberIterator MemberEnd() const { return value_.MemberEnd(); }
    GenericObject MemberReserve(SizeType newCapacity, AllocatorType &allocator) const { value_.MemberReserve(newCapacity, allocator); return *this; }
    bool HasMember(const Ch* name) const { return value_.HasMember(name); }
#if RAPIDJSON_HAS_STDSTRING
    bool HasMember(const std::basic_string<Ch>& name) const { return value_.HasMember(name); }
#endif
    template <typename SourceAllocator> bool HasMember(const GenericValue<EncodingType, SourceAllocator>& name) const { return value_.HasMember(name); }
    MemberIterator FindMember(const Ch* name) const { return value_.FindMember(name); }
    template <typename SourceAllocator> MemberIterator FindMember(const GenericValue<EncodingType, SourceAllocator>& name) const { return value_.FindMember(name); }
#if RAPIDJSON_HAS_STDSTRING
    MemberIterator FindMember(const std::basic_string<Ch>& name) const { return value_.FindMember(name); }
#endif
    GenericObject AddMember(ValueType& name, ValueType& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    GenericObject AddMember(ValueType& name, StringRefType value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
#if RAPIDJSON_HAS_STDSTRING
    GenericObject AddMember(ValueType& name, std::basic_string<Ch>& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
#endif
    template <typename T> RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (ValueType&)) AddMember(ValueType& name, T value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericObject AddMember(ValueType&& name, ValueType&& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    GenericObject AddMember(ValueType&& name, ValueType& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    GenericObject AddMember(ValueType& name, ValueType&& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    GenericObject AddMember(StringRefType name, ValueType&& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
#endif // RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericObject AddMember(StringRefType name, ValueType& value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    GenericObject AddMember(StringRefType name, StringRefType value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    template <typename T> RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (GenericObject)) AddMember(StringRefType name, T value, AllocatorType& allocator) const { value_.AddMember(name, value, allocator); return *this; }
    void RemoveAllMembers() { value_.RemoveAllMembers(); }
    bool RemoveMember(const Ch* name) const { return value_.RemoveMember(name); }
#if RAPIDJSON_HAS_STDSTRING
    bool RemoveMember(const std::basic_string<Ch>& name) const { return value_.RemoveMember(name); }
#endif
    template <typename SourceAllocator> bool RemoveMember(const GenericValue<EncodingType, SourceAllocator>& name) const { return value_.RemoveMember(name); }
    MemberIterator RemoveMember(MemberIterator m) const { return value_.RemoveMember(m); }
    MemberIterator EraseMember(ConstMemberIterator pos) const { return value_.EraseMember(pos); }
    MemberIterator EraseMember(ConstMemberIterator first, ConstMemberIterator last) const { return value_.EraseMember(first, last); }
    bool EraseMember(const Ch* name) const { return value_.EraseMember(name); }
#if RAPIDJSON_HAS_STDSTRING
    bool EraseMember(const std::basic_string<Ch>& name) const { return EraseMember(ValueType(StringRef(name))); }
#endif
    template <typename SourceAllocator> bool EraseMember(const GenericValue<EncodingType, SourceAllocator>& name) const { return value_.EraseMember(name); }

#if RAPIDJSON_HAS_CXX11_RANGE_FOR
    MemberIterator begin() const { return value_.MemberBegin(); }
    MemberIterator end() const { return value_.MemberEnd(); }
#endif

private:
    GenericObject();
    GenericObject(ValueType& value) : value_(value) {}
    ValueType& value_;
};

RAPIDJSON_NAMESPACE_END
RAPIDJSON_DIAG_POP

#ifdef RAPIDJSON_WINDOWS_GETOBJECT_WORKAROUND_APPLIED
#pragma pop_macro("GetObject")
#undef RAPIDJSON_WINDOWS_GETOBJECT_WORKAROUND_APPLIED
#endif

#endif // RAPIDJSON_DOCUMENT_H_

// End file:document.h


// Begin file: pointer.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_POINTER_H_
#define RAPIDJSON_POINTER_H_


// Begin file: document.h
// already included
// End file:document.h


// Begin file: uri.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// (C) Copyright IBM Corporation 2021
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_URI_H_
#define RAPIDJSON_URI_H_


// Begin file: internal/strfunc.h
// already included
// End file:internal/strfunc.h


#if defined(__clang__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(c++98-compat)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_OFF(4512) // assignment operator could not be generated
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// GenericUri

template <typename ValueType, typename Allocator=CrtAllocator>
class GenericUri {
public:
    typedef typename ValueType::Ch Ch;
#if RAPIDJSON_HAS_STDSTRING
    typedef std::basic_string<Ch> String;
#endif

    //! Constructors
    GenericUri(Allocator* allocator = 0) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(allocator), ownAllocator_() {
    }

    GenericUri(const Ch* uri, SizeType len, Allocator* allocator = 0) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(allocator), ownAllocator_() {
        Parse(uri, len);
    }

    GenericUri(const Ch* uri, Allocator* allocator = 0) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(allocator), ownAllocator_() {
        Parse(uri, internal::StrLen<Ch>(uri));
    }

    // Use with specializations of GenericValue
    template<typename T> GenericUri(const T& uri, Allocator* allocator = 0) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(allocator), ownAllocator_() {
        const Ch* u = uri.template Get<const Ch*>(); // TypeHelper from document.h
        Parse(u, internal::StrLen<Ch>(u));
    }

#if RAPIDJSON_HAS_STDSTRING
    GenericUri(const String& uri, Allocator* allocator = 0) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(allocator), ownAllocator_() {
        Parse(uri.c_str(), internal::StrLen<Ch>(uri.c_str()));
    }
#endif

    //! Copy constructor
    GenericUri(const GenericUri& rhs) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(), ownAllocator_() {
        *this = rhs;
    }

    //! Copy constructor
    GenericUri(const GenericUri& rhs, Allocator* allocator) : uri_(), base_(), scheme_(), auth_(), path_(), query_(), frag_(), allocator_(allocator), ownAllocator_() {
        *this = rhs;
    }

    //! Destructor.
    ~GenericUri() {
        Free();
        RAPIDJSON_DELETE(ownAllocator_);
    }

    //! Assignment operator
    GenericUri& operator=(const GenericUri& rhs) {
        if (this != &rhs) {
            // Do not delete ownAllocator
            Free();
            Allocate(rhs.GetStringLength());
            auth_ = CopyPart(scheme_, rhs.scheme_, rhs.GetSchemeStringLength());
            path_ = CopyPart(auth_, rhs.auth_, rhs.GetAuthStringLength());
            query_ = CopyPart(path_, rhs.path_, rhs.GetPathStringLength());
            frag_ = CopyPart(query_, rhs.query_, rhs.GetQueryStringLength());
            base_ = CopyPart(frag_, rhs.frag_, rhs.GetFragStringLength());
            uri_ = CopyPart(base_, rhs.base_, rhs.GetBaseStringLength());
            CopyPart(uri_, rhs.uri_, rhs.GetStringLength());
        }
        return *this;
    }

    //! Getters
    // Use with specializations of GenericValue
    template<typename T> void Get(T& uri, Allocator& allocator) {
        uri.template Set<const Ch*>(this->GetString(), allocator); // TypeHelper from document.h
    }

    const Ch* GetString() const { return uri_; }
    SizeType GetStringLength() const { return uri_ == 0 ? 0 : internal::StrLen<Ch>(uri_); }
    const Ch* GetBaseString() const { return base_; }
    SizeType GetBaseStringLength() const { return base_ == 0 ? 0 : internal::StrLen<Ch>(base_); }
    const Ch* GetSchemeString() const { return scheme_; }
    SizeType GetSchemeStringLength() const { return scheme_ == 0 ? 0 : internal::StrLen<Ch>(scheme_); }
    const Ch* GetAuthString() const { return auth_; }
    SizeType GetAuthStringLength() const { return auth_ == 0 ? 0 : internal::StrLen<Ch>(auth_); }
    const Ch* GetPathString() const { return path_; }
    SizeType GetPathStringLength() const { return path_ == 0 ? 0 : internal::StrLen<Ch>(path_); }
    const Ch* GetQueryString() const { return query_; }
    SizeType GetQueryStringLength() const { return query_ == 0 ? 0 : internal::StrLen<Ch>(query_); }
    const Ch* GetFragString() const { return frag_; }
    SizeType GetFragStringLength() const { return frag_ == 0 ? 0 : internal::StrLen<Ch>(frag_); }

#if RAPIDJSON_HAS_STDSTRING
    static String Get(const GenericUri& uri) { return String(uri.GetString(), uri.GetStringLength()); }
    static String GetBase(const GenericUri& uri) { return String(uri.GetBaseString(), uri.GetBaseStringLength()); }
    static String GetScheme(const GenericUri& uri) { return String(uri.GetSchemeString(), uri.GetSchemeStringLength()); }
    static String GetAuth(const GenericUri& uri) { return String(uri.GetAuthString(), uri.GetAuthStringLength()); }
    static String GetPath(const GenericUri& uri) { return String(uri.GetPathString(), uri.GetPathStringLength()); }
    static String GetQuery(const GenericUri& uri) { return String(uri.GetQueryString(), uri.GetQueryStringLength()); }
    static String GetFrag(const GenericUri& uri) { return String(uri.GetFragString(), uri.GetFragStringLength()); }
#endif

    //! Equality operators
    bool operator==(const GenericUri& rhs) const {
        return Match(rhs, true);
    }

    bool operator!=(const GenericUri& rhs) const {
        return !Match(rhs, true);
    }

    bool Match(const GenericUri& uri, bool full = true) const {
        Ch* s1;
        Ch* s2;
        if (full) {
            s1 = uri_;
            s2 = uri.uri_;
        } else {
            s1 = base_;
            s2 = uri.base_;
        }
        if (s1 == s2) return true;
        if (s1 == 0 || s2 == 0) return false;
        return internal::StrCmp<Ch>(s1, s2) == 0;
    }

    //! Resolve this URI against another (base) URI in accordance with URI resolution rules.
    // See https://tools.ietf.org/html/rfc3986
    // Use for resolving an id or $ref with an in-scope id.
    // Returns a new GenericUri for the resolved URI.
    GenericUri Resolve(const GenericUri& baseuri, Allocator* allocator = 0) {
        GenericUri resuri;
        resuri.allocator_ = allocator;
        // Ensure enough space for combining paths
        resuri.Allocate(GetStringLength() + baseuri.GetStringLength() + 1); // + 1 for joining slash

        if (!(GetSchemeStringLength() == 0)) {
            // Use all of this URI
            resuri.auth_ = CopyPart(resuri.scheme_, scheme_, GetSchemeStringLength());
            resuri.path_ = CopyPart(resuri.auth_, auth_, GetAuthStringLength());
            resuri.query_ = CopyPart(resuri.path_, path_, GetPathStringLength());
            resuri.frag_ = CopyPart(resuri.query_, query_, GetQueryStringLength());
            resuri.RemoveDotSegments();
        } else {
            // Use the base scheme
            resuri.auth_ = CopyPart(resuri.scheme_, baseuri.scheme_, baseuri.GetSchemeStringLength());
            if (!(GetAuthStringLength() == 0)) {
                // Use this auth, path, query
                resuri.path_ = CopyPart(resuri.auth_, auth_, GetAuthStringLength());
                resuri.query_ = CopyPart(resuri.path_, path_, GetPathStringLength());
                resuri.frag_ = CopyPart(resuri.query_, query_, GetQueryStringLength());
                resuri.RemoveDotSegments();
            } else {
                // Use the base auth
                resuri.path_ = CopyPart(resuri.auth_, baseuri.auth_, baseuri.GetAuthStringLength());
                if (GetPathStringLength() == 0) {
                    // Use the base path
                    resuri.query_ = CopyPart(resuri.path_, baseuri.path_, baseuri.GetPathStringLength());
                    if (GetQueryStringLength() == 0) {
                        // Use the base query
                        resuri.frag_ = CopyPart(resuri.query_, baseuri.query_, baseuri.GetQueryStringLength());
                    } else {
                        // Use this query
                        resuri.frag_ = CopyPart(resuri.query_, query_, GetQueryStringLength());
                    }
                } else {
                    if (path_[0] == '/') {
                        // Absolute path - use all of this path
                        resuri.query_ = CopyPart(resuri.path_, path_, GetPathStringLength());
                        resuri.RemoveDotSegments();
                    } else {
                        // Relative path - append this path to base path after base path's last slash
                        size_t pos = 0;
                        if (!(baseuri.GetAuthStringLength() == 0) && baseuri.GetPathStringLength() == 0) {
                            resuri.path_[pos] = '/';
                            pos++;
                        }
                        size_t lastslashpos = baseuri.GetPathStringLength();
                        while (lastslashpos > 0) {
                            if (baseuri.path_[lastslashpos - 1] == '/') break;
                            lastslashpos--;
                        }
                        std::memcpy(&resuri.path_[pos], baseuri.path_, lastslashpos * sizeof(Ch));
                        pos += lastslashpos;
                        resuri.query_ = CopyPart(&resuri.path_[pos], path_, GetPathStringLength());
                        resuri.RemoveDotSegments();
                    }
                    // Use this query
                    resuri.frag_ = CopyPart(resuri.query_, query_, GetQueryStringLength());
                }
            }
        }
        // Always use this frag
        resuri.base_ = CopyPart(resuri.frag_, frag_, GetFragStringLength());

        // Re-constitute base_ and uri_
        resuri.SetBase();
        resuri.uri_ = resuri.base_ + resuri.GetBaseStringLength() + 1;
        resuri.SetUri();
        return resuri;
    }

    //! Get the allocator of this GenericUri.
    Allocator& GetAllocator() { return *allocator_; }

private:
    // Allocate memory for a URI
    // Returns total amount allocated
    std::size_t Allocate(std::size_t len) {
        // Create own allocator if user did not supply.
        if (!allocator_)
            ownAllocator_ =  allocator_ = RAPIDJSON_NEW(Allocator)();

        // Allocate one block containing each part of the URI (5) plus base plus full URI, all null terminated.
        // Order: scheme, auth, path, query, frag, base, uri
        // Note need to set, increment, assign in 3 stages to avoid compiler warning bug.
        size_t total = (3 * len + 7) * sizeof(Ch);
        scheme_ = static_cast<Ch*>(allocator_->Malloc(total));
        *scheme_ = '\0';
        auth_ = scheme_;
        auth_++;
        *auth_ = '\0';
        path_ = auth_;
        path_++;
        *path_ = '\0';
        query_ = path_;
        query_++;
        *query_ = '\0';
        frag_ = query_;
        frag_++;
        *frag_ = '\0';
        base_ = frag_;
        base_++;
        *base_ = '\0';
        uri_ = base_;
        uri_++;
        *uri_ = '\0';
        return total;
    }

    // Free memory for a URI
    void Free() {
        if (scheme_) {
            Allocator::Free(scheme_);
            scheme_ = 0;
        }
    }

    // Parse a URI into constituent scheme, authority, path, query, & fragment parts
    // Supports URIs that match regex ^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))? as per
    // https://tools.ietf.org/html/rfc3986
    void Parse(const Ch* uri, std::size_t len) {
        std::size_t start = 0, pos1 = 0, pos2 = 0;
        Allocate(len);

        // Look for scheme ([^:/?#]+):)?
        if (start < len) {
            while (pos1 < len) {
                if (uri[pos1] == ':') break;
                pos1++;
            }
            if (pos1 != len) {
                while (pos2 < len) {
                    if (uri[pos2] == '/') break;
                    if (uri[pos2] == '?') break;
                    if (uri[pos2] == '#') break;
                    pos2++;
                }
                if (pos1 < pos2) {
                    pos1++;
                    std::memcpy(scheme_, &uri[start], pos1 * sizeof(Ch));
                    scheme_[pos1] = '\0';
                    start = pos1;
                }
            }
        }
        // Look for auth (//([^/?#]*))?
        // Note need to set, increment, assign in 3 stages to avoid compiler warning bug.
        auth_ = scheme_ + GetSchemeStringLength();
        auth_++;
        *auth_ = '\0';
        if (start < len - 1 && uri[start] == '/' && uri[start + 1] == '/') {
            pos2 = start + 2;
            while (pos2 < len) {
                if (uri[pos2] == '/') break;
                if (uri[pos2] == '?') break;
                if (uri[pos2] == '#') break;
                pos2++;
            }
            std::memcpy(auth_, &uri[start], (pos2 - start) * sizeof(Ch));
            auth_[pos2 - start] = '\0';
            start = pos2;
        }
        // Look for path ([^?#]*)
        // Note need to set, increment, assign in 3 stages to avoid compiler warning bug.
        path_ = auth_ + GetAuthStringLength();
        path_++;
        *path_ = '\0';
        if (start < len) {
            pos2 = start;
            while (pos2 < len) {
                if (uri[pos2] == '?') break;
                if (uri[pos2] == '#') break;
                pos2++;
            }
            if (start != pos2) {
                std::memcpy(path_, &uri[start], (pos2 - start) * sizeof(Ch));
                path_[pos2 - start] = '\0';
                if (path_[0] == '/')
                    RemoveDotSegments();   // absolute path - normalize
                start = pos2;
            }
        }
        // Look for query (\?([^#]*))?
        // Note need to set, increment, assign in 3 stages to avoid compiler warning bug.
        query_ = path_ + GetPathStringLength();
        query_++;
        *query_ = '\0';
        if (start < len && uri[start] == '?') {
            pos2 = start + 1;
            while (pos2 < len) {
                if (uri[pos2] == '#') break;
                pos2++;
            }
            if (start != pos2) {
                std::memcpy(query_, &uri[start], (pos2 - start) * sizeof(Ch));
                query_[pos2 - start] = '\0';
                start = pos2;
            }
        }
        // Look for fragment (#(.*))?
        // Note need to set, increment, assign in 3 stages to avoid compiler warning bug.
        frag_ = query_ + GetQueryStringLength();
        frag_++;
        *frag_ = '\0';
        if (start < len && uri[start] == '#') {
            std::memcpy(frag_, &uri[start], (len - start) * sizeof(Ch));
            frag_[len - start] = '\0';
        }

        // Re-constitute base_ and uri_
        base_ = frag_ + GetFragStringLength() + 1;
        SetBase();
        uri_ = base_ + GetBaseStringLength() + 1;
        SetUri();
    }

    // Reconstitute base
    void SetBase() {
        Ch* next = base_;
        std::memcpy(next, scheme_, GetSchemeStringLength() * sizeof(Ch));
        next+= GetSchemeStringLength();
        std::memcpy(next, auth_, GetAuthStringLength() * sizeof(Ch));
        next+= GetAuthStringLength();
        std::memcpy(next, path_, GetPathStringLength() * sizeof(Ch));
        next+= GetPathStringLength();
        std::memcpy(next, query_, GetQueryStringLength() * sizeof(Ch));
        next+= GetQueryStringLength();
        *next = '\0';
    }

    // Reconstitute uri
    void SetUri() {
        Ch* next = uri_;
        std::memcpy(next, base_, GetBaseStringLength() * sizeof(Ch));
        next+= GetBaseStringLength();
        std::memcpy(next, frag_, GetFragStringLength() * sizeof(Ch));
        next+= GetFragStringLength();
        *next = '\0';
    }

    // Copy a part from one GenericUri to another
    // Return the pointer to the next part to be copied to
    Ch* CopyPart(Ch* to, Ch* from, std::size_t len) {
        RAPIDJSON_ASSERT(to != 0);
        RAPIDJSON_ASSERT(from != 0);
        std::memcpy(to, from, len * sizeof(Ch));
        to[len] = '\0';
        Ch* next = to + len + 1;
        return next;
    }

    // Remove . and .. segments from the path_ member.
    // https://tools.ietf.org/html/rfc3986
    // This is done in place as we are only removing segments.
    void RemoveDotSegments() {
        std::size_t pathlen = GetPathStringLength();
        std::size_t pathpos = 0;  // Position in path_
        std::size_t newpos = 0;   // Position in new path_

        // Loop through each segment in original path_
        while (pathpos < pathlen) {
            // Get next segment, bounded by '/' or end
            size_t slashpos = 0;
            while ((pathpos + slashpos) < pathlen) {
                if (path_[pathpos + slashpos] == '/') break;
                slashpos++;
            }
            // Check for .. and . segments
            if (slashpos == 2 && path_[pathpos] == '.' && path_[pathpos + 1] == '.') {
                // Backup a .. segment in the new path_
                // We expect to find a previously added slash at the end or nothing
                RAPIDJSON_ASSERT(newpos == 0 || path_[newpos - 1] == '/');
                size_t lastslashpos = newpos;
                // Make sure we don't go beyond the start segment
                if (lastslashpos > 1) {
                    // Find the next to last slash and back up to it
                    lastslashpos--;
                    while (lastslashpos > 0) {
                        if (path_[lastslashpos - 1] == '/') break;
                        lastslashpos--;
                    }
                    // Set the new path_ position
                    newpos = lastslashpos;
                }
            } else if (slashpos == 1 && path_[pathpos] == '.') {
                // Discard . segment, leaves new path_ unchanged
            } else {
                // Move any other kind of segment to the new path_
                RAPIDJSON_ASSERT(newpos <= pathpos);
                std::memmove(&path_[newpos], &path_[pathpos], slashpos * sizeof(Ch));
                newpos += slashpos;
                // Add slash if not at end
                if ((pathpos + slashpos) < pathlen) {
                    path_[newpos] = '/';
                    newpos++;
                }
            }
            // Move to next segment
            pathpos += slashpos + 1;
        }
        path_[newpos] = '\0';
    }

    Ch* uri_;    // Everything
    Ch* base_;   // Everything except fragment
    Ch* scheme_; // Includes the :
    Ch* auth_;   // Includes the //
    Ch* path_;   // Absolute if starts with /
    Ch* query_;  // Includes the ?
    Ch* frag_;   // Includes the #

    Allocator* allocator_;      //!< The current allocator. It is either user-supplied or equal to ownAllocator_.
    Allocator* ownAllocator_;   //!< Allocator owned by this Uri.
};

//! GenericUri for Value (UTF-8, default allocator).
typedef GenericUri<Value> Uri;

RAPIDJSON_NAMESPACE_END

#if defined(__clang__)
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_URI_H_

// End file:uri.h


// Begin file: internal/itoa.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ITOA_
#define RAPIDJSON_ITOA_


// Begin file: ../rapidjson.h
// already included
// End file:../rapidjson.h


RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

inline const char* GetDigitsLut() {
    static const char cDigitsLut[200] = {
        '0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
        '1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
        '2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
        '3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
        '4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
        '5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
        '6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
        '7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
        '8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
        '9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9'
    };
    return cDigitsLut;
}

inline char* u32toa(uint32_t value, char* buffer) {
    RAPIDJSON_ASSERT(buffer != 0);

    const char* cDigitsLut = GetDigitsLut();

    if (value < 10000) {
        const uint32_t d1 = (value / 100) << 1;
        const uint32_t d2 = (value % 100) << 1;

        if (value >= 1000)
            *buffer++ = cDigitsLut[d1];
        if (value >= 100)
            *buffer++ = cDigitsLut[d1 + 1];
        if (value >= 10)
            *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
    }
    else if (value < 100000000) {
        // value = bbbbcccc
        const uint32_t b = value / 10000;
        const uint32_t c = value % 10000;

        const uint32_t d1 = (b / 100) << 1;
        const uint32_t d2 = (b % 100) << 1;

        const uint32_t d3 = (c / 100) << 1;
        const uint32_t d4 = (c % 100) << 1;

        if (value >= 10000000)
            *buffer++ = cDigitsLut[d1];
        if (value >= 1000000)
            *buffer++ = cDigitsLut[d1 + 1];
        if (value >= 100000)
            *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];

        *buffer++ = cDigitsLut[d3];
        *buffer++ = cDigitsLut[d3 + 1];
        *buffer++ = cDigitsLut[d4];
        *buffer++ = cDigitsLut[d4 + 1];
    }
    else {
        // value = aabbbbcccc in decimal

        const uint32_t a = value / 100000000; // 1 to 42
        value %= 100000000;

        if (a >= 10) {
            const unsigned i = a << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
        }
        else
            *buffer++ = static_cast<char>('0' + static_cast<char>(a));

        const uint32_t b = value / 10000; // 0 to 9999
        const uint32_t c = value % 10000; // 0 to 9999

        const uint32_t d1 = (b / 100) << 1;
        const uint32_t d2 = (b % 100) << 1;

        const uint32_t d3 = (c / 100) << 1;
        const uint32_t d4 = (c % 100) << 1;

        *buffer++ = cDigitsLut[d1];
        *buffer++ = cDigitsLut[d1 + 1];
        *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
        *buffer++ = cDigitsLut[d3];
        *buffer++ = cDigitsLut[d3 + 1];
        *buffer++ = cDigitsLut[d4];
        *buffer++ = cDigitsLut[d4 + 1];
    }
    return buffer;
}

inline char* i32toa(int32_t value, char* buffer) {
    RAPIDJSON_ASSERT(buffer != 0);
    uint32_t u = static_cast<uint32_t>(value);
    if (value < 0) {
        *buffer++ = '-';
        u = ~u + 1;
    }

    return u32toa(u, buffer);
}

inline char* u64toa(uint64_t value, char* buffer) {
    RAPIDJSON_ASSERT(buffer != 0);
    const char* cDigitsLut = GetDigitsLut();
    const uint64_t  kTen8 = 100000000;
    const uint64_t  kTen9 = kTen8 * 10;
    const uint64_t kTen10 = kTen8 * 100;
    const uint64_t kTen11 = kTen8 * 1000;
    const uint64_t kTen12 = kTen8 * 10000;
    const uint64_t kTen13 = kTen8 * 100000;
    const uint64_t kTen14 = kTen8 * 1000000;
    const uint64_t kTen15 = kTen8 * 10000000;
    const uint64_t kTen16 = kTen8 * kTen8;

    if (value < kTen8) {
        uint32_t v = static_cast<uint32_t>(value);
        if (v < 10000) {
            const uint32_t d1 = (v / 100) << 1;
            const uint32_t d2 = (v % 100) << 1;

            if (v >= 1000)
                *buffer++ = cDigitsLut[d1];
            if (v >= 100)
                *buffer++ = cDigitsLut[d1 + 1];
            if (v >= 10)
                *buffer++ = cDigitsLut[d2];
            *buffer++ = cDigitsLut[d2 + 1];
        }
        else {
            // value = bbbbcccc
            const uint32_t b = v / 10000;
            const uint32_t c = v % 10000;

            const uint32_t d1 = (b / 100) << 1;
            const uint32_t d2 = (b % 100) << 1;

            const uint32_t d3 = (c / 100) << 1;
            const uint32_t d4 = (c % 100) << 1;

            if (value >= 10000000)
                *buffer++ = cDigitsLut[d1];
            if (value >= 1000000)
                *buffer++ = cDigitsLut[d1 + 1];
            if (value >= 100000)
                *buffer++ = cDigitsLut[d2];
            *buffer++ = cDigitsLut[d2 + 1];

            *buffer++ = cDigitsLut[d3];
            *buffer++ = cDigitsLut[d3 + 1];
            *buffer++ = cDigitsLut[d4];
            *buffer++ = cDigitsLut[d4 + 1];
        }
    }
    else if (value < kTen16) {
        const uint32_t v0 = static_cast<uint32_t>(value / kTen8);
        const uint32_t v1 = static_cast<uint32_t>(value % kTen8);

        const uint32_t b0 = v0 / 10000;
        const uint32_t c0 = v0 % 10000;

        const uint32_t d1 = (b0 / 100) << 1;
        const uint32_t d2 = (b0 % 100) << 1;

        const uint32_t d3 = (c0 / 100) << 1;
        const uint32_t d4 = (c0 % 100) << 1;

        const uint32_t b1 = v1 / 10000;
        const uint32_t c1 = v1 % 10000;

        const uint32_t d5 = (b1 / 100) << 1;
        const uint32_t d6 = (b1 % 100) << 1;

        const uint32_t d7 = (c1 / 100) << 1;
        const uint32_t d8 = (c1 % 100) << 1;

        if (value >= kTen15)
            *buffer++ = cDigitsLut[d1];
        if (value >= kTen14)
            *buffer++ = cDigitsLut[d1 + 1];
        if (value >= kTen13)
            *buffer++ = cDigitsLut[d2];
        if (value >= kTen12)
            *buffer++ = cDigitsLut[d2 + 1];
        if (value >= kTen11)
            *buffer++ = cDigitsLut[d3];
        if (value >= kTen10)
            *buffer++ = cDigitsLut[d3 + 1];
        if (value >= kTen9)
            *buffer++ = cDigitsLut[d4];

        *buffer++ = cDigitsLut[d4 + 1];
        *buffer++ = cDigitsLut[d5];
        *buffer++ = cDigitsLut[d5 + 1];
        *buffer++ = cDigitsLut[d6];
        *buffer++ = cDigitsLut[d6 + 1];
        *buffer++ = cDigitsLut[d7];
        *buffer++ = cDigitsLut[d7 + 1];
        *buffer++ = cDigitsLut[d8];
        *buffer++ = cDigitsLut[d8 + 1];
    }
    else {
        const uint32_t a = static_cast<uint32_t>(value / kTen16); // 1 to 1844
        value %= kTen16;

        if (a < 10)
            *buffer++ = static_cast<char>('0' + static_cast<char>(a));
        else if (a < 100) {
            const uint32_t i = a << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
        }
        else if (a < 1000) {
            *buffer++ = static_cast<char>('0' + static_cast<char>(a / 100));

            const uint32_t i = (a % 100) << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
        }
        else {
            const uint32_t i = (a / 100) << 1;
            const uint32_t j = (a % 100) << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
            *buffer++ = cDigitsLut[j];
            *buffer++ = cDigitsLut[j + 1];
        }

        const uint32_t v0 = static_cast<uint32_t>(value / kTen8);
        const uint32_t v1 = static_cast<uint32_t>(value % kTen8);

        const uint32_t b0 = v0 / 10000;
        const uint32_t c0 = v0 % 10000;

        const uint32_t d1 = (b0 / 100) << 1;
        const uint32_t d2 = (b0 % 100) << 1;

        const uint32_t d3 = (c0 / 100) << 1;
        const uint32_t d4 = (c0 % 100) << 1;

        const uint32_t b1 = v1 / 10000;
        const uint32_t c1 = v1 % 10000;

        const uint32_t d5 = (b1 / 100) << 1;
        const uint32_t d6 = (b1 % 100) << 1;

        const uint32_t d7 = (c1 / 100) << 1;
        const uint32_t d8 = (c1 % 100) << 1;

        *buffer++ = cDigitsLut[d1];
        *buffer++ = cDigitsLut[d1 + 1];
        *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
        *buffer++ = cDigitsLut[d3];
        *buffer++ = cDigitsLut[d3 + 1];
        *buffer++ = cDigitsLut[d4];
        *buffer++ = cDigitsLut[d4 + 1];
        *buffer++ = cDigitsLut[d5];
        *buffer++ = cDigitsLut[d5 + 1];
        *buffer++ = cDigitsLut[d6];
        *buffer++ = cDigitsLut[d6 + 1];
        *buffer++ = cDigitsLut[d7];
        *buffer++ = cDigitsLut[d7 + 1];
        *buffer++ = cDigitsLut[d8];
        *buffer++ = cDigitsLut[d8 + 1];
    }

    return buffer;
}

inline char* i64toa(int64_t value, char* buffer) {
    RAPIDJSON_ASSERT(buffer != 0);
    uint64_t u = static_cast<uint64_t>(value);
    if (value < 0) {
        *buffer++ = '-';
        u = ~u + 1;
    }

    return u64toa(u, buffer);
}

} // namespace internal
RAPIDJSON_NAMESPACE_END

#endif // RAPIDJSON_ITOA_

// End file:internal/itoa.h


// Begin file: error/error.h
// already included
// End file:error/error.h


#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(switch-enum)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4512) // assignment operator could not be generated
#endif

#if defined(RAPIDJSON_CPLUSPLUS) && RAPIDJSON_CPLUSPLUS >= 201703L
#define RAPIDJSON_IF_CONSTEXPR if constexpr
#else
#define RAPIDJSON_IF_CONSTEXPR if
#endif

RAPIDJSON_NAMESPACE_BEGIN

static const SizeType kPointerInvalidIndex = ~SizeType(0);  //!< Represents an invalid index in GenericPointer::Token

///////////////////////////////////////////////////////////////////////////////
// GenericPointer

//! Represents a JSON Pointer. Use Pointer for UTF8 encoding and default allocator.
/*!
    This class implements RFC 6901 "JavaScript Object Notation (JSON) Pointer" 
    (https://tools.ietf.org/html/rfc6901).

    A JSON pointer is for identifying a specific value in a JSON document
    (GenericDocument). It can simplify coding of DOM tree manipulation, because it
    can access multiple-level depth of DOM tree with single API call.

    After it parses a string representation (e.g. "/foo/0" or URI fragment 
    representation (e.g. "#/foo/0") into its internal representation (tokens),
    it can be used to resolve a specific value in multiple documents, or sub-tree 
    of documents.

    Contrary to GenericValue, Pointer can be copy constructed and copy assigned.
    Apart from assignment, a Pointer cannot be modified after construction.

    Although Pointer is very convenient, please aware that constructing Pointer
    involves parsing and dynamic memory allocation. A special constructor with user-
    supplied tokens eliminates these.

    GenericPointer depends on GenericDocument and GenericValue.

    \tparam ValueType The value type of the DOM tree. E.g. GenericValue<UTF8<> >
    \tparam Allocator The allocator type for allocating memory for internal representation.

    \note GenericPointer uses same encoding of ValueType.
    However, Allocator of GenericPointer is independent of Allocator of Value.
*/
template <typename ValueType, typename Allocator = CrtAllocator>
class GenericPointer {
public:
    typedef typename ValueType::EncodingType EncodingType;  //!< Encoding type from Value
    typedef typename ValueType::Ch Ch;                      //!< Character type from Value
    typedef GenericUri<ValueType, Allocator> UriType;


  //! A token is the basic units of internal representation.
    /*!
        A JSON pointer string representation "/foo/123" is parsed to two tokens: 
        "foo" and 123. 123 will be represented in both numeric form and string form.
        They are resolved according to the actual value type (object or array).

        For token that are not numbers, or the numeric value is out of bound
        (greater than limits of SizeType), they are only treated as string form
        (i.e. the token's index will be equal to kPointerInvalidIndex).

        This struct is public so that user can create a Pointer without parsing and 
        allocation, using a special constructor.
    */
    struct Token {
        const Ch* name;             //!< Name of the token. It has null character at the end but it can contain null character.
        SizeType length;            //!< Length of the name.
        SizeType index;             //!< A valid array index, if it is not equal to kPointerInvalidIndex.
    };

    //!@name Constructors and destructor.
    //@{

    //! Default constructor.
    GenericPointer(Allocator* allocator = 0) : allocator_(allocator), ownAllocator_(), nameBuffer_(), tokens_(), tokenCount_(), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {}

    //! Constructor that parses a string or URI fragment representation.
    /*!
        \param source A null-terminated, string or URI fragment representation of JSON pointer.
        \param allocator User supplied allocator for this pointer. If no allocator is provided, it creates a self-owned one.
    */
    explicit GenericPointer(const Ch* source, Allocator* allocator = 0) : allocator_(allocator), ownAllocator_(), nameBuffer_(), tokens_(), tokenCount_(), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {
        Parse(source, internal::StrLen(source));
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Constructor that parses a string or URI fragment representation.
    /*!
        \param source A string or URI fragment representation of JSON pointer.
        \param allocator User supplied allocator for this pointer. If no allocator is provided, it creates a self-owned one.
        \note Requires the definition of the preprocessor symbol \ref RAPIDJSON_HAS_STDSTRING.
    */
    explicit GenericPointer(const std::basic_string<Ch>& source, Allocator* allocator = 0) : allocator_(allocator), ownAllocator_(), nameBuffer_(), tokens_(), tokenCount_(), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {
        Parse(source.c_str(), source.size());
    }
#endif

    //! Constructor that parses a string or URI fragment representation, with length of the source string.
    /*!
        \param source A string or URI fragment representation of JSON pointer.
        \param length Length of source.
        \param allocator User supplied allocator for this pointer. If no allocator is provided, it creates a self-owned one.
        \note Slightly faster than the overload without length.
    */
    GenericPointer(const Ch* source, size_t length, Allocator* allocator = 0) : allocator_(allocator), ownAllocator_(), nameBuffer_(), tokens_(), tokenCount_(), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {
        Parse(source, length);
    }

    //! Constructor with user-supplied tokens.
    /*!
        This constructor let user supplies const array of tokens.
        This prevents the parsing process and eliminates allocation.
        This is preferred for memory constrained environments.

        \param tokens An constant array of tokens representing the JSON pointer.
        \param tokenCount Number of tokens.

        \b Example
        \code
        #define NAME(s) { s, sizeof(s) / sizeof(s[0]) - 1, kPointerInvalidIndex }
        #define INDEX(i) { #i, sizeof(#i) - 1, i }

        static const Pointer::Token kTokens[] = { NAME("foo"), INDEX(123) };
        static const Pointer p(kTokens, sizeof(kTokens) / sizeof(kTokens[0]));
        // Equivalent to static const Pointer p("/foo/123");

        #undef NAME
        #undef INDEX
        \endcode
    */
    GenericPointer(const Token* tokens, size_t tokenCount) : allocator_(), ownAllocator_(), nameBuffer_(), tokens_(const_cast<Token*>(tokens)), tokenCount_(tokenCount), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {}

    //! Copy constructor.
    GenericPointer(const GenericPointer& rhs) : allocator_(), ownAllocator_(), nameBuffer_(), tokens_(), tokenCount_(), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {
        *this = rhs;
    }

    //! Copy constructor.
    GenericPointer(const GenericPointer& rhs, Allocator* allocator) : allocator_(allocator), ownAllocator_(), nameBuffer_(), tokens_(), tokenCount_(), parseErrorOffset_(), parseErrorCode_(kPointerParseErrorNone) {
        *this = rhs;
    }

    //! Destructor.
    ~GenericPointer() {
        if (nameBuffer_)    // If user-supplied tokens constructor is used, nameBuffer_ is nullptr and tokens_ are not deallocated.
            Allocator::Free(tokens_);
        RAPIDJSON_DELETE(ownAllocator_);
    }

    //! Assignment operator.
    GenericPointer& operator=(const GenericPointer& rhs) {
        if (this != &rhs) {
            // Do not delete ownAllcator
            if (nameBuffer_)
                Allocator::Free(tokens_);

            tokenCount_ = rhs.tokenCount_;
            parseErrorOffset_ = rhs.parseErrorOffset_;
            parseErrorCode_ = rhs.parseErrorCode_;

            if (rhs.nameBuffer_)
                CopyFromRaw(rhs); // Normally parsed tokens.
            else {
                tokens_ = rhs.tokens_; // User supplied const tokens.
                nameBuffer_ = 0;
            }
        }
        return *this;
    }

    //! Swap the content of this pointer with an other.
    /*!
        \param other The pointer to swap with.
        \note Constant complexity.
    */
    GenericPointer& Swap(GenericPointer& other) RAPIDJSON_NOEXCEPT {
        internal::Swap(allocator_, other.allocator_);
        internal::Swap(ownAllocator_, other.ownAllocator_);
        internal::Swap(nameBuffer_, other.nameBuffer_);
        internal::Swap(tokens_, other.tokens_);
        internal::Swap(tokenCount_, other.tokenCount_);
        internal::Swap(parseErrorOffset_, other.parseErrorOffset_);
        internal::Swap(parseErrorCode_, other.parseErrorCode_);
        return *this;
    }

    //! free-standing swap function helper
    /*!
        Helper function to enable support for common swap implementation pattern based on \c std::swap:
        \code
        void swap(MyClass& a, MyClass& b) {
            using std::swap;
            swap(a.pointer, b.pointer);
            // ...
        }
        \endcode
        \see Swap()
     */
    friend inline void swap(GenericPointer& a, GenericPointer& b) RAPIDJSON_NOEXCEPT { a.Swap(b); }

    //@}

    //!@name Append token
    //@{

    //! Append a token and return a new Pointer
    /*!
        \param token Token to be appended.
        \param allocator Allocator for the newly return Pointer.
        \return A new Pointer with appended token.
    */
    GenericPointer Append(const Token& token, Allocator* allocator = 0) const {
        GenericPointer r;
        r.allocator_ = allocator;
        Ch *p = r.CopyFromRaw(*this, 1, token.length + 1);
        std::memcpy(p, token.name, (token.length + 1) * sizeof(Ch));
        r.tokens_[tokenCount_].name = p;
        r.tokens_[tokenCount_].length = token.length;
        r.tokens_[tokenCount_].index = token.index;
        return r;
    }

    //! Append a name token with length, and return a new Pointer
    /*!
        \param name Name to be appended.
        \param length Length of name.
        \param allocator Allocator for the newly return Pointer.
        \return A new Pointer with appended token.
    */
    GenericPointer Append(const Ch* name, SizeType length, Allocator* allocator = 0) const {
        Token token = { name, length, kPointerInvalidIndex };
        return Append(token, allocator);
    }

    //! Append a name token without length, and return a new Pointer
    /*!
        \param name Name (const Ch*) to be appended.
        \param allocator Allocator for the newly return Pointer.
        \return A new Pointer with appended token.
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::NotExpr<internal::IsSame<typename internal::RemoveConst<T>::Type, Ch> >), (GenericPointer))
    Append(T* name, Allocator* allocator = 0) const {
        return Append(name, internal::StrLen(name), allocator);
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Append a name token, and return a new Pointer
    /*!
        \param name Name to be appended.
        \param allocator Allocator for the newly return Pointer.
        \return A new Pointer with appended token.
    */
    GenericPointer Append(const std::basic_string<Ch>& name, Allocator* allocator = 0) const {
        return Append(name.c_str(), static_cast<SizeType>(name.size()), allocator);
    }
#endif

    //! Append a index token, and return a new Pointer
    /*!
        \param index Index to be appended.
        \param allocator Allocator for the newly return Pointer.
        \return A new Pointer with appended token.
    */
    GenericPointer Append(SizeType index, Allocator* allocator = 0) const {
        char buffer[21];
        char* end = sizeof(SizeType) == 4 ? internal::u32toa(index, buffer) : internal::u64toa(index, buffer);
        SizeType length = static_cast<SizeType>(end - buffer);
        buffer[length] = '\0';

        RAPIDJSON_IF_CONSTEXPR (sizeof(Ch) == 1) {
            Token token = { reinterpret_cast<Ch*>(buffer), length, index };
            return Append(token, allocator);
        }
        else {
            Ch name[21];
            for (size_t i = 0; i <= length; i++)
                name[i] = static_cast<Ch>(buffer[i]);
            Token token = { name, length, index };
            return Append(token, allocator);
        }
    }

    //! Append a token by value, and return a new Pointer
    /*!
        \param token token to be appended.
        \param allocator Allocator for the newly return Pointer.
        \return A new Pointer with appended token.
    */
    GenericPointer Append(const ValueType& token, Allocator* allocator = 0) const {
        if (token.IsString())
            return Append(token.GetString(), token.GetStringLength(), allocator);
        else {
            RAPIDJSON_ASSERT(token.IsUint64());
            RAPIDJSON_ASSERT(token.GetUint64() <= SizeType(~0));
            return Append(static_cast<SizeType>(token.GetUint64()), allocator);
        }
    }

    //!@name Handling Parse Error
    //@{

    //! Check whether this is a valid pointer.
    bool IsValid() const { return parseErrorCode_ == kPointerParseErrorNone; }

    //! Get the parsing error offset in code unit.
    size_t GetParseErrorOffset() const { return parseErrorOffset_; }

    //! Get the parsing error code.
    PointerParseErrorCode GetParseErrorCode() const { return parseErrorCode_; }

    //@}

    //! Get the allocator of this pointer.
    Allocator& GetAllocator() { return *allocator_; }

    //!@name Tokens
    //@{

    //! Get the token array (const version only).
    const Token* GetTokens() const { return tokens_; }

    //! Get the number of tokens.
    size_t GetTokenCount() const { return tokenCount_; }

    //@}

    //!@name Equality/inequality operators
    //@{

    //! Equality operator.
    /*!
        \note When any pointers are invalid, always returns false.
    */
    bool operator==(const GenericPointer& rhs) const {
        if (!IsValid() || !rhs.IsValid() || tokenCount_ != rhs.tokenCount_)
            return false;

        for (size_t i = 0; i < tokenCount_; i++) {
            if (tokens_[i].index != rhs.tokens_[i].index ||
                tokens_[i].length != rhs.tokens_[i].length || 
                (tokens_[i].length != 0 && std::memcmp(tokens_[i].name, rhs.tokens_[i].name, sizeof(Ch)* tokens_[i].length) != 0))
            {
                return false;
            }
        }

        return true;
    }

    //! Inequality operator.
    /*!
        \note When any pointers are invalid, always returns true.
    */
    bool operator!=(const GenericPointer& rhs) const { return !(*this == rhs); }

    //! Less than operator.
    /*!
        \note Invalid pointers are always greater than valid ones.
    */
    bool operator<(const GenericPointer& rhs) const {
        if (!IsValid())
            return false;
        if (!rhs.IsValid())
            return true;

        if (tokenCount_ != rhs.tokenCount_)
            return tokenCount_ < rhs.tokenCount_;

        for (size_t i = 0; i < tokenCount_; i++) {
            if (tokens_[i].index != rhs.tokens_[i].index)
                return tokens_[i].index < rhs.tokens_[i].index;

            if (tokens_[i].length != rhs.tokens_[i].length)
                return tokens_[i].length < rhs.tokens_[i].length;

            if (int cmp = std::memcmp(tokens_[i].name, rhs.tokens_[i].name, sizeof(Ch) * tokens_[i].length))
                return cmp < 0;
        }

        return false;
    }

    //@}

    //!@name Stringify
    //@{

    //! Stringify the pointer into string representation.
    /*!
        \tparam OutputStream Type of output stream.
        \param os The output stream.
    */
    template<typename OutputStream>
    bool Stringify(OutputStream& os) const {
        return Stringify<false, OutputStream>(os);
    }

    //! Stringify the pointer into URI fragment representation.
    /*!
        \tparam OutputStream Type of output stream.
        \param os The output stream.
    */
    template<typename OutputStream>
    bool StringifyUriFragment(OutputStream& os) const {
        return Stringify<true, OutputStream>(os);
    }

    //@}

    //!@name Create value
    //@{

    //! Create a value in a subtree.
    /*!
        If the value is not exist, it creates all parent values and a JSON Null value.
        So it always succeed and return the newly created or existing value.

        Remind that it may change types of parents according to tokens, so it 
        potentially removes previously stored values. For example, if a document 
        was an array, and "/foo" is used to create a value, then the document 
        will be changed to an object, and all existing array elements are lost.

        \param root Root value of a DOM subtree to be resolved. It can be any value other than document root.
        \param allocator Allocator for creating the values if the specified value or its parents are not exist.
        \param alreadyExist If non-null, it stores whether the resolved value is already exist.
        \return The resolved newly created (a JSON Null value), or already exists value.
    */
    ValueType& Create(ValueType& root, typename ValueType::AllocatorType& allocator, bool* alreadyExist = 0) const {
        RAPIDJSON_ASSERT(IsValid());
        ValueType* v = &root;
        bool exist = true;
        for (const Token *t = tokens_; t != tokens_ + tokenCount_; ++t) {
            if (v->IsArray() && t->name[0] == '-' && t->length == 1) {
                v->PushBack(ValueType().Move(), allocator);
                v = &((*v)[v->Size() - 1]);
                exist = false;
            }
            else {
                if (t->index == kPointerInvalidIndex) { // must be object name
                    if (!v->IsObject())
                        v->SetObject(); // Change to Object
                }
                else { // object name or array index
                    if (!v->IsArray() && !v->IsObject())
                        v->SetArray(); // Change to Array
                }

                if (v->IsArray()) {
                    if (t->index >= v->Size()) {
                        v->Reserve(t->index + 1, allocator);
                        while (t->index >= v->Size())
                            v->PushBack(ValueType().Move(), allocator);
                        exist = false;
                    }
                    v = &((*v)[t->index]);
                }
                else {
                    typename ValueType::MemberIterator m = v->FindMember(GenericValue<EncodingType>(GenericStringRef<Ch>(t->name, t->length)));
                    if (m == v->MemberEnd()) {
                        v->AddMember(ValueType(t->name, t->length, allocator).Move(), ValueType().Move(), allocator);
                        m = v->MemberEnd();
                        v = &(--m)->value; // Assumes AddMember() appends at the end
                        exist = false;
                    }
                    else
                        v = &m->value;
                }
            }
        }

        if (alreadyExist)
            *alreadyExist = exist;

        return *v;
    }

    //! Creates a value in a document.
    /*!
        \param document A document to be resolved.
        \param alreadyExist If non-null, it stores whether the resolved value is already exist.
        \return The resolved newly created, or already exists value.
    */
    template <typename stackAllocator>
    ValueType& Create(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, bool* alreadyExist = 0) const {
        return Create(document, document.GetAllocator(), alreadyExist);
    }

    //@}

    //!@name Compute URI
    //@{

    //! Compute the in-scope URI for a subtree.
    //  For use with JSON pointers into JSON schema documents.
    /*!
        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \param rootUri Root URI
        \param unresolvedTokenIndex If the pointer cannot resolve a token in the pointer, this parameter can obtain the index of unresolved token.
        \param allocator Allocator for Uris
        \return Uri if it can be resolved. Otherwise null.

        \note
        There are only 3 situations when a URI cannot be resolved:
        1. A value in the path is not an array nor object.
        2. An object value does not contain the token.
        3. A token is out of range of an array value.

        Use unresolvedTokenIndex to retrieve the token index.
    */
    UriType GetUri(ValueType& root, const UriType& rootUri, size_t* unresolvedTokenIndex = 0, Allocator* allocator = 0) const {
        static const Ch kIdString[] = { 'i', 'd', '\0' };
        static const ValueType kIdValue(kIdString, 2);
        UriType base = UriType(rootUri, allocator);
        RAPIDJSON_ASSERT(IsValid());
        ValueType* v = &root;
        for (const Token *t = tokens_; t != tokens_ + tokenCount_; ++t) {
            switch (v->GetType()) {
                case kObjectType:
                {
                    // See if we have an id, and if so resolve with the current base
                    typename ValueType::MemberIterator m = v->FindMember(kIdValue);
                    if (m != v->MemberEnd() && (m->value).IsString()) {
                        UriType here = UriType(m->value, allocator).Resolve(base, allocator);
                        base = here;
                    }
                    m = v->FindMember(GenericValue<EncodingType>(GenericStringRef<Ch>(t->name, t->length)));
                    if (m == v->MemberEnd())
                        break;
                    v = &m->value;
                }
                  continue;
                case kArrayType:
                    if (t->index == kPointerInvalidIndex || t->index >= v->Size())
                        break;
                    v = &((*v)[t->index]);
                    continue;
                default:
                    break;
            }

            // Error: unresolved token
            if (unresolvedTokenIndex)
                *unresolvedTokenIndex = static_cast<size_t>(t - tokens_);
            return UriType(allocator);
        }
        return base;
    }

    UriType GetUri(const ValueType& root, const UriType& rootUri, size_t* unresolvedTokenIndex = 0, Allocator* allocator = 0) const {
      return GetUri(const_cast<ValueType&>(root), rootUri, unresolvedTokenIndex, allocator);
    }


    //!@name Query value
    //@{

    //! Query a value in a subtree.
    /*!
        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \param unresolvedTokenIndex If the pointer cannot resolve a token in the pointer, this parameter can obtain the index of unresolved token.
        \return Pointer to the value if it can be resolved. Otherwise null.

        \note
        There are only 3 situations when a value cannot be resolved:
        1. A value in the path is not an array nor object.
        2. An object value does not contain the token.
        3. A token is out of range of an array value.

        Use unresolvedTokenIndex to retrieve the token index.
    */
    ValueType* Get(ValueType& root, size_t* unresolvedTokenIndex = 0) const {
        RAPIDJSON_ASSERT(IsValid());
        ValueType* v = &root;
        for (const Token *t = tokens_; t != tokens_ + tokenCount_; ++t) {
            switch (v->GetType()) {
            case kObjectType:
                {
                    typename ValueType::MemberIterator m = v->FindMember(GenericValue<EncodingType>(GenericStringRef<Ch>(t->name, t->length)));
                    if (m == v->MemberEnd())
                        break;
                    v = &m->value;
                }
                continue;
            case kArrayType:
                if (t->index == kPointerInvalidIndex || t->index >= v->Size())
                    break;
                v = &((*v)[t->index]);
                continue;
            default:
                break;
            }

            // Error: unresolved token
            if (unresolvedTokenIndex)
                *unresolvedTokenIndex = static_cast<size_t>(t - tokens_);
            return 0;
        }
        return v;
    }

    //! Query a const value in a const subtree.
    /*!
        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \return Pointer to the value if it can be resolved. Otherwise null.
    */
    const ValueType* Get(const ValueType& root, size_t* unresolvedTokenIndex = 0) const { 
        return Get(const_cast<ValueType&>(root), unresolvedTokenIndex);
    }

    //@}

    //!@name Query a value with default
    //@{

    //! Query a value in a subtree with default value.
    /*!
        Similar to Get(), but if the specified value do not exists, it creates all parents and clone the default value.
        So that this function always succeed.

        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \param defaultValue Default value to be cloned if the value was not exists.
        \param allocator Allocator for creating the values if the specified value or its parents are not exist.
        \see Create()
    */
    ValueType& GetWithDefault(ValueType& root, const ValueType& defaultValue, typename ValueType::AllocatorType& allocator) const {
        bool alreadyExist;
        ValueType& v = Create(root, allocator, &alreadyExist);
        return alreadyExist ? v : v.CopyFrom(defaultValue, allocator);
    }

    //! Query a value in a subtree with default null-terminated string.
    ValueType& GetWithDefault(ValueType& root, const Ch* defaultValue, typename ValueType::AllocatorType& allocator) const {
        bool alreadyExist;
        ValueType& v = Create(root, allocator, &alreadyExist);
        return alreadyExist ? v : v.SetString(defaultValue, allocator);
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Query a value in a subtree with default std::basic_string.
    ValueType& GetWithDefault(ValueType& root, const std::basic_string<Ch>& defaultValue, typename ValueType::AllocatorType& allocator) const {
        bool alreadyExist;
        ValueType& v = Create(root, allocator, &alreadyExist);
        return alreadyExist ? v : v.SetString(defaultValue, allocator);
    }
#endif

    //! Query a value in a subtree with default primitive value.
    /*!
        \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t, \c bool
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (ValueType&))
    GetWithDefault(ValueType& root, T defaultValue, typename ValueType::AllocatorType& allocator) const {
        return GetWithDefault(root, ValueType(defaultValue).Move(), allocator);
    }

    //! Query a value in a document with default value.
    template <typename stackAllocator>
    ValueType& GetWithDefault(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, const ValueType& defaultValue) const {
        return GetWithDefault(document, defaultValue, document.GetAllocator());
    }

    //! Query a value in a document with default null-terminated string.
    template <typename stackAllocator>
    ValueType& GetWithDefault(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, const Ch* defaultValue) const {
        return GetWithDefault(document, defaultValue, document.GetAllocator());
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Query a value in a document with default std::basic_string.
    template <typename stackAllocator>
    ValueType& GetWithDefault(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, const std::basic_string<Ch>& defaultValue) const {
        return GetWithDefault(document, defaultValue, document.GetAllocator());
    }
#endif

    //! Query a value in a document with default primitive value.
    /*!
        \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t, \c bool
    */
    template <typename T, typename stackAllocator>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (ValueType&))
    GetWithDefault(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, T defaultValue) const {
        return GetWithDefault(document, defaultValue, document.GetAllocator());
    }

    //@}

    //!@name Set a value
    //@{

    //! Set a value in a subtree, with move semantics.
    /*!
        It creates all parents if they are not exist or types are different to the tokens.
        So this function always succeeds but potentially remove existing values.

        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \param value Value to be set.
        \param allocator Allocator for creating the values if the specified value or its parents are not exist.
        \see Create()
    */
    ValueType& Set(ValueType& root, ValueType& value, typename ValueType::AllocatorType& allocator) const {
        return Create(root, allocator) = value;
    }

    //! Set a value in a subtree, with copy semantics.
    ValueType& Set(ValueType& root, const ValueType& value, typename ValueType::AllocatorType& allocator) const {
        return Create(root, allocator).CopyFrom(value, allocator);
    }

    //! Set a null-terminated string in a subtree.
    ValueType& Set(ValueType& root, const Ch* value, typename ValueType::AllocatorType& allocator) const {
        return Create(root, allocator) = ValueType(value, allocator).Move();
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Set a std::basic_string in a subtree.
    ValueType& Set(ValueType& root, const std::basic_string<Ch>& value, typename ValueType::AllocatorType& allocator) const {
        return Create(root, allocator) = ValueType(value, allocator).Move();
    }
#endif

    //! Set a primitive value in a subtree.
    /*!
        \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t, \c bool
    */
    template <typename T>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (ValueType&))
    Set(ValueType& root, T value, typename ValueType::AllocatorType& allocator) const {
        return Create(root, allocator) = ValueType(value).Move();
    }

    //! Set a value in a document, with move semantics.
    template <typename stackAllocator>
    ValueType& Set(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, ValueType& value) const {
        return Create(document) = value;
    }

    //! Set a value in a document, with copy semantics.
    template <typename stackAllocator>
    ValueType& Set(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, const ValueType& value) const {
        return Create(document).CopyFrom(value, document.GetAllocator());
    }

    //! Set a null-terminated string in a document.
    template <typename stackAllocator>
    ValueType& Set(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, const Ch* value) const {
        return Create(document) = ValueType(value, document.GetAllocator()).Move();
    }

#if RAPIDJSON_HAS_STDSTRING
    //! Sets a std::basic_string in a document.
    template <typename stackAllocator>
    ValueType& Set(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, const std::basic_string<Ch>& value) const {
        return Create(document) = ValueType(value, document.GetAllocator()).Move();
    }
#endif

    //! Set a primitive value in a document.
    /*!
    \tparam T Either \ref Type, \c int, \c unsigned, \c int64_t, \c uint64_t, \c bool
    */
    template <typename T, typename stackAllocator>
    RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >), (ValueType&))
        Set(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, T value) const {
            return Create(document) = value;
    }

    //@}

    //!@name Swap a value
    //@{

    //! Swap a value with a value in a subtree.
    /*!
        It creates all parents if they are not exist or types are different to the tokens.
        So this function always succeeds but potentially remove existing values.

        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \param value Value to be swapped.
        \param allocator Allocator for creating the values if the specified value or its parents are not exist.
        \see Create()
    */
    ValueType& Swap(ValueType& root, ValueType& value, typename ValueType::AllocatorType& allocator) const {
        return Create(root, allocator).Swap(value);
    }

    //! Swap a value with a value in a document.
    template <typename stackAllocator>
    ValueType& Swap(GenericDocument<EncodingType, typename ValueType::AllocatorType, stackAllocator>& document, ValueType& value) const {
        return Create(document).Swap(value);
    }

    //@}

    //! Erase a value in a subtree.
    /*!
        \param root Root value of a DOM sub-tree to be resolved. It can be any value other than document root.
        \return Whether the resolved value is found and erased.

        \note Erasing with an empty pointer \c Pointer(""), i.e. the root, always fail and return false.
    */
    bool Erase(ValueType& root) const {
        RAPIDJSON_ASSERT(IsValid());
        if (tokenCount_ == 0) // Cannot erase the root
            return false;

        ValueType* v = &root;
        const Token* last = tokens_ + (tokenCount_ - 1);
        for (const Token *t = tokens_; t != last; ++t) {
            switch (v->GetType()) {
            case kObjectType:
                {
                    typename ValueType::MemberIterator m = v->FindMember(GenericValue<EncodingType>(GenericStringRef<Ch>(t->name, t->length)));
                    if (m == v->MemberEnd())
                        return false;
                    v = &m->value;
                }
                break;
            case kArrayType:
                if (t->index == kPointerInvalidIndex || t->index >= v->Size())
                    return false;
                v = &((*v)[t->index]);
                break;
            default:
                return false;
            }
        }

        switch (v->GetType()) {
        case kObjectType:
            return v->EraseMember(GenericStringRef<Ch>(last->name, last->length));
        case kArrayType:
            if (last->index == kPointerInvalidIndex || last->index >= v->Size())
                return false;
            v->Erase(v->Begin() + last->index);
            return true;
        default:
            return false;
        }
    }

private:
    //! Clone the content from rhs to this.
    /*!
        \param rhs Source pointer.
        \param extraToken Extra tokens to be allocated.
        \param extraNameBufferSize Extra name buffer size (in number of Ch) to be allocated.
        \return Start of non-occupied name buffer, for storing extra names.
    */
    Ch* CopyFromRaw(const GenericPointer& rhs, size_t extraToken = 0, size_t extraNameBufferSize = 0) {
        if (!allocator_) // allocator is independently owned.
            ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();

        size_t nameBufferSize = rhs.tokenCount_; // null terminators for tokens
        for (Token *t = rhs.tokens_; t != rhs.tokens_ + rhs.tokenCount_; ++t)
            nameBufferSize += t->length;

        tokenCount_ = rhs.tokenCount_ + extraToken;
        tokens_ = static_cast<Token *>(allocator_->Malloc(tokenCount_ * sizeof(Token) + (nameBufferSize + extraNameBufferSize) * sizeof(Ch)));
        nameBuffer_ = reinterpret_cast<Ch *>(tokens_ + tokenCount_);
        if (rhs.tokenCount_ > 0) {
            std::memcpy(tokens_, rhs.tokens_, rhs.tokenCount_ * sizeof(Token));
        }
        if (nameBufferSize > 0) {
            std::memcpy(nameBuffer_, rhs.nameBuffer_, nameBufferSize * sizeof(Ch));
        }

        // The names of each token point to a string in the nameBuffer_. The
        // previous memcpy copied over string pointers into the rhs.nameBuffer_,
        // but they should point to the strings in the new nameBuffer_.
        for (size_t i = 0; i < rhs.tokenCount_; ++i) {
          // The offset between the string address and the name buffer should
          // still be constant, so we can just get this offset and set each new
          // token name according the new buffer start + the known offset.
          std::ptrdiff_t name_offset = rhs.tokens_[i].name - rhs.nameBuffer_;
          tokens_[i].name = nameBuffer_ + name_offset;
        }

        return nameBuffer_ + nameBufferSize;
    }

    //! Check whether a character should be percent-encoded.
    /*!
        According to RFC 3986 2.3 Unreserved Characters.
        \param c The character (code unit) to be tested.
    */
    bool NeedPercentEncode(Ch c) const {
        return !((c >= '0' && c <= '9') || (c >= 'A' && c <='Z') || (c >= 'a' && c <= 'z') || c == '-' || c == '.' || c == '_' || c =='~');
    }

    //! Parse a JSON String or its URI fragment representation into tokens.
#ifndef __clang__ // -Wdocumentation
    /*!
        \param source Either a JSON Pointer string, or its URI fragment representation. Not need to be null terminated.
        \param length Length of the source string.
        \note Source cannot be JSON String Representation of JSON Pointer, e.g. In "/\u0000", \u0000 will not be unescaped.
    */
#endif
    void Parse(const Ch* source, size_t length) {
        RAPIDJSON_ASSERT(source != NULL);
        RAPIDJSON_ASSERT(nameBuffer_ == 0);
        RAPIDJSON_ASSERT(tokens_ == 0);

        // Create own allocator if user did not supply.
        if (!allocator_)
            ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();

        // Count number of '/' as tokenCount
        tokenCount_ = 0;
        for (const Ch* s = source; s != source + length; s++) 
            if (*s == '/')
                tokenCount_++;

        Token* token = tokens_ = static_cast<Token *>(allocator_->Malloc(tokenCount_ * sizeof(Token) + length * sizeof(Ch)));
        Ch* name = nameBuffer_ = reinterpret_cast<Ch *>(tokens_ + tokenCount_);
        size_t i = 0;

        // Detect if it is a URI fragment
        bool uriFragment = false;
        if (source[i] == '#') {
            uriFragment = true;
            i++;
        }

        if (i != length && source[i] != '/') {
            parseErrorCode_ = kPointerParseErrorTokenMustBeginWithSolidus;
            goto error;
        }

        while (i < length) {
            RAPIDJSON_ASSERT(source[i] == '/');
            i++; // consumes '/'

            token->name = name;
            bool isNumber = true;

            while (i < length && source[i] != '/') {
                Ch c = source[i];
                if (uriFragment) {
                    // Decoding percent-encoding for URI fragment
                    if (c == '%') {
                        PercentDecodeStream is(&source[i], source + length);
                        GenericInsituStringStream<EncodingType> os(name);
                        Ch* begin = os.PutBegin();
                        if (!Transcoder<UTF8<>, EncodingType>().Validate(is, os) || !is.IsValid()) {
                            parseErrorCode_ = kPointerParseErrorInvalidPercentEncoding;
                            goto error;
                        }
                        size_t len = os.PutEnd(begin);
                        i += is.Tell() - 1;
                        if (len == 1)
                            c = *name;
                        else {
                            name += len;
                            isNumber = false;
                            i++;
                            continue;
                        }
                    }
                    else if (NeedPercentEncode(c)) {
                        parseErrorCode_ = kPointerParseErrorCharacterMustPercentEncode;
                        goto error;
                    }
                }

                i++;

                // Escaping "~0" -> '~', "~1" -> '/'
                if (c == '~') {
                    if (i < length) {
                        c = source[i];
                        if (c == '0')       c = '~';
                        else if (c == '1')  c = '/';
                        else {
                            parseErrorCode_ = kPointerParseErrorInvalidEscape;
                            goto error;
                        }
                        i++;
                    }
                    else {
                        parseErrorCode_ = kPointerParseErrorInvalidEscape;
                        goto error;
                    }
                }

                // First check for index: all of characters are digit
                if (c < '0' || c > '9')
                    isNumber = false;

                *name++ = c;
            }
            token->length = static_cast<SizeType>(name - token->name);
            if (token->length == 0)
                isNumber = false;
            *name++ = '\0'; // Null terminator

            // Second check for index: more than one digit cannot have leading zero
            if (isNumber && token->length > 1 && token->name[0] == '0')
                isNumber = false;

            // String to SizeType conversion
            SizeType n = 0;
            if (isNumber) {
                for (size_t j = 0; j < token->length; j++) {
                    SizeType m = n * 10 + static_cast<SizeType>(token->name[j] - '0');
                    if (m < n) {   // overflow detection
                        isNumber = false;
                        break;
                    }
                    n = m;
                }
            }

            token->index = isNumber ? n : kPointerInvalidIndex;
            token++;
        }

        RAPIDJSON_ASSERT(name <= nameBuffer_ + length); // Should not overflow buffer
        parseErrorCode_ = kPointerParseErrorNone;
        return;

    error:
        Allocator::Free(tokens_);
        nameBuffer_ = 0;
        tokens_ = 0;
        tokenCount_ = 0;
        parseErrorOffset_ = i;
        return;
    }

    //! Stringify to string or URI fragment representation.
    /*!
        \tparam uriFragment True for stringifying to URI fragment representation. False for string representation.
        \tparam OutputStream type of output stream.
        \param os The output stream.
    */
    template<bool uriFragment, typename OutputStream>
    bool Stringify(OutputStream& os) const {
        RAPIDJSON_ASSERT(IsValid());

        if (uriFragment)
            os.Put('#');

        for (Token *t = tokens_; t != tokens_ + tokenCount_; ++t) {
            os.Put('/');
            for (size_t j = 0; j < t->length; j++) {
                Ch c = t->name[j];
                if (c == '~') {
                    os.Put('~');
                    os.Put('0');
                }
                else if (c == '/') {
                    os.Put('~');
                    os.Put('1');
                }
                else if (uriFragment && NeedPercentEncode(c)) { 
                    // Transcode to UTF8 sequence
                    GenericStringStream<typename ValueType::EncodingType> source(&t->name[j]);
                    PercentEncodeStream<OutputStream> target(os);
                    if (!Transcoder<EncodingType, UTF8<> >().Validate(source, target))
                        return false;
                    j += source.Tell() - 1;
                }
                else
                    os.Put(c);
            }
        }
        return true;
    }

    //! A helper stream for decoding a percent-encoded sequence into code unit.
    /*!
        This stream decodes %XY triplet into code unit (0-255).
        If it encounters invalid characters, it sets output code unit as 0 and 
        mark invalid, and to be checked by IsValid().
    */
    class PercentDecodeStream {
    public:
        typedef typename ValueType::Ch Ch;

        //! Constructor
        /*!
            \param source Start of the stream
            \param end Past-the-end of the stream.
        */
        PercentDecodeStream(const Ch* source, const Ch* end) : src_(source), head_(source), end_(end), valid_(true) {}

        Ch Take() {
            if (*src_ != '%' || src_ + 3 > end_) { // %XY triplet
                valid_ = false;
                return 0;
            }
            src_++;
            Ch c = 0;
            for (int j = 0; j < 2; j++) {
                c = static_cast<Ch>(c << 4);
                Ch h = *src_;
                if      (h >= '0' && h <= '9') c = static_cast<Ch>(c + h - '0');
                else if (h >= 'A' && h <= 'F') c = static_cast<Ch>(c + h - 'A' + 10);
                else if (h >= 'a' && h <= 'f') c = static_cast<Ch>(c + h - 'a' + 10);
                else {
                    valid_ = false;
                    return 0;
                }
                src_++;
            }
            return c;
        }

        size_t Tell() const { return static_cast<size_t>(src_ - head_); }
        bool IsValid() const { return valid_; }

    private:
        const Ch* src_;     //!< Current read position.
        const Ch* head_;    //!< Original head of the string.
        const Ch* end_;     //!< Past-the-end position.
        bool valid_;        //!< Whether the parsing is valid.
    };

    //! A helper stream to encode character (UTF-8 code unit) into percent-encoded sequence.
    template <typename OutputStream>
    class PercentEncodeStream {
    public:
        PercentEncodeStream(OutputStream& os) : os_(os) {}
        void Put(char c) { // UTF-8 must be byte
            unsigned char u = static_cast<unsigned char>(c);
            static const char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
            os_.Put('%');
            os_.Put(static_cast<typename OutputStream::Ch>(hexDigits[u >> 4]));
            os_.Put(static_cast<typename OutputStream::Ch>(hexDigits[u & 15]));
        }
    private:
        OutputStream& os_;
    };

    Allocator* allocator_;                  //!< The current allocator. It is either user-supplied or equal to ownAllocator_.
    Allocator* ownAllocator_;               //!< Allocator owned by this Pointer.
    Ch* nameBuffer_;                        //!< A buffer containing all names in tokens.
    Token* tokens_;                         //!< A list of tokens.
    size_t tokenCount_;                     //!< Number of tokens in tokens_.
    size_t parseErrorOffset_;               //!< Offset in code unit when parsing fail.
    PointerParseErrorCode parseErrorCode_;  //!< Parsing error code.
};

//! GenericPointer for Value (UTF-8, default allocator).
typedef GenericPointer<Value> Pointer;

//!@name Helper functions for GenericPointer
//@{

//////////////////////////////////////////////////////////////////////////////

template <typename T>
typename T::ValueType& CreateValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, typename T::AllocatorType& a) {
    return pointer.Create(root, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& CreateValueByPointer(T& root, const CharType(&source)[N], typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Create(root, a);
}

// No allocator parameter

template <typename DocumentType>
typename DocumentType::ValueType& CreateValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer) {
    return pointer.Create(document);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& CreateValueByPointer(DocumentType& document, const CharType(&source)[N]) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Create(document);
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
typename T::ValueType* GetValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, size_t* unresolvedTokenIndex = 0) {
    return pointer.Get(root, unresolvedTokenIndex);
}

template <typename T>
const typename T::ValueType* GetValueByPointer(const T& root, const GenericPointer<typename T::ValueType>& pointer, size_t* unresolvedTokenIndex = 0) {
    return pointer.Get(root, unresolvedTokenIndex);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType* GetValueByPointer(T& root, const CharType (&source)[N], size_t* unresolvedTokenIndex = 0) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Get(root, unresolvedTokenIndex);
}

template <typename T, typename CharType, size_t N>
const typename T::ValueType* GetValueByPointer(const T& root, const CharType(&source)[N], size_t* unresolvedTokenIndex = 0) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Get(root, unresolvedTokenIndex);
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
typename T::ValueType& GetValueByPointerWithDefault(T& root, const GenericPointer<typename T::ValueType>& pointer, const typename T::ValueType& defaultValue, typename T::AllocatorType& a) {
    return pointer.GetWithDefault(root, defaultValue, a);
}

template <typename T>
typename T::ValueType& GetValueByPointerWithDefault(T& root, const GenericPointer<typename T::ValueType>& pointer, const typename T::Ch* defaultValue, typename T::AllocatorType& a) {
    return pointer.GetWithDefault(root, defaultValue, a);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename T>
typename T::ValueType& GetValueByPointerWithDefault(T& root, const GenericPointer<typename T::ValueType>& pointer, const std::basic_string<typename T::Ch>& defaultValue, typename T::AllocatorType& a) {
    return pointer.GetWithDefault(root, defaultValue, a);
}
#endif

template <typename T, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename T::ValueType&))
GetValueByPointerWithDefault(T& root, const GenericPointer<typename T::ValueType>& pointer, T2 defaultValue, typename T::AllocatorType& a) {
    return pointer.GetWithDefault(root, defaultValue, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& GetValueByPointerWithDefault(T& root, const CharType(&source)[N], const typename T::ValueType& defaultValue, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).GetWithDefault(root, defaultValue, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& GetValueByPointerWithDefault(T& root, const CharType(&source)[N], const typename T::Ch* defaultValue, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).GetWithDefault(root, defaultValue, a);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename T, typename CharType, size_t N>
typename T::ValueType& GetValueByPointerWithDefault(T& root, const CharType(&source)[N], const std::basic_string<typename T::Ch>& defaultValue, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).GetWithDefault(root, defaultValue, a);
}
#endif

template <typename T, typename CharType, size_t N, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename T::ValueType&))
GetValueByPointerWithDefault(T& root, const CharType(&source)[N], T2 defaultValue, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).GetWithDefault(root, defaultValue, a);
}

// No allocator parameter

template <typename DocumentType>
typename DocumentType::ValueType& GetValueByPointerWithDefault(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, const typename DocumentType::ValueType& defaultValue) {
    return pointer.GetWithDefault(document, defaultValue);
}

template <typename DocumentType>
typename DocumentType::ValueType& GetValueByPointerWithDefault(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, const typename DocumentType::Ch* defaultValue) {
    return pointer.GetWithDefault(document, defaultValue);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename DocumentType>
typename DocumentType::ValueType& GetValueByPointerWithDefault(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, const std::basic_string<typename DocumentType::Ch>& defaultValue) {
    return pointer.GetWithDefault(document, defaultValue);
}
#endif

template <typename DocumentType, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename DocumentType::ValueType&))
GetValueByPointerWithDefault(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, T2 defaultValue) {
    return pointer.GetWithDefault(document, defaultValue);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& GetValueByPointerWithDefault(DocumentType& document, const CharType(&source)[N], const typename DocumentType::ValueType& defaultValue) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).GetWithDefault(document, defaultValue);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& GetValueByPointerWithDefault(DocumentType& document, const CharType(&source)[N], const typename DocumentType::Ch* defaultValue) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).GetWithDefault(document, defaultValue);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& GetValueByPointerWithDefault(DocumentType& document, const CharType(&source)[N], const std::basic_string<typename DocumentType::Ch>& defaultValue) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).GetWithDefault(document, defaultValue);
}
#endif

template <typename DocumentType, typename CharType, size_t N, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename DocumentType::ValueType&))
GetValueByPointerWithDefault(DocumentType& document, const CharType(&source)[N], T2 defaultValue) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).GetWithDefault(document, defaultValue);
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
typename T::ValueType& SetValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, typename T::ValueType& value, typename T::AllocatorType& a) {
    return pointer.Set(root, value, a);
}

template <typename T>
typename T::ValueType& SetValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, const typename T::ValueType& value, typename T::AllocatorType& a) {
    return pointer.Set(root, value, a);
}

template <typename T>
typename T::ValueType& SetValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, const typename T::Ch* value, typename T::AllocatorType& a) {
    return pointer.Set(root, value, a);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename T>
typename T::ValueType& SetValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, const std::basic_string<typename T::Ch>& value, typename T::AllocatorType& a) {
    return pointer.Set(root, value, a);
}
#endif

template <typename T, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename T::ValueType&))
SetValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, T2 value, typename T::AllocatorType& a) {
    return pointer.Set(root, value, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& SetValueByPointer(T& root, const CharType(&source)[N], typename T::ValueType& value, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Set(root, value, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& SetValueByPointer(T& root, const CharType(&source)[N], const typename T::ValueType& value, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Set(root, value, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& SetValueByPointer(T& root, const CharType(&source)[N], const typename T::Ch* value, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Set(root, value, a);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename T, typename CharType, size_t N>
typename T::ValueType& SetValueByPointer(T& root, const CharType(&source)[N], const std::basic_string<typename T::Ch>& value, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Set(root, value, a);
}
#endif

template <typename T, typename CharType, size_t N, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename T::ValueType&))
SetValueByPointer(T& root, const CharType(&source)[N], T2 value, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Set(root, value, a);
}

// No allocator parameter

template <typename DocumentType>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, typename DocumentType::ValueType& value) {
    return pointer.Set(document, value);
}

template <typename DocumentType>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, const typename DocumentType::ValueType& value) {
    return pointer.Set(document, value);
}

template <typename DocumentType>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, const typename DocumentType::Ch* value) {
    return pointer.Set(document, value);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename DocumentType>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, const std::basic_string<typename DocumentType::Ch>& value) {
    return pointer.Set(document, value);
}
#endif

template <typename DocumentType, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename DocumentType::ValueType&))
SetValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, T2 value) {
    return pointer.Set(document, value);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const CharType(&source)[N], typename DocumentType::ValueType& value) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Set(document, value);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const CharType(&source)[N], const typename DocumentType::ValueType& value) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Set(document, value);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const CharType(&source)[N], const typename DocumentType::Ch* value) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Set(document, value);
}

#if RAPIDJSON_HAS_STDSTRING
template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& SetValueByPointer(DocumentType& document, const CharType(&source)[N], const std::basic_string<typename DocumentType::Ch>& value) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Set(document, value);
}
#endif

template <typename DocumentType, typename CharType, size_t N, typename T2>
RAPIDJSON_DISABLEIF_RETURN((internal::OrExpr<internal::IsPointer<T2>, internal::IsGenericValue<T2> >), (typename DocumentType::ValueType&))
SetValueByPointer(DocumentType& document, const CharType(&source)[N], T2 value) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Set(document, value);
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
typename T::ValueType& SwapValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer, typename T::ValueType& value, typename T::AllocatorType& a) {
    return pointer.Swap(root, value, a);
}

template <typename T, typename CharType, size_t N>
typename T::ValueType& SwapValueByPointer(T& root, const CharType(&source)[N], typename T::ValueType& value, typename T::AllocatorType& a) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Swap(root, value, a);
}

template <typename DocumentType>
typename DocumentType::ValueType& SwapValueByPointer(DocumentType& document, const GenericPointer<typename DocumentType::ValueType>& pointer, typename DocumentType::ValueType& value) {
    return pointer.Swap(document, value);
}

template <typename DocumentType, typename CharType, size_t N>
typename DocumentType::ValueType& SwapValueByPointer(DocumentType& document, const CharType(&source)[N], typename DocumentType::ValueType& value) {
    return GenericPointer<typename DocumentType::ValueType>(source, N - 1).Swap(document, value);
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
bool EraseValueByPointer(T& root, const GenericPointer<typename T::ValueType>& pointer) {
    return pointer.Erase(root);
}

template <typename T, typename CharType, size_t N>
bool EraseValueByPointer(T& root, const CharType(&source)[N]) {
    return GenericPointer<typename T::ValueType>(source, N - 1).Erase(root);
}

//@}

RAPIDJSON_NAMESPACE_END

#if defined(__clang__) || defined(_MSC_VER)
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_POINTER_H_

// End file:pointer.h


// Begin file: stringbuffer.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_STRINGBUFFER_H_
#define RAPIDJSON_STRINGBUFFER_H_


// Begin file: stream.h
// already included
// End file:stream.h


// Begin file: internal/stack.h
// already included
// End file:internal/stack.h


#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
#include <utility> // std::move
#endif


// Begin file: internal/stack.h
// already included
// End file:internal/stack.h


#if defined(__clang__)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(c++98-compat)
#endif

RAPIDJSON_NAMESPACE_BEGIN

//! Represents an in-memory output stream.
/*!
    \tparam Encoding Encoding of the stream.
    \tparam Allocator type for allocating memory buffer.
    \note implements Stream concept
*/
template <typename Encoding, typename Allocator = CrtAllocator>
class GenericStringBuffer {
public:
    typedef typename Encoding::Ch Ch;

    GenericStringBuffer(Allocator* allocator = 0, size_t capacity = kDefaultCapacity) : stack_(allocator, capacity) {}

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    GenericStringBuffer(GenericStringBuffer&& rhs) : stack_(std::move(rhs.stack_)) {}
    GenericStringBuffer& operator=(GenericStringBuffer&& rhs) {
        if (&rhs != this)
            stack_ = std::move(rhs.stack_);
        return *this;
    }
#endif

    void Put(Ch c) { *stack_.template Push<Ch>() = c; }
    void PutUnsafe(Ch c) { *stack_.template PushUnsafe<Ch>() = c; }
    void Flush() {}

    void Clear() { stack_.Clear(); }
    void ShrinkToFit() {
        // Push and pop a null terminator. This is safe.
        *stack_.template Push<Ch>() = '\0';
        stack_.ShrinkToFit();
        stack_.template Pop<Ch>(1);
    }

    void Reserve(size_t count) { stack_.template Reserve<Ch>(count); }
    Ch* Push(size_t count) { return stack_.template Push<Ch>(count); }
    Ch* PushUnsafe(size_t count) { return stack_.template PushUnsafe<Ch>(count); }
    void Pop(size_t count) { stack_.template Pop<Ch>(count); }

    const Ch* GetString() const {
        // Push and pop a null terminator. This is safe.
        *stack_.template Push<Ch>() = '\0';
        stack_.template Pop<Ch>(1);

        return stack_.template Bottom<Ch>();
    }

    //! Get the size of string in bytes in the string buffer.
    size_t GetSize() const { return stack_.GetSize(); }

    //! Get the length of string in Ch in the string buffer.
    size_t GetLength() const { return stack_.GetSize() / sizeof(Ch); }

    static const size_t kDefaultCapacity = 256;
    mutable internal::Stack<Allocator> stack_;

private:
    // Prohibit copy constructor & assignment operator.
    GenericStringBuffer(const GenericStringBuffer&);
    GenericStringBuffer& operator=(const GenericStringBuffer&);
};

//! String buffer with UTF8 encoding
typedef GenericStringBuffer<UTF8<> > StringBuffer;

template<typename Encoding, typename Allocator>
inline void PutReserve(GenericStringBuffer<Encoding, Allocator>& stream, size_t count) {
    stream.Reserve(count);
}

template<typename Encoding, typename Allocator>
inline void PutUnsafe(GenericStringBuffer<Encoding, Allocator>& stream, typename Encoding::Ch c) {
    stream.PutUnsafe(c);
}

//! Implement specialized version of PutN() with memset() for better performance.
template<>
inline void PutN(GenericStringBuffer<UTF8<> >& stream, char c, size_t n) {
    std::memset(stream.stack_.Push<char>(n), c, n * sizeof(c));
}

RAPIDJSON_NAMESPACE_END

#if defined(__clang__)
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_STRINGBUFFER_H_

// End file:stringbuffer.h


// Begin file: error/en.h
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_ERROR_EN_H_
#define RAPIDJSON_ERROR_EN_H_


// Begin file: error.h
// already included
// End file:error.h


#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(switch-enum)
RAPIDJSON_DIAG_OFF(covered-switch-default)
#endif

RAPIDJSON_NAMESPACE_BEGIN

//! Maps error code of parsing into error message.
/*!
    \ingroup RAPIDJSON_ERRORS
    \param parseErrorCode Error code obtained in parsing.
    \return the error message.
    \note User can make a copy of this function for localization.
        Using switch-case is safer for future modification of error codes.
*/
inline const RAPIDJSON_ERROR_CHARTYPE* GetParseError_En(ParseErrorCode parseErrorCode) {
    switch (parseErrorCode) {
        case kParseErrorNone:                           return RAPIDJSON_ERROR_STRING("No error.");

        case kParseErrorDocumentEmpty:                  return RAPIDJSON_ERROR_STRING("The document is empty.");
        case kParseErrorDocumentRootNotSingular:        return RAPIDJSON_ERROR_STRING("The document root must not be followed by other values.");

        case kParseErrorValueInvalid:                   return RAPIDJSON_ERROR_STRING("Invalid value.");

        case kParseErrorObjectMissName:                 return RAPIDJSON_ERROR_STRING("Missing a name for object member.");
        case kParseErrorObjectMissColon:                return RAPIDJSON_ERROR_STRING("Missing a colon after a name of object member.");
        case kParseErrorObjectMissCommaOrCurlyBracket:  return RAPIDJSON_ERROR_STRING("Missing a comma or '}' after an object member.");

        case kParseErrorArrayMissCommaOrSquareBracket:  return RAPIDJSON_ERROR_STRING("Missing a comma or ']' after an array element.");

        case kParseErrorStringUnicodeEscapeInvalidHex:  return RAPIDJSON_ERROR_STRING("Incorrect hex digit after \\u escape in string.");
        case kParseErrorStringUnicodeSurrogateInvalid:  return RAPIDJSON_ERROR_STRING("The surrogate pair in string is invalid.");
        case kParseErrorStringEscapeInvalid:            return RAPIDJSON_ERROR_STRING("Invalid escape character in string.");
        case kParseErrorStringMissQuotationMark:        return RAPIDJSON_ERROR_STRING("Missing a closing quotation mark in string.");
        case kParseErrorStringInvalidEncoding:          return RAPIDJSON_ERROR_STRING("Invalid encoding in string.");

        case kParseErrorNumberTooBig:                   return RAPIDJSON_ERROR_STRING("Number too big to be stored in double.");
        case kParseErrorNumberMissFraction:             return RAPIDJSON_ERROR_STRING("Miss fraction part in number.");
        case kParseErrorNumberMissExponent:             return RAPIDJSON_ERROR_STRING("Miss exponent in number.");

        case kParseErrorTermination:                    return RAPIDJSON_ERROR_STRING("Terminate parsing due to Handler error.");
        case kParseErrorUnspecificSyntaxError:          return RAPIDJSON_ERROR_STRING("Unspecific syntax error.");

        default:                                        return RAPIDJSON_ERROR_STRING("Unknown error.");
    }
}

//! Maps error code of validation into error message.
/*!
    \ingroup RAPIDJSON_ERRORS
    \param validateErrorCode Error code obtained from validator.
    \return the error message.
    \note User can make a copy of this function for localization.
        Using switch-case is safer for future modification of error codes.
*/
inline const RAPIDJSON_ERROR_CHARTYPE* GetValidateError_En(ValidateErrorCode validateErrorCode) {
    switch (validateErrorCode) {
        case kValidateErrors:                           return RAPIDJSON_ERROR_STRING("One or more validation errors have occurred");
        case kValidateErrorNone:                        return RAPIDJSON_ERROR_STRING("No error.");

        case kValidateErrorMultipleOf:                  return RAPIDJSON_ERROR_STRING("Number '%actual' is not a multiple of the 'multipleOf' value '%expected'.");
        case kValidateErrorMaximum:                     return RAPIDJSON_ERROR_STRING("Number '%actual' is greater than the 'maximum' value '%expected'.");
        case kValidateErrorExclusiveMaximum:            return RAPIDJSON_ERROR_STRING("Number '%actual' is greater than or equal to the 'exclusiveMaximum' value '%expected'.");
        case kValidateErrorMinimum:                     return RAPIDJSON_ERROR_STRING("Number '%actual' is less than the 'minimum' value '%expected'.");
        case kValidateErrorExclusiveMinimum:            return RAPIDJSON_ERROR_STRING("Number '%actual' is less than or equal to the 'exclusiveMinimum' value '%expected'.");

        case kValidateErrorMaxLength:                   return RAPIDJSON_ERROR_STRING("String '%actual' is longer than the 'maxLength' value '%expected'.");
        case kValidateErrorMinLength:                   return RAPIDJSON_ERROR_STRING("String '%actual' is shorter than the 'minLength' value '%expected'.");
        case kValidateErrorPattern:                     return RAPIDJSON_ERROR_STRING("String '%actual' does not match the 'pattern' regular expression.");

        case kValidateErrorMaxItems:                    return RAPIDJSON_ERROR_STRING("Array of length '%actual' is longer than the 'maxItems' value '%expected'.");
        case kValidateErrorMinItems:                    return RAPIDJSON_ERROR_STRING("Array of length '%actual' is shorter than the 'minItems' value '%expected'.");
        case kValidateErrorUniqueItems:                 return RAPIDJSON_ERROR_STRING("Array has duplicate items at indices '%duplicates' but 'uniqueItems' is true.");
        case kValidateErrorAdditionalItems:             return RAPIDJSON_ERROR_STRING("Array has an additional item at index '%disallowed' that is not allowed by the schema.");

        case kValidateErrorMaxProperties:               return RAPIDJSON_ERROR_STRING("Object has '%actual' members which is more than 'maxProperties' value '%expected'.");
        case kValidateErrorMinProperties:               return RAPIDJSON_ERROR_STRING("Object has '%actual' members which is less than 'minProperties' value '%expected'.");
        case kValidateErrorRequired:                    return RAPIDJSON_ERROR_STRING("Object is missing the following members required by the schema: '%missing'.");
        case kValidateErrorAdditionalProperties:        return RAPIDJSON_ERROR_STRING("Object has an additional member '%disallowed' that is not allowed by the schema.");
        case kValidateErrorPatternProperties:           return RAPIDJSON_ERROR_STRING("Object has 'patternProperties' that are not allowed by the schema.");
        case kValidateErrorDependencies:                return RAPIDJSON_ERROR_STRING("Object has missing property or schema dependencies, refer to following errors.");

        case kValidateErrorEnum:                        return RAPIDJSON_ERROR_STRING("Property has a value that is not one of its allowed enumerated values.");
        case kValidateErrorType:                        return RAPIDJSON_ERROR_STRING("Property has a type '%actual' that is not in the following list: '%expected'.");

        case kValidateErrorOneOf:                       return RAPIDJSON_ERROR_STRING("Property did not match any of the sub-schemas specified by 'oneOf', refer to following errors.");
        case kValidateErrorOneOfMatch:                  return RAPIDJSON_ERROR_STRING("Property matched more than one of the sub-schemas specified by 'oneOf', indices '%matches'.");
        case kValidateErrorAllOf:                       return RAPIDJSON_ERROR_STRING("Property did not match all of the sub-schemas specified by 'allOf', refer to following errors.");
        case kValidateErrorAnyOf:                       return RAPIDJSON_ERROR_STRING("Property did not match any of the sub-schemas specified by 'anyOf', refer to following errors.");
        case kValidateErrorNot:                         return RAPIDJSON_ERROR_STRING("Property matched the sub-schema specified by 'not'.");

        case kValidateErrorReadOnly:                    return RAPIDJSON_ERROR_STRING("Property is read-only but has been provided when validation is for writing.");
        case kValidateErrorWriteOnly:                   return RAPIDJSON_ERROR_STRING("Property is write-only but has been provided when validation is for reading.");

        default:                                        return RAPIDJSON_ERROR_STRING("Unknown error.");
    }
}

//! Maps error code of schema document compilation into error message.
/*!
    \ingroup RAPIDJSON_ERRORS
    \param schemaErrorCode Error code obtained from compiling the schema document.
    \return the error message.
    \note User can make a copy of this function for localization.
        Using switch-case is safer for future modification of error codes.
*/
  inline const RAPIDJSON_ERROR_CHARTYPE* GetSchemaError_En(SchemaErrorCode schemaErrorCode) {
      switch (schemaErrorCode) {
          case kSchemaErrorNone:                        return RAPIDJSON_ERROR_STRING("No error.");

          case kSchemaErrorStartUnknown:                return RAPIDJSON_ERROR_STRING("Pointer '%value' to start of schema does not resolve to a location in the document.");
          case kSchemaErrorRefPlainName:                return RAPIDJSON_ERROR_STRING("$ref fragment '%value' must be a JSON pointer.");
          case kSchemaErrorRefInvalid:                  return RAPIDJSON_ERROR_STRING("$ref must not be an empty string.");
          case kSchemaErrorRefPointerInvalid:           return RAPIDJSON_ERROR_STRING("$ref fragment '%value' is not a valid JSON pointer at offset '%offset'.");
          case kSchemaErrorRefUnknown:                  return RAPIDJSON_ERROR_STRING("$ref '%value' does not resolve to a location in the target document.");
          case kSchemaErrorRefCyclical:                 return RAPIDJSON_ERROR_STRING("$ref '%value' is cyclical.");
          case kSchemaErrorRefNoRemoteProvider:         return RAPIDJSON_ERROR_STRING("$ref is remote but there is no remote provider.");
          case kSchemaErrorRefNoRemoteSchema:           return RAPIDJSON_ERROR_STRING("$ref '%value' is remote but the remote provider did not return a schema.");
          case kSchemaErrorRegexInvalid:                return RAPIDJSON_ERROR_STRING("Invalid regular expression '%value' in 'pattern' or 'patternProperties'.");
          case kSchemaErrorSpecUnknown:                 return RAPIDJSON_ERROR_STRING("JSON schema draft or OpenAPI version is not recognized.");
          case kSchemaErrorSpecUnsupported:             return RAPIDJSON_ERROR_STRING("JSON schema draft or OpenAPI version is not supported.");
          case kSchemaErrorSpecIllegal:                 return RAPIDJSON_ERROR_STRING("Both JSON schema draft and OpenAPI version found in document.");
          case kSchemaErrorReadOnlyAndWriteOnly:        return RAPIDJSON_ERROR_STRING("Property must not be both 'readOnly' and 'writeOnly'.");

          default:                                      return RAPIDJSON_ERROR_STRING("Unknown error.");
    }
  }

//! Maps error code of pointer parse into error message.
/*!
    \ingroup RAPIDJSON_ERRORS
    \param pointerParseErrorCode Error code obtained from pointer parse.
    \return the error message.
    \note User can make a copy of this function for localization.
        Using switch-case is safer for future modification of error codes.
*/
inline const RAPIDJSON_ERROR_CHARTYPE* GetPointerParseError_En(PointerParseErrorCode pointerParseErrorCode) {
    switch (pointerParseErrorCode) {
        case kPointerParseErrorNone:                       return RAPIDJSON_ERROR_STRING("No error.");

        case kPointerParseErrorTokenMustBeginWithSolidus:  return RAPIDJSON_ERROR_STRING("A token must begin with a '/'.");
        case kPointerParseErrorInvalidEscape:              return RAPIDJSON_ERROR_STRING("Invalid escape.");
        case kPointerParseErrorInvalidPercentEncoding:     return RAPIDJSON_ERROR_STRING("Invalid percent encoding in URI fragment.");
        case kPointerParseErrorCharacterMustPercentEncode: return RAPIDJSON_ERROR_STRING("A character must be percent encoded in a URI fragment.");

        default:                                           return RAPIDJSON_ERROR_STRING("Unknown error.");
    }
}

RAPIDJSON_NAMESPACE_END

#ifdef __clang__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_ERROR_EN_H_

// End file:error/en.h


// Begin file: uri.h
// already included
// End file:uri.h

#include <cmath> // abs, floor

#if !defined(RAPIDJSON_SCHEMA_USE_INTERNALREGEX)
#define RAPIDJSON_SCHEMA_USE_INTERNALREGEX 1
#endif

#if !defined(RAPIDJSON_SCHEMA_USE_STDREGEX) || !(__cplusplus >=201103L || (defined(_MSC_VER) && _MSC_VER >= 1800))
#define RAPIDJSON_SCHEMA_USE_STDREGEX 0
#endif

#if RAPIDJSON_SCHEMA_USE_INTERNALREGEX

// Begin file: internal/regex.h
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_INTERNAL_REGEX_H_
#define RAPIDJSON_INTERNAL_REGEX_H_


// Begin file: ../allocators.h
// already included
// End file:../allocators.h


// Begin file: ../stream.h
// already included
// End file:../stream.h


// Begin file: stack.h
// already included
// End file:stack.h


#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
RAPIDJSON_DIAG_OFF(switch-enum)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4512) // assignment operator could not be generated
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(effc++)
#endif

#ifndef RAPIDJSON_REGEX_VERBOSE
#define RAPIDJSON_REGEX_VERBOSE 0
#endif

RAPIDJSON_NAMESPACE_BEGIN
namespace internal {

///////////////////////////////////////////////////////////////////////////////
// DecodedStream

template <typename SourceStream, typename Encoding>
class DecodedStream {
public:
    DecodedStream(SourceStream& ss) : ss_(ss), codepoint_() { Decode(); }
    unsigned Peek() { return codepoint_; }
    unsigned Take() {
        unsigned c = codepoint_;
        if (c) // No further decoding when '\0'
            Decode();
        return c;
    }

private:
    void Decode() {
        if (!Encoding::Decode(ss_, &codepoint_))
            codepoint_ = 0;
    }

    SourceStream& ss_;
    unsigned codepoint_;
};

///////////////////////////////////////////////////////////////////////////////
// GenericRegex

static const SizeType kRegexInvalidState = ~SizeType(0);  //!< Represents an invalid index in GenericRegex::State::out, out1
static const SizeType kRegexInvalidRange = ~SizeType(0);

template <typename Encoding, typename Allocator>
class GenericRegexSearch;

//! Regular expression engine with subset of ECMAscript grammar.
/*!
    Supported regular expression syntax:
    - \c ab     Concatenation
    - \c a|b    Alternation
    - \c a?     Zero or one
    - \c a*     Zero or more
    - \c a+     One or more
    - \c a{3}   Exactly 3 times
    - \c a{3,}  At least 3 times
    - \c a{3,5} 3 to 5 times
    - \c (ab)   Grouping
    - \c ^a     At the beginning
    - \c a$     At the end
    - \c .      Any character
    - \c [abc]  Character classes
    - \c [a-c]  Character class range
    - \c [a-z0-9_] Character class combination
    - \c [^abc] Negated character classes
    - \c [^a-c] Negated character class range
    - \c [\b]   Backspace (U+0008)
    - \c \\| \\\\ ...  Escape characters
    - \c \\f Form feed (U+000C)
    - \c \\n Line feed (U+000A)
    - \c \\r Carriage return (U+000D)
    - \c \\t Tab (U+0009)
    - \c \\v Vertical tab (U+000B)

    \note This is a Thompson NFA engine, implemented with reference to 
        Cox, Russ. "Regular Expression Matching Can Be Simple And Fast (but is slow in Java, Perl, PHP, Python, Ruby,...).", 
        https://swtch.com/~rsc/regexp/regexp1.html 
*/
template <typename Encoding, typename Allocator = CrtAllocator>
class GenericRegex {
public:
    typedef Encoding EncodingType;
    typedef typename Encoding::Ch Ch;
    template <typename, typename> friend class GenericRegexSearch;

    GenericRegex(const Ch* source, Allocator* allocator = 0) : 
        ownAllocator_(allocator ? 0 : RAPIDJSON_NEW(Allocator)()), allocator_(allocator ? allocator : ownAllocator_), 
        states_(allocator_, 256), ranges_(allocator_, 256), root_(kRegexInvalidState), stateCount_(), rangeCount_(), 
        anchorBegin_(), anchorEnd_()
    {
        GenericStringStream<Encoding> ss(source);
        DecodedStream<GenericStringStream<Encoding>, Encoding> ds(ss);
        Parse(ds);
    }

    ~GenericRegex()
    {
        RAPIDJSON_DELETE(ownAllocator_);
    }

    bool IsValid() const {
        return root_ != kRegexInvalidState;
    }

private:
    enum Operator {
        kZeroOrOne,
        kZeroOrMore,
        kOneOrMore,
        kConcatenation,
        kAlternation,
        kLeftParenthesis
    };

    static const unsigned kAnyCharacterClass = 0xFFFFFFFF;   //!< For '.'
    static const unsigned kRangeCharacterClass = 0xFFFFFFFE;
    static const unsigned kRangeNegationFlag = 0x80000000;

    struct Range {
        unsigned start; // 
        unsigned end;
        SizeType next;
    };

    struct State {
        SizeType out;     //!< Equals to kInvalid for matching state
        SizeType out1;    //!< Equals to non-kInvalid for split
        SizeType rangeStart;
        unsigned codepoint;
    };

    struct Frag {
        Frag(SizeType s, SizeType o, SizeType m) : start(s), out(o), minIndex(m) {}
        SizeType start;
        SizeType out; //!< link-list of all output states
        SizeType minIndex;
    };

    State& GetState(SizeType index) {
        RAPIDJSON_ASSERT(index < stateCount_);
        return states_.template Bottom<State>()[index];
    }

    const State& GetState(SizeType index) const {
        RAPIDJSON_ASSERT(index < stateCount_);
        return states_.template Bottom<State>()[index];
    }

    Range& GetRange(SizeType index) {
        RAPIDJSON_ASSERT(index < rangeCount_);
        return ranges_.template Bottom<Range>()[index];
    }

    const Range& GetRange(SizeType index) const {
        RAPIDJSON_ASSERT(index < rangeCount_);
        return ranges_.template Bottom<Range>()[index];
    }

    template <typename InputStream>
    void Parse(DecodedStream<InputStream, Encoding>& ds) {
        Stack<Allocator> operandStack(allocator_, 256);    // Frag
        Stack<Allocator> operatorStack(allocator_, 256);   // Operator
        Stack<Allocator> atomCountStack(allocator_, 256);  // unsigned (Atom per parenthesis)

        *atomCountStack.template Push<unsigned>() = 0;

        unsigned codepoint;
        while (ds.Peek() != 0) {
            switch (codepoint = ds.Take()) {
                case '^':
                    anchorBegin_ = true;
                    break;

                case '$':
                    anchorEnd_ = true;
                    break;

                case '|':
                    while (!operatorStack.Empty() && *operatorStack.template Top<Operator>() < kAlternation)
                        if (!Eval(operandStack, *operatorStack.template Pop<Operator>(1)))
                            return;
                    *operatorStack.template Push<Operator>() = kAlternation;
                    *atomCountStack.template Top<unsigned>() = 0;
                    break;

                case '(':
                    *operatorStack.template Push<Operator>() = kLeftParenthesis;
                    *atomCountStack.template Push<unsigned>() = 0;
                    break;

                case ')':
                    while (!operatorStack.Empty() && *operatorStack.template Top<Operator>() != kLeftParenthesis)
                        if (!Eval(operandStack, *operatorStack.template Pop<Operator>(1)))
                            return;
                    if (operatorStack.Empty())
                        return;
                    operatorStack.template Pop<Operator>(1);
                    atomCountStack.template Pop<unsigned>(1);
                    ImplicitConcatenation(atomCountStack, operatorStack);
                    break;

                case '?':
                    if (!Eval(operandStack, kZeroOrOne))
                        return;
                    break;

                case '*':
                    if (!Eval(operandStack, kZeroOrMore))
                        return;
                    break;

                case '+':
                    if (!Eval(operandStack, kOneOrMore))
                        return;
                    break;

                case '{':
                    {
                        unsigned n, m;
                        if (!ParseUnsigned(ds, &n))
                            return;

                        if (ds.Peek() == ',') {
                            ds.Take();
                            if (ds.Peek() == '}')
                                m = kInfinityQuantifier;
                            else if (!ParseUnsigned(ds, &m) || m < n)
                                return;
                        }
                        else
                            m = n;

                        if (!EvalQuantifier(operandStack, n, m) || ds.Peek() != '}')
                            return;
                        ds.Take();
                    }
                    break;

                case '.':
                    PushOperand(operandStack, kAnyCharacterClass);
                    ImplicitConcatenation(atomCountStack, operatorStack);
                    break;

                case '[':
                    {
                        SizeType range;
                        if (!ParseRange(ds, &range))
                            return;
                        SizeType s = NewState(kRegexInvalidState, kRegexInvalidState, kRangeCharacterClass);
                        GetState(s).rangeStart = range;
                        *operandStack.template Push<Frag>() = Frag(s, s, s);
                    }
                    ImplicitConcatenation(atomCountStack, operatorStack);
                    break;

                case '\\': // Escape character
                    if (!CharacterEscape(ds, &codepoint))
                        return; // Unsupported escape character
                    // fall through to default
                    RAPIDJSON_DELIBERATE_FALLTHROUGH;

                default: // Pattern character
                    PushOperand(operandStack, codepoint);
                    ImplicitConcatenation(atomCountStack, operatorStack);
            }
        }

        while (!operatorStack.Empty())
            if (!Eval(operandStack, *operatorStack.template Pop<Operator>(1)))
                return;

        // Link the operand to matching state.
        if (operandStack.GetSize() == sizeof(Frag)) {
            Frag* e = operandStack.template Pop<Frag>(1);
            Patch(e->out, NewState(kRegexInvalidState, kRegexInvalidState, 0));
            root_ = e->start;

#if RAPIDJSON_REGEX_VERBOSE
            printf("root: %d\n", root_);
            for (SizeType i = 0; i < stateCount_ ; i++) {
                State& s = GetState(i);
                printf("[%2d] out: %2d out1: %2d c: '%c'\n", i, s.out, s.out1, (char)s.codepoint);
            }
            printf("\n");
#endif
        }
    }

    SizeType NewState(SizeType out, SizeType out1, unsigned codepoint) {
        State* s = states_.template Push<State>();
        s->out = out;
        s->out1 = out1;
        s->codepoint = codepoint;
        s->rangeStart = kRegexInvalidRange;
        return stateCount_++;
    }

    void PushOperand(Stack<Allocator>& operandStack, unsigned codepoint) {
        SizeType s = NewState(kRegexInvalidState, kRegexInvalidState, codepoint);
        *operandStack.template Push<Frag>() = Frag(s, s, s);
    }

    void ImplicitConcatenation(Stack<Allocator>& atomCountStack, Stack<Allocator>& operatorStack) {
        if (*atomCountStack.template Top<unsigned>())
            *operatorStack.template Push<Operator>() = kConcatenation;
        (*atomCountStack.template Top<unsigned>())++;
    }

    SizeType Append(SizeType l1, SizeType l2) {
        SizeType old = l1;
        while (GetState(l1).out != kRegexInvalidState)
            l1 = GetState(l1).out;
        GetState(l1).out = l2;
        return old;
    }

    void Patch(SizeType l, SizeType s) {
        for (SizeType next; l != kRegexInvalidState; l = next) {
            next = GetState(l).out;
            GetState(l).out = s;
        }
    }

    bool Eval(Stack<Allocator>& operandStack, Operator op) {
        switch (op) {
            case kConcatenation:
                RAPIDJSON_ASSERT(operandStack.GetSize() >= sizeof(Frag) * 2);
                {
                    Frag e2 = *operandStack.template Pop<Frag>(1);
                    Frag e1 = *operandStack.template Pop<Frag>(1);
                    Patch(e1.out, e2.start);
                    *operandStack.template Push<Frag>() = Frag(e1.start, e2.out, Min(e1.minIndex, e2.minIndex));
                }
                return true;

            case kAlternation:
                if (operandStack.GetSize() >= sizeof(Frag) * 2) {
                    Frag e2 = *operandStack.template Pop<Frag>(1);
                    Frag e1 = *operandStack.template Pop<Frag>(1);
                    SizeType s = NewState(e1.start, e2.start, 0);
                    *operandStack.template Push<Frag>() = Frag(s, Append(e1.out, e2.out), Min(e1.minIndex, e2.minIndex));
                    return true;
                }
                return false;

            case kZeroOrOne:
                if (operandStack.GetSize() >= sizeof(Frag)) {
                    Frag e = *operandStack.template Pop<Frag>(1);
                    SizeType s = NewState(kRegexInvalidState, e.start, 0);
                    *operandStack.template Push<Frag>() = Frag(s, Append(e.out, s), e.minIndex);
                    return true;
                }
                return false;

            case kZeroOrMore:
                if (operandStack.GetSize() >= sizeof(Frag)) {
                    Frag e = *operandStack.template Pop<Frag>(1);
                    SizeType s = NewState(kRegexInvalidState, e.start, 0);
                    Patch(e.out, s);
                    *operandStack.template Push<Frag>() = Frag(s, s, e.minIndex);
                    return true;
                }
                return false;

            case kOneOrMore:
                if (operandStack.GetSize() >= sizeof(Frag)) {
                    Frag e = *operandStack.template Pop<Frag>(1);
                    SizeType s = NewState(kRegexInvalidState, e.start, 0);
                    Patch(e.out, s);
                    *operandStack.template Push<Frag>() = Frag(e.start, s, e.minIndex);
                    return true;
                }
                return false;

            default: 
                // syntax error (e.g. unclosed kLeftParenthesis)
                return false;
        }
    }

    bool EvalQuantifier(Stack<Allocator>& operandStack, unsigned n, unsigned m) {
        RAPIDJSON_ASSERT(n <= m);
        RAPIDJSON_ASSERT(operandStack.GetSize() >= sizeof(Frag));

        if (n == 0) {
            if (m == 0)                             // a{0} not support
                return false;
            else if (m == kInfinityQuantifier)
                Eval(operandStack, kZeroOrMore);    // a{0,} -> a*
            else {
                Eval(operandStack, kZeroOrOne);         // a{0,5} -> a?
                for (unsigned i = 0; i < m - 1; i++)
                    CloneTopOperand(operandStack);      // a{0,5} -> a? a? a? a? a?
                for (unsigned i = 0; i < m - 1; i++)
                    Eval(operandStack, kConcatenation); // a{0,5} -> a?a?a?a?a?
            }
            return true;
        }

        for (unsigned i = 0; i < n - 1; i++)        // a{3} -> a a a
            CloneTopOperand(operandStack);

        if (m == kInfinityQuantifier)
            Eval(operandStack, kOneOrMore);         // a{3,} -> a a a+
        else if (m > n) {
            CloneTopOperand(operandStack);          // a{3,5} -> a a a a
            Eval(operandStack, kZeroOrOne);         // a{3,5} -> a a a a?
            for (unsigned i = n; i < m - 1; i++)
                CloneTopOperand(operandStack);      // a{3,5} -> a a a a? a?
            for (unsigned i = n; i < m; i++)
                Eval(operandStack, kConcatenation); // a{3,5} -> a a aa?a?
        }

        for (unsigned i = 0; i < n - 1; i++)
            Eval(operandStack, kConcatenation);     // a{3} -> aaa, a{3,} -> aaa+, a{3.5} -> aaaa?a?

        return true;
    }

    static SizeType Min(SizeType a, SizeType b) { return a < b ? a : b; }

    void CloneTopOperand(Stack<Allocator>& operandStack) {
        const Frag src = *operandStack.template Top<Frag>(); // Copy constructor to prevent invalidation
        SizeType count = stateCount_ - src.minIndex; // Assumes top operand contains states in [src->minIndex, stateCount_)
        State* s = states_.template Push<State>(count);
        memcpy(s, &GetState(src.minIndex), count * sizeof(State));
        for (SizeType j = 0; j < count; j++) {
            if (s[j].out != kRegexInvalidState)
                s[j].out += count;
            if (s[j].out1 != kRegexInvalidState)
                s[j].out1 += count;
        }
        *operandStack.template Push<Frag>() = Frag(src.start + count, src.out + count, src.minIndex + count);
        stateCount_ += count;
    }

    template <typename InputStream>
    bool ParseUnsigned(DecodedStream<InputStream, Encoding>& ds, unsigned* u) {
        unsigned r = 0;
        if (ds.Peek() < '0' || ds.Peek() > '9')
            return false;
        while (ds.Peek() >= '0' && ds.Peek() <= '9') {
            if (r >= 429496729 && ds.Peek() > '5') // 2^32 - 1 = 4294967295
                return false; // overflow
            r = r * 10 + (ds.Take() - '0');
        }
        *u = r;
        return true;
    }

    template <typename InputStream>
    bool ParseRange(DecodedStream<InputStream, Encoding>& ds, SizeType* range) {
        bool isBegin = true;
        bool negate = false;
        int step = 0;
        SizeType start = kRegexInvalidRange;
        SizeType current = kRegexInvalidRange;
        unsigned codepoint;
        while ((codepoint = ds.Take()) != 0) {
            if (isBegin) {
                isBegin = false;
                if (codepoint == '^') {
                    negate = true;
                    continue;
                }
            }

            switch (codepoint) {
            case ']':
                if (start == kRegexInvalidRange)
                    return false;   // Error: nothing inside []
                if (step == 2) { // Add trailing '-'
                    SizeType r = NewRange('-');
                    RAPIDJSON_ASSERT(current != kRegexInvalidRange);
                    GetRange(current).next = r;
                }
                if (negate)
                    GetRange(start).start |= kRangeNegationFlag;
                *range = start;
                return true;

            case '\\':
                if (ds.Peek() == 'b') {
                    ds.Take();
                    codepoint = 0x0008; // Escape backspace character
                }
                else if (!CharacterEscape(ds, &codepoint))
                    return false;
                // fall through to default
                RAPIDJSON_DELIBERATE_FALLTHROUGH;

            default:
                switch (step) {
                case 1:
                    if (codepoint == '-') {
                        step++;
                        break;
                    }
                    // fall through to step 0 for other characters
                    RAPIDJSON_DELIBERATE_FALLTHROUGH;

                case 0:
                    {
                        SizeType r = NewRange(codepoint);
                        if (current != kRegexInvalidRange)
                            GetRange(current).next = r;
                        if (start == kRegexInvalidRange)
                            start = r;
                        current = r;
                    }
                    step = 1;
                    break;

                default:
                    RAPIDJSON_ASSERT(step == 2);
                    GetRange(current).end = codepoint;
                    step = 0;
                }
            }
        }
        return false;
    }
    
    SizeType NewRange(unsigned codepoint) {
        Range* r = ranges_.template Push<Range>();
        r->start = r->end = codepoint;
        r->next = kRegexInvalidRange;
        return rangeCount_++;
    }

    template <typename InputStream>
    bool CharacterEscape(DecodedStream<InputStream, Encoding>& ds, unsigned* escapedCodepoint) {
        unsigned codepoint;
        switch (codepoint = ds.Take()) {
            case '^':
            case '$':
            case '|':
            case '(':
            case ')':
            case '?':
            case '*':
            case '+':
            case '.':
            case '[':
            case ']':
            case '{':
            case '}':
            case '\\':
                *escapedCodepoint = codepoint; return true;
            case 'f': *escapedCodepoint = 0x000C; return true;
            case 'n': *escapedCodepoint = 0x000A; return true;
            case 'r': *escapedCodepoint = 0x000D; return true;
            case 't': *escapedCodepoint = 0x0009; return true;
            case 'v': *escapedCodepoint = 0x000B; return true;
            default:
                return false; // Unsupported escape character
        }
    }

    Allocator* ownAllocator_;
    Allocator* allocator_;
    Stack<Allocator> states_;
    Stack<Allocator> ranges_;
    SizeType root_;
    SizeType stateCount_;
    SizeType rangeCount_;

    static const unsigned kInfinityQuantifier = ~0u;

    // For SearchWithAnchoring()
    bool anchorBegin_;
    bool anchorEnd_;
};

template <typename RegexType, typename Allocator = CrtAllocator>
class GenericRegexSearch {
public:
    typedef typename RegexType::EncodingType Encoding;
    typedef typename Encoding::Ch Ch;

    GenericRegexSearch(const RegexType& regex, Allocator* allocator = 0) : 
        regex_(regex), allocator_(allocator), ownAllocator_(0),
        state0_(allocator, 0), state1_(allocator, 0), stateSet_()
    {
        RAPIDJSON_ASSERT(regex_.IsValid());
        if (!allocator_)
            ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();
        stateSet_ = static_cast<uint32_t*>(allocator_->Malloc(GetStateSetSize()));
        state0_.template Reserve<SizeType>(regex_.stateCount_);
        state1_.template Reserve<SizeType>(regex_.stateCount_);
    }

    ~GenericRegexSearch() {
        Allocator::Free(stateSet_);
        RAPIDJSON_DELETE(ownAllocator_);
    }

    template <typename InputStream>
    bool Match(InputStream& is) {
        return SearchWithAnchoring(is, true, true);
    }

    bool Match(const Ch* s) {
        GenericStringStream<Encoding> is(s);
        return Match(is);
    }

    template <typename InputStream>
    bool Search(InputStream& is) {
        return SearchWithAnchoring(is, regex_.anchorBegin_, regex_.anchorEnd_);
    }

    bool Search(const Ch* s) {
        GenericStringStream<Encoding> is(s);
        return Search(is);
    }

private:
    typedef typename RegexType::State State;
    typedef typename RegexType::Range Range;

    template <typename InputStream>
    bool SearchWithAnchoring(InputStream& is, bool anchorBegin, bool anchorEnd) {
        DecodedStream<InputStream, Encoding> ds(is);

        state0_.Clear();
        Stack<Allocator> *current = &state0_, *next = &state1_;
        const size_t stateSetSize = GetStateSetSize();
        std::memset(stateSet_, 0, stateSetSize);

        bool matched = AddState(*current, regex_.root_);
        unsigned codepoint;
        while (!current->Empty() && (codepoint = ds.Take()) != 0) {
            std::memset(stateSet_, 0, stateSetSize);
            next->Clear();
            matched = false;
            for (const SizeType* s = current->template Bottom<SizeType>(); s != current->template End<SizeType>(); ++s) {
                const State& sr = regex_.GetState(*s);
                if (sr.codepoint == codepoint ||
                    sr.codepoint == RegexType::kAnyCharacterClass || 
                    (sr.codepoint == RegexType::kRangeCharacterClass && MatchRange(sr.rangeStart, codepoint)))
                {
                    matched = AddState(*next, sr.out) || matched;
                    if (!anchorEnd && matched)
                        return true;
                }
                if (!anchorBegin)
                    AddState(*next, regex_.root_);
            }
            internal::Swap(current, next);
        }

        return matched;
    }

    size_t GetStateSetSize() const {
        return (regex_.stateCount_ + 31) / 32 * 4;
    }

    // Return whether the added states is a match state
    bool AddState(Stack<Allocator>& l, SizeType index) {
        RAPIDJSON_ASSERT(index != kRegexInvalidState);

        const State& s = regex_.GetState(index);
        if (s.out1 != kRegexInvalidState) { // Split
            bool matched = AddState(l, s.out);
            return AddState(l, s.out1) || matched;
        }
        else if (!(stateSet_[index >> 5] & (1u << (index & 31)))) {
            stateSet_[index >> 5] |= (1u << (index & 31));
            *l.template PushUnsafe<SizeType>() = index;
        }
        return s.out == kRegexInvalidState; // by using PushUnsafe() above, we can ensure s is not validated due to reallocation.
    }

    bool MatchRange(SizeType rangeIndex, unsigned codepoint) const {
        bool yes = (regex_.GetRange(rangeIndex).start & RegexType::kRangeNegationFlag) == 0;
        while (rangeIndex != kRegexInvalidRange) {
            const Range& r = regex_.GetRange(rangeIndex);
            if (codepoint >= (r.start & ~RegexType::kRangeNegationFlag) && codepoint <= r.end)
                return yes;
            rangeIndex = r.next;
        }
        return !yes;
    }

    const RegexType& regex_;
    Allocator* allocator_;
    Allocator* ownAllocator_;
    Stack<Allocator> state0_;
    Stack<Allocator> state1_;
    uint32_t* stateSet_;
};

typedef GenericRegex<UTF8<> > Regex;
typedef GenericRegexSearch<Regex> RegexSearch;

} // namespace internal
RAPIDJSON_NAMESPACE_END

#ifdef __GNUC__
RAPIDJSON_DIAG_POP
#endif

#if defined(__clang__) || defined(_MSC_VER)
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_INTERNAL_REGEX_H_

// End file:internal/regex.h

#elif RAPIDJSON_SCHEMA_USE_STDREGEX
#include <regex>
#endif

#if RAPIDJSON_SCHEMA_USE_INTERNALREGEX || RAPIDJSON_SCHEMA_USE_STDREGEX
#define RAPIDJSON_SCHEMA_HAS_REGEX 1
#else
#define RAPIDJSON_SCHEMA_HAS_REGEX 0
#endif

#ifndef RAPIDJSON_SCHEMA_VERBOSE
#define RAPIDJSON_SCHEMA_VERBOSE 0
#endif

RAPIDJSON_DIAG_PUSH

#if defined(__GNUC__)
RAPIDJSON_DIAG_OFF(effc++)
#endif

#ifdef __clang__
RAPIDJSON_DIAG_OFF(weak-vtables)
RAPIDJSON_DIAG_OFF(exit-time-destructors)
RAPIDJSON_DIAG_OFF(c++98-compat-pedantic)
RAPIDJSON_DIAG_OFF(variadic-macros)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_OFF(4512) // assignment operator could not be generated
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// Verbose Utilities

#if RAPIDJSON_SCHEMA_VERBOSE

namespace internal {

inline void PrintInvalidKeywordData(const char* keyword) {
    printf("    Fail keyword: '%s'\n", keyword);
}

inline void PrintInvalidKeywordData(const wchar_t* keyword) {
    wprintf(L"    Fail keyword: '%ls'\n", keyword);
}

inline void PrintInvalidDocumentData(const char* document) {
    printf("    Fail document: '%s'\n", document);
}

inline void PrintInvalidDocumentData(const wchar_t* document) {
    wprintf(L"    Fail document: '%ls'\n", document);
}

inline void PrintValidatorPointersData(const char* s, const char* d, unsigned depth) {
    printf("    Sch: %*s'%s'\n    Doc: %*s'%s'\n", depth * 4, " ", s, depth * 4, " ", d);
}

inline void PrintValidatorPointersData(const wchar_t* s, const wchar_t* d, unsigned depth) {
    wprintf(L"    Sch: %*ls'%ls'\n    Doc: %*ls'%ls'\n", depth * 4, L" ", s, depth * 4, L" ", d);
}

inline void PrintSchemaIdsData(const char* base, const char* local, const char* resolved) {
    printf("    Resolving id: Base: '%s', Local: '%s', Resolved: '%s'\n", base, local, resolved);
}

inline void PrintSchemaIdsData(const wchar_t* base, const wchar_t* local, const wchar_t* resolved) {
    wprintf(L"    Resolving id: Base: '%ls', Local: '%ls', Resolved: '%ls'\n", base, local, resolved);
}

inline void PrintMethodData(const char* method) {
    printf("%s\n", method);
}

inline void PrintMethodData(const char* method, bool b) {
    printf("%s, Data: '%s'\n", method, b ? "true" : "false");
}

inline void PrintMethodData(const char* method, int64_t i) {
    printf("%s, Data: '%" PRId64 "'\n", method, i);
}

inline void PrintMethodData(const char* method, uint64_t u) {
    printf("%s, Data: '%" PRIu64 "'\n", method, u);
}

inline void PrintMethodData(const char* method, double d) {
    printf("%s, Data: '%lf'\n", method, d);
}

inline void PrintMethodData(const char* method, const char* s) {
    printf("%s, Data: '%s'\n", method, s);
}

inline void PrintMethodData(const char* method, const wchar_t* s) {
    wprintf(L"%hs, Data: '%ls'\n", method, s);
}

inline void PrintMethodData(const char* method, const char* s1, const char* s2) {
    printf("%s, Data: '%s', '%s'\n", method, s1, s2);
}

inline void PrintMethodData(const char* method, const wchar_t* s1, const wchar_t* s2) {
    wprintf(L"%hs, Data: '%ls', '%ls'\n", method, s1, s2);
}

} // namespace internal

#endif // RAPIDJSON_SCHEMA_VERBOSE

#ifndef RAPIDJSON_SCHEMA_PRINT
#if RAPIDJSON_SCHEMA_VERBOSE
#define RAPIDJSON_SCHEMA_PRINT(name, ...) internal::Print##name##Data(__VA_ARGS__)
#else
#define RAPIDJSON_SCHEMA_PRINT(name, ...)
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_INVALID_KEYWORD_RETURN

#define RAPIDJSON_INVALID_KEYWORD_RETURN(code)\
RAPIDJSON_MULTILINEMACRO_BEGIN\
    context.invalidCode = code;\
    context.invalidKeyword = SchemaType::GetValidateErrorKeyword(code).GetString();\
    RAPIDJSON_SCHEMA_PRINT(InvalidKeyword, context.invalidKeyword);\
    return false;\
RAPIDJSON_MULTILINEMACRO_END

///////////////////////////////////////////////////////////////////////////////
// ValidateFlag

/*! \def RAPIDJSON_VALIDATE_DEFAULT_FLAGS
    \ingroup RAPIDJSON_CONFIG
    \brief User-defined kValidateDefaultFlags definition.

    User can define this as any \c ValidateFlag combinations.
*/
#ifndef RAPIDJSON_VALIDATE_DEFAULT_FLAGS
#define RAPIDJSON_VALIDATE_DEFAULT_FLAGS kValidateNoFlags
#endif

//! Combination of validate flags
enum ValidateFlag {
    kValidateNoFlags = 0,                                       //!< No flags are set.
    kValidateContinueOnErrorFlag = 1,                           //!< Don't stop after first validation error.
    kValidateReadFlag = 2,                                      //!< Validation is for a read semantic.
    kValidateWriteFlag = 4,                                     //!< Validation is for a write semantic.
    kValidateDefaultFlags = RAPIDJSON_VALIDATE_DEFAULT_FLAGS    //!< Default validate flags. Can be customized by defining RAPIDJSON_VALIDATE_DEFAULT_FLAGS
};

///////////////////////////////////////////////////////////////////////////////
// Specification
enum SchemaDraft {
    kDraftUnknown = -1,
    kDraftNone = 0,
    kDraft03 = 3,
    kDraftMin = 4,                       //!< Current minimum supported draft
    kDraft04 = 4,
    kDraft05 = 5,
    kDraftMax = 5,                       //!< Current maximum supported draft
    kDraft06 = 6,
    kDraft07 = 7,
    kDraft2019_09 = 8,
    kDraft2020_12 = 9
};

enum OpenApiVersion {
    kVersionUnknown = -1,
    kVersionNone = 0,
    kVersionMin = 2,                      //!< Current minimum supported version
    kVersion20 = 2,
    kVersion30 = 3,
    kVersionMax = 3,                      //!< Current maximum supported version
    kVersion31 = 4,
};

struct Specification {
    Specification(SchemaDraft d) : draft(d), oapi(kVersionNone) {}
    Specification(OpenApiVersion o) : oapi(o) {
        if (oapi == kVersion20) draft = kDraft04;
        else if (oapi == kVersion30) draft = kDraft05;
        else if (oapi == kVersion31) draft = kDraft2020_12;
        else draft = kDraft04;
    }
    ~Specification() {}
    bool IsSupported() const {
        return ((draft >= kDraftMin && draft <= kDraftMax) && ((oapi == kVersionNone) || (oapi >= kVersionMin && oapi <= kVersionMax)));
    }
    SchemaDraft draft;
    OpenApiVersion oapi;
};

///////////////////////////////////////////////////////////////////////////////
// Forward declarations

template <typename ValueType, typename Allocator>
class GenericSchemaDocument;

namespace internal {

template <typename SchemaDocumentType>
class Schema;

///////////////////////////////////////////////////////////////////////////////
// ISchemaValidator

class ISchemaValidator {
public:
    virtual ~ISchemaValidator() {}
    virtual bool IsValid() const = 0;
    virtual void SetValidateFlags(unsigned flags) = 0;
    virtual unsigned GetValidateFlags() const = 0;
};

///////////////////////////////////////////////////////////////////////////////
// ISchemaStateFactory

template <typename SchemaType>
class ISchemaStateFactory {
public:
    virtual ~ISchemaStateFactory() {}
    virtual ISchemaValidator* CreateSchemaValidator(const SchemaType&, const bool inheritContinueOnErrors) = 0;
    virtual void DestroySchemaValidator(ISchemaValidator* validator) = 0;
    virtual void* CreateHasher() = 0;
    virtual uint64_t GetHashCode(void* hasher) = 0;
    virtual void DestroryHasher(void* hasher) = 0;
    virtual void* MallocState(size_t size) = 0;
    virtual void FreeState(void* p) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// IValidationErrorHandler

template <typename SchemaType>
class IValidationErrorHandler {
public:
    typedef typename SchemaType::Ch Ch;
    typedef typename SchemaType::SValue SValue;

    virtual ~IValidationErrorHandler() {}

    virtual void NotMultipleOf(int64_t actual, const SValue& expected) = 0;
    virtual void NotMultipleOf(uint64_t actual, const SValue& expected) = 0;
    virtual void NotMultipleOf(double actual, const SValue& expected) = 0;
    virtual void AboveMaximum(int64_t actual, const SValue& expected, bool exclusive) = 0;
    virtual void AboveMaximum(uint64_t actual, const SValue& expected, bool exclusive) = 0;
    virtual void AboveMaximum(double actual, const SValue& expected, bool exclusive) = 0;
    virtual void BelowMinimum(int64_t actual, const SValue& expected, bool exclusive) = 0;
    virtual void BelowMinimum(uint64_t actual, const SValue& expected, bool exclusive) = 0;
    virtual void BelowMinimum(double actual, const SValue& expected, bool exclusive) = 0;

    virtual void TooLong(const Ch* str, SizeType length, SizeType expected) = 0;
    virtual void TooShort(const Ch* str, SizeType length, SizeType expected) = 0;
    virtual void DoesNotMatch(const Ch* str, SizeType length) = 0;

    virtual void DisallowedItem(SizeType index) = 0;
    virtual void TooFewItems(SizeType actualCount, SizeType expectedCount) = 0;
    virtual void TooManyItems(SizeType actualCount, SizeType expectedCount) = 0;
    virtual void DuplicateItems(SizeType index1, SizeType index2) = 0;

    virtual void TooManyProperties(SizeType actualCount, SizeType expectedCount) = 0;
    virtual void TooFewProperties(SizeType actualCount, SizeType expectedCount) = 0;
    virtual void StartMissingProperties() = 0;
    virtual void AddMissingProperty(const SValue& name) = 0;
    virtual bool EndMissingProperties() = 0;
    virtual void PropertyViolations(ISchemaValidator** subvalidators, SizeType count) = 0;
    virtual void DisallowedProperty(const Ch* name, SizeType length) = 0;

    virtual void StartDependencyErrors() = 0;
    virtual void StartMissingDependentProperties() = 0;
    virtual void AddMissingDependentProperty(const SValue& targetName) = 0;
    virtual void EndMissingDependentProperties(const SValue& sourceName) = 0;
    virtual void AddDependencySchemaError(const SValue& souceName, ISchemaValidator* subvalidator) = 0;
    virtual bool EndDependencyErrors() = 0;

    virtual void DisallowedValue(const ValidateErrorCode code) = 0;
    virtual void StartDisallowedType() = 0;
    virtual void AddExpectedType(const typename SchemaType::ValueType& expectedType) = 0;
    virtual void EndDisallowedType(const typename SchemaType::ValueType& actualType) = 0;
    virtual void NotAllOf(ISchemaValidator** subvalidators, SizeType count) = 0;
    virtual void NoneOf(ISchemaValidator** subvalidators, SizeType count) = 0;
    virtual void NotOneOf(ISchemaValidator** subvalidators, SizeType count) = 0;
    virtual void MultipleOneOf(SizeType index1, SizeType index2) = 0;
    virtual void Disallowed() = 0;
    virtual void DisallowedWhenWriting() = 0;
    virtual void DisallowedWhenReading() = 0;
};


///////////////////////////////////////////////////////////////////////////////
// Hasher

// For comparison of compound value
template<typename Encoding, typename Allocator>
class Hasher {
public:
    typedef typename Encoding::Ch Ch;

    Hasher(Allocator* allocator = 0, size_t stackCapacity = kDefaultSize) : stack_(allocator, stackCapacity) {}

    bool Null() { return WriteType(kNullType); }
    bool Bool(bool b) { return WriteType(b ? kTrueType : kFalseType); }
    bool Int(int i) { Number n; n.u.i = i; n.d = static_cast<double>(i); return WriteNumber(n); }
    bool Uint(unsigned u) { Number n; n.u.u = u; n.d = static_cast<double>(u); return WriteNumber(n); }
    bool Int64(int64_t i) { Number n; n.u.i = i; n.d = static_cast<double>(i); return WriteNumber(n); }
    bool Uint64(uint64_t u) { Number n; n.u.u = u; n.d = static_cast<double>(u); return WriteNumber(n); }
    bool Double(double d) {
        Number n;
        if (d < 0) n.u.i = static_cast<int64_t>(d);
        else       n.u.u = static_cast<uint64_t>(d);
        n.d = d;
        return WriteNumber(n);
    }

    bool RawNumber(const Ch* str, SizeType len, bool) {
        WriteBuffer(kNumberType, str, len * sizeof(Ch));
        return true;
    }

    bool String(const Ch* str, SizeType len, bool) {
        WriteBuffer(kStringType, str, len * sizeof(Ch));
        return true;
    }

    bool StartObject() { return true; }
    bool Key(const Ch* str, SizeType len, bool copy) { return String(str, len, copy); }
    bool EndObject(SizeType memberCount) { 
        uint64_t h = Hash(0, kObjectType);
        uint64_t* kv = stack_.template Pop<uint64_t>(memberCount * 2);
        for (SizeType i = 0; i < memberCount; i++)
            // Issue #2205
            // Hasing the key to avoid key=value cases with bug-prone zero-value hash
            h ^= Hash(Hash(0, kv[i * 2]), kv[i * 2 + 1]);  // Use xor to achieve member order insensitive
        *stack_.template Push<uint64_t>() = h;
        return true;
    }
    
    bool StartArray() { return true; }
    bool EndArray(SizeType elementCount) { 
        uint64_t h = Hash(0, kArrayType);
        uint64_t* e = stack_.template Pop<uint64_t>(elementCount);
        for (SizeType i = 0; i < elementCount; i++)
            h = Hash(h, e[i]); // Use hash to achieve element order sensitive
        *stack_.template Push<uint64_t>() = h;
        return true;
    }

    bool IsValid() const { return stack_.GetSize() == sizeof(uint64_t); }

    uint64_t GetHashCode() const {
        RAPIDJSON_ASSERT(IsValid());
        return *stack_.template Top<uint64_t>();
    }

private:
    static const size_t kDefaultSize = 256;
    struct Number {
        union U {
            uint64_t u;
            int64_t i;
        }u;
        double d;
    };

    bool WriteType(Type type) { return WriteBuffer(type, 0, 0); }
    
    bool WriteNumber(const Number& n) { return WriteBuffer(kNumberType, &n, sizeof(n)); }
    
    bool WriteBuffer(Type type, const void* data, size_t len) {
        // FNV-1a from http://isthe.com/chongo/tech/comp/fnv/
        uint64_t h = Hash(RAPIDJSON_UINT64_C2(0xcbf29ce4, 0x84222325), type);
        const unsigned char* d = static_cast<const unsigned char*>(data);
        for (size_t i = 0; i < len; i++)
            h = Hash(h, d[i]);
        *stack_.template Push<uint64_t>() = h;
        return true;
    }

    static uint64_t Hash(uint64_t h, uint64_t d) {
        static const uint64_t kPrime = RAPIDJSON_UINT64_C2(0x00000100, 0x000001b3);
        h ^= d;
        h *= kPrime;
        return h;
    }

    Stack<Allocator> stack_;
};

///////////////////////////////////////////////////////////////////////////////
// SchemaValidationContext

template <typename SchemaDocumentType>
struct SchemaValidationContext {
    typedef Schema<SchemaDocumentType> SchemaType;
    typedef ISchemaStateFactory<SchemaType> SchemaValidatorFactoryType;
    typedef IValidationErrorHandler<SchemaType> ErrorHandlerType;
    typedef typename SchemaType::ValueType ValueType;
    typedef typename ValueType::Ch Ch;

    enum PatternValidatorType {
        kPatternValidatorOnly,
        kPatternValidatorWithProperty,
        kPatternValidatorWithAdditionalProperty
    };

    SchemaValidationContext(SchemaValidatorFactoryType& f, ErrorHandlerType& eh, const SchemaType* s, unsigned fl = 0) :
        factory(f),
        error_handler(eh),
        schema(s),
        flags(fl),
        valueSchema(),
        invalidKeyword(),
        invalidCode(),
        hasher(),
        arrayElementHashCodes(),
        validators(),
        validatorCount(),
        patternPropertiesValidators(),
        patternPropertiesValidatorCount(),
        patternPropertiesSchemas(),
        patternPropertiesSchemaCount(),
        valuePatternValidatorType(kPatternValidatorOnly),
        propertyExist(),
        inArray(false),
        valueUniqueness(false),
        arrayUniqueness(false)
    {
    }

    ~SchemaValidationContext() {
        if (hasher)
            factory.DestroryHasher(hasher);
        if (validators) {
            for (SizeType i = 0; i < validatorCount; i++) {
                if (validators[i]) {
                    factory.DestroySchemaValidator(validators[i]);
                }
            }
            factory.FreeState(validators);
        }
        if (patternPropertiesValidators) {
            for (SizeType i = 0; i < patternPropertiesValidatorCount; i++) {
                if (patternPropertiesValidators[i]) {
                    factory.DestroySchemaValidator(patternPropertiesValidators[i]);
                }
            }
            factory.FreeState(patternPropertiesValidators);
        }
        if (patternPropertiesSchemas)
            factory.FreeState(patternPropertiesSchemas);
        if (propertyExist)
            factory.FreeState(propertyExist);
    }

    SchemaValidatorFactoryType& factory;
    ErrorHandlerType& error_handler;
    const SchemaType* schema;
    unsigned flags;
    const SchemaType* valueSchema;
    const Ch* invalidKeyword;
    ValidateErrorCode invalidCode;
    void* hasher; // Only validator access
    void* arrayElementHashCodes; // Only validator access this
    ISchemaValidator** validators;
    SizeType validatorCount;
    ISchemaValidator** patternPropertiesValidators;
    SizeType patternPropertiesValidatorCount;
    const SchemaType** patternPropertiesSchemas;
    SizeType patternPropertiesSchemaCount;
    PatternValidatorType valuePatternValidatorType;
    PatternValidatorType objectPatternValidatorType;
    SizeType arrayElementIndex;
    bool* propertyExist;
    bool inArray;
    bool valueUniqueness;
    bool arrayUniqueness;
};

///////////////////////////////////////////////////////////////////////////////
// Schema

template <typename SchemaDocumentType>
class Schema {
public:
    typedef typename SchemaDocumentType::ValueType ValueType;
    typedef typename SchemaDocumentType::AllocatorType AllocatorType;
    typedef typename SchemaDocumentType::PointerType PointerType;
    typedef typename ValueType::EncodingType EncodingType;
    typedef typename EncodingType::Ch Ch;
    typedef SchemaValidationContext<SchemaDocumentType> Context;
    typedef Schema<SchemaDocumentType> SchemaType;
    typedef GenericValue<EncodingType, AllocatorType> SValue;
    typedef IValidationErrorHandler<Schema> ErrorHandler;
    typedef GenericUri<ValueType, AllocatorType> UriType;
    friend class GenericSchemaDocument<ValueType, AllocatorType>;

    Schema(SchemaDocumentType* schemaDocument, const PointerType& p, const ValueType& value, const ValueType& document, AllocatorType* allocator, const UriType& id = UriType()) :
        allocator_(allocator),
        uri_(schemaDocument->GetURI(), *allocator),
        id_(id, allocator),
        spec_(schemaDocument->GetSpecification()),
        pointer_(p, allocator),
        typeless_(schemaDocument->GetTypeless()),
        enum_(),
        enumCount_(),
        not_(),
        type_((1 << kTotalSchemaType) - 1), // typeless
        validatorCount_(),
        notValidatorIndex_(),
        properties_(),
        additionalPropertiesSchema_(),
        patternProperties_(),
        patternPropertyCount_(),
        propertyCount_(),
        minProperties_(),
        maxProperties_(SizeType(~0)),
        additionalProperties_(true),
        hasDependencies_(),
        hasRequired_(),
        hasSchemaDependencies_(),
        additionalItemsSchema_(),
        itemsList_(),
        itemsTuple_(),
        itemsTupleCount_(),
        minItems_(),
        maxItems_(SizeType(~0)),
        additionalItems_(true),
        uniqueItems_(false),
        pattern_(),
        minLength_(0),
        maxLength_(~SizeType(0)),
        exclusiveMinimum_(false),
        exclusiveMaximum_(false),
        defaultValueLength_(0),
        readOnly_(false),
        writeOnly_(false),
        nullable_(false)
    {
        GenericStringBuffer<EncodingType> sb;
        p.StringifyUriFragment(sb);
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Schema", sb.GetString(), id.GetString());

        typedef typename ValueType::ConstValueIterator ConstValueIterator;
        typedef typename ValueType::ConstMemberIterator ConstMemberIterator;

        // PR #1393
        // Early add this Schema and its $ref(s) in schemaDocument's map to avoid infinite
        // recursion (with recursive schemas), since schemaDocument->getSchema() is always
        // checked before creating a new one. Don't cache typeless_, though.
        if (this != typeless_) {
          typedef typename SchemaDocumentType::SchemaEntry SchemaEntry;
          SchemaEntry *entry = schemaDocument->schemaMap_.template Push<SchemaEntry>();
          new (entry) SchemaEntry(pointer_, this, true, allocator_);
          schemaDocument->AddSchemaRefs(this);
        }

        if (!value.IsObject())
            return;

        // If we have an id property, resolve it with the in-scope id
        // Not supported for open api 2.0 or 3.0
        if (spec_.oapi != kVersion20 && spec_.oapi != kVersion30)
        if (const ValueType* v = GetMember(value, GetIdString())) {
            if (v->IsString()) {
                UriType local(*v, allocator);
                id_ = local.Resolve(id_, allocator);
                    RAPIDJSON_SCHEMA_PRINT(SchemaIds, id.GetString(), v->GetString(), id_.GetString());
            }
        }

        if (const ValueType* v = GetMember(value, GetTypeString())) {
            type_ = 0;
            if (v->IsString())
                AddType(*v);
            else if (v->IsArray())
                for (ConstValueIterator itr = v->Begin(); itr != v->End(); ++itr)
                    AddType(*itr);
        }

        if (const ValueType* v = GetMember(value, GetEnumString())) {
            if (v->IsArray() && v->Size() > 0) {
                enum_ = static_cast<uint64_t*>(allocator_->Malloc(sizeof(uint64_t) * v->Size()));
                for (ConstValueIterator itr = v->Begin(); itr != v->End(); ++itr) {
                    typedef Hasher<EncodingType, MemoryPoolAllocator<AllocatorType> > EnumHasherType;
                    char buffer[256u + 24];
                    MemoryPoolAllocator<AllocatorType> hasherAllocator(buffer, sizeof(buffer));
                    EnumHasherType h(&hasherAllocator, 256);
                    itr->Accept(h);
                    enum_[enumCount_++] = h.GetHashCode();
                }
            }
        }

        if (schemaDocument)
            AssignIfExist(allOf_, *schemaDocument, p, value, GetAllOfString(), document);

        // AnyOf, OneOf, Not not supported for open api 2.0
        if (schemaDocument && spec_.oapi != kVersion20) {
            AssignIfExist(anyOf_, *schemaDocument, p, value, GetAnyOfString(), document);
            AssignIfExist(oneOf_, *schemaDocument, p, value, GetOneOfString(), document);

            if (const ValueType* v = GetMember(value, GetNotString())) {
                schemaDocument->CreateSchema(&not_, p.Append(GetNotString(), allocator_), *v, document, id_);
                notValidatorIndex_ = validatorCount_;
                validatorCount_++;
            }
        }

        // Object

        const ValueType* properties = GetMember(value, GetPropertiesString());
        const ValueType* required = GetMember(value, GetRequiredString());
        const ValueType* dependencies = GetMember(value, GetDependenciesString());
        {
            // Gather properties from properties/required/dependencies
            SValue allProperties(kArrayType);

            if (properties && properties->IsObject())
                for (ConstMemberIterator itr = properties->MemberBegin(); itr != properties->MemberEnd(); ++itr)
                    AddUniqueElement(allProperties, itr->name);

            if (required && required->IsArray())
                for (ConstValueIterator itr = required->Begin(); itr != required->End(); ++itr)
                    if (itr->IsString())
                        AddUniqueElement(allProperties, *itr);

            // Dependencies not supported for open api 2.0 and 3.0
            if (spec_.oapi != kVersion20 && spec_.oapi != kVersion30)
            if (dependencies && dependencies->IsObject())
                for (ConstMemberIterator itr = dependencies->MemberBegin(); itr != dependencies->MemberEnd(); ++itr) {
                    AddUniqueElement(allProperties, itr->name);
                    if (itr->value.IsArray())
                        for (ConstValueIterator i = itr->value.Begin(); i != itr->value.End(); ++i)
                            if (i->IsString())
                                AddUniqueElement(allProperties, *i);
                }

            if (allProperties.Size() > 0) {
                propertyCount_ = allProperties.Size();
                properties_ = static_cast<Property*>(allocator_->Malloc(sizeof(Property) * propertyCount_));
                for (SizeType i = 0; i < propertyCount_; i++) {
                    new (&properties_[i]) Property();
                    properties_[i].name = allProperties[i];
                    properties_[i].schema = typeless_;
                }
            }
        }

        if (properties && properties->IsObject()) {
            PointerType q = p.Append(GetPropertiesString(), allocator_);
            for (ConstMemberIterator itr = properties->MemberBegin(); itr != properties->MemberEnd(); ++itr) {
                SizeType index;
                if (FindPropertyIndex(itr->name, &index))
                    schemaDocument->CreateSchema(&properties_[index].schema, q.Append(itr->name, allocator_), itr->value, document, id_);
            }
        }

        // PatternProperties not supported for open api 2.0 and 3.0
        if (spec_.oapi != kVersion20 && spec_.oapi != kVersion30)
        if (const ValueType* v = GetMember(value, GetPatternPropertiesString())) {
            PointerType q = p.Append(GetPatternPropertiesString(), allocator_);
            patternProperties_ = static_cast<PatternProperty*>(allocator_->Malloc(sizeof(PatternProperty) * v->MemberCount()));
            patternPropertyCount_ = 0;

            for (ConstMemberIterator itr = v->MemberBegin(); itr != v->MemberEnd(); ++itr) {
                new (&patternProperties_[patternPropertyCount_]) PatternProperty();
                PointerType r = q.Append(itr->name, allocator_);
                patternProperties_[patternPropertyCount_].pattern = CreatePattern(itr->name, schemaDocument, r);
                schemaDocument->CreateSchema(&patternProperties_[patternPropertyCount_].schema, r, itr->value, document, id_);
                patternPropertyCount_++;
            }
        }

        if (required && required->IsArray())
            for (ConstValueIterator itr = required->Begin(); itr != required->End(); ++itr)
                if (itr->IsString()) {
                    SizeType index;
                    if (FindPropertyIndex(*itr, &index)) {
                        properties_[index].required = true;
                        hasRequired_ = true;
                    }
                }

        // Dependencies not supported for open api 2.0 and 3.0
        if (spec_.oapi != kVersion20 && spec_.oapi != kVersion30)
        if (dependencies && dependencies->IsObject()) {
            PointerType q = p.Append(GetDependenciesString(), allocator_);
            hasDependencies_ = true;
            for (ConstMemberIterator itr = dependencies->MemberBegin(); itr != dependencies->MemberEnd(); ++itr) {
                SizeType sourceIndex;
                if (FindPropertyIndex(itr->name, &sourceIndex)) {
                    if (itr->value.IsArray()) {
                        properties_[sourceIndex].dependencies = static_cast<bool*>(allocator_->Malloc(sizeof(bool) * propertyCount_));
                        std::memset(properties_[sourceIndex].dependencies, 0, sizeof(bool)* propertyCount_);
                        for (ConstValueIterator targetItr = itr->value.Begin(); targetItr != itr->value.End(); ++targetItr) {
                            SizeType targetIndex;
                            if (FindPropertyIndex(*targetItr, &targetIndex))
                                properties_[sourceIndex].dependencies[targetIndex] = true;
                        }
                    }
                    else if (itr->value.IsObject()) {
                        hasSchemaDependencies_ = true;
                        schemaDocument->CreateSchema(&properties_[sourceIndex].dependenciesSchema, q.Append(itr->name, allocator_), itr->value, document, id_);
                        properties_[sourceIndex].dependenciesValidatorIndex = validatorCount_;
                        validatorCount_++;
                    }
                }
            }
        }

        if (const ValueType* v = GetMember(value, GetAdditionalPropertiesString())) {
            if (v->IsBool())
                additionalProperties_ = v->GetBool();
            else if (v->IsObject())
                schemaDocument->CreateSchema(&additionalPropertiesSchema_, p.Append(GetAdditionalPropertiesString(), allocator_), *v, document, id_);
        }

        AssignIfExist(minProperties_, value, GetMinPropertiesString());
        AssignIfExist(maxProperties_, value, GetMaxPropertiesString());

        // Array
        if (const ValueType* v = GetMember(value, GetItemsString())) {
            PointerType q = p.Append(GetItemsString(), allocator_);
            if (v->IsObject()) // List validation
                schemaDocument->CreateSchema(&itemsList_, q, *v, document, id_);
            else if (v->IsArray()) { // Tuple validation
                itemsTuple_ = static_cast<const Schema**>(allocator_->Malloc(sizeof(const Schema*) * v->Size()));
                SizeType index = 0;
                for (ConstValueIterator itr = v->Begin(); itr != v->End(); ++itr, index++)
                    schemaDocument->CreateSchema(&itemsTuple_[itemsTupleCount_++], q.Append(index, allocator_), *itr, document, id_);
            }
        }

        AssignIfExist(minItems_, value, GetMinItemsString());
        AssignIfExist(maxItems_, value, GetMaxItemsString());

        // AdditionalItems not supported for openapi 2.0 and 3.0
        if (spec_.oapi != kVersion20 && spec_.oapi != kVersion30)
        if (const ValueType* v = GetMember(value, GetAdditionalItemsString())) {
            if (v->IsBool())
                additionalItems_ = v->GetBool();
            else if (v->IsObject())
                schemaDocument->CreateSchema(&additionalItemsSchema_, p.Append(GetAdditionalItemsString(), allocator_), *v, document, id_);
        }

        AssignIfExist(uniqueItems_, value, GetUniqueItemsString());

        // String
        AssignIfExist(minLength_, value, GetMinLengthString());
        AssignIfExist(maxLength_, value, GetMaxLengthString());

        if (const ValueType* v = GetMember(value, GetPatternString()))
            pattern_ = CreatePattern(*v, schemaDocument, p.Append(GetPatternString(), allocator_));

        // Number
        if (const ValueType* v = GetMember(value, GetMinimumString()))
            if (v->IsNumber())
                minimum_.CopyFrom(*v, *allocator_);

        if (const ValueType* v = GetMember(value, GetMaximumString()))
            if (v->IsNumber())
                maximum_.CopyFrom(*v, *allocator_);

        AssignIfExist(exclusiveMinimum_, value, GetExclusiveMinimumString());
        AssignIfExist(exclusiveMaximum_, value, GetExclusiveMaximumString());

        if (const ValueType* v = GetMember(value, GetMultipleOfString()))
            if (v->IsNumber() && v->GetDouble() > 0.0)
                multipleOf_.CopyFrom(*v, *allocator_);

        // Default
        if (const ValueType* v = GetMember(value, GetDefaultValueString()))
            if (v->IsString())
                defaultValueLength_ = v->GetStringLength();

        // ReadOnly - open api only (until draft 7 supported)
        // WriteOnly - open api 3 only (until draft 7 supported)
        // Both can't be true
        if (spec_.oapi != kVersionNone)
            AssignIfExist(readOnly_, value, GetReadOnlyString());
        if (spec_.oapi >= kVersion30)
            AssignIfExist(writeOnly_, value, GetWriteOnlyString());
        if (readOnly_ && writeOnly_)
            schemaDocument->SchemaError(kSchemaErrorReadOnlyAndWriteOnly, p);

        // Nullable - open api 3 only
        // If true add 'null' as allowable type
        if (spec_.oapi >= kVersion30) {
            AssignIfExist(nullable_, value, GetNullableString());
            if (nullable_)
                AddType(GetNullString());
        }
    }

    ~Schema() {
        AllocatorType::Free(enum_);
        if (properties_) {
            for (SizeType i = 0; i < propertyCount_; i++)
                properties_[i].~Property();
            AllocatorType::Free(properties_);
        }
        if (patternProperties_) {
            for (SizeType i = 0; i < patternPropertyCount_; i++)
                patternProperties_[i].~PatternProperty();
            AllocatorType::Free(patternProperties_);
        }
        AllocatorType::Free(itemsTuple_);
#if RAPIDJSON_SCHEMA_HAS_REGEX
        if (pattern_) {
            pattern_->~RegexType();
            AllocatorType::Free(pattern_);
        }
#endif
    }

    const SValue& GetURI() const {
        return uri_;
    }

    const UriType& GetId() const {
        return id_;
    }

    const Specification& GetSpecification() const {
        return spec_;
    }

    const PointerType& GetPointer() const {
        return pointer_;
    }

    bool BeginValue(Context& context) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::BeginValue");
        if (context.inArray) {
            if (uniqueItems_)
                context.valueUniqueness = true;

            if (itemsList_)
                context.valueSchema = itemsList_;
            else if (itemsTuple_) {
                if (context.arrayElementIndex < itemsTupleCount_)
                    context.valueSchema = itemsTuple_[context.arrayElementIndex];
                else if (additionalItemsSchema_)
                    context.valueSchema = additionalItemsSchema_;
                else if (additionalItems_)
                    context.valueSchema = typeless_;
                else {
                    context.error_handler.DisallowedItem(context.arrayElementIndex);
                    // Must set valueSchema for when kValidateContinueOnErrorFlag is set, else reports spurious type error
                    context.valueSchema = typeless_;
                    // Must bump arrayElementIndex for when kValidateContinueOnErrorFlag is set
                    context.arrayElementIndex++;
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorAdditionalItems);
                }
            }
            else
                context.valueSchema = typeless_;

            context.arrayElementIndex++;
        }
        return true;
    }

    RAPIDJSON_FORCEINLINE bool EndValue(Context& context) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::EndValue");
        // Only check pattern properties if we have validators
        if (context.patternPropertiesValidatorCount > 0) {
            bool otherValid = false;
            SizeType count = context.patternPropertiesValidatorCount;
            if (context.objectPatternValidatorType != Context::kPatternValidatorOnly)
                otherValid = context.patternPropertiesValidators[--count]->IsValid();

            bool patternValid = true;
            for (SizeType i = 0; i < count; i++)
                if (!context.patternPropertiesValidators[i]->IsValid()) {
                    patternValid = false;
                    break;
                }

            if (context.objectPatternValidatorType == Context::kPatternValidatorOnly) {
                if (!patternValid) {
                    context.error_handler.PropertyViolations(context.patternPropertiesValidators, count);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorPatternProperties);
                }
            }
            else if (context.objectPatternValidatorType == Context::kPatternValidatorWithProperty) {
                if (!patternValid || !otherValid) {
                    context.error_handler.PropertyViolations(context.patternPropertiesValidators, count + 1);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorPatternProperties);
                }
            }
            else if (!patternValid && !otherValid) { // kPatternValidatorWithAdditionalProperty)
                context.error_handler.PropertyViolations(context.patternPropertiesValidators, count + 1);
                RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorPatternProperties);
            }
        }

        // For enums only check if we have a hasher
        if (enum_ && context.hasher) {
            const uint64_t h = context.factory.GetHashCode(context.hasher);
            for (SizeType i = 0; i < enumCount_; i++)
                if (enum_[i] == h)
                    goto foundEnum;
            context.error_handler.DisallowedValue(kValidateErrorEnum);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorEnum);
            foundEnum:;
        }

        // Only check allOf etc if we have validators
        if (context.validatorCount > 0) {
            if (allOf_.schemas)
                for (SizeType i = allOf_.begin; i < allOf_.begin + allOf_.count; i++)
                    if (!context.validators[i]->IsValid()) {
                        context.error_handler.NotAllOf(&context.validators[allOf_.begin], allOf_.count);
                        RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorAllOf);
                    }

            if (anyOf_.schemas) {
                for (SizeType i = anyOf_.begin; i < anyOf_.begin + anyOf_.count; i++)
                    if (context.validators[i]->IsValid())
                        goto foundAny;
                context.error_handler.NoneOf(&context.validators[anyOf_.begin], anyOf_.count);
                RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorAnyOf);
                foundAny:;
            }

            if (oneOf_.schemas) {
                bool oneValid = false;
                SizeType firstMatch = 0;
                for (SizeType i = oneOf_.begin; i < oneOf_.begin + oneOf_.count; i++)
                    if (context.validators[i]->IsValid()) {
                        if (oneValid) {
                            context.error_handler.MultipleOneOf(firstMatch, i - oneOf_.begin);
                            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorOneOfMatch);
                        } else {
                            oneValid = true;
                            firstMatch = i - oneOf_.begin;
                        }
                    }
                if (!oneValid) {
                    context.error_handler.NotOneOf(&context.validators[oneOf_.begin], oneOf_.count);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorOneOf);
                }
            }

            if (not_ && context.validators[notValidatorIndex_]->IsValid()) {
                context.error_handler.Disallowed();
                RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorNot);
            }
        }

        return true;
    }

    bool Null(Context& context) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Null");
        if (!(type_ & (1 << kNullSchemaType))) {
            DisallowedType(context, GetNullString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }
        return CreateParallelValidator(context);
    }

    bool Bool(Context& context, bool b) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Bool", b);
        if (!CheckBool(context, b))
            return false;
        return CreateParallelValidator(context);
    }

    bool Int(Context& context, int i) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Int", (int64_t)i);
        if (!CheckInt(context, i))
            return false;
        return CreateParallelValidator(context);
    }

    bool Uint(Context& context, unsigned u) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Uint", (uint64_t)u);
        if (!CheckUint(context, u))
            return false;
        return CreateParallelValidator(context);
    }

    bool Int64(Context& context, int64_t i) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Int64", i);
        if (!CheckInt(context, i))
            return false;
        return CreateParallelValidator(context);
    }

    bool Uint64(Context& context, uint64_t u) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Uint64", u);
        if (!CheckUint(context, u))
            return false;
        return CreateParallelValidator(context);
    }

    bool Double(Context& context, double d) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Double", d);
        if (!(type_ & (1 << kNumberSchemaType))) {
            DisallowedType(context, GetNumberString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }

        if (!minimum_.IsNull() && !CheckDoubleMinimum(context, d))
            return false;

        if (!maximum_.IsNull() && !CheckDoubleMaximum(context, d))
            return false;

        if (!multipleOf_.IsNull() && !CheckDoubleMultipleOf(context, d))
            return false;

        return CreateParallelValidator(context);
    }

    bool String(Context& context, const Ch* str, SizeType length, bool) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::String", str);
        if (!(type_ & (1 << kStringSchemaType))) {
            DisallowedType(context, GetStringString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }

        if (minLength_ != 0 || maxLength_ != SizeType(~0)) {
            SizeType count;
            if (internal::CountStringCodePoint<EncodingType>(str, length, &count)) {
                if (count < minLength_) {
                    context.error_handler.TooShort(str, length, minLength_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMinLength);
                }
                if (count > maxLength_) {
                    context.error_handler.TooLong(str, length, maxLength_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMaxLength);
                }
            }
        }

        if (pattern_ && !IsPatternMatch(pattern_, str, length)) {
            context.error_handler.DoesNotMatch(str, length);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorPattern);
        }

        return CreateParallelValidator(context);
    }

    bool StartObject(Context& context) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::StartObject");
        if (!(type_ & (1 << kObjectSchemaType))) {
            DisallowedType(context, GetObjectString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }

        if (hasDependencies_ || hasRequired_) {
            context.propertyExist = static_cast<bool*>(context.factory.MallocState(sizeof(bool) * propertyCount_));
            std::memset(context.propertyExist, 0, sizeof(bool) * propertyCount_);
        }

        if (patternProperties_) { // pre-allocate schema array
            SizeType count = patternPropertyCount_ + 1; // extra for valuePatternValidatorType
            context.patternPropertiesSchemas = static_cast<const SchemaType**>(context.factory.MallocState(sizeof(const SchemaType*) * count));
            context.patternPropertiesSchemaCount = 0;
            std::memset(context.patternPropertiesSchemas, 0, sizeof(SchemaType*) * count);
        }

        return CreateParallelValidator(context);
    }

    bool Key(Context& context, const Ch* str, SizeType len, bool) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::Key", str);

        if (patternProperties_) {
            context.patternPropertiesSchemaCount = 0;
            for (SizeType i = 0; i < patternPropertyCount_; i++)
                if (patternProperties_[i].pattern && IsPatternMatch(patternProperties_[i].pattern, str, len)) {
                    context.patternPropertiesSchemas[context.patternPropertiesSchemaCount++] = patternProperties_[i].schema;
                    context.valueSchema = typeless_;
                }
        }

        SizeType index  = 0;
        if (FindPropertyIndex(ValueType(str, len).Move(), &index)) {
            if (context.patternPropertiesSchemaCount > 0) {
                context.patternPropertiesSchemas[context.patternPropertiesSchemaCount++] = properties_[index].schema;
                context.valueSchema = typeless_;
                context.valuePatternValidatorType = Context::kPatternValidatorWithProperty;
            }
            else
                context.valueSchema = properties_[index].schema;

            if (context.propertyExist)
                context.propertyExist[index] = true;

            return true;
        }

        if (additionalPropertiesSchema_) {
            if (context.patternPropertiesSchemaCount > 0) {
                context.patternPropertiesSchemas[context.patternPropertiesSchemaCount++] = additionalPropertiesSchema_;
                context.valueSchema = typeless_;
                context.valuePatternValidatorType = Context::kPatternValidatorWithAdditionalProperty;
            }
            else
                context.valueSchema = additionalPropertiesSchema_;
            return true;
        }
        else if (additionalProperties_) {
            context.valueSchema = typeless_;
            return true;
        }

        if (context.patternPropertiesSchemaCount == 0) { // patternProperties are not additional properties
            // Must set valueSchema for when kValidateContinueOnErrorFlag is set, else reports spurious type error
            context.valueSchema = typeless_;
            context.error_handler.DisallowedProperty(str, len);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorAdditionalProperties);
        }

        return true;
    }

    bool EndObject(Context& context, SizeType memberCount) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::EndObject");
        if (hasRequired_) {
            context.error_handler.StartMissingProperties();
            for (SizeType index = 0; index < propertyCount_; index++)
                if (properties_[index].required && !context.propertyExist[index])
                    if (properties_[index].schema->defaultValueLength_ == 0 )
                        context.error_handler.AddMissingProperty(properties_[index].name);
            if (context.error_handler.EndMissingProperties())
                RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorRequired);
        }

        if (memberCount < minProperties_) {
            context.error_handler.TooFewProperties(memberCount, minProperties_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMinProperties);
        }

        if (memberCount > maxProperties_) {
            context.error_handler.TooManyProperties(memberCount, maxProperties_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMaxProperties);
        }

        if (hasDependencies_) {
            context.error_handler.StartDependencyErrors();
            for (SizeType sourceIndex = 0; sourceIndex < propertyCount_; sourceIndex++) {
                const Property& source = properties_[sourceIndex];
                if (context.propertyExist[sourceIndex]) {
                    if (source.dependencies) {
                        context.error_handler.StartMissingDependentProperties();
                        for (SizeType targetIndex = 0; targetIndex < propertyCount_; targetIndex++)
                            if (source.dependencies[targetIndex] && !context.propertyExist[targetIndex])
                                context.error_handler.AddMissingDependentProperty(properties_[targetIndex].name);
                        context.error_handler.EndMissingDependentProperties(source.name);
                    }
                    else if (source.dependenciesSchema) {
                        ISchemaValidator* dependenciesValidator = context.validators[source.dependenciesValidatorIndex];
                        if (!dependenciesValidator->IsValid())
                            context.error_handler.AddDependencySchemaError(source.name, dependenciesValidator);
                    }
                }
            }
            if (context.error_handler.EndDependencyErrors())
                RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorDependencies);
        }

        return true;
    }

    bool StartArray(Context& context) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::StartArray");
        context.arrayElementIndex = 0;
        context.inArray = true;  // Ensure we note that we are in an array

        if (!(type_ & (1 << kArraySchemaType))) {
            DisallowedType(context, GetArrayString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }

        return CreateParallelValidator(context);
    }

    bool EndArray(Context& context, SizeType elementCount) const {
        RAPIDJSON_SCHEMA_PRINT(Method, "Schema::EndArray");
        context.inArray = false;

        if (elementCount < minItems_) {
            context.error_handler.TooFewItems(elementCount, minItems_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMinItems);
        }

        if (elementCount > maxItems_) {
            context.error_handler.TooManyItems(elementCount, maxItems_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMaxItems);
        }

        return true;
    }

    static const ValueType& GetValidateErrorKeyword(ValidateErrorCode validateErrorCode) {
        switch (validateErrorCode) {
            case kValidateErrorMultipleOf:              return GetMultipleOfString();
            case kValidateErrorMaximum:                 return GetMaximumString();
            case kValidateErrorExclusiveMaximum:        return GetMaximumString(); // Same
            case kValidateErrorMinimum:                 return GetMinimumString();
            case kValidateErrorExclusiveMinimum:        return GetMinimumString(); // Same

            case kValidateErrorMaxLength:               return GetMaxLengthString();
            case kValidateErrorMinLength:               return GetMinLengthString();
            case kValidateErrorPattern:                 return GetPatternString();

            case kValidateErrorMaxItems:                return GetMaxItemsString();
            case kValidateErrorMinItems:                return GetMinItemsString();
            case kValidateErrorUniqueItems:             return GetUniqueItemsString();
            case kValidateErrorAdditionalItems:         return GetAdditionalItemsString();

            case kValidateErrorMaxProperties:           return GetMaxPropertiesString();
            case kValidateErrorMinProperties:           return GetMinPropertiesString();
            case kValidateErrorRequired:                return GetRequiredString();
            case kValidateErrorAdditionalProperties:    return GetAdditionalPropertiesString();
            case kValidateErrorPatternProperties:       return GetPatternPropertiesString();
            case kValidateErrorDependencies:            return GetDependenciesString();

            case kValidateErrorEnum:                    return GetEnumString();
            case kValidateErrorType:                    return GetTypeString();

            case kValidateErrorOneOf:                   return GetOneOfString();
            case kValidateErrorOneOfMatch:              return GetOneOfString(); // Same
            case kValidateErrorAllOf:                   return GetAllOfString();
            case kValidateErrorAnyOf:                   return GetAnyOfString();
            case kValidateErrorNot:                     return GetNotString();

            case kValidateErrorReadOnly:                return GetReadOnlyString();
            case kValidateErrorWriteOnly:               return GetWriteOnlyString();

            default:                                    return GetNullString();
        }
    }


    // Generate functions for string literal according to Ch
#define RAPIDJSON_STRING_(name, ...) \
    static const ValueType& Get##name##String() {\
        static const Ch s[] = { __VA_ARGS__, '\0' };\
        static const ValueType v(s, static_cast<SizeType>(sizeof(s) / sizeof(Ch) - 1));\
        return v;\
    }

    RAPIDJSON_STRING_(Null, 'n', 'u', 'l', 'l')
    RAPIDJSON_STRING_(Boolean, 'b', 'o', 'o', 'l', 'e', 'a', 'n')
    RAPIDJSON_STRING_(Object, 'o', 'b', 'j', 'e', 'c', 't')
    RAPIDJSON_STRING_(Array, 'a', 'r', 'r', 'a', 'y')
    RAPIDJSON_STRING_(String, 's', 't', 'r', 'i', 'n', 'g')
    RAPIDJSON_STRING_(Number, 'n', 'u', 'm', 'b', 'e', 'r')
    RAPIDJSON_STRING_(Integer, 'i', 'n', 't', 'e', 'g', 'e', 'r')
    RAPIDJSON_STRING_(Type, 't', 'y', 'p', 'e')
    RAPIDJSON_STRING_(Enum, 'e', 'n', 'u', 'm')
    RAPIDJSON_STRING_(AllOf, 'a', 'l', 'l', 'O', 'f')
    RAPIDJSON_STRING_(AnyOf, 'a', 'n', 'y', 'O', 'f')
    RAPIDJSON_STRING_(OneOf, 'o', 'n', 'e', 'O', 'f')
    RAPIDJSON_STRING_(Not, 'n', 'o', 't')
    RAPIDJSON_STRING_(Properties, 'p', 'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's')
    RAPIDJSON_STRING_(Required, 'r', 'e', 'q', 'u', 'i', 'r', 'e', 'd')
    RAPIDJSON_STRING_(Dependencies, 'd', 'e', 'p', 'e', 'n', 'd', 'e', 'n', 'c', 'i', 'e', 's')
    RAPIDJSON_STRING_(PatternProperties, 'p', 'a', 't', 't', 'e', 'r', 'n', 'P', 'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's')
    RAPIDJSON_STRING_(AdditionalProperties, 'a', 'd', 'd', 'i', 't', 'i', 'o', 'n', 'a', 'l', 'P', 'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's')
    RAPIDJSON_STRING_(MinProperties, 'm', 'i', 'n', 'P', 'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's')
    RAPIDJSON_STRING_(MaxProperties, 'm', 'a', 'x', 'P', 'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's')
    RAPIDJSON_STRING_(Items, 'i', 't', 'e', 'm', 's')
    RAPIDJSON_STRING_(MinItems, 'm', 'i', 'n', 'I', 't', 'e', 'm', 's')
    RAPIDJSON_STRING_(MaxItems, 'm', 'a', 'x', 'I', 't', 'e', 'm', 's')
    RAPIDJSON_STRING_(AdditionalItems, 'a', 'd', 'd', 'i', 't', 'i', 'o', 'n', 'a', 'l', 'I', 't', 'e', 'm', 's')
    RAPIDJSON_STRING_(UniqueItems, 'u', 'n', 'i', 'q', 'u', 'e', 'I', 't', 'e', 'm', 's')
    RAPIDJSON_STRING_(MinLength, 'm', 'i', 'n', 'L', 'e', 'n', 'g', 't', 'h')
    RAPIDJSON_STRING_(MaxLength, 'm', 'a', 'x', 'L', 'e', 'n', 'g', 't', 'h')
    RAPIDJSON_STRING_(Pattern, 'p', 'a', 't', 't', 'e', 'r', 'n')
    RAPIDJSON_STRING_(Minimum, 'm', 'i', 'n', 'i', 'm', 'u', 'm')
    RAPIDJSON_STRING_(Maximum, 'm', 'a', 'x', 'i', 'm', 'u', 'm')
    RAPIDJSON_STRING_(ExclusiveMinimum, 'e', 'x', 'c', 'l', 'u', 's', 'i', 'v', 'e', 'M', 'i', 'n', 'i', 'm', 'u', 'm')
    RAPIDJSON_STRING_(ExclusiveMaximum, 'e', 'x', 'c', 'l', 'u', 's', 'i', 'v', 'e', 'M', 'a', 'x', 'i', 'm', 'u', 'm')
    RAPIDJSON_STRING_(MultipleOf, 'm', 'u', 'l', 't', 'i', 'p', 'l', 'e', 'O', 'f')
    RAPIDJSON_STRING_(DefaultValue, 'd', 'e', 'f', 'a', 'u', 'l', 't')
    RAPIDJSON_STRING_(Schema, '$', 's', 'c', 'h', 'e', 'm', 'a')
    RAPIDJSON_STRING_(Ref, '$', 'r', 'e', 'f')
    RAPIDJSON_STRING_(Id, 'i', 'd')
    RAPIDJSON_STRING_(Swagger, 's', 'w', 'a', 'g', 'g', 'e', 'r')
    RAPIDJSON_STRING_(OpenApi, 'o', 'p', 'e', 'n', 'a', 'p', 'i')
    RAPIDJSON_STRING_(ReadOnly, 'r', 'e', 'a', 'd', 'O', 'n', 'l', 'y')
    RAPIDJSON_STRING_(WriteOnly, 'w', 'r', 'i', 't', 'e', 'O', 'n', 'l', 'y')
    RAPIDJSON_STRING_(Nullable, 'n', 'u', 'l', 'l', 'a', 'b', 'l', 'e')

#undef RAPIDJSON_STRING_

private:
    enum SchemaValueType {
        kNullSchemaType,
        kBooleanSchemaType,
        kObjectSchemaType,
        kArraySchemaType,
        kStringSchemaType,
        kNumberSchemaType,
        kIntegerSchemaType,
        kTotalSchemaType
    };

#if RAPIDJSON_SCHEMA_USE_INTERNALREGEX
        typedef internal::GenericRegex<EncodingType, AllocatorType> RegexType;
#elif RAPIDJSON_SCHEMA_USE_STDREGEX
        typedef std::basic_regex<Ch> RegexType;
#else
        typedef char RegexType;
#endif

    struct SchemaArray {
        SchemaArray() : schemas(), count() {}
        ~SchemaArray() { AllocatorType::Free(schemas); }
        const SchemaType** schemas;
        SizeType begin; // begin index of context.validators
        SizeType count;
    };

    template <typename V1, typename V2>
    void AddUniqueElement(V1& a, const V2& v) {
        for (typename V1::ConstValueIterator itr = a.Begin(); itr != a.End(); ++itr)
            if (*itr == v)
                return;
        V1 c(v, *allocator_);
        a.PushBack(c, *allocator_);
    }

    static const ValueType* GetMember(const ValueType& value, const ValueType& name) {
        typename ValueType::ConstMemberIterator itr = value.FindMember(name);
        return itr != value.MemberEnd() ? &(itr->value) : 0;
    }

    static void AssignIfExist(bool& out, const ValueType& value, const ValueType& name) {
        if (const ValueType* v = GetMember(value, name))
            if (v->IsBool())
                out = v->GetBool();
    }

    static void AssignIfExist(SizeType& out, const ValueType& value, const ValueType& name) {
        if (const ValueType* v = GetMember(value, name))
            if (v->IsUint64() && v->GetUint64() <= SizeType(~0))
                out = static_cast<SizeType>(v->GetUint64());
    }

    void AssignIfExist(SchemaArray& out, SchemaDocumentType& schemaDocument, const PointerType& p, const ValueType& value, const ValueType& name, const ValueType& document) {
        if (const ValueType* v = GetMember(value, name)) {
            if (v->IsArray() && v->Size() > 0) {
                PointerType q = p.Append(name, allocator_);
                out.count = v->Size();
                out.schemas = static_cast<const Schema**>(allocator_->Malloc(out.count * sizeof(const Schema*)));
                memset(out.schemas, 0, sizeof(Schema*)* out.count);
                for (SizeType i = 0; i < out.count; i++)
                    schemaDocument.CreateSchema(&out.schemas[i], q.Append(i, allocator_), (*v)[i], document, id_);
                out.begin = validatorCount_;
                validatorCount_ += out.count;
            }
        }
    }

#if RAPIDJSON_SCHEMA_USE_INTERNALREGEX
    template <typename ValueType>
    RegexType* CreatePattern(const ValueType& value, SchemaDocumentType* sd, const PointerType& p) {
        if (value.IsString()) {
            RegexType* r = new (allocator_->Malloc(sizeof(RegexType))) RegexType(value.GetString(), allocator_);
            if (!r->IsValid()) {
                sd->SchemaErrorValue(kSchemaErrorRegexInvalid, p, value.GetString(), value.GetStringLength());
                r->~RegexType();
                AllocatorType::Free(r);
                r = 0;
            }
            return r;
        }
        return 0;
    }

    static bool IsPatternMatch(const RegexType* pattern, const Ch *str, SizeType) {
        GenericRegexSearch<RegexType> rs(*pattern);
        return rs.Search(str);
    }
#elif RAPIDJSON_SCHEMA_USE_STDREGEX
    template <typename ValueType>
    RegexType* CreatePattern(const ValueType& value, SchemaDocumentType* sd, const PointerType& p) {
        if (value.IsString()) {
            RegexType *r = static_cast<RegexType*>(allocator_->Malloc(sizeof(RegexType)));
            try {
                return new (r) RegexType(value.GetString(), std::size_t(value.GetStringLength()), std::regex_constants::ECMAScript);
            }
            catch (const std::regex_error& e) {
                sd->SchemaErrorValue(kSchemaErrorRegexInvalid, p, value.GetString(), value.GetStringLength());
                AllocatorType::Free(r);
            }
        }
        return 0;
    }

    static bool IsPatternMatch(const RegexType* pattern, const Ch *str, SizeType length) {
        std::match_results<const Ch*> r;
        return std::regex_search(str, str + length, r, *pattern);
    }
#else
    template <typename ValueType>
    RegexType* CreatePattern(const ValueType&) {
        return 0;
    }

    static bool IsPatternMatch(const RegexType*, const Ch *, SizeType) { return true; }
#endif // RAPIDJSON_SCHEMA_USE_STDREGEX

    void AddType(const ValueType& type) {
        if      (type == GetNullString()   ) type_ |= 1 << kNullSchemaType;
        else if (type == GetBooleanString()) type_ |= 1 << kBooleanSchemaType;
        else if (type == GetObjectString() ) type_ |= 1 << kObjectSchemaType;
        else if (type == GetArrayString()  ) type_ |= 1 << kArraySchemaType;
        else if (type == GetStringString() ) type_ |= 1 << kStringSchemaType;
        else if (type == GetIntegerString()) type_ |= 1 << kIntegerSchemaType;
        else if (type == GetNumberString() ) type_ |= (1 << kNumberSchemaType) | (1 << kIntegerSchemaType);
    }

    // Creates parallel validators for allOf, anyOf, oneOf, not and schema dependencies, if required.
    // Also creates a hasher for enums and array uniqueness, if required.
    // Also a useful place to add type-independent error checks.
    bool CreateParallelValidator(Context& context) const {
        if (enum_ || context.arrayUniqueness)
            context.hasher = context.factory.CreateHasher();

        if (validatorCount_) {
            RAPIDJSON_ASSERT(context.validators == 0);
            context.validators = static_cast<ISchemaValidator**>(context.factory.MallocState(sizeof(ISchemaValidator*) * validatorCount_));
            std::memset(context.validators, 0, sizeof(ISchemaValidator*) * validatorCount_);
            context.validatorCount = validatorCount_;

            // Always return after first failure for these sub-validators
            if (allOf_.schemas)
                CreateSchemaValidators(context, allOf_, false);

            if (anyOf_.schemas)
                CreateSchemaValidators(context, anyOf_, false);

            if (oneOf_.schemas)
                CreateSchemaValidators(context, oneOf_, false);

            if (not_)
                context.validators[notValidatorIndex_] = context.factory.CreateSchemaValidator(*not_, false);

            if (hasSchemaDependencies_) {
                for (SizeType i = 0; i < propertyCount_; i++)
                    if (properties_[i].dependenciesSchema)
                        context.validators[properties_[i].dependenciesValidatorIndex] = context.factory.CreateSchemaValidator(*properties_[i].dependenciesSchema, false);
            }
        }

        // Add any other type-independent checks here
        if (readOnly_ && (context.flags & kValidateWriteFlag)) {
            context.error_handler.DisallowedWhenWriting();
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorReadOnly);
        }
        if (writeOnly_ && (context.flags & kValidateReadFlag)) {
            context.error_handler.DisallowedWhenReading();
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorWriteOnly);
        }

        return true;
    }

    void CreateSchemaValidators(Context& context, const SchemaArray& schemas, const bool inheritContinueOnErrors) const {
        for (SizeType i = 0; i < schemas.count; i++)
            context.validators[schemas.begin + i] = context.factory.CreateSchemaValidator(*schemas.schemas[i], inheritContinueOnErrors);
    }

    // O(n)
    bool FindPropertyIndex(const ValueType& name, SizeType* outIndex) const {
        SizeType len = name.GetStringLength();
        const Ch* str = name.GetString();
        for (SizeType index = 0; index < propertyCount_; index++)
            if (properties_[index].name.GetStringLength() == len &&
                (std::memcmp(properties_[index].name.GetString(), str, sizeof(Ch) * len) == 0))
            {
                *outIndex = index;
                return true;
            }
        return false;
    }

    bool CheckBool(Context& context, bool) const {
        if (!(type_ & (1 << kBooleanSchemaType))) {
            DisallowedType(context, GetBooleanString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }
        return true;
    }

    bool CheckInt(Context& context, int64_t i) const {
        if (!(type_ & ((1 << kIntegerSchemaType) | (1 << kNumberSchemaType)))) {
            DisallowedType(context, GetIntegerString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }

        if (!minimum_.IsNull()) {
            if (minimum_.IsInt64()) {
                if (exclusiveMinimum_ ? i <= minimum_.GetInt64() : i < minimum_.GetInt64()) {
                    context.error_handler.BelowMinimum(i, minimum_, exclusiveMinimum_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMinimum_ ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum);
                }
            }
            else if (minimum_.IsUint64()) {
                context.error_handler.BelowMinimum(i, minimum_, exclusiveMinimum_);
                RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMinimum_ ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum); // i <= max(int64_t) < minimum.GetUint64()
            }
            else if (!CheckDoubleMinimum(context, static_cast<double>(i)))
                return false;
        }

        if (!maximum_.IsNull()) {
            if (maximum_.IsInt64()) {
                if (exclusiveMaximum_ ? i >= maximum_.GetInt64() : i > maximum_.GetInt64()) {
                    context.error_handler.AboveMaximum(i, maximum_, exclusiveMaximum_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMaximum_ ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum);
                }
            }
            else if (maximum_.IsUint64()) { }
                /* do nothing */ // i <= max(int64_t) < maximum_.GetUint64()
            else if (!CheckDoubleMaximum(context, static_cast<double>(i)))
                return false;
        }

        if (!multipleOf_.IsNull()) {
            if (multipleOf_.IsUint64()) {
                if (static_cast<uint64_t>(i >= 0 ? i : -i) % multipleOf_.GetUint64() != 0) {
                    context.error_handler.NotMultipleOf(i, multipleOf_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMultipleOf);
                }
            }
            else if (!CheckDoubleMultipleOf(context, static_cast<double>(i)))
                return false;
        }

        return true;
    }

    bool CheckUint(Context& context, uint64_t i) const {
        if (!(type_ & ((1 << kIntegerSchemaType) | (1 << kNumberSchemaType)))) {
            DisallowedType(context, GetIntegerString());
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorType);
        }

        if (!minimum_.IsNull()) {
            if (minimum_.IsUint64()) {
                if (exclusiveMinimum_ ? i <= minimum_.GetUint64() : i < minimum_.GetUint64()) {
                    context.error_handler.BelowMinimum(i, minimum_, exclusiveMinimum_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMinimum_ ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum);
                }
            }
            else if (minimum_.IsInt64())
                /* do nothing */; // i >= 0 > minimum.Getint64()
            else if (!CheckDoubleMinimum(context, static_cast<double>(i)))
                return false;
        }

        if (!maximum_.IsNull()) {
            if (maximum_.IsUint64()) {
                if (exclusiveMaximum_ ? i >= maximum_.GetUint64() : i > maximum_.GetUint64()) {
                    context.error_handler.AboveMaximum(i, maximum_, exclusiveMaximum_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMaximum_ ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum);
                }
            }
            else if (maximum_.IsInt64()) {
                context.error_handler.AboveMaximum(i, maximum_, exclusiveMaximum_);
                RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMaximum_ ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum); // i >= 0 > maximum_
            }
            else if (!CheckDoubleMaximum(context, static_cast<double>(i)))
                return false;
        }

        if (!multipleOf_.IsNull()) {
            if (multipleOf_.IsUint64()) {
                if (i % multipleOf_.GetUint64() != 0) {
                    context.error_handler.NotMultipleOf(i, multipleOf_);
                    RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMultipleOf);
                }
            }
            else if (!CheckDoubleMultipleOf(context, static_cast<double>(i)))
                return false;
        }

        return true;
    }

    bool CheckDoubleMinimum(Context& context, double d) const {
        if (exclusiveMinimum_ ? d <= minimum_.GetDouble() : d < minimum_.GetDouble()) {
            context.error_handler.BelowMinimum(d, minimum_, exclusiveMinimum_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMinimum_ ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum);
        }
        return true;
    }

    bool CheckDoubleMaximum(Context& context, double d) const {
        if (exclusiveMaximum_ ? d >= maximum_.GetDouble() : d > maximum_.GetDouble()) {
            context.error_handler.AboveMaximum(d, maximum_, exclusiveMaximum_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(exclusiveMaximum_ ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum);
        }
        return true;
    }

    bool CheckDoubleMultipleOf(Context& context, double d) const {
        double a = std::abs(d), b = std::abs(multipleOf_.GetDouble());
        double q = a / b;
        double qRounded = std::floor(q + 0.5);
        double scaledEpsilon = (q + qRounded) * std::numeric_limits<double>::epsilon();
        double difference = std::abs(qRounded - q);
        bool isMultiple = difference <= scaledEpsilon || difference < (std::numeric_limits<double>::min)();
        if (!isMultiple) {
            context.error_handler.NotMultipleOf(d, multipleOf_);
            RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorMultipleOf);
        }
        return true;
    }

    void DisallowedType(Context& context, const ValueType& actualType) const {
        ErrorHandler& eh = context.error_handler;
        eh.StartDisallowedType();

        if (type_ & (1 << kNullSchemaType)) eh.AddExpectedType(GetNullString());
        if (type_ & (1 << kBooleanSchemaType)) eh.AddExpectedType(GetBooleanString());
        if (type_ & (1 << kObjectSchemaType)) eh.AddExpectedType(GetObjectString());
        if (type_ & (1 << kArraySchemaType)) eh.AddExpectedType(GetArrayString());
        if (type_ & (1 << kStringSchemaType)) eh.AddExpectedType(GetStringString());

        if (type_ & (1 << kNumberSchemaType)) eh.AddExpectedType(GetNumberString());
        else if (type_ & (1 << kIntegerSchemaType)) eh.AddExpectedType(GetIntegerString());

        eh.EndDisallowedType(actualType);
    }

    struct Property {
        Property() : schema(), dependenciesSchema(), dependenciesValidatorIndex(), dependencies(), required(false) {}
        ~Property() { AllocatorType::Free(dependencies); }
        SValue name;
        const SchemaType* schema;
        const SchemaType* dependenciesSchema;
        SizeType dependenciesValidatorIndex;
        bool* dependencies;
        bool required;
    };

    struct PatternProperty {
        PatternProperty() : schema(), pattern() {}
        ~PatternProperty() {
            if (pattern) {
                pattern->~RegexType();
                AllocatorType::Free(pattern);
            }
        }
        const SchemaType* schema;
        RegexType* pattern;
    };

    AllocatorType* allocator_;
    SValue uri_;
    UriType id_;
    Specification spec_;
    PointerType pointer_;
    const SchemaType* typeless_;
    uint64_t* enum_;
    SizeType enumCount_;
    SchemaArray allOf_;
    SchemaArray anyOf_;
    SchemaArray oneOf_;
    const SchemaType* not_;
    unsigned type_; // bitmask of kSchemaType
    SizeType validatorCount_;
    SizeType notValidatorIndex_;

    Property* properties_;
    const SchemaType* additionalPropertiesSchema_;
    PatternProperty* patternProperties_;
    SizeType patternPropertyCount_;
    SizeType propertyCount_;
    SizeType minProperties_;
    SizeType maxProperties_;
    bool additionalProperties_;
    bool hasDependencies_;
    bool hasRequired_;
    bool hasSchemaDependencies_;

    const SchemaType* additionalItemsSchema_;
    const SchemaType* itemsList_;
    const SchemaType** itemsTuple_;
    SizeType itemsTupleCount_;
    SizeType minItems_;
    SizeType maxItems_;
    bool additionalItems_;
    bool uniqueItems_;

    RegexType* pattern_;
    SizeType minLength_;
    SizeType maxLength_;

    SValue minimum_;
    SValue maximum_;
    SValue multipleOf_;
    bool exclusiveMinimum_;
    bool exclusiveMaximum_;

    SizeType defaultValueLength_;

    bool readOnly_;
    bool writeOnly_;
    bool nullable_;
};

template<typename Stack, typename Ch>
struct TokenHelper {
    RAPIDJSON_FORCEINLINE static void AppendIndexToken(Stack& documentStack, SizeType index) {
        *documentStack.template Push<Ch>() = '/';
        char buffer[21];
        size_t length = static_cast<size_t>((sizeof(SizeType) == 4 ? u32toa(index, buffer) : u64toa(index, buffer)) - buffer);
        for (size_t i = 0; i < length; i++)
            *documentStack.template Push<Ch>() = static_cast<Ch>(buffer[i]);
    }
};

// Partial specialized version for char to prevent buffer copying.
template <typename Stack>
struct TokenHelper<Stack, char> {
    RAPIDJSON_FORCEINLINE static void AppendIndexToken(Stack& documentStack, SizeType index) {
        RAPIDJSON_IF_CONSTEXPR (sizeof(SizeType) == 4) {
            char *buffer = documentStack.template Push<char>(1 + 10); // '/' + uint
            *buffer++ = '/';
            const char* end = internal::u32toa(index, buffer);
             documentStack.template Pop<char>(static_cast<size_t>(10 - (end - buffer)));
        }
        else {
            char *buffer = documentStack.template Push<char>(1 + 20); // '/' + uint64
            *buffer++ = '/';
            const char* end = internal::u64toa(index, buffer);
            documentStack.template Pop<char>(static_cast<size_t>(20 - (end - buffer)));
        }
    }
};

} // namespace internal

///////////////////////////////////////////////////////////////////////////////
// IGenericRemoteSchemaDocumentProvider

template <typename SchemaDocumentType>
class IGenericRemoteSchemaDocumentProvider {
public:
    typedef typename SchemaDocumentType::Ch Ch;
    typedef typename SchemaDocumentType::ValueType ValueType;
    typedef typename SchemaDocumentType::AllocatorType AllocatorType;

    virtual ~IGenericRemoteSchemaDocumentProvider() {}
    virtual const SchemaDocumentType* GetRemoteDocument(const Ch* uri, SizeType length) = 0;
    virtual const SchemaDocumentType* GetRemoteDocument(const GenericUri<ValueType, AllocatorType> uri, Specification& spec) {
        // Default implementation just calls through for compatibility
        // Following line suppresses unused parameter warning
        (void)spec;
        // printf("GetRemoteDocument: %d %d\n", spec.draft, spec.oapi);
        return GetRemoteDocument(uri.GetBaseString(), uri.GetBaseStringLength());
    }
};

///////////////////////////////////////////////////////////////////////////////
// GenericSchemaDocument

//! JSON schema document.
/*!
    A JSON schema document is a compiled version of a JSON schema.
    It is basically a tree of internal::Schema.

    \note This is an immutable class (i.e. its instance cannot be modified after construction).
    \tparam ValueT Type of JSON value (e.g. \c Value ), which also determine the encoding.
    \tparam Allocator Allocator type for allocating memory of this document.
*/
template <typename ValueT, typename Allocator = CrtAllocator>
class GenericSchemaDocument {
public:
    typedef ValueT ValueType;
    typedef IGenericRemoteSchemaDocumentProvider<GenericSchemaDocument> IRemoteSchemaDocumentProviderType;
    typedef Allocator AllocatorType;
    typedef typename ValueType::EncodingType EncodingType;
    typedef typename EncodingType::Ch Ch;
    typedef internal::Schema<GenericSchemaDocument> SchemaType;
    typedef GenericPointer<ValueType, Allocator> PointerType;
    typedef GenericValue<EncodingType, AllocatorType> GValue;
    typedef GenericUri<ValueType, Allocator> UriType;
    typedef GenericStringRef<Ch> StringRefType;
    friend class internal::Schema<GenericSchemaDocument>;
    template <typename, typename, typename>
    friend class GenericSchemaValidator;

    //! Constructor.
    /*!
        Compile a JSON document into schema document.

        \param document A JSON document as source.
        \param uri The base URI of this schema document for purposes of violation reporting.
        \param uriLength Length of \c name, in code points.
        \param remoteProvider An optional remote schema document provider for resolving remote reference. Can be null.
        \param allocator An optional allocator instance for allocating memory. Can be null.
        \param pointer An optional JSON pointer to the start of the schema document
        \param spec Optional schema draft or OpenAPI version. Used if no specification in document. Defaults to draft-04.
    */
    explicit GenericSchemaDocument(const ValueType& document, const Ch* uri = 0, SizeType uriLength = 0,
        IRemoteSchemaDocumentProviderType* remoteProvider = 0, Allocator* allocator = 0,
        const PointerType& pointer = PointerType(), // PR #1393
        const Specification& spec = Specification(kDraft04)) :
        remoteProvider_(remoteProvider),
        allocator_(allocator),
        ownAllocator_(),
        root_(),
        typeless_(),
        schemaMap_(allocator, kInitialSchemaMapSize),
        schemaRef_(allocator, kInitialSchemaRefSize),
        spec_(spec),
        error_(kObjectType),
        currentError_()
    {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaDocument::GenericSchemaDocument");
        if (!allocator_)
            ownAllocator_ = allocator_ = RAPIDJSON_NEW(Allocator)();

        Ch noUri[1] = {0};
        uri_.SetString(uri ? uri : noUri, uriLength, *allocator_);
        docId_ = UriType(uri_, allocator_);

        typeless_ = static_cast<SchemaType*>(allocator_->Malloc(sizeof(SchemaType)));
        new (typeless_) SchemaType(this, PointerType(), ValueType(kObjectType).Move(), ValueType(kObjectType).Move(), allocator_, docId_);

        // Establish the schema draft or open api version.
        // We only ever look for '$schema' or 'swagger' or 'openapi' at the root of the document.
        SetSchemaSpecification(document);

        // Generate root schema, it will call CreateSchema() to create sub-schemas,
        // And call HandleRefSchema() if there are $ref.
        // PR #1393 use input pointer if supplied
        root_ = typeless_;
        if (pointer.GetTokenCount() == 0) {
            CreateSchemaRecursive(&root_, pointer, document, document, docId_);
        }
        else if (const ValueType* v = pointer.Get(document)) {
            CreateSchema(&root_, pointer, *v, document, docId_);
        }
        else {
            GenericStringBuffer<EncodingType> sb;
            pointer.StringifyUriFragment(sb);
            SchemaErrorValue(kSchemaErrorStartUnknown, PointerType(), sb.GetString(), static_cast<SizeType>(sb.GetSize() / sizeof(Ch)));
        }

        RAPIDJSON_ASSERT(root_ != 0);

        schemaRef_.ShrinkToFit(); // Deallocate all memory for ref
    }

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move constructor in C++11
    GenericSchemaDocument(GenericSchemaDocument&& rhs) RAPIDJSON_NOEXCEPT :
        remoteProvider_(rhs.remoteProvider_),
        allocator_(rhs.allocator_),
        ownAllocator_(rhs.ownAllocator_),
        root_(rhs.root_),
        typeless_(rhs.typeless_),
        schemaMap_(std::move(rhs.schemaMap_)),
        schemaRef_(std::move(rhs.schemaRef_)),
        uri_(std::move(rhs.uri_)),
        docId_(std::move(rhs.docId_)),
        spec_(rhs.spec_),
        error_(std::move(rhs.error_)),
        currentError_(std::move(rhs.currentError_))
    {
        rhs.remoteProvider_ = 0;
        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.typeless_ = 0;
    }
#endif

    //! Destructor
    ~GenericSchemaDocument() {
        while (!schemaMap_.Empty())
            schemaMap_.template Pop<SchemaEntry>(1)->~SchemaEntry();

        if (typeless_) {
            typeless_->~SchemaType();
            Allocator::Free(typeless_);
        }

        // these may contain some allocator data so clear before deleting ownAllocator_
        uri_.SetNull();
        error_.SetNull();
        currentError_.SetNull();

        RAPIDJSON_DELETE(ownAllocator_);
    }

    const GValue& GetURI() const { return uri_; }

    const Specification& GetSpecification() const { return spec_; }
    bool IsSupportedSpecification() const { return spec_.IsSupported(); }

    //! Static method to get the specification of any schema document
    //  Returns kDraftNone if document is silent
    static const Specification GetSpecification(const ValueType& document) {
      SchemaDraft draft = GetSchemaDraft(document);
      if (draft != kDraftNone)
        return Specification(draft);
      else {
        OpenApiVersion oapi = GetOpenApiVersion(document);
        if (oapi != kVersionNone)
          return Specification(oapi);
      }
      return Specification(kDraftNone);
    }

    //! Get the root schema.
    const SchemaType& GetRoot() const { return *root_; }

    //! Gets the error object.
    GValue& GetError() { return error_; }
    const GValue& GetError() const { return error_; }

    static const StringRefType& GetSchemaErrorKeyword(SchemaErrorCode schemaErrorCode) {
        switch (schemaErrorCode) {
            case kSchemaErrorStartUnknown:             return GetStartUnknownString();
            case kSchemaErrorRefPlainName:             return GetRefPlainNameString();
            case kSchemaErrorRefInvalid:               return GetRefInvalidString();
            case kSchemaErrorRefPointerInvalid:        return GetRefPointerInvalidString();
            case kSchemaErrorRefUnknown:               return GetRefUnknownString();
            case kSchemaErrorRefCyclical:              return GetRefCyclicalString();
            case kSchemaErrorRefNoRemoteProvider:      return GetRefNoRemoteProviderString();
            case kSchemaErrorRefNoRemoteSchema:        return GetRefNoRemoteSchemaString();
            case kSchemaErrorRegexInvalid:             return GetRegexInvalidString();
            case kSchemaErrorSpecUnknown:              return GetSpecUnknownString();
            case kSchemaErrorSpecUnsupported:          return GetSpecUnsupportedString();
            case kSchemaErrorSpecIllegal:              return GetSpecIllegalString();
            case kSchemaErrorReadOnlyAndWriteOnly:     return GetReadOnlyAndWriteOnlyString();
            default:                                   return GetNullString();
        }
    }

    //! Default error method
    void SchemaError(const SchemaErrorCode code, const PointerType& location) {
      currentError_ = GValue(kObjectType);
      AddCurrentError(code, location);
    }

    //! Method for error with single string value insert
    void SchemaErrorValue(const SchemaErrorCode code, const PointerType& location, const Ch* value, SizeType length) {
      currentError_ = GValue(kObjectType);
      currentError_.AddMember(GetValueString(), GValue(value, length, *allocator_).Move(), *allocator_);
      AddCurrentError(code, location);
    }

    //! Method for error with invalid pointer
    void SchemaErrorPointer(const SchemaErrorCode code, const PointerType& location, const Ch* value, SizeType length, const PointerType& pointer) {
      currentError_ = GValue(kObjectType);
      currentError_.AddMember(GetValueString(), GValue(value, length, *allocator_).Move(), *allocator_);
      currentError_.AddMember(GetOffsetString(), static_cast<SizeType>(pointer.GetParseErrorOffset() / sizeof(Ch)), *allocator_);
      AddCurrentError(code, location);
    }

  private:
    //! Prohibit copying
    GenericSchemaDocument(const GenericSchemaDocument&);
    //! Prohibit assignment
    GenericSchemaDocument& operator=(const GenericSchemaDocument&);

    typedef const PointerType* SchemaRefPtr; // PR #1393

    struct SchemaEntry {
        SchemaEntry(const PointerType& p, SchemaType* s, bool o, Allocator* allocator) : pointer(p, allocator), schema(s), owned(o) {}
        ~SchemaEntry() {
            if (owned) {
                schema->~SchemaType();
                Allocator::Free(schema);
            }
        }
        PointerType pointer;
        SchemaType* schema;
        bool owned;
    };

    void AddErrorInstanceLocation(GValue& result, const PointerType& location) {
      GenericStringBuffer<EncodingType> sb;
      location.StringifyUriFragment(sb);
      GValue instanceRef(sb.GetString(), static_cast<SizeType>(sb.GetSize() / sizeof(Ch)), *allocator_);
      result.AddMember(GetInstanceRefString(), instanceRef, *allocator_);
    }

    void AddError(GValue& keyword, GValue& error) {
      typename GValue::MemberIterator member = error_.FindMember(keyword);
      if (member == error_.MemberEnd())
        error_.AddMember(keyword, error, *allocator_);
      else {
        if (member->value.IsObject()) {
          GValue errors(kArrayType);
          errors.PushBack(member->value, *allocator_);
          member->value = errors;
        }
        member->value.PushBack(error, *allocator_);
      }
    }

    void AddCurrentError(const SchemaErrorCode code, const PointerType& location) {
      RAPIDJSON_SCHEMA_PRINT(InvalidKeyword, GetSchemaErrorKeyword(code));
      currentError_.AddMember(GetErrorCodeString(), code, *allocator_);
      AddErrorInstanceLocation(currentError_, location);
      AddError(GValue(GetSchemaErrorKeyword(code)).Move(), currentError_);
    }

#define RAPIDJSON_STRING_(name, ...) \
    static const StringRefType& Get##name##String() {\
        static const Ch s[] = { __VA_ARGS__, '\0' };\
        static const StringRefType v(s, static_cast<SizeType>(sizeof(s) / sizeof(Ch) - 1)); \
        return v;\
    }

    RAPIDJSON_STRING_(InstanceRef, 'i', 'n', 's', 't', 'a', 'n', 'c', 'e', 'R', 'e', 'f')
    RAPIDJSON_STRING_(ErrorCode, 'e', 'r', 'r', 'o', 'r', 'C', 'o', 'd', 'e')
    RAPIDJSON_STRING_(Value, 'v', 'a', 'l', 'u', 'e')
    RAPIDJSON_STRING_(Offset, 'o', 'f', 'f', 's', 'e', 't')

    RAPIDJSON_STRING_(Null, 'n', 'u', 'l', 'l')
    RAPIDJSON_STRING_(SpecUnknown, 'S', 'p', 'e', 'c', 'U', 'n', 'k', 'n', 'o', 'w', 'n')
    RAPIDJSON_STRING_(SpecUnsupported, 'S', 'p', 'e', 'c', 'U', 'n', 's', 'u', 'p', 'p', 'o', 'r', 't', 'e', 'd')
    RAPIDJSON_STRING_(SpecIllegal, 'S', 'p', 'e', 'c', 'I', 'l', 'l', 'e', 'g', 'a', 'l')
    RAPIDJSON_STRING_(StartUnknown, 'S', 't', 'a', 'r', 't', 'U', 'n', 'k', 'n', 'o', 'w', 'n')
    RAPIDJSON_STRING_(RefPlainName, 'R', 'e', 'f', 'P', 'l', 'a', 'i', 'n', 'N', 'a', 'm', 'e')
    RAPIDJSON_STRING_(RefInvalid, 'R', 'e', 'f', 'I', 'n', 'v', 'a', 'l', 'i', 'd')
    RAPIDJSON_STRING_(RefPointerInvalid, 'R', 'e', 'f', 'P', 'o', 'i', 'n', 't', 'e', 'r', 'I', 'n', 'v', 'a', 'l', 'i', 'd')
    RAPIDJSON_STRING_(RefUnknown, 'R', 'e', 'f', 'U', 'n', 'k', 'n', 'o', 'w', 'n')
    RAPIDJSON_STRING_(RefCyclical, 'R', 'e', 'f', 'C', 'y', 'c', 'l', 'i', 'c', 'a', 'l')
    RAPIDJSON_STRING_(RefNoRemoteProvider, 'R', 'e', 'f', 'N', 'o', 'R', 'e', 'm', 'o', 't', 'e', 'P', 'r', 'o', 'v', 'i', 'd', 'e', 'r')
    RAPIDJSON_STRING_(RefNoRemoteSchema, 'R', 'e', 'f', 'N', 'o', 'R', 'e', 'm', 'o', 't', 'e', 'S', 'c', 'h', 'e', 'm', 'a')
    RAPIDJSON_STRING_(ReadOnlyAndWriteOnly, 'R', 'e', 'a', 'd', 'O', 'n', 'l', 'y', 'A', 'n', 'd', 'W', 'r', 'i', 't', 'e', 'O', 'n', 'l', 'y')
    RAPIDJSON_STRING_(RegexInvalid, 'R', 'e', 'g', 'e', 'x', 'I', 'n', 'v', 'a', 'l', 'i', 'd')

#undef RAPIDJSON_STRING_

    // Static method to get schema draft of any schema document
    static SchemaDraft GetSchemaDraft(const ValueType& document) {
        static const Ch kDraft03String[] = { 'h', 't', 't', 'p', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '-', '0', '3', '/', 's', 'c', 'h', 'e', 'm', 'a', '#', '\0' };
        static const Ch kDraft04String[] = { 'h', 't', 't', 'p', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '-', '0', '4', '/', 's', 'c', 'h', 'e', 'm', 'a', '#', '\0' };
        static const Ch kDraft05String[] = { 'h', 't', 't', 'p', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '-', '0', '5', '/', 's', 'c', 'h', 'e', 'm', 'a', '#', '\0' };
        static const Ch kDraft06String[] = { 'h', 't', 't', 'p', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '-', '0', '6', '/', 's', 'c', 'h', 'e', 'm', 'a', '#', '\0' };
        static const Ch kDraft07String[] = { 'h', 't', 't', 'p', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '-', '0', '7', '/', 's', 'c', 'h', 'e', 'm', 'a', '#', '\0' };
        static const Ch kDraft2019_09String[] = { 'h', 't', 't', 'p', 's', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '/', '2', '0', '1', '9', '-', '0', '9', '/', 's', 'c', 'h', 'e', 'm', 'a', '\0' };
        static const Ch kDraft2020_12String[] = { 'h', 't', 't', 'p', 's', ':', '/', '/', 'j', 's', 'o', 'n', '-', 's', 'c', 'h', 'e', 'm', 'a', '.', 'o', 'r', 'g', '/', 'd', 'r', 'a', 'f', 't', '/', '2', '0', '2', '0', '-', '1', '2', '/', 's', 'c', 'h', 'e', 'm', 'a', '\0' };

        if (!document.IsObject()) {
            return kDraftNone;
        }

        // Get the schema draft from the $schema keyword at the supplied location
        typename ValueType::ConstMemberIterator itr = document.FindMember(SchemaType::GetSchemaString());
        if (itr != document.MemberEnd()) {
            if (!itr->value.IsString()) return kDraftUnknown;
            const UriType draftUri(itr->value);
            // Check base uri for match
            if (draftUri.Match(UriType(kDraft04String), false)) return kDraft04;
            if (draftUri.Match(UriType(kDraft05String), false)) return kDraft05;
            if (draftUri.Match(UriType(kDraft06String), false)) return kDraft06;
            if (draftUri.Match(UriType(kDraft07String), false)) return kDraft07;
            if (draftUri.Match(UriType(kDraft03String), false)) return kDraft03;
            if (draftUri.Match(UriType(kDraft2019_09String), false)) return kDraft2019_09;
            if (draftUri.Match(UriType(kDraft2020_12String), false)) return kDraft2020_12;
            return kDraftUnknown;
        }
        // $schema not found
        return kDraftNone;
    }


    // Get open api version of any schema document
    static OpenApiVersion GetOpenApiVersion(const ValueType& document) {
        static const Ch kVersion20String[] = { '2', '.', '0', '\0' };
        static const Ch kVersion30String[] = { '3', '.', '0', '.', '\0' }; // ignore patch level
        static const Ch kVersion31String[] = { '3', '.', '1', '.', '\0' }; // ignore patch level
        static SizeType len = internal::StrLen<Ch>(kVersion30String);

        if (!document.IsObject()) {
            return kVersionNone;
        }

        // Get the open api version from the swagger / openapi keyword at the supplied location
        typename ValueType::ConstMemberIterator itr = document.FindMember(SchemaType::GetSwaggerString());
        if (itr == document.MemberEnd()) itr = document.FindMember(SchemaType::GetOpenApiString());
        if (itr != document.MemberEnd()) {
            if (!itr->value.IsString()) return kVersionUnknown;
            const ValueType kVersion20Value(kVersion20String);
            if (kVersion20Value == itr->value) return kVersion20; // must match 2.0 exactly
            const ValueType kVersion30Value(kVersion30String);
            if (itr->value.GetStringLength() > len && kVersion30Value == ValueType(itr->value.GetString(), len)) return kVersion30; // must match 3.0.x
            const ValueType kVersion31Value(kVersion31String);
            if (itr->value.GetStringLength() > len && kVersion31Value == ValueType(itr->value.GetString(), len)) return kVersion31; // must match 3.1.x
            return kVersionUnknown;
        }
        // swagger or openapi not found
        return kVersionNone;
    }

    // Get the draft of the schema or the open api version (which implies the draft).
    // Report an error if schema draft or open api version not supported or not recognized, or both in document, and carry on.
    void SetSchemaSpecification(const ValueType& document) {
        // Look for '$schema', 'swagger' or 'openapi' keyword at document root
        SchemaDraft docDraft = GetSchemaDraft(document);
        OpenApiVersion docOapi = GetOpenApiVersion(document);
        // Error if both in document
        if (docDraft != kDraftNone && docOapi != kVersionNone)
          SchemaError(kSchemaErrorSpecIllegal, PointerType());
        // Use document draft or open api version if present or use spec from constructor
        if (docDraft != kDraftNone)
            spec_ = Specification(docDraft);
        else if (docOapi != kVersionNone)
            spec_ = Specification(docOapi);
        // Error if draft or version unknown
        if (spec_.draft == kDraftUnknown || spec_.oapi == kVersionUnknown)
          SchemaError(kSchemaErrorSpecUnknown, PointerType());
        else if (!spec_.IsSupported())
            SchemaError(kSchemaErrorSpecUnsupported, PointerType());
    }

    // Changed by PR #1393
    void CreateSchemaRecursive(const SchemaType** schema, const PointerType& pointer, const ValueType& v, const ValueType& document, const UriType& id) {
        if (v.GetType() == kObjectType) {
            UriType newid = UriType(CreateSchema(schema, pointer, v, document, id), allocator_);

            for (typename ValueType::ConstMemberIterator itr = v.MemberBegin(); itr != v.MemberEnd(); ++itr)
                CreateSchemaRecursive(0, pointer.Append(itr->name, allocator_), itr->value, document, newid);
        }
        else if (v.GetType() == kArrayType)
            for (SizeType i = 0; i < v.Size(); i++)
                CreateSchemaRecursive(0, pointer.Append(i, allocator_), v[i], document, id);
    }

    // Changed by PR #1393
    const UriType& CreateSchema(const SchemaType** schema, const PointerType& pointer, const ValueType& v, const ValueType& document, const UriType& id) {
        RAPIDJSON_ASSERT(pointer.IsValid());
        GenericStringBuffer<EncodingType> sb;
        pointer.StringifyUriFragment(sb);
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaDocument::CreateSchema", sb.GetString(), id.GetString());
        if (v.IsObject()) {
            if (const SchemaType* sc = GetSchema(pointer)) {
                if (schema)
                    *schema = sc;
                AddSchemaRefs(const_cast<SchemaType*>(sc));
            }
            else if (!HandleRefSchema(pointer, schema, v, document, id)) {
                // The new schema constructor adds itself and its $ref(s) to schemaMap_
                SchemaType* s = new (allocator_->Malloc(sizeof(SchemaType))) SchemaType(this, pointer, v, document, allocator_, id);
                if (schema)
                    *schema = s;
                return s->GetId();
            }
        }
        else {
            if (schema)
                *schema = typeless_;
            AddSchemaRefs(typeless_);
        }
        return id;
    }

    // Changed by PR #1393
    // TODO should this return a UriType& ?
    bool HandleRefSchema(const PointerType& source, const SchemaType** schema, const ValueType& v, const ValueType& document, const UriType& id) {
        typename ValueType::ConstMemberIterator itr = v.FindMember(SchemaType::GetRefString());
        if (itr == v.MemberEnd())
            return false;

        GenericStringBuffer<EncodingType> sb;
        source.StringifyUriFragment(sb);
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaDocument::HandleRefSchema", sb.GetString(), id.GetString());
        // Resolve the source pointer to the $ref'ed schema (finally)
        new (schemaRef_.template Push<SchemaRefPtr>()) SchemaRefPtr(&source);

        if (itr->value.IsString()) {
            SizeType len = itr->value.GetStringLength();
            if (len == 0)
                SchemaError(kSchemaErrorRefInvalid, source);
            else {
                // First resolve $ref against the in-scope id
                UriType scopeId = UriType(id, allocator_);
                UriType ref = UriType(itr->value, allocator_).Resolve(scopeId, allocator_);
                RAPIDJSON_SCHEMA_PRINT(SchemaIds, id.GetString(), itr->value.GetString(), ref.GetString());
                // See if the resolved $ref minus the fragment matches a resolved id in this document
                // Search from the root. Returns the subschema in the document and its absolute JSON pointer.
                PointerType basePointer = PointerType();
                const ValueType *base = FindId(document, ref, basePointer, docId_, false);
                if (!base) {
                    // Remote reference - call the remote document provider
                    if (!remoteProvider_)
                        SchemaError(kSchemaErrorRefNoRemoteProvider, source);
                    else {
                        if (const GenericSchemaDocument* remoteDocument = remoteProvider_->GetRemoteDocument(ref, spec_)) {
                            const Ch* s = ref.GetFragString();
                            len = ref.GetFragStringLength();
                            if (len <= 1 || s[1] == '/') {
                                // JSON pointer fragment, absolute in the remote schema
                                const PointerType pointer(s, len, allocator_);
                                if (!pointer.IsValid())
                                    SchemaErrorPointer(kSchemaErrorRefPointerInvalid, source, s, len, pointer);
                                else {
                                    // Get the subschema
                                    if (const SchemaType *sc = remoteDocument->GetSchema(pointer)) {
                                        if (schema)
                                            *schema = sc;
                                        AddSchemaRefs(const_cast<SchemaType *>(sc));
                                        return true;
                                    } else
                                        SchemaErrorValue(kSchemaErrorRefUnknown, source, ref.GetString(), ref.GetStringLength());
                                }
                            } else
                                // Plain name fragment, not allowed in remote schema
                                SchemaErrorValue(kSchemaErrorRefPlainName, source, s, len);
                        } else
                          SchemaErrorValue(kSchemaErrorRefNoRemoteSchema, source, ref.GetString(), ref.GetStringLength());
                    }
                }
                else { // Local reference
                    const Ch* s = ref.GetFragString();
                    len = ref.GetFragStringLength();
                    if (len <= 1 || s[1] == '/') {
                        // JSON pointer fragment, relative to the resolved URI
                        const PointerType relPointer(s, len, allocator_);
                        if (!relPointer.IsValid())
                            SchemaErrorPointer(kSchemaErrorRefPointerInvalid, source, s, len, relPointer);
                        else {
                            // Get the subschema
                            if (const ValueType *pv = relPointer.Get(*base)) {
                                // Now get the absolute JSON pointer by adding relative to base
                                PointerType pointer(basePointer, allocator_);
                                for (SizeType i = 0; i < relPointer.GetTokenCount(); i++)
                                    pointer = pointer.Append(relPointer.GetTokens()[i], allocator_);
                                if (IsCyclicRef(pointer))
                                    SchemaErrorValue(kSchemaErrorRefCyclical, source, ref.GetString(), ref.GetStringLength());
                                else {
                                    // Call CreateSchema recursively, but first compute the in-scope id for the $ref target as we have jumped there
                                    // TODO: cache pointer <-> id mapping
                                    size_t unresolvedTokenIndex;
                                    scopeId = pointer.GetUri(document, docId_, &unresolvedTokenIndex, allocator_);
                                    CreateSchema(schema, pointer, *pv, document, scopeId);
                                    return true;
                                }
                            } else
                                SchemaErrorValue(kSchemaErrorRefUnknown, source, ref.GetString(), ref.GetStringLength());
                        }
                    } else {
                        // Plain name fragment, relative to the resolved URI
                        // Not supported in open api 2.0 and 3.0
                        PointerType pointer(allocator_);
                        if (spec_.oapi == kVersion20 || spec_.oapi == kVersion30)
                            SchemaErrorValue(kSchemaErrorRefPlainName, source, s, len);
                        // See if the fragment matches an id in this document.
                        // Search from the base we just established. Returns the subschema in the document and its absolute JSON pointer.
                        else if (const ValueType *pv = FindId(*base, ref, pointer, UriType(ref.GetBaseString(), ref.GetBaseStringLength(), allocator_), true, basePointer)) {
                            if (IsCyclicRef(pointer))
                                SchemaErrorValue(kSchemaErrorRefCyclical, source, ref.GetString(), ref.GetStringLength());
                            else {
                                // Call CreateSchema recursively, but first compute the in-scope id for the $ref target as we have jumped there
                                // TODO: cache pointer <-> id mapping
                                size_t unresolvedTokenIndex;
                                scopeId = pointer.GetUri(document, docId_, &unresolvedTokenIndex, allocator_);
                                CreateSchema(schema, pointer, *pv, document, scopeId);
                                return true;
                            }
                        } else
                            SchemaErrorValue(kSchemaErrorRefUnknown, source, ref.GetString(), ref.GetStringLength());
                    }
                }
            }
        }

        // Invalid/Unknown $ref
        if (schema)
            *schema = typeless_;
        AddSchemaRefs(typeless_);
        return true;
    }

    //! Find the first subschema with a resolved 'id' that matches the specified URI.
    // If full specified use all URI else ignore fragment.
    // If found, return a pointer to the subschema and its JSON pointer.
    // TODO cache pointer <-> id mapping
    ValueType* FindId(const ValueType& doc, const UriType& finduri, PointerType& resptr, const UriType& baseuri, bool full, const PointerType& here = PointerType()) const {
        SizeType i = 0;
        ValueType* resval = 0;
        UriType tempuri = UriType(finduri, allocator_);
        UriType localuri = UriType(baseuri, allocator_);
        if (doc.GetType() == kObjectType) {
            // Establish the base URI of this object
            typename ValueType::ConstMemberIterator m = doc.FindMember(SchemaType::GetIdString());
            if (m != doc.MemberEnd() && m->value.GetType() == kStringType) {
                localuri = UriType(m->value, allocator_).Resolve(baseuri, allocator_);
            }
            // See if it matches
            if (localuri.Match(finduri, full)) {
                RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaDocument::FindId (match)", full ? localuri.GetString() : localuri.GetBaseString());
                resval = const_cast<ValueType *>(&doc);
                resptr = here;
                return resval;
            }
            // No match, continue looking
            for (m = doc.MemberBegin(); m != doc.MemberEnd(); ++m) {
                if (m->value.GetType() == kObjectType || m->value.GetType() == kArrayType) {
                    resval = FindId(m->value, finduri, resptr, localuri, full, here.Append(m->name.GetString(), m->name.GetStringLength(), allocator_));
                }
                if (resval) break;
            }
        } else if (doc.GetType() == kArrayType) {
            // Continue looking
            for (typename ValueType::ConstValueIterator v = doc.Begin(); v != doc.End(); ++v) {
                if (v->GetType() == kObjectType || v->GetType() == kArrayType) {
                    resval = FindId(*v, finduri, resptr, localuri, full, here.Append(i, allocator_));
                }
                if (resval) break;
                i++;
            }
        }
        return resval;
    }

    // Added by PR #1393
    void AddSchemaRefs(SchemaType* schema) {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaDocument::AddSchemaRefs");
        while (!schemaRef_.Empty()) {
            SchemaRefPtr *ref = schemaRef_.template Pop<SchemaRefPtr>(1);
            SchemaEntry *entry = schemaMap_.template Push<SchemaEntry>();
            new (entry) SchemaEntry(**ref, schema, false, allocator_);
        }
    }

    // Added by PR #1393
    bool IsCyclicRef(const PointerType& pointer) const {
        for (const SchemaRefPtr* ref = schemaRef_.template Bottom<SchemaRefPtr>(); ref != schemaRef_.template End<SchemaRefPtr>(); ++ref)
            if (pointer == **ref)
                return true;
        return false;
    }

    const SchemaType* GetSchema(const PointerType& pointer) const {
        for (const SchemaEntry* target = schemaMap_.template Bottom<SchemaEntry>(); target != schemaMap_.template End<SchemaEntry>(); ++target)
            if (pointer == target->pointer)
                return target->schema;
        return 0;
    }

    PointerType GetPointer(const SchemaType* schema) const {
        for (const SchemaEntry* target = schemaMap_.template Bottom<SchemaEntry>(); target != schemaMap_.template End<SchemaEntry>(); ++target)
            if (schema == target->schema)
                return target->pointer;
        return PointerType();
    }

    const SchemaType* GetTypeless() const { return typeless_; }

    static const size_t kInitialSchemaMapSize = 64;
    static const size_t kInitialSchemaRefSize = 64;

    IRemoteSchemaDocumentProviderType* remoteProvider_;
    Allocator *allocator_;
    Allocator *ownAllocator_;
    const SchemaType* root_;                //!< Root schema.
    SchemaType* typeless_;
    internal::Stack<Allocator> schemaMap_;  // Stores created Pointer -> Schemas
    internal::Stack<Allocator> schemaRef_;  // Stores Pointer(s) from $ref(s) until resolved
    GValue uri_;                            // Schema document URI
    UriType docId_;
    Specification spec_;
    GValue error_;
    GValue currentError_;
};

//! GenericSchemaDocument using Value type.
typedef GenericSchemaDocument<Value> SchemaDocument;
//! IGenericRemoteSchemaDocumentProvider using SchemaDocument.
typedef IGenericRemoteSchemaDocumentProvider<SchemaDocument> IRemoteSchemaDocumentProvider;

///////////////////////////////////////////////////////////////////////////////
// GenericSchemaValidator

//! JSON Schema Validator.
/*!
    A SAX style JSON schema validator.
    It uses a \c GenericSchemaDocument to validate SAX events.
    It delegates the incoming SAX events to an output handler.
    The default output handler does nothing.
    It can be reused multiple times by calling \c Reset().

    \tparam SchemaDocumentType Type of schema document.
    \tparam OutputHandler Type of output handler. Default handler does nothing.
    \tparam StateAllocator Allocator for storing the internal validation states.
*/
template <
    typename SchemaDocumentType,
    typename OutputHandler = BaseReaderHandler<typename SchemaDocumentType::SchemaType::EncodingType>,
    typename StateAllocator = CrtAllocator>
class GenericSchemaValidator :
    public internal::ISchemaStateFactory<typename SchemaDocumentType::SchemaType>, 
    public internal::ISchemaValidator,
    public internal::IValidationErrorHandler<typename SchemaDocumentType::SchemaType> {
public:
    typedef typename SchemaDocumentType::SchemaType SchemaType;
    typedef typename SchemaDocumentType::PointerType PointerType;
    typedef typename SchemaType::EncodingType EncodingType;
    typedef typename SchemaType::SValue SValue;
    typedef typename EncodingType::Ch Ch;
    typedef GenericStringRef<Ch> StringRefType;
    typedef GenericValue<EncodingType, StateAllocator> ValueType;

    //! Constructor without output handler.
    /*!
        \param schemaDocument The schema document to conform to.
        \param allocator Optional allocator for storing internal validation states.
        \param schemaStackCapacity Optional initial capacity of schema path stack.
        \param documentStackCapacity Optional initial capacity of document path stack.
    */
    GenericSchemaValidator(
        const SchemaDocumentType& schemaDocument,
        StateAllocator* allocator = 0, 
        size_t schemaStackCapacity = kDefaultSchemaStackCapacity,
        size_t documentStackCapacity = kDefaultDocumentStackCapacity)
        :
        schemaDocument_(&schemaDocument),
        root_(schemaDocument.GetRoot()),
        stateAllocator_(allocator),
        ownStateAllocator_(0),
        schemaStack_(allocator, schemaStackCapacity),
        documentStack_(allocator, documentStackCapacity),
        outputHandler_(0),
        error_(kObjectType),
        currentError_(),
        missingDependents_(),
        valid_(true),
        flags_(kValidateDefaultFlags),
        depth_(0)
    {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::GenericSchemaValidator");
    }

    //! Constructor with output handler.
    /*!
        \param schemaDocument The schema document to conform to.
        \param allocator Optional allocator for storing internal validation states.
        \param schemaStackCapacity Optional initial capacity of schema path stack.
        \param documentStackCapacity Optional initial capacity of document path stack.
    */
    GenericSchemaValidator(
        const SchemaDocumentType& schemaDocument,
        OutputHandler& outputHandler,
        StateAllocator* allocator = 0, 
        size_t schemaStackCapacity = kDefaultSchemaStackCapacity,
        size_t documentStackCapacity = kDefaultDocumentStackCapacity)
        :
        schemaDocument_(&schemaDocument),
        root_(schemaDocument.GetRoot()),
        stateAllocator_(allocator),
        ownStateAllocator_(0),
        schemaStack_(allocator, schemaStackCapacity),
        documentStack_(allocator, documentStackCapacity),
        outputHandler_(&outputHandler),
        error_(kObjectType),
        currentError_(),
        missingDependents_(),
        valid_(true),
        flags_(kValidateDefaultFlags),
        depth_(0)
    {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::GenericSchemaValidator (output handler)");
    }

    //! Destructor.
    ~GenericSchemaValidator() {
        Reset();
        RAPIDJSON_DELETE(ownStateAllocator_);
    }

    //! Reset the internal states.
    void Reset() {
        while (!schemaStack_.Empty())
            PopSchema();
        documentStack_.Clear();
        ResetError();
    }

    //! Reset the error state.
    void ResetError() {
        error_.SetObject();
        currentError_.SetNull();
        missingDependents_.SetNull();
        valid_ = true;
    }

    //! Implementation of ISchemaValidator
    void SetValidateFlags(unsigned flags) {
        flags_ = flags;
    }
    virtual unsigned GetValidateFlags() const {
        return flags_;
    }

    virtual bool IsValid() const {
        if (!valid_) return false;
        if (GetContinueOnErrors() && !error_.ObjectEmpty()) return false;
        return true;
    }
    //! End of Implementation of ISchemaValidator

    //! Gets the error object.
    ValueType& GetError() { return error_; }
    const ValueType& GetError() const { return error_; }

    //! Gets the JSON pointer pointed to the invalid schema.
    //  If reporting all errors, the stack will be empty.
    PointerType GetInvalidSchemaPointer() const {
        return schemaStack_.Empty() ? PointerType() : CurrentSchema().GetPointer();
    }

    //! Gets the keyword of invalid schema.
    //  If reporting all errors, the stack will be empty, so return "errors".
    const Ch* GetInvalidSchemaKeyword() const {
        if (!schemaStack_.Empty()) return CurrentContext().invalidKeyword;
        if (GetContinueOnErrors() && !error_.ObjectEmpty()) return static_cast<const Ch*>(GetErrorsString());
        return 0;
    }

    //! Gets the error code of invalid schema.
    //  If reporting all errors, the stack will be empty, so return kValidateErrors.
    ValidateErrorCode GetInvalidSchemaCode() const {
        if (!schemaStack_.Empty()) return CurrentContext().invalidCode;
        if (GetContinueOnErrors() && !error_.ObjectEmpty()) return kValidateErrors;
        return kValidateErrorNone;
    }

    //! Gets the JSON pointer pointed to the invalid value.
    //  If reporting all errors, the stack will be empty.
    PointerType GetInvalidDocumentPointer() const {
        if (documentStack_.Empty()) {
            return PointerType();
        }
        else {
            return PointerType(documentStack_.template Bottom<Ch>(), documentStack_.GetSize() / sizeof(Ch));
        }
    }

    void NotMultipleOf(int64_t actual, const SValue& expected) {
        AddNumberError(kValidateErrorMultipleOf, ValueType(actual).Move(), expected);
    }
    void NotMultipleOf(uint64_t actual, const SValue& expected) {
        AddNumberError(kValidateErrorMultipleOf, ValueType(actual).Move(), expected);
    }
    void NotMultipleOf(double actual, const SValue& expected) {
        AddNumberError(kValidateErrorMultipleOf, ValueType(actual).Move(), expected);
    }
    void AboveMaximum(int64_t actual, const SValue& expected, bool exclusive) {
        AddNumberError(exclusive ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum, ValueType(actual).Move(), expected,
            exclusive ? &SchemaType::GetExclusiveMaximumString : 0);
    }
    void AboveMaximum(uint64_t actual, const SValue& expected, bool exclusive) {
        AddNumberError(exclusive ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum, ValueType(actual).Move(), expected,
            exclusive ? &SchemaType::GetExclusiveMaximumString : 0);
    }
    void AboveMaximum(double actual, const SValue& expected, bool exclusive) {
        AddNumberError(exclusive ? kValidateErrorExclusiveMaximum : kValidateErrorMaximum, ValueType(actual).Move(), expected,
            exclusive ? &SchemaType::GetExclusiveMaximumString : 0);
    }
    void BelowMinimum(int64_t actual, const SValue& expected, bool exclusive) {
        AddNumberError(exclusive ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum, ValueType(actual).Move(), expected,
            exclusive ? &SchemaType::GetExclusiveMinimumString : 0);
    }
    void BelowMinimum(uint64_t actual, const SValue& expected, bool exclusive) {
        AddNumberError(exclusive ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum, ValueType(actual).Move(), expected,
            exclusive ? &SchemaType::GetExclusiveMinimumString : 0);
    }
    void BelowMinimum(double actual, const SValue& expected, bool exclusive) {
        AddNumberError(exclusive ? kValidateErrorExclusiveMinimum : kValidateErrorMinimum, ValueType(actual).Move(), expected,
            exclusive ? &SchemaType::GetExclusiveMinimumString : 0);
    }

    void TooLong(const Ch* str, SizeType length, SizeType expected) {
        AddNumberError(kValidateErrorMaxLength,
            ValueType(str, length, GetStateAllocator()).Move(), SValue(expected).Move());
    }
    void TooShort(const Ch* str, SizeType length, SizeType expected) {
        AddNumberError(kValidateErrorMinLength,
            ValueType(str, length, GetStateAllocator()).Move(), SValue(expected).Move());
    }
    void DoesNotMatch(const Ch* str, SizeType length) {
        currentError_.SetObject();
        currentError_.AddMember(GetActualString(), ValueType(str, length, GetStateAllocator()).Move(), GetStateAllocator());
        AddCurrentError(kValidateErrorPattern);
    }

    void DisallowedItem(SizeType index) {
        currentError_.SetObject();
        currentError_.AddMember(GetDisallowedString(), ValueType(index).Move(), GetStateAllocator());
        AddCurrentError(kValidateErrorAdditionalItems, true);
    }
    void TooFewItems(SizeType actualCount, SizeType expectedCount) {
        AddNumberError(kValidateErrorMinItems,
            ValueType(actualCount).Move(), SValue(expectedCount).Move());
    }
    void TooManyItems(SizeType actualCount, SizeType expectedCount) {
        AddNumberError(kValidateErrorMaxItems,
            ValueType(actualCount).Move(), SValue(expectedCount).Move());
    }
    void DuplicateItems(SizeType index1, SizeType index2) {
        ValueType duplicates(kArrayType);
        duplicates.PushBack(index1, GetStateAllocator());
        duplicates.PushBack(index2, GetStateAllocator());
        currentError_.SetObject();
        currentError_.AddMember(GetDuplicatesString(), duplicates, GetStateAllocator());
        AddCurrentError(kValidateErrorUniqueItems, true);
    }

    void TooManyProperties(SizeType actualCount, SizeType expectedCount) {
        AddNumberError(kValidateErrorMaxProperties,
            ValueType(actualCount).Move(), SValue(expectedCount).Move());
    }
    void TooFewProperties(SizeType actualCount, SizeType expectedCount) {
        AddNumberError(kValidateErrorMinProperties,
            ValueType(actualCount).Move(), SValue(expectedCount).Move());
    }
    void StartMissingProperties() {
        currentError_.SetArray();
    }
    void AddMissingProperty(const SValue& name) {
        currentError_.PushBack(ValueType(name, GetStateAllocator()).Move(), GetStateAllocator());
    }
    bool EndMissingProperties() {
        if (currentError_.Empty())
            return false;
        ValueType error(kObjectType);
        error.AddMember(GetMissingString(), currentError_, GetStateAllocator());
        currentError_ = error;
        AddCurrentError(kValidateErrorRequired);
        return true;
    }
    void PropertyViolations(ISchemaValidator** subvalidators, SizeType count) {
        for (SizeType i = 0; i < count; ++i)
            MergeError(static_cast<GenericSchemaValidator*>(subvalidators[i])->GetError());
    }
    void DisallowedProperty(const Ch* name, SizeType length) {
        currentError_.SetObject();
        currentError_.AddMember(GetDisallowedString(), ValueType(name, length, GetStateAllocator()).Move(), GetStateAllocator());
        AddCurrentError(kValidateErrorAdditionalProperties, true);
    }

    void StartDependencyErrors() {
        currentError_.SetObject();
    }
    void StartMissingDependentProperties() {
        missingDependents_.SetArray();
    }
    void AddMissingDependentProperty(const SValue& targetName) {
        missingDependents_.PushBack(ValueType(targetName, GetStateAllocator()).Move(), GetStateAllocator());
    }
    void EndMissingDependentProperties(const SValue& sourceName) {
        if (!missingDependents_.Empty()) {
            // Create equivalent 'required' error
            ValueType error(kObjectType);
            ValidateErrorCode code = kValidateErrorRequired;
            error.AddMember(GetMissingString(), missingDependents_.Move(), GetStateAllocator());
            AddErrorCode(error, code);
            AddErrorInstanceLocation(error, false);
            // When appending to a pointer ensure its allocator is used
            PointerType schemaRef = GetInvalidSchemaPointer().Append(SchemaType::GetValidateErrorKeyword(kValidateErrorDependencies), &GetInvalidSchemaPointer().GetAllocator());
            AddErrorSchemaLocation(error, schemaRef.Append(sourceName.GetString(), sourceName.GetStringLength(), &GetInvalidSchemaPointer().GetAllocator()));
            ValueType wrapper(kObjectType);
            wrapper.AddMember(ValueType(SchemaType::GetValidateErrorKeyword(code), GetStateAllocator()).Move(), error, GetStateAllocator());
            currentError_.AddMember(ValueType(sourceName, GetStateAllocator()).Move(), wrapper, GetStateAllocator());
        }
    }
    void AddDependencySchemaError(const SValue& sourceName, ISchemaValidator* subvalidator) {
        currentError_.AddMember(ValueType(sourceName, GetStateAllocator()).Move(),
            static_cast<GenericSchemaValidator*>(subvalidator)->GetError(), GetStateAllocator());
    }
    bool EndDependencyErrors() {
        if (currentError_.ObjectEmpty())
            return false;
        ValueType error(kObjectType);
        error.AddMember(GetErrorsString(), currentError_, GetStateAllocator());
        currentError_ = error;
        AddCurrentError(kValidateErrorDependencies);
        return true;
    }

    void DisallowedValue(const ValidateErrorCode code = kValidateErrorEnum) {
        currentError_.SetObject();
        AddCurrentError(code);
    }
    void StartDisallowedType() {
        currentError_.SetArray();
    }
    void AddExpectedType(const typename SchemaType::ValueType& expectedType) {
        currentError_.PushBack(ValueType(expectedType, GetStateAllocator()).Move(), GetStateAllocator());
    }
    void EndDisallowedType(const typename SchemaType::ValueType& actualType) {
        ValueType error(kObjectType);
        error.AddMember(GetExpectedString(), currentError_, GetStateAllocator());
        error.AddMember(GetActualString(), ValueType(actualType, GetStateAllocator()).Move(), GetStateAllocator());
        currentError_ = error;
        AddCurrentError(kValidateErrorType);
    }
    void NotAllOf(ISchemaValidator** subvalidators, SizeType count) {
        // Treat allOf like oneOf and anyOf to match https://rapidjson.org/md_doc_schema.html#allOf-anyOf-oneOf
        AddErrorArray(kValidateErrorAllOf, subvalidators, count);
        //for (SizeType i = 0; i < count; ++i) {
        //    MergeError(static_cast<GenericSchemaValidator*>(subvalidators[i])->GetError());
        //}
    }
    void NoneOf(ISchemaValidator** subvalidators, SizeType count) {
        AddErrorArray(kValidateErrorAnyOf, subvalidators, count);
    }
    void NotOneOf(ISchemaValidator** subvalidators, SizeType count) {
        AddErrorArray(kValidateErrorOneOf, subvalidators, count);
    }
    void MultipleOneOf(SizeType index1, SizeType index2) {
        ValueType matches(kArrayType);
        matches.PushBack(index1, GetStateAllocator());
        matches.PushBack(index2, GetStateAllocator());
        currentError_.SetObject();
        currentError_.AddMember(GetMatchesString(), matches, GetStateAllocator());
        AddCurrentError(kValidateErrorOneOfMatch);
    }
    void Disallowed() {
        currentError_.SetObject();
        AddCurrentError(kValidateErrorNot);
    }
    void DisallowedWhenWriting() {
        currentError_.SetObject();
        AddCurrentError(kValidateErrorReadOnly);
    }
    void DisallowedWhenReading() {
        currentError_.SetObject();
        AddCurrentError(kValidateErrorWriteOnly);
    }

#define RAPIDJSON_STRING_(name, ...) \
    static const StringRefType& Get##name##String() {\
        static const Ch s[] = { __VA_ARGS__, '\0' };\
        static const StringRefType v(s, static_cast<SizeType>(sizeof(s) / sizeof(Ch) - 1)); \
        return v;\
    }

    RAPIDJSON_STRING_(InstanceRef, 'i', 'n', 's', 't', 'a', 'n', 'c', 'e', 'R', 'e', 'f')
    RAPIDJSON_STRING_(SchemaRef, 's', 'c', 'h', 'e', 'm', 'a', 'R', 'e', 'f')
    RAPIDJSON_STRING_(Expected, 'e', 'x', 'p', 'e', 'c', 't', 'e', 'd')
    RAPIDJSON_STRING_(Actual, 'a', 'c', 't', 'u', 'a', 'l')
    RAPIDJSON_STRING_(Disallowed, 'd', 'i', 's', 'a', 'l', 'l', 'o', 'w', 'e', 'd')
    RAPIDJSON_STRING_(Missing, 'm', 'i', 's', 's', 'i', 'n', 'g')
    RAPIDJSON_STRING_(Errors, 'e', 'r', 'r', 'o', 'r', 's')
    RAPIDJSON_STRING_(ErrorCode, 'e', 'r', 'r', 'o', 'r', 'C', 'o', 'd', 'e')
    RAPIDJSON_STRING_(ErrorMessage, 'e', 'r', 'r', 'o', 'r', 'M', 'e', 's', 's', 'a', 'g', 'e')
    RAPIDJSON_STRING_(Duplicates, 'd', 'u', 'p', 'l', 'i', 'c', 'a', 't', 'e', 's')
    RAPIDJSON_STRING_(Matches, 'm', 'a', 't', 'c', 'h', 'e', 's')

#undef RAPIDJSON_STRING_

#define RAPIDJSON_SCHEMA_HANDLE_BEGIN_(method, arg1)\
    if (!valid_) return false; \
    if ((!BeginValue() && !GetContinueOnErrors()) || (!CurrentSchema().method arg1 && !GetContinueOnErrors())) {\
        *documentStack_.template Push<Ch>() = '\0';\
        documentStack_.template Pop<Ch>(1);\
        RAPIDJSON_SCHEMA_PRINT(InvalidDocument, documentStack_.template Bottom<Ch>());\
        valid_ = false;\
        return valid_;\
    }

#define RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(method, arg2)\
    for (Context* context = schemaStack_.template Bottom<Context>(); context != schemaStack_.template End<Context>(); context++) {\
        if (context->hasher)\
            static_cast<HasherType*>(context->hasher)->method arg2;\
        if (context->validators)\
            for (SizeType i_ = 0; i_ < context->validatorCount; i_++)\
                static_cast<GenericSchemaValidator*>(context->validators[i_])->method arg2;\
        if (context->patternPropertiesValidators)\
            for (SizeType i_ = 0; i_ < context->patternPropertiesValidatorCount; i_++)\
                static_cast<GenericSchemaValidator*>(context->patternPropertiesValidators[i_])->method arg2;\
    }

#define RAPIDJSON_SCHEMA_HANDLE_END_(method, arg2)\
    valid_ = (EndValue() || GetContinueOnErrors()) && (!outputHandler_ || outputHandler_->method arg2);\
    return valid_;

#define RAPIDJSON_SCHEMA_HANDLE_VALUE_(method, arg1, arg2) \
    RAPIDJSON_SCHEMA_HANDLE_BEGIN_   (method, arg1);\
    RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(method, arg2);\
    RAPIDJSON_SCHEMA_HANDLE_END_     (method, arg2)

    bool Null()             { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Null,   (CurrentContext()), ( )); }
    bool Bool(bool b)       { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Bool,   (CurrentContext(), b), (b)); }
    bool Int(int i)         { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Int,    (CurrentContext(), i), (i)); }
    bool Uint(unsigned u)   { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Uint,   (CurrentContext(), u), (u)); }
    bool Int64(int64_t i)   { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Int64,  (CurrentContext(), i), (i)); }
    bool Uint64(uint64_t u) { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Uint64, (CurrentContext(), u), (u)); }
    bool Double(double d)   { RAPIDJSON_SCHEMA_HANDLE_VALUE_(Double, (CurrentContext(), d), (d)); }
    bool RawNumber(const Ch* str, SizeType length, bool copy)
                                    { RAPIDJSON_SCHEMA_HANDLE_VALUE_(String, (CurrentContext(), str, length, copy), (str, length, copy)); }
    bool String(const Ch* str, SizeType length, bool copy)
                                    { RAPIDJSON_SCHEMA_HANDLE_VALUE_(String, (CurrentContext(), str, length, copy), (str, length, copy)); }

    bool StartObject() {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::StartObject");
        RAPIDJSON_SCHEMA_HANDLE_BEGIN_(StartObject, (CurrentContext()));
        RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(StartObject, ());
        valid_ = !outputHandler_ || outputHandler_->StartObject();
        return valid_;
    }
    
    bool Key(const Ch* str, SizeType len, bool copy) {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::Key", str);
        if (!valid_) return false;
        AppendToken(str, len);
        if (!CurrentSchema().Key(CurrentContext(), str, len, copy) && !GetContinueOnErrors()) {
            valid_ = false;
            return valid_;
        }
        RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(Key, (str, len, copy));
        valid_ = !outputHandler_ || outputHandler_->Key(str, len, copy);
        return valid_;
    }
    
    bool EndObject(SizeType memberCount) {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::EndObject");
        if (!valid_) return false;
        RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(EndObject, (memberCount));
        if (!CurrentSchema().EndObject(CurrentContext(), memberCount) && !GetContinueOnErrors()) { 
            valid_ = false; 
            return valid_; 
        }
        RAPIDJSON_SCHEMA_HANDLE_END_(EndObject, (memberCount));
    }

    bool StartArray() {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::StartArray");
        RAPIDJSON_SCHEMA_HANDLE_BEGIN_(StartArray, (CurrentContext()));
        RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(StartArray, ());
        valid_ = !outputHandler_ || outputHandler_->StartArray();
        return valid_;
    }
    
    bool EndArray(SizeType elementCount) {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::EndArray");
        if (!valid_) return false;
        RAPIDJSON_SCHEMA_HANDLE_PARALLEL_(EndArray, (elementCount));
        if (!CurrentSchema().EndArray(CurrentContext(), elementCount) && !GetContinueOnErrors()) {
            valid_ = false;
            return valid_;
        }
        RAPIDJSON_SCHEMA_HANDLE_END_(EndArray, (elementCount));
    }

#undef RAPIDJSON_SCHEMA_HANDLE_BEGIN_
#undef RAPIDJSON_SCHEMA_HANDLE_PARALLEL_
#undef RAPIDJSON_SCHEMA_HANDLE_VALUE_

    // Implementation of ISchemaStateFactory<SchemaType>
    virtual ISchemaValidator* CreateSchemaValidator(const SchemaType& root, const bool inheritContinueOnErrors) {
        *documentStack_.template Push<Ch>() = '\0';
        documentStack_.template Pop<Ch>(1);
        ISchemaValidator* sv = new (GetStateAllocator().Malloc(sizeof(GenericSchemaValidator))) GenericSchemaValidator(*schemaDocument_, root, documentStack_.template Bottom<char>(), documentStack_.GetSize(),
        depth_ + 1,
        &GetStateAllocator());
        sv->SetValidateFlags(inheritContinueOnErrors ? GetValidateFlags() : GetValidateFlags() & ~static_cast<unsigned>(kValidateContinueOnErrorFlag));
        return sv;
    }

    virtual void DestroySchemaValidator(ISchemaValidator* validator) {
        GenericSchemaValidator* v = static_cast<GenericSchemaValidator*>(validator);
        v->~GenericSchemaValidator();
        StateAllocator::Free(v);
    }

    virtual void* CreateHasher() {
        return new (GetStateAllocator().Malloc(sizeof(HasherType))) HasherType(&GetStateAllocator());
    }

    virtual uint64_t GetHashCode(void* hasher) {
        return static_cast<HasherType*>(hasher)->GetHashCode();
    }

    virtual void DestroryHasher(void* hasher) {
        HasherType* h = static_cast<HasherType*>(hasher);
        h->~HasherType();
        StateAllocator::Free(h);
    }

    virtual void* MallocState(size_t size) {
        return GetStateAllocator().Malloc(size);
    }

    virtual void FreeState(void* p) {
        StateAllocator::Free(p);
    }
    // End of implementation of ISchemaStateFactory<SchemaType>

private:
    typedef typename SchemaType::Context Context;
    typedef GenericValue<UTF8<>, StateAllocator> HashCodeArray;
    typedef internal::Hasher<EncodingType, StateAllocator> HasherType;

    GenericSchemaValidator( 
        const SchemaDocumentType& schemaDocument,
        const SchemaType& root,
        const char* basePath, size_t basePathSize,
        unsigned depth,
        StateAllocator* allocator = 0,
        size_t schemaStackCapacity = kDefaultSchemaStackCapacity,
        size_t documentStackCapacity = kDefaultDocumentStackCapacity)
        :
        schemaDocument_(&schemaDocument),
        root_(root),
        stateAllocator_(allocator),
        ownStateAllocator_(0),
        schemaStack_(allocator, schemaStackCapacity),
        documentStack_(allocator, documentStackCapacity),
        outputHandler_(0),
        error_(kObjectType),
        currentError_(),
        missingDependents_(),
        valid_(true),
        flags_(kValidateDefaultFlags),
        depth_(depth)
    {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::GenericSchemaValidator (internal)", basePath && basePathSize ? basePath : "");
        if (basePath && basePathSize)
            memcpy(documentStack_.template Push<char>(basePathSize), basePath, basePathSize);
    }

    StateAllocator& GetStateAllocator() {
        if (!stateAllocator_)
            stateAllocator_ = ownStateAllocator_ = RAPIDJSON_NEW(StateAllocator)();
        return *stateAllocator_;
    }

    bool GetContinueOnErrors() const {
        return flags_ & kValidateContinueOnErrorFlag;
    }

    bool BeginValue() {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::BeginValue");
        if (schemaStack_.Empty())
            PushSchema(root_);
        else {
            if (CurrentContext().inArray)
                internal::TokenHelper<internal::Stack<StateAllocator>, Ch>::AppendIndexToken(documentStack_, CurrentContext().arrayElementIndex);

            if (!CurrentSchema().BeginValue(CurrentContext()) && !GetContinueOnErrors())
                return false;

            SizeType count = CurrentContext().patternPropertiesSchemaCount;
            const SchemaType** sa = CurrentContext().patternPropertiesSchemas;
            typename Context::PatternValidatorType patternValidatorType = CurrentContext().valuePatternValidatorType;
            bool valueUniqueness = CurrentContext().valueUniqueness;
            RAPIDJSON_ASSERT(CurrentContext().valueSchema);
            PushSchema(*CurrentContext().valueSchema);

            if (count > 0) {
                CurrentContext().objectPatternValidatorType = patternValidatorType;
                ISchemaValidator**& va = CurrentContext().patternPropertiesValidators;
                SizeType& validatorCount = CurrentContext().patternPropertiesValidatorCount;
                va = static_cast<ISchemaValidator**>(MallocState(sizeof(ISchemaValidator*) * count));
                std::memset(va, 0, sizeof(ISchemaValidator*) * count);
                for (SizeType i = 0; i < count; i++)
                    va[validatorCount++] = CreateSchemaValidator(*sa[i], true);  // Inherit continueOnError
            }

            CurrentContext().arrayUniqueness = valueUniqueness;
        }
        return true;
    }

    bool EndValue() {
        RAPIDJSON_SCHEMA_PRINT(Method, "GenericSchemaValidator::EndValue");
        if (!CurrentSchema().EndValue(CurrentContext()) && !GetContinueOnErrors())
            return false;

        GenericStringBuffer<EncodingType> sb;
        schemaDocument_->GetPointer(&CurrentSchema()).StringifyUriFragment(sb);
        *documentStack_.template Push<Ch>() = '\0';
        documentStack_.template Pop<Ch>(1);
        RAPIDJSON_SCHEMA_PRINT(ValidatorPointers, sb.GetString(), documentStack_.template Bottom<Ch>(), depth_);
        void* hasher = CurrentContext().hasher;
        uint64_t h = hasher && CurrentContext().arrayUniqueness ? static_cast<HasherType*>(hasher)->GetHashCode() : 0;
        
        PopSchema();

        if (!schemaStack_.Empty()) {
            Context& context = CurrentContext();
            // Only check uniqueness if there is a hasher
            if (hasher && context.valueUniqueness) {
                HashCodeArray* a = static_cast<HashCodeArray*>(context.arrayElementHashCodes);
                if (!a)
                    CurrentContext().arrayElementHashCodes = a = new (GetStateAllocator().Malloc(sizeof(HashCodeArray))) HashCodeArray(kArrayType);
                for (typename HashCodeArray::ConstValueIterator itr = a->Begin(); itr != a->End(); ++itr)
                    if (itr->GetUint64() == h) {
                        DuplicateItems(static_cast<SizeType>(itr - a->Begin()), a->Size());
                        // Cleanup before returning if continuing
                        if (GetContinueOnErrors()) {
                            a->PushBack(h, GetStateAllocator());
                            while (!documentStack_.Empty() && *documentStack_.template Pop<Ch>(1) != '/');
                        }
                        RAPIDJSON_INVALID_KEYWORD_RETURN(kValidateErrorUniqueItems);
                    }
                a->PushBack(h, GetStateAllocator());
            }
        }

        // Remove the last token of document pointer
        while (!documentStack_.Empty() && *documentStack_.template Pop<Ch>(1) != '/')
            ;

        return true;
    }

    void AppendToken(const Ch* str, SizeType len) {
        documentStack_.template Reserve<Ch>(1 + len * 2); // worst case all characters are escaped as two characters
        *documentStack_.template PushUnsafe<Ch>() = '/';
        for (SizeType i = 0; i < len; i++) {
            if (str[i] == '~') {
                *documentStack_.template PushUnsafe<Ch>() = '~';
                *documentStack_.template PushUnsafe<Ch>() = '0';
            }
            else if (str[i] == '/') {
                *documentStack_.template PushUnsafe<Ch>() = '~';
                *documentStack_.template PushUnsafe<Ch>() = '1';
            }
            else
                *documentStack_.template PushUnsafe<Ch>() = str[i];
        }
    }

    RAPIDJSON_FORCEINLINE void PushSchema(const SchemaType& schema) { new (schemaStack_.template Push<Context>()) Context(*this, *this, &schema, flags_); }
    
    RAPIDJSON_FORCEINLINE void PopSchema() {
        Context* c = schemaStack_.template Pop<Context>(1);
        if (HashCodeArray* a = static_cast<HashCodeArray*>(c->arrayElementHashCodes)) {
            a->~HashCodeArray();
            StateAllocator::Free(a);
        }
        c->~Context();
    }

    void AddErrorInstanceLocation(ValueType& result, bool parent) {
        GenericStringBuffer<EncodingType> sb;
        PointerType instancePointer = GetInvalidDocumentPointer();
        ((parent && instancePointer.GetTokenCount() > 0)
         ? PointerType(instancePointer.GetTokens(), instancePointer.GetTokenCount() - 1)
         : instancePointer).StringifyUriFragment(sb);
        ValueType instanceRef(sb.GetString(), static_cast<SizeType>(sb.GetSize() / sizeof(Ch)),
                              GetStateAllocator());
        result.AddMember(GetInstanceRefString(), instanceRef, GetStateAllocator());
    }

    void AddErrorSchemaLocation(ValueType& result, PointerType schema = PointerType()) {
        GenericStringBuffer<EncodingType> sb;
        SizeType len = CurrentSchema().GetURI().GetStringLength();
        if (len) memcpy(sb.Push(len), CurrentSchema().GetURI().GetString(), len * sizeof(Ch));
        if (schema.GetTokenCount()) schema.StringifyUriFragment(sb);
        else GetInvalidSchemaPointer().StringifyUriFragment(sb);
        ValueType schemaRef(sb.GetString(), static_cast<SizeType>(sb.GetSize() / sizeof(Ch)),
            GetStateAllocator());
        result.AddMember(GetSchemaRefString(), schemaRef, GetStateAllocator());
    }

    void AddErrorCode(ValueType& result, const ValidateErrorCode code) {
        result.AddMember(GetErrorCodeString(), code, GetStateAllocator());
    }

    void AddError(ValueType& keyword, ValueType& error) {
        typename ValueType::MemberIterator member = error_.FindMember(keyword);
        if (member == error_.MemberEnd())
            error_.AddMember(keyword, error, GetStateAllocator());
        else {
            if (member->value.IsObject()) {
                ValueType errors(kArrayType);
                errors.PushBack(member->value, GetStateAllocator());
                member->value = errors;
            }
            member->value.PushBack(error, GetStateAllocator());
        }
    }

    void AddCurrentError(const ValidateErrorCode code, bool parent = false) {
        AddErrorCode(currentError_, code);
        AddErrorInstanceLocation(currentError_, parent);
        AddErrorSchemaLocation(currentError_);
        AddError(ValueType(SchemaType::GetValidateErrorKeyword(code), GetStateAllocator(), false).Move(), currentError_);
    }

    void MergeError(ValueType& other) {
        for (typename ValueType::MemberIterator it = other.MemberBegin(), end = other.MemberEnd(); it != end; ++it) {
            AddError(it->name, it->value);
        }
    }

    void AddNumberError(const ValidateErrorCode code, ValueType& actual, const SValue& expected,
        const typename SchemaType::ValueType& (*exclusive)() = 0) {
        currentError_.SetObject();
        currentError_.AddMember(GetActualString(), actual, GetStateAllocator());
        currentError_.AddMember(GetExpectedString(), ValueType(expected, GetStateAllocator()).Move(), GetStateAllocator());
        if (exclusive)
            currentError_.AddMember(ValueType(exclusive(), GetStateAllocator()).Move(), true, GetStateAllocator());
        AddCurrentError(code);
    }

    void AddErrorArray(const ValidateErrorCode code,
        ISchemaValidator** subvalidators, SizeType count) {
        ValueType errors(kArrayType);
        for (SizeType i = 0; i < count; ++i)
            errors.PushBack(static_cast<GenericSchemaValidator*>(subvalidators[i])->GetError(), GetStateAllocator());
        currentError_.SetObject();
        currentError_.AddMember(GetErrorsString(), errors, GetStateAllocator());
        AddCurrentError(code);
    }

    const SchemaType& CurrentSchema() const { return *schemaStack_.template Top<Context>()->schema; }
    Context& CurrentContext() { return *schemaStack_.template Top<Context>(); }
    const Context& CurrentContext() const { return *schemaStack_.template Top<Context>(); }

    static const size_t kDefaultSchemaStackCapacity = 1024;
    static const size_t kDefaultDocumentStackCapacity = 256;
    const SchemaDocumentType* schemaDocument_;
    const SchemaType& root_;
    StateAllocator* stateAllocator_;
    StateAllocator* ownStateAllocator_;
    internal::Stack<StateAllocator> schemaStack_;    //!< stack to store the current path of schema (BaseSchemaType *)
    internal::Stack<StateAllocator> documentStack_;  //!< stack to store the current path of validating document (Ch)
    OutputHandler* outputHandler_;
    ValueType error_;
    ValueType currentError_;
    ValueType missingDependents_;
    bool valid_;
    unsigned flags_;
    unsigned depth_;
};

typedef GenericSchemaValidator<SchemaDocument> SchemaValidator;

///////////////////////////////////////////////////////////////////////////////
// SchemaValidatingReader

//! A helper class for parsing with validation.
/*!
    This helper class is a functor, designed as a parameter of \ref GenericDocument::Populate().

    \tparam parseFlags Combination of \ref ParseFlag.
    \tparam InputStream Type of input stream, implementing Stream concept.
    \tparam SourceEncoding Encoding of the input stream.
    \tparam SchemaDocumentType Type of schema document.
    \tparam StackAllocator Allocator type for stack.
*/
template <
    unsigned parseFlags,
    typename InputStream,
    typename SourceEncoding,
    typename SchemaDocumentType = SchemaDocument,
    typename StackAllocator = CrtAllocator>
class SchemaValidatingReader {
public:
    typedef typename SchemaDocumentType::PointerType PointerType;
    typedef typename InputStream::Ch Ch;
    typedef GenericValue<SourceEncoding, StackAllocator> ValueType;

    //! Constructor
    /*!
        \param is Input stream.
        \param sd Schema document.
    */
    SchemaValidatingReader(InputStream& is, const SchemaDocumentType& sd) : is_(is), sd_(sd), invalidSchemaKeyword_(), invalidSchemaCode_(kValidateErrorNone), error_(kObjectType), isValid_(true) {}

    template <typename Handler>
    bool operator()(Handler& handler) {
        GenericReader<SourceEncoding, typename SchemaDocumentType::EncodingType, StackAllocator> reader;
        GenericSchemaValidator<SchemaDocumentType, Handler> validator(sd_, handler);
        parseResult_ = reader.template Parse<parseFlags>(is_, validator);

        isValid_ = validator.IsValid();
        if (isValid_) {
            invalidSchemaPointer_ = PointerType();
            invalidSchemaKeyword_ = 0;
            invalidDocumentPointer_ = PointerType();
            error_.SetObject();
        }
        else {
            invalidSchemaPointer_ = validator.GetInvalidSchemaPointer();
            invalidSchemaKeyword_ = validator.GetInvalidSchemaKeyword();
            invalidSchemaCode_ = validator.GetInvalidSchemaCode();
            invalidDocumentPointer_ = validator.GetInvalidDocumentPointer();
            error_.CopyFrom(validator.GetError(), allocator_);
        }

        return parseResult_;
    }

    const ParseResult& GetParseResult() const { return parseResult_; }
    bool IsValid() const { return isValid_; }
    const PointerType& GetInvalidSchemaPointer() const { return invalidSchemaPointer_; }
    const Ch* GetInvalidSchemaKeyword() const { return invalidSchemaKeyword_; }
    const PointerType& GetInvalidDocumentPointer() const { return invalidDocumentPointer_; }
    const ValueType& GetError() const { return error_; }
    ValidateErrorCode GetInvalidSchemaCode() const { return invalidSchemaCode_; }

private:
    InputStream& is_;
    const SchemaDocumentType& sd_;

    ParseResult parseResult_;
    PointerType invalidSchemaPointer_;
    const Ch* invalidSchemaKeyword_;
    PointerType invalidDocumentPointer_;
    ValidateErrorCode invalidSchemaCode_;
    StackAllocator allocator_;
    ValueType error_;
    bool isValid_;
};

RAPIDJSON_NAMESPACE_END
RAPIDJSON_DIAG_POP

#endif // RAPIDJSON_SCHEMA_H_

// End file:schema.h

