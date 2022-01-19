//  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//  SPDX-License-Identifier: MIT
//  RapidFuzz v0.0.1
//  Generated: 2022-01-19 18:30:47.704695
//  ----------------------------------------------------------
//  This file is an amalgamation of multiple different files.
//  You probably shouldn't edit it directly.
//  ----------------------------------------------------------
#ifndef RAPIDFUZZ_AMALGAMATED_HPP_INCLUDED
#define RAPIDFUZZ_AMALGAMATED_HPP_INCLUDED



#include <array>
#include <cmath>
#include <cstring>
#include <algorithm>


#include <algorithm>
#include <cstddef>
#include <type_traits>
#include <vector>

// Copyright 2017-2020 by Martin Moene
//
// string-view lite, a C++17-like string_view for C++98 and later.
// For more information see https://github.com/martinmoene/string-view-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef NONSTD_SV_LITE_H_INCLUDED
#    define NONSTD_SV_LITE_H_INCLUDED

#    define string_view_lite_MAJOR 1
#    define string_view_lite_MINOR 4
#    define string_view_lite_PATCH 0

#    define string_view_lite_VERSION                                                               \
        nssv_STRINGIFY(string_view_lite_MAJOR) "." nssv_STRINGIFY(                                 \
            string_view_lite_MINOR) "." nssv_STRINGIFY(string_view_lite_PATCH)

#    define nssv_STRINGIFY(x) nssv_STRINGIFY_(x)
#    define nssv_STRINGIFY_(x) #    x

// string-view lite configuration:

#    define nssv_STRING_VIEW_DEFAULT 0
#    define nssv_STRING_VIEW_NONSTD 1
#    define nssv_STRING_VIEW_STD 2

#    if !defined(nssv_CONFIG_SELECT_STRING_VIEW)
#        define nssv_CONFIG_SELECT_STRING_VIEW                                                     \
            (nssv_HAVE_STD_STRING_VIEW ? nssv_STRING_VIEW_STD : nssv_STRING_VIEW_NONSTD)
#    endif

#    if defined(nssv_CONFIG_SELECT_STD_STRING_VIEW) ||                                             \
        defined(nssv_CONFIG_SELECT_NONSTD_STRING_VIEW)
#        error nssv_CONFIG_SELECT_STD_STRING_VIEW and nssv_CONFIG_SELECT_NONSTD_STRING_VIEW are deprecated and removed, please use nssv_CONFIG_SELECT_STRING_VIEW=nssv_STRING_VIEW_...
#    endif

#    ifndef nssv_CONFIG_STD_SV_OPERATOR
#        define nssv_CONFIG_STD_SV_OPERATOR 0
#    endif

#    ifndef nssv_CONFIG_USR_SV_OPERATOR
#        define nssv_CONFIG_USR_SV_OPERATOR 1
#    endif

#    ifdef nssv_CONFIG_CONVERSION_STD_STRING
#        define nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS nssv_CONFIG_CONVERSION_STD_STRING
#        define nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS nssv_CONFIG_CONVERSION_STD_STRING
#    endif

#    ifndef nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
#        define nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS 1
#    endif

#    ifndef nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
#        define nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS 1
#    endif

// Control presence of exception handling (try and auto discover):

#    ifndef nssv_CONFIG_NO_EXCEPTIONS
#        if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)
#            define nssv_CONFIG_NO_EXCEPTIONS 0
#        else
#            define nssv_CONFIG_NO_EXCEPTIONS 1
#        endif
#    endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#    ifndef nssv_CPLUSPLUS
#        if defined(_MSVC_LANG) && !defined(__clang__)
#            define nssv_CPLUSPLUS (_MSC_VER == 1900 ? 201103L : _MSVC_LANG)
#        else
#            define nssv_CPLUSPLUS __cplusplus
#        endif
#    endif

#    define nssv_CPP98_OR_GREATER (nssv_CPLUSPLUS >= 199711L)
#    define nssv_CPP11_OR_GREATER (nssv_CPLUSPLUS >= 201103L)
#    define nssv_CPP11_OR_GREATER_ (nssv_CPLUSPLUS >= 201103L)
#    define nssv_CPP14_OR_GREATER (nssv_CPLUSPLUS >= 201402L)
#    define nssv_CPP17_OR_GREATER (nssv_CPLUSPLUS >= 201703L)
#    define nssv_CPP20_OR_GREATER (nssv_CPLUSPLUS >= 202000L)

// use C++17 std::string_view if available and requested:

#    if nssv_CPP17_OR_GREATER && defined(__has_include)
#        if __has_include(<string_view> )
#            define nssv_HAVE_STD_STRING_VIEW 1
#        else
#            define nssv_HAVE_STD_STRING_VIEW 0
#        endif
#    else
#        define nssv_HAVE_STD_STRING_VIEW 0
#    endif

#    define nssv_USES_STD_STRING_VIEW                                                              \
        ((nssv_CONFIG_SELECT_STRING_VIEW == nssv_STRING_VIEW_STD) ||                               \
         ((nssv_CONFIG_SELECT_STRING_VIEW == nssv_STRING_VIEW_DEFAULT) &&                          \
          nssv_HAVE_STD_STRING_VIEW))

#    define nssv_HAVE_STARTS_WITH (nssv_CPP20_OR_GREATER || !nssv_USES_STD_STRING_VIEW)
#    define nssv_HAVE_ENDS_WITH nssv_HAVE_STARTS_WITH

//
// Use C++17 std::string_view:
//

#    if nssv_USES_STD_STRING_VIEW

#        include <string_view>

// Extensions for std::string:

#        if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

namespace rapidfuzz {

template <class CharT, class Traits, class Allocator = std::allocator<CharT>>
std::basic_string<CharT, Traits, Allocator> to_string(std::basic_string_view<CharT, Traits> v,
                                                      Allocator const& a = Allocator())
{
    return std::basic_string<CharT, Traits, Allocator>(v.begin(), v.end(), a);
}

template <class CharT, class Traits, class Allocator>
std::basic_string_view<CharT, Traits>
to_string_view(std::basic_string<CharT, Traits, Allocator> const& s)
{
    return std::basic_string_view<CharT, Traits>(s.data(), s.size());
}

// Literal operators sv and _sv:

#            if nssv_CONFIG_STD_SV_OPERATOR

using namespace std::literals::string_view_literals;

#            endif

#            if nssv_CONFIG_USR_SV_OPERATOR

inline namespace literals {
inline namespace string_view_literals {

constexpr std::string_view operator"" _sv(const char* str, size_t len) noexcept // (1)
{
    return std::string_view{str, len};
}

constexpr std::u16string_view operator"" _sv(const char16_t* str, size_t len) noexcept // (2)
{
    return std::u16string_view{str, len};
}

constexpr std::u32string_view operator"" _sv(const char32_t* str, size_t len) noexcept // (3)
{
    return std::u32string_view{str, len};
}

constexpr std::wstring_view operator"" _sv(const wchar_t* str, size_t len) noexcept // (4)
{
    return std::wstring_view{str, len};
}

} // namespace string_view_literals
} // namespace literals

#            endif // nssv_CONFIG_USR_SV_OPERATOR

} // namespace rapidfuzz

#        endif // nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

namespace rapidfuzz {

using std::basic_string_view;
using std::string_view;
using std::u16string_view;
using std::u32string_view;
using std::wstring_view;

// literal "sv" and "_sv", see above

using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;

using std::operator<<;

} // namespace rapidfuzz

#    else // nssv_HAVE_STD_STRING_VIEW

//
// Before C++17: use string_view lite:
//

// Compiler versions:
//
// MSVC++  6.0  _MSC_VER == 1200  nssv_COMPILER_MSVC_VERSION ==  60  (Visual Studio 6.0)
// MSVC++  7.0  _MSC_VER == 1300  nssv_COMPILER_MSVC_VERSION ==  70  (Visual Studio .NET 2002)
// MSVC++  7.1  _MSC_VER == 1310  nssv_COMPILER_MSVC_VERSION ==  71  (Visual Studio .NET 2003)
// MSVC++  8.0  _MSC_VER == 1400  nssv_COMPILER_MSVC_VERSION ==  80  (Visual Studio 2005)
// MSVC++  9.0  _MSC_VER == 1500  nssv_COMPILER_MSVC_VERSION ==  90  (Visual Studio 2008)
// MSVC++ 10.0  _MSC_VER == 1600  nssv_COMPILER_MSVC_VERSION == 100  (Visual Studio 2010)
// MSVC++ 11.0  _MSC_VER == 1700  nssv_COMPILER_MSVC_VERSION == 110  (Visual Studio 2012)
// MSVC++ 12.0  _MSC_VER == 1800  nssv_COMPILER_MSVC_VERSION == 120  (Visual Studio 2013)
// MSVC++ 14.0  _MSC_VER == 1900  nssv_COMPILER_MSVC_VERSION == 140  (Visual Studio 2015)
// MSVC++ 14.1  _MSC_VER >= 1910  nssv_COMPILER_MSVC_VERSION == 141  (Visual Studio 2017)
// MSVC++ 14.2  _MSC_VER >= 1920  nssv_COMPILER_MSVC_VERSION == 142  (Visual Studio 2019)

#        if defined(_MSC_VER) && !defined(__clang__)
#            define nssv_COMPILER_MSVC_VER (_MSC_VER)
#            define nssv_COMPILER_MSVC_VERSION (_MSC_VER / 10 - 10 * (5 + (_MSC_VER < 1900)))
#        else
#            define nssv_COMPILER_MSVC_VER 0
#            define nssv_COMPILER_MSVC_VERSION 0
#        endif

#        define nssv_COMPILER_VERSION(major, minor, patch) (10 * (10 * (major) + (minor)) + (patch))

#        if defined(__clang__)
#            define nssv_COMPILER_CLANG_VERSION                                                    \
                nssv_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#        else
#            define nssv_COMPILER_CLANG_VERSION 0
#        endif

#        if defined(__GNUC__) && !defined(__clang__)
#            define nssv_COMPILER_GNUC_VERSION                                                     \
                nssv_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#        else
#            define nssv_COMPILER_GNUC_VERSION 0
#        endif

// half-open range [lo..hi):
#        define nssv_BETWEEN(v, lo, hi) ((lo) <= (v) && (v) < (hi))

// Presence of language and library features:

#        ifdef _HAS_CPP0X
#            define nssv_HAS_CPP0X _HAS_CPP0X
#        else
#            define nssv_HAS_CPP0X 0
#        endif

// Unless defined otherwise below, consider VC14 as C++11 for variant-lite:

#        if nssv_COMPILER_MSVC_VER >= 1900
#            undef nssv_CPP11_OR_GREATER
#            define nssv_CPP11_OR_GREATER 1
#        endif

#        define nssv_CPP11_90 (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1500)
#        define nssv_CPP11_100 (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1600)
#        define nssv_CPP11_110 (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1700)
#        define nssv_CPP11_120 (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1800)
#        define nssv_CPP11_140 (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1900)
#        define nssv_CPP11_141 (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1910)

#        define nssv_CPP14_000 (nssv_CPP14_OR_GREATER)
#        define nssv_CPP17_000 (nssv_CPP17_OR_GREATER)

// Presence of C++11 language features:

#        define nssv_HAVE_CONSTEXPR_11 nssv_CPP11_140
#        define nssv_HAVE_EXPLICIT_CONVERSION nssv_CPP11_140
#        define nssv_HAVE_INLINE_NAMESPACE nssv_CPP11_140
#        define nssv_HAVE_NOEXCEPT nssv_CPP11_140
#        define nssv_HAVE_NULLPTR nssv_CPP11_100
#        define nssv_HAVE_REF_QUALIFIER nssv_CPP11_140
#        define nssv_HAVE_UNICODE_LITERALS nssv_CPP11_140
#        define nssv_HAVE_USER_DEFINED_LITERALS nssv_CPP11_140
#        define nssv_HAVE_WCHAR16_T nssv_CPP11_100
#        define nssv_HAVE_WCHAR32_T nssv_CPP11_100

#        if !((nssv_CPP11_OR_GREATER && nssv_COMPILER_CLANG_VERSION) ||                            \
              nssv_BETWEEN(nssv_COMPILER_CLANG_VERSION, 300, 400))
#            define nssv_HAVE_STD_DEFINED_LITERALS nssv_CPP11_140
#        else
#            define nssv_HAVE_STD_DEFINED_LITERALS 0
#        endif

// Presence of C++14 language features:

#        define nssv_HAVE_CONSTEXPR_14 nssv_CPP14_000

// Presence of C++17 language features:

#        define nssv_HAVE_NODISCARD nssv_CPP17_000

// Presence of C++ library features:

#        define nssv_HAVE_STD_HASH nssv_CPP11_120

// C++ feature usage:

#        if nssv_HAVE_CONSTEXPR_11
#            define nssv_constexpr constexpr
#        else
#            define nssv_constexpr /*constexpr*/
#        endif

#        if nssv_HAVE_CONSTEXPR_14
#            define nssv_constexpr14 constexpr
#        else
#            define nssv_constexpr14 /*constexpr*/
#        endif

#        if nssv_HAVE_EXPLICIT_CONVERSION
#            define nssv_explicit explicit
#        else
#            define nssv_explicit /*explicit*/
#        endif

#        if nssv_HAVE_INLINE_NAMESPACE
#            define nssv_inline_ns inline
#        else
#            define nssv_inline_ns /*inline*/
#        endif

#        if nssv_HAVE_NOEXCEPT
#            define nssv_noexcept noexcept
#        else
#            define nssv_noexcept /*noexcept*/
#        endif

//#if nssv_HAVE_REF_QUALIFIER
//# define nssv_ref_qual  &
//# define nssv_refref_qual  &&
//#else
//# define nssv_ref_qual  /*&*/
//# define nssv_refref_qual  /*&&*/
//#endif

#        if nssv_HAVE_NULLPTR
#            define nssv_nullptr nullptr
#        else
#            define nssv_nullptr NULL
#        endif

#        if nssv_HAVE_NODISCARD
#            define nssv_nodiscard [[nodiscard]]
#        else
#            define nssv_nodiscard /*[[nodiscard]]*/
#        endif

// Additional includes:

#        include <algorithm>
#        include <cassert>
#        include <iterator>
#        include <limits>
#        include <ostream>
#        include <string> // std::char_traits<>

#        if !nssv_CONFIG_NO_EXCEPTIONS
#            include <stdexcept>
#        endif

#        if nssv_CPP11_OR_GREATER
#            include <type_traits>
#        endif

// Clang, GNUC, MSVC warning suppression macros:

#        if defined(__clang__)
#            pragma clang diagnostic ignored "-Wreserved-user-defined-literal"
#            pragma clang diagnostic push
#            pragma clang diagnostic ignored "-Wuser-defined-literals"
#        elif defined(__GNUC__)
#            pragma GCC diagnostic push
#            pragma GCC diagnostic ignored "-Wliteral-suffix"
#        endif // __clang__

#        if nssv_COMPILER_MSVC_VERSION >= 140
#            define nssv_SUPPRESS_MSGSL_WARNING(expr) [[gsl::suppress(expr)]]
#            define nssv_SUPPRESS_MSVC_WARNING(code, descr) __pragma(warning(suppress : code))
#            define nssv_DISABLE_MSVC_WARNINGS(codes)                                              \
                __pragma(warning(push)) __pragma(warning(disable : codes))
#        else
#            define nssv_SUPPRESS_MSGSL_WARNING(expr)
#            define nssv_SUPPRESS_MSVC_WARNING(code, descr)
#            define nssv_DISABLE_MSVC_WARNINGS(codes)
#        endif

#        if defined(__clang__)
#            define nssv_RESTORE_WARNINGS() _Pragma("clang diagnostic pop")
#        elif defined(__GNUC__)
#            define nssv_RESTORE_WARNINGS() _Pragma("GCC diagnostic pop")
#        elif nssv_COMPILER_MSVC_VERSION >= 140
#            define nssv_RESTORE_WARNINGS() __pragma(warning(pop))
#        else
#            define nssv_RESTORE_WARNINGS()
#        endif

// Suppress the following MSVC (GSL) warnings:
// - C4455, non-gsl   : 'operator ""sv': literal suffix identifiers that do not
//                      start with an underscore are reserved
// - C26472, gsl::t.1 : don't use a static_cast for arithmetic conversions;
//                      use brace initialization, gsl::narrow_cast or gsl::narow
// - C26481: gsl::b.1 : don't use pointer arithmetic. Use span instead

nssv_DISABLE_MSVC_WARNINGS(4455 26481 26472)
    // nssv_DISABLE_CLANG_WARNINGS( "-Wuser-defined-literals" )
    // nssv_DISABLE_GNUC_WARNINGS( -Wliteral-suffix )

    namespace rapidfuzz
{
    namespace sv_lite {

#        if nssv_CPP11_OR_GREATER

    namespace detail {

#            if nssv_CPP14_OR_GREATER

    template <typename CharT>
    inline constexpr std::size_t length(CharT* s, std::size_t result = 0)
    {
        CharT* v = s;
        std::size_t r = result;
        while (*v != '\0') {
            ++v;
            ++r;
        }
        return r;
    }

#            else // nssv_CPP14_OR_GREATER

    // Expect tail call optimization to make length() non-recursive:

    template <typename CharT>
    inline constexpr std::size_t length(CharT* s, std::size_t result = 0)
    {
        return *s == '\0' ? result : length(s + 1, result + 1);
    }

#            endif // nssv_CPP14_OR_GREATER

    } // namespace detail

#        endif // nssv_CPP11_OR_GREATER

    template <class CharT, class Traits = std::char_traits<CharT>>
    class basic_string_view;

    //
    // basic_string_view:
    //

    template <class CharT, class Traits /* = std::char_traits<CharT> */
              >
    class basic_string_view {
    public:
        // Member types:

        typedef Traits traits_type;
        typedef CharT value_type;

        typedef CharT* pointer;
        typedef CharT const* const_pointer;
        typedef CharT& reference;
        typedef CharT const& const_reference;

        typedef const_pointer iterator;
        typedef const_pointer const_iterator;
        typedef std::reverse_iterator<const_iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        // 24.4.2.1 Construction and assignment:

        nssv_constexpr basic_string_view() nssv_noexcept : data_(nssv_nullptr), size_(0)
        {}

#        if nssv_CPP11_OR_GREATER
        nssv_constexpr basic_string_view(basic_string_view const& other) nssv_noexcept = default;
#        else
        nssv_constexpr basic_string_view(basic_string_view const& other) nssv_noexcept
            : data_(other.data_),
              size_(other.size_)
        {}
#        endif

        nssv_constexpr basic_string_view(CharT const* s,
                                         size_type count) nssv_noexcept // non-standard noexcept
            : data_(s),
              size_(count)
        {}

        nssv_constexpr basic_string_view(CharT const* s) nssv_noexcept // non-standard noexcept
            : data_(s)
#        if nssv_CPP17_OR_GREATER
            ,
              size_(Traits::length(s))
#        elif nssv_CPP11_OR_GREATER
            ,
              size_(detail::length(s))
#        else
            ,
              size_(Traits::length(s))
#        endif
        {}

        // Assignment:

#        if nssv_CPP11_OR_GREATER
        nssv_constexpr14 basic_string_view&
        operator=(basic_string_view const& other) nssv_noexcept = default;
#        else
        nssv_constexpr14 basic_string_view& operator=(basic_string_view const& other) nssv_noexcept
        {
            data_ = other.data_;
            size_ = other.size_;
            return *this;
        }
#        endif

        // 24.4.2.2 Iterator support:

        nssv_constexpr const_iterator begin() const nssv_noexcept
        {
            return data_;
        }
        nssv_constexpr const_iterator end() const nssv_noexcept
        {
            return data_ + size_;
        }

        nssv_constexpr const_iterator cbegin() const nssv_noexcept
        {
            return begin();
        }
        nssv_constexpr const_iterator cend() const nssv_noexcept
        {
            return end();
        }

        nssv_constexpr const_reverse_iterator rbegin() const nssv_noexcept
        {
            return const_reverse_iterator(end());
        }
        nssv_constexpr const_reverse_iterator rend() const nssv_noexcept
        {
            return const_reverse_iterator(begin());
        }

        nssv_constexpr const_reverse_iterator crbegin() const nssv_noexcept
        {
            return rbegin();
        }
        nssv_constexpr const_reverse_iterator crend() const nssv_noexcept
        {
            return rend();
        }

        // 24.4.2.3 Capacity:

        nssv_constexpr size_type size() const nssv_noexcept
        {
            return size_;
        }
        nssv_constexpr size_type length() const nssv_noexcept
        {
            return size_;
        }
        nssv_constexpr size_type max_size() const nssv_noexcept
        {
            return (std::numeric_limits<size_type>::max)();
        }

        // since C++20
        nssv_nodiscard nssv_constexpr bool empty() const nssv_noexcept
        {
            return 0 == size_;
        }

        // 24.4.2.4 Element access:

        nssv_constexpr const_reference operator[](size_type pos) const
        {
            return data_at(pos);
        }

        nssv_constexpr14 const_reference at(size_type pos) const
        {
#        if nssv_CONFIG_NO_EXCEPTIONS
            assert(pos < size());
#        else
            if (pos >= size()) {
                throw std::out_of_range("rapidfuzz::string_view::at()");
            }
#        endif
            return data_at(pos);
        }

        nssv_constexpr const_reference front() const
        {
            return data_at(0);
        }
        nssv_constexpr const_reference back() const
        {
            return data_at(size() - 1);
        }

        nssv_constexpr const_pointer data() const nssv_noexcept
        {
            return data_;
        }

        // 24.4.2.5 Modifiers:

        nssv_constexpr14 void remove_prefix(size_type n)
        {
            assert(n <= size());
            data_ += n;
            size_ -= n;
        }

        nssv_constexpr14 void remove_suffix(size_type n)
        {
            assert(n <= size());
            size_ -= n;
        }

        nssv_constexpr14 void swap(basic_string_view& other) nssv_noexcept
        {
            using std::swap;
            swap(data_, other.data_);
            swap(size_, other.size_);
        }

        // 24.4.2.6 String operations:

        size_type copy(CharT* dest, size_type n, size_type pos = 0) const
        {
#        if nssv_CONFIG_NO_EXCEPTIONS
            assert(pos <= size());
#        else
            if (pos > size()) {
                throw std::out_of_range("rapidfuzz::string_view::copy()");
            }
#        endif
            const size_type rlen = (std::min)(n, size() - pos);

            (void)Traits::copy(dest, data() + pos, rlen);

            return rlen;
        }

        nssv_constexpr14 basic_string_view substr(size_type pos = 0, size_type n = npos) const
        {
#        if nssv_CONFIG_NO_EXCEPTIONS
            assert(pos <= size());
#        else
            if (pos > size()) {
                throw std::out_of_range("rapidfuzz::string_view::substr()");
            }
#        endif
            return basic_string_view(data() + pos, (std::min)(n, size() - pos));
        }

        // compare(), 6x:

        nssv_constexpr14 int compare(basic_string_view other) const nssv_noexcept // (1)
        {
            if (const int result =
                    Traits::compare(data(), other.data(), (std::min)(size(), other.size()))) {
                return result;
            }

            return size() == other.size() ? 0 : size() < other.size() ? -1 : 1;
        }

        nssv_constexpr int compare(size_type pos1, size_type n1,
                                   basic_string_view other) const // (2)
        {
            return substr(pos1, n1).compare(other);
        }

        nssv_constexpr int compare(size_type pos1, size_type n1, basic_string_view other,
                                   size_type pos2, size_type n2) const // (3)
        {
            return substr(pos1, n1).compare(other.substr(pos2, n2));
        }

        nssv_constexpr int compare(CharT const* s) const // (4)
        {
            return compare(basic_string_view(s));
        }

        nssv_constexpr int compare(size_type pos1, size_type n1, CharT const* s) const // (5)
        {
            return substr(pos1, n1).compare(basic_string_view(s));
        }

        nssv_constexpr int compare(size_type pos1, size_type n1, CharT const* s,
                                   size_type n2) const // (6)
        {
            return substr(pos1, n1).compare(basic_string_view(s, n2));
        }

        // 24.4.2.7 Searching:

        // starts_with(), 3x, since C++20:

        nssv_constexpr bool starts_with(basic_string_view v) const nssv_noexcept // (1)
        {
            return size() >= v.size() && compare(0, v.size(), v) == 0;
        }

        nssv_constexpr bool starts_with(CharT c) const nssv_noexcept // (2)
        {
            return starts_with(basic_string_view(&c, 1));
        }

        nssv_constexpr bool starts_with(CharT const* s) const // (3)
        {
            return starts_with(basic_string_view(s));
        }

        // ends_with(), 3x, since C++20:

        nssv_constexpr bool ends_with(basic_string_view v) const nssv_noexcept // (1)
        {
            return size() >= v.size() && compare(size() - v.size(), npos, v) == 0;
        }

        nssv_constexpr bool ends_with(CharT c) const nssv_noexcept // (2)
        {
            return ends_with(basic_string_view(&c, 1));
        }

        nssv_constexpr bool ends_with(CharT const* s) const // (3)
        {
            return ends_with(basic_string_view(s));
        }

        // find(), 4x:

        nssv_constexpr14 size_type find(basic_string_view v,
                                        size_type pos = 0) const nssv_noexcept // (1)
        {
            return assert(v.size() == 0 || v.data() != nssv_nullptr),
                   pos >= size() ? npos
                                 : to_pos(std::search(cbegin() + pos, cend(), v.cbegin(), v.cend(),
                                                      Traits::eq));
        }

        nssv_constexpr14 size_type find(CharT c, size_type pos = 0) const nssv_noexcept // (2)
        {
            return find(basic_string_view(&c, 1), pos);
        }

        nssv_constexpr14 size_type find(CharT const* s, size_type pos, size_type n) const // (3)
        {
            return find(basic_string_view(s, n), pos);
        }

        nssv_constexpr14 size_type find(CharT const* s, size_type pos = 0) const // (4)
        {
            return find(basic_string_view(s), pos);
        }

        // rfind(), 4x:

        nssv_constexpr14 size_type rfind(basic_string_view v,
                                         size_type pos = npos) const nssv_noexcept // (1)
        {
            if (size() < v.size()) {
                return npos;
            }

            if (v.empty()) {
                return (std::min)(size(), pos);
            }

            const_iterator last = cbegin() + (std::min)(size() - v.size(), pos) + v.size();
            const_iterator result = std::find_end(cbegin(), last, v.cbegin(), v.cend(), Traits::eq);

            return result != last ? size_type(result - cbegin()) : npos;
        }

        nssv_constexpr14 size_type rfind(CharT c, size_type pos = npos) const nssv_noexcept // (2)
        {
            return rfind(basic_string_view(&c, 1), pos);
        }

        nssv_constexpr14 size_type rfind(CharT const* s, size_type pos, size_type n) const // (3)
        {
            return rfind(basic_string_view(s, n), pos);
        }

        nssv_constexpr14 size_type rfind(CharT const* s, size_type pos = npos) const // (4)
        {
            return rfind(basic_string_view(s), pos);
        }

        // find_first_of(), 4x:

        nssv_constexpr size_type find_first_of(basic_string_view v,
                                               size_type pos = 0) const nssv_noexcept // (1)
        {
            return pos >= size() ? npos
                                 : to_pos(std::find_first_of(cbegin() + pos, cend(), v.cbegin(),
                                                             v.cend(), Traits::eq));
        }

        nssv_constexpr size_type find_first_of(CharT c,
                                               size_type pos = 0) const nssv_noexcept // (2)
        {
            return find_first_of(basic_string_view(&c, 1), pos);
        }

        nssv_constexpr size_type find_first_of(CharT const* s, size_type pos,
                                               size_type n) const // (3)
        {
            return find_first_of(basic_string_view(s, n), pos);
        }

        nssv_constexpr size_type find_first_of(CharT const* s, size_type pos = 0) const // (4)
        {
            return find_first_of(basic_string_view(s), pos);
        }

        // find_last_of(), 4x:

        nssv_constexpr size_type find_last_of(basic_string_view v,
                                              size_type pos = npos) const nssv_noexcept // (1)
        {
            return empty() ? npos
                   : pos >= size()
                       ? find_last_of(v, size() - 1)
                       : to_pos(std::find_first_of(const_reverse_iterator(cbegin() + pos + 1),
                                                   crend(), v.cbegin(), v.cend(), Traits::eq));
        }

        nssv_constexpr size_type find_last_of(CharT c,
                                              size_type pos = npos) const nssv_noexcept // (2)
        {
            return find_last_of(basic_string_view(&c, 1), pos);
        }

        nssv_constexpr size_type find_last_of(CharT const* s, size_type pos,
                                              size_type count) const // (3)
        {
            return find_last_of(basic_string_view(s, count), pos);
        }

        nssv_constexpr size_type find_last_of(CharT const* s, size_type pos = npos) const // (4)
        {
            return find_last_of(basic_string_view(s), pos);
        }

        // find_first_not_of(), 4x:

        nssv_constexpr size_type find_first_not_of(basic_string_view v,
                                                   size_type pos = 0) const nssv_noexcept // (1)
        {
            return pos >= size() ? npos
                                 : to_pos(std::find_if(cbegin() + pos, cend(), not_in_view(v)));
        }

        nssv_constexpr size_type find_first_not_of(CharT c,
                                                   size_type pos = 0) const nssv_noexcept // (2)
        {
            return find_first_not_of(basic_string_view(&c, 1), pos);
        }

        nssv_constexpr size_type find_first_not_of(CharT const* s, size_type pos,
                                                   size_type count) const // (3)
        {
            return find_first_not_of(basic_string_view(s, count), pos);
        }

        nssv_constexpr size_type find_first_not_of(CharT const* s, size_type pos = 0) const // (4)
        {
            return find_first_not_of(basic_string_view(s), pos);
        }

        // find_last_not_of(), 4x:

        nssv_constexpr size_type find_last_not_of(basic_string_view v,
                                                  size_type pos = npos) const nssv_noexcept // (1)
        {
            return empty()         ? npos
                   : pos >= size() ? find_last_not_of(v, size() - 1)
                                   : to_pos(std::find_if(const_reverse_iterator(cbegin() + pos + 1),
                                                         crend(), not_in_view(v)));
        }

        nssv_constexpr size_type find_last_not_of(CharT c,
                                                  size_type pos = npos) const nssv_noexcept // (2)
        {
            return find_last_not_of(basic_string_view(&c, 1), pos);
        }

        nssv_constexpr size_type find_last_not_of(CharT const* s, size_type pos,
                                                  size_type count) const // (3)
        {
            return find_last_not_of(basic_string_view(s, count), pos);
        }

        nssv_constexpr size_type find_last_not_of(CharT const* s, size_type pos = npos) const // (4)
        {
            return find_last_not_of(basic_string_view(s), pos);
        }

        // Constants:

#        if nssv_CPP17_OR_GREATER
        static nssv_constexpr size_type npos = size_type(-1);
#        elif nssv_CPP11_OR_GREATER
        enum : size_type { npos = size_type(-1) };
#        else
        enum { npos = size_type(-1) };
#        endif

    private:
        struct not_in_view {
            const basic_string_view v;

            nssv_constexpr explicit not_in_view(basic_string_view v_) : v(v_)
            {}

            nssv_constexpr bool operator()(CharT c) const
            {
                return npos == v.find_first_of(c);
            }
        };

        nssv_constexpr size_type to_pos(const_iterator it) const
        {
            return it == cend() ? npos : size_type(it - cbegin());
        }

        nssv_constexpr size_type to_pos(const_reverse_iterator it) const
        {
            return it == crend() ? npos : size_type(crend() - it - 1);
        }

        nssv_constexpr const_reference data_at(size_type pos) const
        {
#        if nssv_BETWEEN(nssv_COMPILER_GNUC_VERSION, 1, 500)
            return data_[pos];
#        else
            return assert(pos < size()), data_[pos];
#        endif
        }

    private:
        const_pointer data_;
        size_type size_;

    public:
#        if nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS

        template <class Allocator>
        basic_string_view(std::basic_string<CharT, Traits, Allocator> const& s) nssv_noexcept
            : data_(s.data()),
              size_(s.size())
        {}

#            if nssv_HAVE_EXPLICIT_CONVERSION

        template <class Allocator>
        explicit operator std::basic_string<CharT, Traits, Allocator>() const
        {
            return to_string(Allocator());
        }

#            endif // nssv_HAVE_EXPLICIT_CONVERSION

#            if nssv_CPP11_OR_GREATER

        template <class Allocator = std::allocator<CharT>>
        std::basic_string<CharT, Traits, Allocator>
        to_string(Allocator const& a = Allocator()) const
        {
            return std::basic_string<CharT, Traits, Allocator>(begin(), end(), a);
        }

#            else

        std::basic_string<CharT, Traits> to_string() const
        {
            return std::basic_string<CharT, Traits>(begin(), end());
        }

        template <class Allocator>
        std::basic_string<CharT, Traits, Allocator> to_string(Allocator const& a) const
        {
            return std::basic_string<CharT, Traits, Allocator>(begin(), end(), a);
        }

#            endif // nssv_CPP11_OR_GREATER

#        endif // nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
    };

    //
    // Non-member functions:
    //

    // 24.4.3 Non-member comparison functions:
    // lexicographically compare two string views (function template):

    template <class CharT, class Traits>
    nssv_constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) == 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) != 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                  basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                  basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) >= 0;
    }

    // Let S be basic_string_view<CharT, Traits>, and sv be an instance of S.
    // Implementations shall provide sufficient additional overloads marked
    // constexpr and noexcept so that an object t with an implicit conversion
    // to S can be compared according to Table 67.

#        if !nssv_CPP11_OR_GREATER || nssv_BETWEEN(nssv_COMPILER_MSVC_VERSION, 100, 141)

    // accomodate for older compilers:

    // ==

    template <class CharT, class Traits>
    nssv_constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                   CharT const* rhs) nssv_noexcept
    {
        return lhs.compare(rhs) == 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator==(CharT const* lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return rhs.compare(lhs) == 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                   std::basic_string<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator==(std::basic_string<CharT, Traits> rhs,
                                   basic_string_view<CharT, Traits> lhs) nssv_noexcept
    {
        return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
    }

    // !=

    template <class CharT, class Traits>
    nssv_constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                   char const* rhs) nssv_noexcept
    {
        return lhs.compare(rhs) != 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator!=(char const* lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return rhs.compare(lhs) != 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                   std::basic_string<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.size() != rhs.size() && lhs.compare(rhs) != 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator!=(std::basic_string<CharT, Traits> rhs,
                                   basic_string_view<CharT, Traits> lhs) nssv_noexcept
    {
        return lhs.size() != rhs.size() || rhs.compare(lhs) != 0;
    }

    // <

    template <class CharT, class Traits>
    nssv_constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                  char const* rhs) nssv_noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<(char const* lhs,
                                  basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return rhs.compare(lhs) > 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                  std::basic_string<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<(std::basic_string<CharT, Traits> rhs,
                                  basic_string_view<CharT, Traits> lhs) nssv_noexcept
    {
        return rhs.compare(lhs) > 0;
    }

    // <=

    template <class CharT, class Traits>
    nssv_constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                   char const* rhs) nssv_noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<=(char const* lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return rhs.compare(lhs) >= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                   std::basic_string<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator<=(std::basic_string<CharT, Traits> rhs,
                                   basic_string_view<CharT, Traits> lhs) nssv_noexcept
    {
        return rhs.compare(lhs) >= 0;
    }

    // >

    template <class CharT, class Traits>
    nssv_constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                  char const* rhs) nssv_noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>(char const* lhs,
                                  basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return rhs.compare(lhs) < 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                  std::basic_string<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>(std::basic_string<CharT, Traits> rhs,
                                  basic_string_view<CharT, Traits> lhs) nssv_noexcept
    {
        return rhs.compare(lhs) < 0;
    }

    // >=

    template <class CharT, class Traits>
    nssv_constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                   char const* rhs) nssv_noexcept
    {
        return lhs.compare(rhs) >= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>=(char const* lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return rhs.compare(lhs) <= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                   std::basic_string<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) >= 0;
    }

    template <class CharT, class Traits>
    nssv_constexpr bool operator>=(std::basic_string<CharT, Traits> rhs,
                                   basic_string_view<CharT, Traits> lhs) nssv_noexcept
    {
        return rhs.compare(lhs) <= 0;
    }

#        else // newer compilers:

#            define nssv_BASIC_STRING_VIEW_I(T, U)                                                 \
                typename std::decay<basic_string_view<T, U>>::type

#            if nssv_BETWEEN(nssv_COMPILER_MSVC_VERSION, 140, 150)
#                define nssv_MSVC_ORDER(x) , int = x
#            else
#                define nssv_MSVC_ORDER(x) /*, int=x*/
#            endif

    // ==

    template <class CharT, class Traits nssv_MSVC_ORDER(1)>
    nssv_constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                   nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs) nssv_noexcept
    {
        return lhs.compare(rhs) == 0;
    }

    template <class CharT, class Traits nssv_MSVC_ORDER(2)>
    nssv_constexpr bool operator==(nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
    }

    // !=

    template <class CharT, class Traits nssv_MSVC_ORDER(1)>
    nssv_constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                   nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs) nssv_noexcept
    {
        return lhs.size() != rhs.size() || lhs.compare(rhs) != 0;
    }

    template <class CharT, class Traits nssv_MSVC_ORDER(2)>
    nssv_constexpr bool operator!=(nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) != 0;
    }

    // <

    template <class CharT, class Traits nssv_MSVC_ORDER(1)>
    nssv_constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                  nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs) nssv_noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    template <class CharT, class Traits nssv_MSVC_ORDER(2)>
    nssv_constexpr bool operator<(nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
                                  basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    // <=

    template <class CharT, class Traits nssv_MSVC_ORDER(1)>
    nssv_constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                   nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs) nssv_noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    template <class CharT, class Traits nssv_MSVC_ORDER(2)>
    nssv_constexpr bool operator<=(nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    // >

    template <class CharT, class Traits nssv_MSVC_ORDER(1)>
    nssv_constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                  nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs) nssv_noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    template <class CharT, class Traits nssv_MSVC_ORDER(2)>
    nssv_constexpr bool operator>(nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
                                  basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    // >=

    template <class CharT, class Traits nssv_MSVC_ORDER(1)>
    nssv_constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                   nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs) nssv_noexcept
    {
        return lhs.compare(rhs) >= 0;
    }

    template <class CharT, class Traits nssv_MSVC_ORDER(2)>
    nssv_constexpr bool operator>=(nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
                                   basic_string_view<CharT, Traits> rhs) nssv_noexcept
    {
        return lhs.compare(rhs) >= 0;
    }

#            undef nssv_MSVC_ORDER
#            undef nssv_BASIC_STRING_VIEW_I

#        endif // compiler-dependent approach to comparisons

    // 24.4.4 Inserters and extractors:

    namespace detail {

    template <class Stream>
    void write_padding(Stream& os, std::streamsize n)
    {
        for (std::streamsize i = 0; i < n; ++i)
            os.rdbuf()->sputc(os.fill());
    }

    template <class Stream, class View>
    Stream& write_to_stream(Stream& os, View const& sv)
    {
        typename Stream::sentry sentry(os);

        if (!os) return os;

        const std::streamsize length = static_cast<std::streamsize>(sv.length());

        // Whether, and how, to pad:
        const bool pad = (length < os.width());
        const bool left_pad =
            pad && (os.flags() & std::ios_base::adjustfield) == std::ios_base::right;

        if (left_pad) write_padding(os, os.width() - length);

        // Write span characters:
        os.rdbuf()->sputn(sv.begin(), length);

        if (pad && !left_pad) write_padding(os, os.width() - length);

        // Reset output stream width:
        os.width(0);

        return os;
    }

    } // namespace detail

    template <class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                  basic_string_view<CharT, Traits> sv)
    {
        return detail::write_to_stream(os, sv);
    }

    // Several typedefs for common character types are provided:

    typedef basic_string_view<char> string_view;
    typedef basic_string_view<wchar_t> wstring_view;
#        if nssv_HAVE_WCHAR16_T
    typedef basic_string_view<char16_t> u16string_view;
    typedef basic_string_view<char32_t> u32string_view;
#        endif

    } // namespace sv_lite
} // namespace rapidfuzz::sv_lite

//
// 24.4.6 Suffix for basic_string_view literals:
//

#        if nssv_HAVE_USER_DEFINED_LITERALS

namespace rapidfuzz {
nssv_inline_ns namespace literals
{
    nssv_inline_ns namespace string_view_literals
    {

#            if nssv_CONFIG_STD_SV_OPERATOR && nssv_HAVE_STD_DEFINED_LITERALS

        nssv_constexpr rapidfuzz::sv_lite::string_view operator"" sv(const char* str, size_t len)
            nssv_noexcept // (1)
        {
            return rapidfuzz::sv_lite::string_view{str, len};
        }

        nssv_constexpr rapidfuzz::sv_lite::u16string_view operator"" sv(
            const char16_t* str, size_t len) nssv_noexcept // (2)
        {
            return rapidfuzz::sv_lite::u16string_view{str, len};
        }

        nssv_constexpr rapidfuzz::sv_lite::u32string_view operator"" sv(
            const char32_t* str, size_t len) nssv_noexcept // (3)
        {
            return rapidfuzz::sv_lite::u32string_view{str, len};
        }

        nssv_constexpr rapidfuzz::sv_lite::wstring_view operator"" sv(
            const wchar_t* str, size_t len) nssv_noexcept // (4)
        {
            return rapidfuzz::sv_lite::wstring_view{str, len};
        }

#            endif // nssv_CONFIG_STD_SV_OPERATOR && nssv_HAVE_STD_DEFINED_LITERALS

#            if nssv_CONFIG_USR_SV_OPERATOR

        nssv_constexpr rapidfuzz::sv_lite::string_view operator"" _sv(const char* str, size_t len)
            nssv_noexcept // (1)
        {
            return rapidfuzz::sv_lite::string_view{str, len};
        }

        nssv_constexpr rapidfuzz::sv_lite::u16string_view operator"" _sv(
            const char16_t* str, size_t len) nssv_noexcept // (2)
        {
            return rapidfuzz::sv_lite::u16string_view{str, len};
        }

        nssv_constexpr rapidfuzz::sv_lite::u32string_view operator"" _sv(
            const char32_t* str, size_t len) nssv_noexcept // (3)
        {
            return rapidfuzz::sv_lite::u32string_view{str, len};
        }

        nssv_constexpr rapidfuzz::sv_lite::wstring_view operator"" _sv(
            const wchar_t* str, size_t len) nssv_noexcept // (4)
        {
            return rapidfuzz::sv_lite::wstring_view{str, len};
        }

#            endif // nssv_CONFIG_USR_SV_OPERATOR
    }
}
} // namespace rapidfuzz

#        endif

//
// Extensions for std::string:
//

#        if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

namespace rapidfuzz {
namespace sv_lite {

// Exclude MSVC 14 (19.00): it yields ambiguous to_string():

#            if nssv_CPP11_OR_GREATER && nssv_COMPILER_MSVC_VERSION != 140

template <class CharT, class Traits, class Allocator = std::allocator<CharT>>
std::basic_string<CharT, Traits, Allocator> to_string(basic_string_view<CharT, Traits> v,
                                                      Allocator const& a = Allocator())
{
    return std::basic_string<CharT, Traits, Allocator>(v.begin(), v.end(), a);
}

#            else

template <class CharT, class Traits>
std::basic_string<CharT, Traits> to_string(basic_string_view<CharT, Traits> v)
{
    return std::basic_string<CharT, Traits>(v.begin(), v.end());
}

template <class CharT, class Traits, class Allocator>
std::basic_string<CharT, Traits, Allocator> to_string(basic_string_view<CharT, Traits> v,
                                                      Allocator const& a)
{
    return std::basic_string<CharT, Traits, Allocator>(v.begin(), v.end(), a);
}

#            endif // nssv_CPP11_OR_GREATER

template <class CharT, class Traits, class Allocator>
basic_string_view<CharT, Traits>
to_string_view(std::basic_string<CharT, Traits, Allocator> const& s)
{
    return basic_string_view<CharT, Traits>(s.data(), s.size());
}

} // namespace sv_lite
} // namespace rapidfuzz

#        endif // nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

//
// make types and algorithms available in namespace rapidfuzz:
//

namespace rapidfuzz {

using sv_lite::basic_string_view;
using sv_lite::string_view;
using sv_lite::wstring_view;

#        if nssv_HAVE_WCHAR16_T
using sv_lite::u16string_view;
#        endif
#        if nssv_HAVE_WCHAR32_T
using sv_lite::u32string_view;
#        endif

// literal "sv"

using sv_lite::operator==;
using sv_lite::operator!=;
using sv_lite::operator<;
using sv_lite::operator<=;
using sv_lite::operator>;
using sv_lite::operator>=;

using sv_lite::operator<<;

#        if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
using sv_lite::to_string;
using sv_lite::to_string_view;
#        endif

} // namespace rapidfuzz

// 24.4.5 Hash support (C++11):

// Note: The hash value of a string view object is equal to the hash value of
// the corresponding string object.

#        if nssv_HAVE_STD_HASH

#            include <functional>

namespace std {

template <>
struct hash<rapidfuzz::string_view> {
public:
    std::size_t operator()(rapidfuzz::string_view v) const nssv_noexcept
    {
        return std::hash<std::string>()(std::string(v.data(), v.size()));
    }
};

template <>
struct hash<rapidfuzz::wstring_view> {
public:
    std::size_t operator()(rapidfuzz::wstring_view v) const nssv_noexcept
    {
        return std::hash<std::wstring>()(std::wstring(v.data(), v.size()));
    }
};

template <>
struct hash<rapidfuzz::u16string_view> {
public:
    std::size_t operator()(rapidfuzz::u16string_view v) const nssv_noexcept
    {
        return std::hash<std::u16string>()(std::u16string(v.data(), v.size()));
    }
};

template <>
struct hash<rapidfuzz::u32string_view> {
public:
    std::size_t operator()(rapidfuzz::u32string_view v) const nssv_noexcept
    {
        return std::hash<std::u32string>()(std::u32string(v.data(), v.size()));
    }
};

} // namespace std

#        endif // nssv_HAVE_STD_HASH

nssv_RESTORE_WARNINGS()

#    endif // nssv_HAVE_STD_STRING_VIEW
#endif     // NONSTD_SV_LITE_H_INCLUDED
namespace rapidfuzz {

template <typename CharT>
using string_view_vec = std::vector<basic_string_view<CharT>>;

struct StringAffix {
    size_t prefix_len;
    size_t suffix_len;
};

struct LevenshteinWeightTable {
    size_t insert_cost;
    size_t delete_cost;
    size_t replace_cost;
};

/**
 * @brief Edit operation types used by the Levenshtein distance
 */
enum class EditType {
    None = 0,    /**< No Operation required */
    Replace = 1, /**< Replace a character if a string by another character */
    Insert = 2,  /**< Insert a character into a string */
    Delete = 3   /**< Delete a character from a string */
};

/**
 * @brief Edit operations used by the Levenshtein distance
 *
 * This represents an edit operation of type type which is applied to
 * the source string
 *
 * Replace: replace character at src_pos with character at dest_pos
 * Insert:  insert character from dest_pos at src_pos
 * Delete:  delete character at src_pos
 */
struct EditOp {
    EditType type;   /**< type of the edit operation */
    size_t src_pos;  /**< index into the source string */
    size_t dest_pos; /**< index into the destination string */

    EditOp() : type(EditType::None), src_pos(0), dest_pos(0)
    {}

    EditOp(EditType type_, size_t src_pos_, size_t dest_pos_)
        : type(type_), src_pos(src_pos_), dest_pos(dest_pos_)
    {}
};

static inline bool operator==(EditOp a, EditOp b)
{
    return (a.type == b.type) && (a.src_pos == b.src_pos) && (a.dest_pos == b.dest_pos);
}

/**
 * @brief Edit operations used by the Levenshtein distance
 *
 * This represents an edit operation of type type which is applied to
 * the source string
 *
 * None:    s1[src_begin:src_end] == s1[dest_begin:dest_end]
 * Replace: s1[i1:i2] should be replaced by s2[dest_begin:dest_end]
 * Insert:  s2[dest_begin:dest_end] should be inserted at s1[src_begin:src_begin].
 *          Note that src_begin==src_end in this case.
 * Delete:  s1[src_begin:src_end] should be deleted.
 *          Note that dest_begin==dest_end in this case.
 */
struct Opcode {
    EditType type;     /**< type of the edit operation */
    size_t src_begin;  /**< index into the source string */
    size_t src_end;    /**< index into the source string */
    size_t dest_begin; /**< index into the destination string */
    size_t dest_end;   /**< index into the destination string */

    Opcode() : type(EditType::None), src_begin(0), src_end(0), dest_begin(0), dest_end(0)
    {}

    Opcode(EditType type_, size_t src_begin_, size_t src_end_, size_t dest_begin_, size_t dest_end_)
        : type(type_),
          src_begin(src_begin_),
          src_end(src_end_),
          dest_begin(dest_begin_),
          dest_end(dest_end_)
    {}
};

static inline bool operator==(Opcode a, Opcode b)
{
    return (a.type == b.type) && (a.src_begin == b.src_begin) && (a.src_end == b.src_end) &&
           (a.dest_begin == b.dest_begin) && (a.dest_end == b.dest_end);
}

namespace detail {
template <typename T>
void vector_slice(std::vector<T>& new_vec, const std::vector<T>& vec, int start, int stop, int step)
{
    if (step > 0) {
        if (start < 0) {
            start = std::max((int)(start + vec.size()), 0);
        }
        else if (start > vec.size()) {
            start = vec.size();
        }

        if (stop < 0) {
            stop = std::max((int)(stop + vec.size()), 0);
        }
        else if (stop > vec.size()) {
            stop = vec.size();
        }

        if (start >= stop) {
            return;
        }

        int count = (stop - 1 - start) / step + 1;
        new_vec.reserve(count);

        for (int i = start; i < stop; i += step) {
            new_vec.push_back(vec[i]);
        }
    }
    else if (step < 0) {
        if (start < 0) {
            start = std::max((int)(start + vec.size()), -1);
        }
        else if (start >= vec.size()) {
            start = vec.size() - 1;
        }

        if (stop < 0) {
            stop = std::max((int)(stop + vec.size()), -1);
        }
        else if (stop >= vec.size()) {
            stop = vec.size() - 1;
        }

        if (start <= stop) {
            return;
        }

        int count = (stop + 1 - start) / step + 1;
        new_vec.reserve(count);

        for (int i = start; i > stop; i += step) {
            new_vec.push_back(vec[i]);
        }
    }
    else {
        throw std::invalid_argument("slice step cannot be zero");
    }
}
} // namespace detail

class Opcodes;

class Editops : private std::vector<EditOp> {
public:
    using std::vector<EditOp>::size_type;

    Editops() : src_len(0), dest_len(0)
    {}

    Editops(size_type count, const EditOp& value)
        : std::vector<EditOp>(count, value), src_len(0), dest_len(0)
    {}

    explicit Editops(size_type count) : std::vector<EditOp>(count), src_len(0), dest_len(0)
    {}

    Editops(const Editops& other)
        : src_len(other.src_len), dest_len(other.dest_len), std::vector<EditOp>(other)
    {}

    Editops(const Opcodes& other);

    Editops(Editops&& other) noexcept
    {
        swap(other);
    }

    Editops& operator=(Editops other)
    {
        swap(other);
        return *this;
    }

    /* Element access */
    using std::vector<EditOp>::at;
    using std::vector<EditOp>::operator[];
    using std::vector<EditOp>::front;
    using std::vector<EditOp>::back;
    using std::vector<EditOp>::data;

    /* Iterators */
    using std::vector<EditOp>::begin;
    using std::vector<EditOp>::cbegin;
    using std::vector<EditOp>::end;
    using std::vector<EditOp>::cend;
    using std::vector<EditOp>::rbegin;
    using std::vector<EditOp>::crbegin;
    using std::vector<EditOp>::rend;
    using std::vector<EditOp>::crend;

    /* Capacity */
    using std::vector<EditOp>::empty;
    using std::vector<EditOp>::size;
    using std::vector<EditOp>::max_size;
    using std::vector<EditOp>::reserve;
    using std::vector<EditOp>::capacity;
    using std::vector<EditOp>::shrink_to_fit;

    /* Modifiers */
    using std::vector<EditOp>::clear;
    using std::vector<EditOp>::insert;
    using std::vector<EditOp>::emplace;
    using std::vector<EditOp>::erase;
    using std::vector<EditOp>::push_back;
    using std::vector<EditOp>::emplace_back;
    using std::vector<EditOp>::pop_back;

    void swap(Editops& rhs) noexcept
    {
        std::swap(src_len, rhs.src_len);
        std::swap(dest_len, rhs.dest_len);
        std::vector<EditOp>::swap(rhs);
    }

    Editops slice(int start, int stop, int step = 1) const
    {
        Editops ed_slice;
        detail::vector_slice(ed_slice, *this, start, stop, step);
        ed_slice.src_len = src_len;
        ed_slice.dest_len = dest_len;
        return ed_slice;
    }

    Editops reverse() const
    {
        Editops reversed = *this;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    size_type get_src_len() const
    {
        return src_len;
    }
    void set_src_len(size_type len)
    {
        src_len = len;
    }
    size_type get_dest_len() const
    {
        return dest_len;
    }
    void set_dest_len(size_type len)
    {
        dest_len = len;
    }

    Editops inverse() const
    {
        Editops inv_ops = *this;
        std::swap(inv_ops.src_len, inv_ops.dest_len);
        for (auto& op : inv_ops) {
            std::swap(op.src_pos, op.dest_pos);
            if (op.type == EditType::Delete) {
                op.type = EditType::Insert;
            }
            else if (op.type == EditType::Insert) {
                op.type = EditType::Delete;
            }
        }
        return inv_ops;
    }

private:
    size_type src_len;
    size_type dest_len;
};

bool operator==(const Editops& lhs, const Editops& rhs)
{
    if (lhs.get_src_len() != rhs.get_src_len() || lhs.get_dest_len() != rhs.get_dest_len()) {
        return false;
    }

    if (lhs.size() != rhs.size()) {
        return false;
    }
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const Editops& lhs, const Editops& rhs)
{
    return !(lhs == rhs);
}

void swap(Editops& lhs, Editops& rhs)
{
    lhs.swap(rhs);
}

class Opcodes : private std::vector<Opcode> {
public:
    using std::vector<Opcode>::size_type;

    Opcodes() : src_len(0), dest_len(0)
    {}

    Opcodes(size_type count, const Opcode& value)
        : std::vector<Opcode>(count, value), src_len(0), dest_len(0)
    {}

    explicit Opcodes(size_type count) : std::vector<Opcode>(count), src_len(0), dest_len(0)
    {}

    Opcodes(const Opcodes& other)
        : src_len(other.src_len), dest_len(other.dest_len), std::vector<Opcode>(other)
    {}

    Opcodes(const Editops& other);

    Opcodes(Opcodes&& other) noexcept
    {
        swap(other);
    }

    Opcodes& operator=(Opcodes other)
    {
        swap(other);
        return *this;
    }

    /* Element access */
    using std::vector<Opcode>::at;
    using std::vector<Opcode>::operator[];
    using std::vector<Opcode>::front;
    using std::vector<Opcode>::back;
    using std::vector<Opcode>::data;

    /* Iterators */
    using std::vector<Opcode>::begin;
    using std::vector<Opcode>::cbegin;
    using std::vector<Opcode>::end;
    using std::vector<Opcode>::cend;
    using std::vector<Opcode>::rbegin;
    using std::vector<Opcode>::crbegin;
    using std::vector<Opcode>::rend;
    using std::vector<Opcode>::crend;

    /* Capacity */
    using std::vector<Opcode>::empty;
    using std::vector<Opcode>::size;
    using std::vector<Opcode>::max_size;
    using std::vector<Opcode>::reserve;
    using std::vector<Opcode>::capacity;
    using std::vector<Opcode>::shrink_to_fit;

    /* Modifiers */
    using std::vector<Opcode>::clear;
    using std::vector<Opcode>::insert;
    using std::vector<Opcode>::emplace;
    using std::vector<Opcode>::erase;
    using std::vector<Opcode>::push_back;
    using std::vector<Opcode>::emplace_back;
    using std::vector<Opcode>::pop_back;

    void swap(Opcodes& rhs) noexcept
    {
        std::swap(src_len, rhs.src_len);
        std::swap(dest_len, rhs.dest_len);
        std::vector<Opcode>::swap(rhs);
    }

    Opcodes slice(int start, int stop, int step = 1) const
    {
        Opcodes ed_slice;
        detail::vector_slice(ed_slice, *this, start, stop, step);
        ed_slice.src_len = src_len;
        ed_slice.dest_len = dest_len;
        return ed_slice;
    }

    Opcodes reverse() const
    {
        Opcodes reversed = *this;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    size_type get_src_len() const
    {
        return src_len;
    }
    void set_src_len(size_type len)
    {
        src_len = len;
    }
    size_type get_dest_len() const
    {
        return dest_len;
    }
    void set_dest_len(size_type len)
    {
        dest_len = len;
    }

    Opcodes inverse() const
    {
        Opcodes inv_ops = *this;
        std::swap(inv_ops.src_len, inv_ops.dest_len);
        for (auto& op : inv_ops) {
            std::swap(op.src_begin, op.dest_begin);
            std::swap(op.src_end, op.dest_end);
            if (op.type == EditType::Delete) {
                op.type = EditType::Insert;
            }
            else if (op.type == EditType::Insert) {
                op.type = EditType::Delete;
            }
        }
        return inv_ops;
    }

private:
    size_type src_len;
    size_type dest_len;
};

bool operator==(const Opcodes& lhs, const Opcodes& rhs)
{
    if (lhs.get_src_len() != rhs.get_src_len() || lhs.get_dest_len() != rhs.get_dest_len()) {
        return false;
    }

    if (lhs.size() != rhs.size()) {
        return false;
    }
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const Opcodes& lhs, const Opcodes& rhs)
{
    return !(lhs == rhs);
}

void swap(Opcodes& lhs, Opcodes& rhs)
{
    lhs.swap(rhs);
}

Editops::Editops(const Opcodes& other)
{
    src_len = other.get_src_len();
    dest_len = other.get_dest_len();
    for (const auto& op : other) {
        switch (op.type) {
        case EditType::None:
            break;

        case EditType::Replace:
            for (size_t j = 0; j < op.src_end - op.src_begin; j++) {
                push_back({EditType::Replace, op.src_begin + j, op.dest_begin + j});
            }
            break;

        case EditType::Insert:
            for (size_t j = 0; j < op.dest_end - op.dest_begin; j++) {
                push_back({EditType::Insert, op.src_begin, op.dest_begin + j});
            }
            break;

        case EditType::Delete:
            for (size_t j = 0; j < op.src_end - op.src_begin; j++) {
                push_back({EditType::Delete, op.src_begin + j, op.dest_begin});
            }
            break;
        }
    }
}

Opcodes::Opcodes(const Editops& other)
{
    src_len = other.get_src_len();
    dest_len = other.get_dest_len();
    size_t src_pos = 0;
    size_t dest_pos = 0;
    for (size_t i = 0; i < other.size();) {
        if (src_pos < other[i].src_pos || dest_pos < other[i].dest_pos) {
            push_back({EditType::None, src_pos, other[i].src_pos, dest_pos, other[i].dest_pos});
            src_pos = other[i].src_pos;
            dest_pos = other[i].dest_pos;
        }

        size_t src_begin = src_pos;
        size_t dest_begin = dest_pos;
        EditType type = other[i].type;
        do {
            switch (type) {
            case EditType::None:
                break;

            case EditType::Replace:
                src_pos++;
                dest_pos++;
                break;

            case EditType::Insert:
                dest_pos++;
                break;

            case EditType::Delete:
                src_pos++;
                break;
            }
            i++;
        } while (i < other.size() && other[i].type == type && src_pos && other[i].src_pos &&
                 dest_pos == other[i].dest_pos);

        push_back({type, src_begin, src_pos, dest_begin, dest_pos});
    }

    if (src_pos < other.get_src_len() || dest_pos < other.get_dest_len()) {
        push_back({EditType::None, src_pos, other.get_src_len(), dest_pos, other.get_dest_len()});
    }
}

} // namespace rapidfuzz
#include <string>

namespace rapidfuzz {

template <typename CharT>
class SplittedSentenceView {
public:
    SplittedSentenceView(string_view_vec<CharT> sentence) : m_sentence(std::move(sentence))
    {}

    size_t dedupe();
    size_t size() const;

    size_t length() const
    {
        return size();
    }

    bool empty() const
    {
        return m_sentence.empty();
    }

    size_t word_count() const
    {
        return m_sentence.size();
    }

    std::basic_string<CharT> join() const;

    string_view_vec<CharT> words() const
    {
        return m_sentence;
    }

private:
    string_view_vec<CharT> m_sentence;
};

template <typename CharT>
size_t SplittedSentenceView<CharT>::dedupe()
{
    size_t old_word_count = word_count();
    m_sentence.erase(std::unique(m_sentence.begin(), m_sentence.end()), m_sentence.end());
    return old_word_count - word_count();
}

template <typename CharT>
size_t SplittedSentenceView<CharT>::size() const
{
    if (m_sentence.empty()) return 0;

    // there is a whitespace between each word
    size_t result = m_sentence.size() - 1;
    for (const auto& word : m_sentence) {
        result += word.size();
    }

    return result;
}

template <typename CharT>
std::basic_string<CharT> SplittedSentenceView<CharT>::join() const
{
    if (m_sentence.empty()) {
        return std::basic_string<CharT>();
    }

    auto sentence_iter = m_sentence.begin();
    std::basic_string<CharT> joined{*sentence_iter};
    const std::basic_string<CharT> whitespace{0x20};
    ++sentence_iter;
    for (; sentence_iter != m_sentence.end(); ++sentence_iter) {
        joined.append(whitespace).append(std::basic_string<CharT>{*sentence_iter});
    }
    return joined;
}

} // namespace rapidfuzz

#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

namespace rapidfuzz {

template <bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

namespace detail {
template <typename T>
auto inner_type(T const*) -> T;

template <typename T>
auto inner_type(T const&) -> typename T::value_type;
} // namespace detail

template <typename T>
using char_type = decltype(detail::inner_type(std::declval<T const&>()));

template <typename... Conds>
struct satisfies_all : std::true_type {};

template <typename Cond, typename... Conds>
struct satisfies_all<Cond, Conds...>
    : std::conditional<Cond::value, satisfies_all<Conds...>, std::false_type>::type {};

template <typename... Conds>
struct satisfies_any : std::false_type {};

template <typename Cond, typename... Conds>
struct satisfies_any<Cond, Conds...>
    : std::conditional<Cond::value, std::true_type, satisfies_any<Conds...>>::type {};

// taken from
// https://stackoverflow.com/questions/16893992/check-if-type-can-be-explicitly-converted
template <typename From, typename To>
struct is_explicitly_convertible {
    template <typename T>
    static void f(T);

    template <typename F, typename T>
    static constexpr auto test(int /*unused*/)
        -> decltype(f(static_cast<T>(std::declval<F>())), true)
    {
        return true;
    }

    template <typename F, typename T>
    static constexpr auto test(...) -> bool
    {
        return false;
    }

    static bool const value = test<From, To>(0);
};

#define GENERATE_HAS_MEMBER(member)                                                                \
                                                                                                   \
    template <typename T>                                                                          \
    struct has_member_##member {                                                                   \
    private:                                                                                       \
        using yes = std::true_type;                                                                \
        using no = std::false_type;                                                                \
                                                                                                   \
        struct Fallback {                                                                          \
            int member;                                                                            \
        };                                                                                         \
        struct Derived : T, Fallback {};                                                           \
                                                                                                   \
        template <class U>                                                                         \
        static no test(decltype(U::member)*);                                                      \
        template <typename U>                                                                      \
        static yes test(U*);                                                                       \
                                                                                                   \
        template <typename U, typename = enable_if_t<std::is_class<U>::value>>                     \
        static constexpr bool class_test(U*)                                                       \
        {                                                                                          \
            return std::is_same<decltype(test<Derived>(nullptr)), yes>::value;                     \
        }                                                                                          \
                                                                                                   \
        template <typename U, typename = enable_if_t<!std::is_class<U>::value>>                    \
        static constexpr bool class_test(const U&)                                                 \
        {                                                                                          \
            return false;                                                                          \
        }                                                                                          \
                                                                                                   \
    public:                                                                                        \
        static constexpr bool value = class_test(static_cast<T*>(nullptr));                        \
    };

GENERATE_HAS_MEMBER(data) // Creates 'has_member_data'
GENERATE_HAS_MEMBER(size) // Creates 'has_member_size'

template <typename Sentence>
using has_data_and_size = satisfies_all<has_member_data<Sentence>, has_member_size<Sentence>>;

// This trait checks if a given type is a standard collection of hashable types
// SFINAE ftw
template <class T>
class is_hashable_sequence {
    is_hashable_sequence() = delete;
    using hashable = char;
    struct not_hashable {
        char t[2];
    }; // Ensured to work on any platform
    template <typename C>
    static hashable matcher(decltype(&std::hash<typename C::value_type>::operator()));
    template <typename C>
    static not_hashable matcher(...);

public:
    static bool const value = (sizeof(matcher<T>(nullptr)) == sizeof(hashable));
};

template <class T>
class is_standard_iterable {
    is_standard_iterable() = delete;
    using iterable = char;
    struct not_iterable {
        char t[2];
    }; // Ensured to work on any platform
    template <typename C>
    static iterable matcher(typename C::const_iterator*);
    template <typename C>
    static not_iterable matcher(...);

public:
    static bool const value = (sizeof(matcher<T>(nullptr)) == sizeof(iterable));
};

template <typename C>
void* sub_matcher(typename C::value_type const& (C::*)(size_t) const);

// TODO: Not a real SFINAE, because of the ambiguity between
// value_type const& operator[](size_t) const;
// and value_type& operator[](size_t);
// Not really important
template <class T>
class has_bracket_operator {
    has_bracket_operator() = delete;
    using has_op = char;
    struct hasnt_op {
        char t[2];
    }; // Ensured to work on any platform
    template <typename C>
    static has_op matcher(decltype(sub_matcher<T>(&T::at)));
    template <typename C>
    static hasnt_op matcher(...);

public:
    static bool const value = (sizeof(matcher<T>(nullptr)) == sizeof(has_op));
};

} // namespace rapidfuzz
#include <tuple>
#include <unordered_map>
#include <vector>

namespace rapidfuzz {

template <typename CharT1, typename CharT2, typename CharT3>
struct DecomposedSet {
    SplittedSentenceView<CharT1> difference_ab;
    SplittedSentenceView<CharT2> difference_ba;
    SplittedSentenceView<CharT3> intersection;
    DecomposedSet(SplittedSentenceView<CharT1> diff_ab, SplittedSentenceView<CharT2> diff_ba,
                  SplittedSentenceView<CharT3> intersect)
        : difference_ab(std::move(diff_ab)),
          difference_ba(std::move(diff_ba)),
          intersection(std::move(intersect))
    {}
};

namespace common {

/**
 * @defgroup Common Common
 * Common utilities shared among multiple functions
 * @{
 */

template <typename CharT1, typename CharT2>
DecomposedSet<CharT1, CharT2, CharT1> set_decomposition(SplittedSentenceView<CharT1> a,
                                                        SplittedSentenceView<CharT2> b);

constexpr double result_cutoff(double result, double score_cutoff)
{
    return (result >= score_cutoff) ? result : 0;
}

template <int Max = 1>
constexpr double norm_distance(size_t dist, size_t lensum, double score_cutoff = 0)
{
    double max = static_cast<double>(Max);
    return result_cutoff((lensum > 0) ? (max - max * dist / lensum) : max, score_cutoff);
}

template <int Max = 1>
static inline size_t score_cutoff_to_distance(double score_cutoff, size_t lensum)
{
    return static_cast<size_t>(std::ceil(static_cast<double>(lensum) * (1.0 - score_cutoff / Max)));
}

template <typename T>
constexpr bool is_zero(T a, T tolerance = std::numeric_limits<T>::epsilon())
{
    return std::fabs(a) <= tolerance;
}

/**
 * @brief Get a string view to the object passed as parameter
 *
 * @tparam Sentence This is a string that can be explicitly converted to
 * basic_string_view<char_type>
 * @tparam CharT This is the char_type of Sentence
 *
 * @param str string that should be converted to string_view (for type info check Template
 * parameters above)
 *
 * @return basic_string_view<CharT> of str
 */
template <
    typename Sentence, typename CharT = char_type<Sentence>,
    typename = enable_if_t<is_explicitly_convertible<Sentence, basic_string_view<CharT>>::value>>
basic_string_view<CharT> to_string_view(Sentence&& str);

/**
 * @brief Get a string view to the object passed as parameter
 *
 * @tparam Sentence This is a string that can not be explicitly converted to
 * basic_string_view<char_type>, but stores a sequence in a similar way (e.g. boost::string_view or
 * std::vector)
 * @tparam CharT This is the char_type of Sentence
 *
 * @param str container that should be converted to string_view (for type info check Template
 * parameters above)
 *
 * @return basic_string_view<CharT> of str
 */
template <
    typename Sentence, typename CharT = char_type<Sentence>,
    typename = enable_if_t<!is_explicitly_convertible<Sentence, basic_string_view<CharT>>::value &&
                           has_data_and_size<Sentence>::value>>
basic_string_view<CharT> to_string_view(const Sentence& str);

template <
    typename Sentence, typename CharT = char_type<Sentence>,
    typename = enable_if_t<is_explicitly_convertible<Sentence, std::basic_string<CharT>>::value>>
std::basic_string<CharT> to_string(Sentence&& str);

template <
    typename Sentence, typename CharT = char_type<Sentence>,
    typename = enable_if_t<!is_explicitly_convertible<Sentence, std::basic_string<CharT>>::value &&
                           has_data_and_size<Sentence>::value>>
std::basic_string<CharT> to_string(const Sentence& str);

/**
 * @brief Finds the first mismatching pair of elements from two ranges:
 * one defined by [first1, last1) and another defined by [first2,last2).
 * Similar implementation to std::mismatch from C++14
 *
 * @param first1, last1	-	the first range of the elements
 * @param first2, last2	-	the second range of the elements
 *
 * @return std::pair with iterators to the first two non-equal elements.
 */
template <typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
                                                   InputIterator2 first2, InputIterator2 last2);

template <typename CharT1, typename CharT2>
StringAffix remove_common_affix(basic_string_view<CharT1>& a, basic_string_view<CharT2>& b);

template <typename CharT1, typename CharT2>
size_t remove_common_prefix(basic_string_view<CharT1>& a, basic_string_view<CharT2>& b);

template <typename CharT1, typename CharT2>
size_t remove_common_suffix(basic_string_view<CharT1>& a, basic_string_view<CharT2>& b);

template <typename Sentence, typename CharT = char_type<Sentence>>
SplittedSentenceView<CharT> sorted_split(Sentence&& sentence);

template <typename T>
constexpr auto to_unsigned(T value) -> typename std::make_unsigned<T>::type
{
    return typename std::make_unsigned<T>::type(value);
}

template <typename T>
constexpr auto to_signed(T value) -> typename std::make_unsigned<T>::type
{
    return typename std::make_signed<T>::type(value);
}

/*
 * taken from https://stackoverflow.com/a/17251989/11335032
 */
template <typename T, typename U>
bool CanTypeFitValue(const U value)
{
    const intmax_t botT = intmax_t(std::numeric_limits<T>::min());
    const intmax_t botU = intmax_t(std::numeric_limits<U>::min());
    const uintmax_t topT = uintmax_t(std::numeric_limits<T>::max());
    const uintmax_t topU = uintmax_t(std::numeric_limits<U>::max());
    return !((botT > botU && value < static_cast<U>(botT)) ||
             (topT < topU && value > static_cast<U>(topT)));
}

struct PatternMatchVector {
    struct MapElem {
        uint64_t key = 0;
        uint64_t value = 0;
    };
    std::array<MapElem, 128> m_map;
    std::array<uint64_t, 256> m_extendedAscii;

    PatternMatchVector() : m_map(), m_extendedAscii()
    {}

    template <typename CharT>
    PatternMatchVector(basic_string_view<CharT> s) : m_map(), m_extendedAscii()
    {
        insert(s);
    }

    template <typename CharT>
    void insert(basic_string_view<CharT> s)
    {
        uint64_t mask = 1;
        for (size_t i = 0; i < s.size(); ++i) {
            insert_mask(s[i], mask);
            mask <<= 1;
        }
    }

    template <typename CharT>
    void insert(CharT key, size_t pos)
    {
        insert_mask(key, 1ull << pos);
    }

    template <typename CharT>
    uint64_t get(CharT key) const
    {
        if (key >= 0 && key <= 255) {
            return m_extendedAscii[key];
        }
        else {
            return m_map[lookup((uint64_t)key)].value;
        }
    }

private:
    template <typename CharT>
    void insert_mask(CharT key, uint64_t mask)
    {
        if (key >= 0 && key <= 255) {
            m_extendedAscii[key] |= mask;
        }
        else {
            size_t i = lookup((uint64_t)key);
            m_map[i].key = key;
            m_map[i].value |= mask;
        }
    }

    /**
     * lookup key inside the hasmap using a similar collision resolution
     * strategy to CPython and Ruby
     */
    size_t lookup(uint64_t key) const
    {
        size_t i = key % 128;

        if (!m_map[i].value || m_map[i].key == key) {
            return i;
        }

        size_t perturb = key;
        while (true) {
            i = ((i * 5) + perturb + 1) % 128;
            if (!m_map[i].value || m_map[i].key == key) {
                return i;
            }

            perturb >>= 5;
        }
    }
};

struct BlockPatternMatchVector {
    std::vector<PatternMatchVector> m_val;

    BlockPatternMatchVector()
    {}

    template <typename CharT>
    BlockPatternMatchVector(basic_string_view<CharT> s)
    {
        insert(s);
    }

    template <typename CharT>
    void insert(size_t block, CharT ch, int pos)
    {
        auto* be = &m_val[block];
        be->insert(ch, pos);
    }

    template <typename CharT>
    void insert(basic_string_view<CharT> s)
    {
        size_t block_count = (s.size() / 64) + (size_t)((s.size() % 64) != 0);
        m_val.resize(block_count);

        for (size_t block = 0; block < block_count; ++block) {
            m_val[block].insert(s.substr(block * 64, 64));
        }
    }

    template <typename CharT>
    uint64_t get(size_t block, CharT ch) const
    {
        auto* be = &m_val[block];
        return be->get(ch);
    }
};

template <typename CharT1, typename ValueType, size_t size = sizeof(CharT1)>
struct CharHashTable;

template <typename CharT1, typename ValueType>
struct CharHashTable<CharT1, ValueType, 1> {
    using UCharT1 = typename std::make_unsigned<CharT1>::type;

    std::array<ValueType, std::numeric_limits<UCharT1>::max() + 1> m_val;
    ValueType m_default;

    CharHashTable() : m_val{}, m_default{}
    {}

    ValueType& create(CharT1 ch)
    {
        return m_val[UCharT1(ch)];
    }

    template <typename CharT2>
    const ValueType& operator[](CharT2 ch) const
    {
        if (!CanTypeFitValue<CharT1>(ch)) {
            return m_default;
        }

        return m_val[UCharT1(ch)];
    }
};

template <typename CharT1, typename ValueType, size_t size>
struct CharHashTable {
    std::unordered_map<CharT1, ValueType> m_val;
    ValueType m_default;

    CharHashTable() : m_val{}, m_default{}
    {}

    ValueType& create(CharT1 ch)
    {
        return m_val[ch];
    }

    template <typename CharT2>
    const ValueType& operator[](CharT2 ch) const
    {
        if (!CanTypeFitValue<CharT1>(ch)) {
            return m_default;
        }

        auto search = m_val.find(CharT1(ch));
        if (search == m_val.end()) {
            return m_default;
        }

        return search->second;
    }
};

template <typename T>
struct MatrixVectorView {
    explicit MatrixVectorView(T* vector, size_t cols) : m_vector(vector), m_cols(cols)
    {}

    T& operator[](uint64_t col)
    {
        assert(col < m_cols);
        return m_vector[col];
    }

private:
    T* m_vector;
    size_t m_cols;
};

template <typename T>
struct ConstMatrixVectorView {
    explicit ConstMatrixVectorView(const T* vector, size_t cols) : m_vector(vector), m_cols(cols)
    {}

    ConstMatrixVectorView(const MatrixVectorView<T>& other) : m_vector(other.m_vector)
    {}

    const T& operator[](uint64_t col)
    {
        assert(col < m_cols);
        return m_vector[col];
    }

private:
    const T* m_vector;
    size_t m_cols;
};

template <typename T>
struct Matrix {
    Matrix(uint64_t rows, uint64_t cols, uint64_t val)
    {
        m_rows = rows;
        m_cols = cols;
        if (rows * cols > 0) {
            m_matrix = new T[rows * cols];
            std::fill_n(m_matrix, rows * cols, val);
        }
        else {
            m_matrix = nullptr;
        }
    }

    ~Matrix()
    {
        delete[] m_matrix;
    }

    MatrixVectorView<uint64_t> operator[](uint64_t row)
    {
        assert(row < m_rows);
        return MatrixVectorView<uint64_t>(&m_matrix[row * m_cols], m_rows);
    }

    ConstMatrixVectorView<uint64_t> operator[](uint64_t row) const
    {
        assert(row < m_rows);
        return ConstMatrixVectorView<uint64_t>(&m_matrix[row * m_cols], m_rows);
    }

private:
    uint64_t m_rows;
    uint64_t m_cols;
    T* m_matrix;
};

/**@}*/

} // namespace common
} // namespace rapidfuzz


#include <algorithm>
#include <array>
#include <cctype>
#include <cwctype>

namespace rapidfuzz {

template <typename CharT1, typename CharT2>
bool string_view_eq(basic_string_view<CharT1> x, basic_string_view<CharT2> y)
{
    if (x.size() != y.size()) return false;

    for (size_t i = 0; i < x.size(); ++i) {
        if (x[i] != y[i]) return false;
    }
    return true;
}

template <typename CharT1, typename CharT2>
DecomposedSet<CharT1, CharT2, CharT1> common::set_decomposition(SplittedSentenceView<CharT1> a,
                                                                SplittedSentenceView<CharT2> b)
{
    a.dedupe();
    b.dedupe();

    string_view_vec<CharT1> intersection;
    string_view_vec<CharT1> difference_ab;
    string_view_vec<CharT2> difference_ba = b.words();

    for (const auto& current_a : a.words()) {
        auto element_b = std::find_if(difference_ba.begin(), difference_ba.end(),
                                      [current_a](basic_string_view<CharT2> current_b) {
                                          return string_view_eq(current_a, current_b);
                                      });

        if (element_b != difference_ba.end()) {
            difference_ba.erase(element_b);
            intersection.push_back(current_a);
        }
        else {
            difference_ab.push_back(current_a);
        }
    }

    return {difference_ab, difference_ba, intersection};
}

template <typename Sentence, typename CharT, typename>
basic_string_view<CharT> common::to_string_view(Sentence&& str)
{
    return basic_string_view<CharT>(std::forward<Sentence>(str));
}

template <typename Sentence, typename CharT, typename>
basic_string_view<CharT> common::to_string_view(const Sentence& str)
{
    return basic_string_view<CharT>(str.data(), str.size());
}

template <typename Sentence, typename CharT, typename>
std::basic_string<CharT> common::to_string(Sentence&& str)
{
    return std::basic_string<CharT>(std::forward<Sentence>(str));
}

template <typename Sentence, typename CharT, typename>
std::basic_string<CharT> common::to_string(const Sentence& str)
{
    return std::basic_string<CharT>(str.data(), str.size());
}

template <typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2>
common::mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                 InputIterator2 last2)
{
    while (first1 != last1 && first2 != last2 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

/**
 * Removes common prefix of two string views
 */
template <typename CharT1, typename CharT2>
size_t common::remove_common_prefix(basic_string_view<CharT1>& a, basic_string_view<CharT2>& b)
{
    size_t prefix = static_cast<size_t>(
        std::distance(a.begin(), common::mismatch(a.begin(), a.end(), b.begin(), b.end()).first));
    a.remove_prefix(prefix);
    b.remove_prefix(prefix);
    return prefix;
}

/**
 * Removes common suffix of two string views
 */
template <typename CharT1, typename CharT2>
size_t common::remove_common_suffix(basic_string_view<CharT1>& a, basic_string_view<CharT2>& b)
{
    size_t suffix = static_cast<size_t>(std::distance(
        a.rbegin(), common::mismatch(a.rbegin(), a.rend(), b.rbegin(), b.rend()).first));
    a.remove_suffix(suffix);
    b.remove_suffix(suffix);
    return suffix;
}

/**
 * Removes common affix of two string views
 */
template <typename CharT1, typename CharT2>
StringAffix common::remove_common_affix(basic_string_view<CharT1>& a, basic_string_view<CharT2>& b)
{
    return StringAffix{remove_common_prefix(a, b), remove_common_suffix(a, b)};
}

template <typename, typename = void>
struct is_space_dispatch_tag : std::integral_constant<int, 0> {};

template <typename CharT>
struct is_space_dispatch_tag<CharT, typename std::enable_if<sizeof(CharT) == 1>::type>
    : std::integral_constant<int, 1> {};

/*
 * Implementation of is_space for char types that are at least 2 Byte in size
 */
template <typename CharT>
bool is_space_impl(const CharT ch, std::integral_constant<int, 0>)
{
    switch (ch) {
    case 0x0009:
    case 0x000A:
    case 0x000B:
    case 0x000C:
    case 0x000D:
    case 0x001C:
    case 0x001D:
    case 0x001E:
    case 0x001F:
    case 0x0020:
    case 0x0085:
    case 0x00A0:
    case 0x1680:
    case 0x2000:
    case 0x2001:
    case 0x2002:
    case 0x2003:
    case 0x2004:
    case 0x2005:
    case 0x2006:
    case 0x2007:
    case 0x2008:
    case 0x2009:
    case 0x200A:
    case 0x2028:
    case 0x2029:
    case 0x202F:
    case 0x205F:
    case 0x3000:
        return true;
    }
    return false;
}

/*
 * Implementation of is_space for char types that are 1 Byte in size
 */
template <typename CharT>
bool is_space_impl(const CharT ch, std::integral_constant<int, 1>)
{
    switch (ch) {
    case 0x0009:
    case 0x000A:
    case 0x000B:
    case 0x000C:
    case 0x000D:
    case 0x001C:
    case 0x001D:
    case 0x001E:
    case 0x001F:
    case 0x0020:
        return true;
    }
    return false;
}

/*
 * checks whether unicode characters have the bidirectional
 * type 'WS', 'B' or 'S' or the category 'Zs'
 */
template <typename CharT>
bool is_space(const CharT ch)
{
    return is_space_impl(ch, is_space_dispatch_tag<CharT>{});
}

template <typename Sentence, typename CharT>
SplittedSentenceView<CharT> common::sorted_split(Sentence&& sentence)
{
    auto s = to_string_view(std::forward<Sentence>(sentence));
    string_view_vec<CharT> splitted;
    const auto* first = s.data();
    const auto* second = s.data();
    const auto* last = first + s.size();

    for (; second != last && first != last; first = second + 1) {
        second = std::find_if(first, last, is_space<CharT>);

        if (first != second) {
            splitted.emplace_back(first, second - first);
        }
    }

    std::sort(splitted.begin(), splitted.end());

    return SplittedSentenceView<CharT>(splitted);
}

} // namespace rapidfuzz

#include <type_traits>

namespace rapidfuzz {
namespace fuzz {

/**
 * @defgroup Fuzz Fuzz
 * A collection of string matching algorithms from FuzzyWuzzy
 * @{
 */

/**
 * @brief calculates a simple ratio between two strings
 *
 * @details
 * @code{.cpp}
 * // score is 96.55
 * double score = ratio("this is a test", "this is a test!")
 * @endcode
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2>
double ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// TODO documentation
template <typename Sentence1>
struct CachedRatio {
    using CharT1 = char_type<Sentence1>;

    CachedRatio(const Sentence1& s1) : s1_view(common::to_string_view(s1)), blockmap_s1(s1_view)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
    common::BlockPatternMatchVector blockmap_s1;
};

/**
 * @brief calculates the fuzz::ratio of the optimal string alignment
 *
 * @details
 * test @cite hyrro_2004 @cite wagner_fischer_1974
 * @code{.cpp}
 * // score is 100
 * double score = partial_ratio("this is a test", "this is a test!")
 * @endcode
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2, typename CharT1 = char_type<Sentence1>,
          typename CharT2 = char_type<Sentence2>>
double partial_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// todo add real implementation
template <typename Sentence1>
struct CachedPartialRatio {
    template <typename>
    friend struct CachedWRatio;
    using CharT1 = char_type<Sentence1>;

    CachedPartialRatio(const Sentence1& s1);

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
    common::CharHashTable<CharT1, bool> s1_char_map;
    CachedRatio<Sentence1> cached_ratio;
};

/**
 * @brief Sorts the words in the strings and calculates the fuzz::ratio between
 * them
 *
 * @details
 * @code{.cpp}
 * // score is 100
 * double score = token_sort_ratio("fuzzy wuzzy was a bear", "wuzzy fuzzy was a
 * bear")
 * @endcode
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2, typename CharT1 = char_type<Sentence1>,
          typename CharT2 = char_type<Sentence2>>
double token_sort_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);
// todo CachedRatio speed for equal strings vs original implementation
// TODO documentation
template <typename Sentence1>
struct CachedTokenSortRatio {
    using CharT1 = char_type<Sentence1>;

    CachedTokenSortRatio(const Sentence1& s1)
        : s1_sorted(common::sorted_split(s1).join()), cached_ratio(s1_sorted)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    std::basic_string<CharT1> s1_sorted;
    CachedRatio<Sentence1> cached_ratio;
};

/**
 * @brief Sorts the words in the strings and calculates the fuzz::partial_ratio
 * between them
 *
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2, typename CharT1 = char_type<Sentence1>,
          typename CharT2 = char_type<Sentence2>>
double partial_token_sort_ratio(const Sentence1& s1, const Sentence2& s2,
                                 double score_cutoff = 0);

// TODO documentation
template <typename Sentence1>
struct CachedPartialTokenSortRatio {
    using CharT1 = char_type<Sentence1>;

    CachedPartialTokenSortRatio(const Sentence1& s1)
        : s1_sorted(common::sorted_split(s1).join()), cached_partial_ratio(s1_sorted)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    std::basic_string<CharT1> s1_sorted;
    CachedPartialRatio<Sentence1> cached_partial_ratio;
};

/**
 * @brief Compares the words in the strings based on unique and common words
 * between them using fuzz::ratio
 *
 * @details
 * @code{.cpp}
 * // score1 is 83.87
 * double score1 = token_sort_ratio("fuzzy was a bear", "fuzzy fuzzy was a
 * bear")
 * // score2 is 100
 * double score2 = token_set_ratio("fuzzy was a bear", "fuzzy fuzzy was a bear")
 * @endcode
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2>
double token_set_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// TODO documentation
template <typename Sentence1>
struct CachedTokenSetRatio {
    using CharT1 = char_type<Sentence1>;

    CachedTokenSetRatio(const Sentence1& s1);

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    SplittedSentenceView<CharT1> tokens_s1;
};

/**
 * @brief Compares the words in the strings based on unique and common words
 * between them using fuzz::partial_ratio
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2, typename CharT1 = char_type<Sentence1>,
          typename CharT2 = char_type<Sentence2>>
double partial_token_set_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// TODO documentation
template <typename Sentence1>
struct CachedPartialTokenSetRatio {
    using CharT1 = char_type<Sentence1>;

    CachedPartialTokenSetRatio(const Sentence1& s1);

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    SplittedSentenceView<CharT1> tokens_s1;
};

/**
 * @brief Helper method that returns the maximum of fuzz::token_set_ratio and
 * fuzz::token_sort_ratio (faster than manually executing the two functions)
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2>
double token_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// todo add real implementation
template <typename Sentence1>
struct CachedTokenRatio {
    using CharT1 = char_type<Sentence1>;

    CachedTokenRatio(const Sentence1& s1)
        : s1_tokens(common::sorted_split(s1)),
          s1_sorted(s1_tokens.join()),
          cached_ratio_s1_sorted(s1_sorted)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    SplittedSentenceView<CharT1> s1_tokens;
    std::basic_string<CharT1> s1_sorted;
    CachedRatio<Sentence1> cached_ratio_s1_sorted;
};

/**
 * @brief Helper method that returns the maximum of
 * fuzz::partial_token_set_ratio and fuzz::partial_token_sort_ratio (faster than
 * manually executing the two functions)
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2, typename CharT1 = char_type<Sentence1>,
          typename CharT2 = char_type<Sentence2>>
double partial_token_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// todo add real implementation
template <typename Sentence1>
struct CachedPartialTokenRatio {
    using CharT1 = char_type<Sentence1>;

    CachedPartialTokenRatio(const Sentence1& s1);

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    SplittedSentenceView<CharT1> tokens_s1;
    std::basic_string<CharT1> s1_sorted;
};

/**
 * @brief Calculates a weighted ratio based on the other ratio algorithms
 *
 * @details
 * @todo add a detailed description
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2>
double WRatio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

// todo add real implementation
template <typename Sentence1>
struct CachedWRatio {
    using CharT1 = char_type<Sentence1>;

    CachedWRatio(const Sentence1& s1);

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    // todo somehow implement this using other ratios with creating PatternMatchVector
    // multiple times
    CachedPartialRatio<Sentence1> cached_partial_ratio;
    rapidfuzz::basic_string_view<CharT1> s1_view;
    SplittedSentenceView<CharT1> tokens_s1;
    std::basic_string<CharT1> s1_sorted;
    common::BlockPatternMatchVector blockmap_s1_sorted;
};

/**
 * @brief Calculates a quick ratio between two strings using fuzz.ratio
 *
 * @details
 * @todo add a detailed description
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1 string to compare with s2 (for type info check Template parameters
 * above)
 * @param s2 string to compare with s1 (for type info check Template parameters
 * above)
 * @param score_cutoff Optional argument for a score threshold between 0% and
 * 100%. Matches with a lower score than this number will not be returned.
 * Defaults to 0.
 *
 * @return returns the ratio between s1 and s2 or 0 when ratio < score_cutoff
 */
template <typename Sentence1, typename Sentence2>
double QRatio(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0);

template <typename Sentence1>
struct CachedQRatio {
    using CharT1 = char_type<Sentence1>;

    CachedQRatio(const Sentence1& s1) : s1_view(common::to_string_view(s1)), cached_ratio(s1)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const;

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
    CachedRatio<Sentence1> cached_ratio;
};

/**@}*/

} // namespace fuzz
} // namespace rapidfuzz


// The MIT License (MIT)
//
// Copyright (c) 2020 Max Bachmann
// Copyright (c) 2014 Jean-Bernard Jansen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.



#include <algorithm>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace rapidfuzz {
namespace detail {
struct MatchingBlock {
    size_t spos;
    size_t dpos;
    size_t length;
    MatchingBlock(size_t aSPos, size_t aDPos, size_t aLength)
        : spos(aSPos), dpos(aDPos), length(aLength)
    {}
};

namespace difflib {

template <typename CharT1, typename CharT2>
class SequenceMatcher {
public:
    using match_t = std::tuple<size_t, size_t, size_t>;

    SequenceMatcher(basic_string_view<CharT1> a, basic_string_view<CharT2> b) : a_(a), b_(b)
    {
        j2len_.resize(b.size() + 1);
        for (size_t i = 0; i < b.size(); ++i) {
            b2j_.create(b[i]).push_back(i);
        }
    }

    match_t find_longest_match(size_t a_low, size_t a_high, size_t b_low,
                               size_t b_high)
    {
        size_t best_i = a_low;
        size_t best_j = b_low;
        size_t best_size = 0;

        // Find longest junk free match
        {
            for (size_t i = a_low; i < a_high; ++i) {
                const auto& indexes = b2j_[a_[i]];
                size_t pos = 0;
                size_t next_val = 0;
                for (; pos < indexes.size(); pos++) {
                    size_t j = indexes[pos];
                    if (j < b_low) continue;

                    next_val = j2len_[j];
                    break;
                }

                for (; pos < indexes.size(); pos++) {
                    size_t j = indexes[pos];
                    if (j >= b_high) break;

                    size_t k = next_val + 1;

                    /* the next value might be overwritten below
                     * so cache it */
                    if (pos + 1 < indexes.size()) {
                        next_val = j2len_[indexes[pos + 1]];
                    }

                    j2len_[j + 1] = k;
                    if (k > best_size) {
                        best_i = i - k + 1;
                        best_j = j - k + 1;
                        best_size = k;
                    }
                }
            }

            std::fill(
                j2len_.begin() + static_cast<std::vector<size_t>::difference_type>(b_low),
                j2len_.begin() + static_cast<std::vector<size_t>::difference_type>(b_high), 0);
        }

        while (best_i > a_low && best_j > b_low && a_[best_i - 1] == b_[best_j - 1]) {
            --best_i;
            --best_j;
            ++best_size;
        }

        while ((best_i + best_size) < a_high && (best_j + best_size) < b_high &&
               a_[best_i + best_size] == b_[best_j + best_size])
        {
            ++best_size;
        }

        return std::make_tuple(best_i, best_j, best_size);
    }

    std::vector<MatchingBlock> get_matching_blocks()
    {
        // The following are tuple extracting aliases
        std::vector<std::tuple<size_t, size_t, size_t, size_t>> queue;
        std::vector<match_t> matching_blocks_pass1;

        size_t queue_head = 0;
        queue.reserve(std::min(a_.size(), b_.size()));
        queue.emplace_back(0, a_.size(), 0, b_.size());

        while (queue_head < queue.size()) {
            size_t a_low, a_high, b_low, b_high;
            std::tie(a_low, a_high, b_low, b_high) = queue[queue_head++];
            size_t spos, dpos, length;
            std::tie(spos, dpos, length) = find_longest_match(a_low, a_high, b_low, b_high);
            if (length) {
                if (a_low < spos && b_low < dpos) {
                    queue.emplace_back(a_low, spos, b_low, dpos);
                }
                if ((spos + length) < a_high && (dpos + length) < b_high) {
                    queue.emplace_back(spos + length, a_high, dpos + length, b_high);
                }
                matching_blocks_pass1.emplace_back(spos, dpos, length);
            }
        }
        std::sort(std::begin(matching_blocks_pass1), std::end(matching_blocks_pass1));

        std::vector<MatchingBlock> matching_blocks;

        matching_blocks.reserve(matching_blocks_pass1.size());

        size_t i1, j1, k1;
        i1 = j1 = k1 = 0;

        for (match_t const& m : matching_blocks_pass1) {
            if (i1 + k1 == std::get<0>(m) && j1 + k1 == std::get<1>(m)) {
                k1 += std::get<2>(m);
            }
            else {
                if (k1) {
                    matching_blocks.emplace_back(i1, j1, k1);
                }
                std::tie(i1, j1, k1) = m;
            }
        }
        if (k1) {
            matching_blocks.emplace_back(i1, j1, k1);
        }
        matching_blocks.emplace_back(a_.size(), b_.size(), 0);

        return matching_blocks;
    }

protected:
    basic_string_view<CharT1> a_;
    basic_string_view<CharT2> b_;

private:
    // Cache to avoid reallocations
    std::vector<size_t> j2len_;
    common::CharHashTable<CharT2, std::vector<size_t>> b2j_;
};
} // namespace difflib

template <typename CharT1, typename CharT2>
std::vector<MatchingBlock> get_matching_blocks(basic_string_view<CharT1> s1,
                                               basic_string_view<CharT2> s2)
{
    return difflib::SequenceMatcher<CharT1, CharT2>(s1, s2).get_matching_blocks();
}

} /* namespace detail */
} /* namespace rapidfuzz */


#include <algorithm>
#include <array>
#include <limits>
#include <numeric>

namespace rapidfuzz {
namespace string_metric {
namespace detail {

template <typename CharT1, typename CharT2>
size_t generic_levenshtein_wagner_fischer(basic_string_view<CharT1> s1,
                                               basic_string_view<CharT2> s2,
                                               LevenshteinWeightTable weights, size_t max)
{
    std::vector<size_t> cache(s1.size() + 1);

    cache[0] = 0;
    for (size_t i = 1; i < cache.size(); ++i) {
        cache[i] = cache[i - 1] + weights.delete_cost;
    }

    for (const auto& char2 : s2) {
        auto cache_iter = cache.begin();
        size_t temp = *cache_iter;
        *cache_iter += weights.insert_cost;

        for (const auto& char1 : s1) {
            if (char1 != char2) {
                temp = std::min({*cache_iter + weights.delete_cost,
                                 *(cache_iter + 1) + weights.insert_cost,
                                 temp + weights.replace_cost});
            }
            ++cache_iter;
            std::swap(*cache_iter, temp);
        }
    }

    return (cache.back() <= max) ? cache.back() : (size_t)-1;
}

template <typename CharT1, typename CharT2>
size_t generic_levenshtein(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                                LevenshteinWeightTable weights, size_t max)
{
    // do not swap the strings, since insertion/deletion cost can be different
    if (s1.size() >= s2.size()) {
        // at least length difference deletions required
        if ((s1.size() - s2.size()) * weights.delete_cost > max) {
            return (size_t)-1;
        }
    }
    else {
        // at least length difference insertions required
        if ((s2.size() - s1.size()) * weights.insert_cost > max) {
            return (size_t)-1;
        }
    }

    // The Levenshtein distance between <prefix><string1><suffix> and <prefix><string2><suffix>
    // is similar to the distance between <string1> and <string2>, so they can be removed in linear
    // time
    common::remove_common_affix(s1, s2);

    return generic_levenshtein_wagner_fischer(s1, s2, weights, max);
}

template <typename CharT1, typename CharT2>
double normalized_generic_levenshtein(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                                      LevenshteinWeightTable weights, const double score_cutoff)
{
    if (s1.empty() || s2.empty()) {
        return static_cast<double>(s1.empty() && s2.empty());
    }

    // calculate the maximum possible edit distance from the weights
    size_t max_dist = 0;
    if (s1.size() >= s2.size()) {
        max_dist = std::min(
            // delete all characters from s1 and insert all characters from s2
            s1.size() * weights.delete_cost + s2.size() * weights.insert_cost,
            // replace all characters and delete the remaining characters from s1
            s2.size() * weights.replace_cost + (s1.size() - s2.size()) * weights.delete_cost);
    }
    else {
        max_dist = std::min(
            // delete all characters from s1 and insert all characters from s2
            s1.size() * weights.delete_cost + s2.size() * weights.insert_cost,
            // replace all characters and insert the remaining characters into s1
            s1.size() * weights.replace_cost + (s2.size() - s1.size()) * weights.insert_cost);
    }

    auto cutoff_distance = common::score_cutoff_to_distance(score_cutoff, max_dist);

    size_t dist = generic_levenshtein(s1, s2, weights, cutoff_distance);
    return (dist != (size_t)-1) ? common::norm_distance(dist, max_dist, score_cutoff) : 0.0;
}

} // namespace detail
} // namespace string_metric
} // namespace rapidfuzz



#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER) && !defined(__clang__)
#    include <intrin.h>
#endif

namespace rapidfuzz {
namespace intrinsics {

static inline uint64_t addc64(uint64_t a, uint64_t b, uint64_t carryin, uint64_t* carryout)
{
    /* todo should use _addcarry_u64 when available */
    a += carryin;
    *carryout = a < carryin;
    a += b;
    *carryout |= a < b;
    return a;
}

static inline size_t popcount64(uint64_t x)
{
    const uint64_t m1 = 0x5555555555555555;
    const uint64_t m2 = 0x3333333333333333;
    const uint64_t m4 = 0x0f0f0f0f0f0f0f0f;
    const uint64_t h01 = 0x0101010101010101;

    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    return static_cast<size_t>((x * h01) >> 56);
}

/**
 * Extract the lowest set bit from a. If no bits are set in a returns 0.
 */
template <typename T>
T blsi(T a)
{
    return a & -a;
}

/**
 * Clear the lowest set bit in a.
 */
template <typename T>
T blsr(T x)
{
    return x & (x - 1);
}

/**
 * Sets all the lower bits of the result to 1 up to and including lowest set bit (=1) in a.
 * If a is zero, blsmsk sets all bits to 1.
 */
template <typename T>
T blsmsk(T a)
{
    return a ^ (a - 1);
}

#if defined(_MSC_VER) && !defined(__clang__)
static inline int tzcnt(uint32_t x)
{
    unsigned long trailing_zero = 0;
    _BitScanForward(&trailing_zero, x);
    return trailing_zero;
}

#    if defined(_M_ARM) || defined(_M_X64)
static inline int tzcnt(uint64_t x)
{
    unsigned long trailing_zero = 0;
    _BitScanForward64(&trailing_zero, x);
    return trailing_zero;
}
#    else
static inline int tzcnt(uint64_t x)
{
    uint32_t msh = (uint32_t)(x >> 32);
    uint32_t lsh = (uint32_t)(x & 0xFFFFFFFF);
    if (lsh != 0) {
        return tzcnt(lsh);
    }
    return 32 + tzcnt(msh);
}
#    endif

#else /*  gcc / clang */
static inline int tzcnt(uint32_t x)
{
    return __builtin_ctz(x);
}

static inline int tzcnt(uint64_t x)
{
    return __builtin_ctzll(x);
}
#endif

} // namespace intrinsics
} // namespace rapidfuzz

namespace rapidfuzz {
namespace string_metric {
namespace detail {

template <typename CharT>
bool isnum(CharT val)
{
    return (val >= '0') && (val <= '9');
}

template <typename CharT1, typename CharT2>
static inline double jaro_calculate_similarity(basic_string_view<CharT1> P,
                                                basic_string_view<CharT2> T, size_t CommonChars,
                                                size_t Transpositions)
{
    Transpositions /= 2;
    double Sim = (double)CommonChars / (double)P.size() + (double)CommonChars / (double)T.size() +
                 (double)(CommonChars - Transpositions) / (double)CommonChars;
    return Sim / 3.0;
}

template <typename CharT1, typename CharT2>
static inline bool jaro_length_filter(basic_string_view<CharT1> P, basic_string_view<CharT2> T,
                                      double score_cutoff)
{
    if (!T.size() || !P.size()) return false;

    double min_len = (double)std::min(P.size(), T.size());
    double Sim = (double)min_len / (double)P.size() + (double)min_len / (double)T.size() + 1.0;
    Sim /= 3.0;
    return Sim >= score_cutoff;
}

template <typename CharT1, typename CharT2>
static inline bool jaro_common_char_filter(basic_string_view<CharT1> P, basic_string_view<CharT2> T,
                                           size_t CommonChars, double score_cutoff)
{
    if (!CommonChars) return false;

    double Sim =
        (double)CommonChars / (double)P.size() + (double)CommonChars / (double)T.size() + 1.0;
    Sim /= 3.0;
    return Sim >= score_cutoff;
}

struct FlaggedCharsOriginal {
    std::vector<int> P_flag;
    std::vector<int> T_flag;
    size_t CommonChars;
};

template <typename CharT1, typename CharT2>
static inline FlaggedCharsOriginal flag_similar_characters_original(basic_string_view<CharT1> P,
                                                                    basic_string_view<CharT2> T)
{
    std::vector<int> P_flag(P.size() + 1);
    std::vector<int> T_flag(T.size() + 1);

    size_t Bound = std::max(P.size(), T.size()) / 2;
    if (Bound > 0) Bound--;

    size_t CommonChars = 0;
    for (size_t i = 0; i < T.size(); i++) {
        size_t lowlim = (i >= Bound) ? i - Bound : 0;
        size_t hilim = (i + Bound <= P.size() - 1) ? (i + Bound) : P.size() - 1;
        for (size_t j = lowlim; j <= hilim; j++) {
            if (!P_flag[j] && P[j] == T[i]) {
                T_flag[i] = 1;
                P_flag[j] = 1;
                CommonChars++;
                break;
            }
        }
    }

    return {P_flag, T_flag, CommonChars};
}

struct FlaggedCharsWord {
    uint64_t P_flag;
    uint64_t T_flag;
    size_t CommonChars;
};

template <typename CharT1, typename CharT2>
static inline FlaggedCharsWord flag_similar_characters_word(const common::PatternMatchVector& PM,
                                                            basic_string_view<CharT1> P,
                                                            basic_string_view<CharT2> T)
{
    using namespace intrinsics;
    assert(P.size() <= 64);
    assert(T.size() <= 64);

    uint64_t P_flag = 0;
    uint64_t T_flag = 0;
    uint64_t Bound = std::max(P.size(), T.size()) / 2 - 1;
    uint64_t BoundMask = (1ull << 1 << Bound) - 1;

    size_t j = 0;
    for (; j < std::min(Bound, (uint64_t)T.size()); ++j) {
        uint64_t PM_j = PM.get(T[j]) & BoundMask & (~P_flag);

        P_flag |= blsi(PM_j);
        T_flag |= (uint64_t)(PM_j != 0) << j;

        BoundMask = (BoundMask << 1) | 1;
    }

    for (; j < std::min((uint64_t)T.size(), (uint64_t)P.size() + Bound); ++j) {
        uint64_t PM_j = PM.get(T[j]) & BoundMask & (~P_flag);

        P_flag |= blsi(PM_j);
        T_flag |= (uint64_t)(PM_j != 0) << j;

        BoundMask <<= 1;
    }

    return {P_flag, T_flag, popcount64(P_flag)};
}

template <typename CharT>
static inline size_t count_transpositions_word(const common::PatternMatchVector& PM,
                                               uint64_t P_mapped, basic_string_view<CharT> T,
                                               uint64_t T_mapped)
{
    using namespace intrinsics;
    size_t Transpositions = 0;
    while (T_mapped) {
        uint64_t PatternFlagMask = blsi(P_mapped);

        Transpositions += !(PM.get(T[tzcnt(T_mapped)]) & PatternFlagMask);

        T_mapped = blsr(T_mapped);
        P_mapped ^= PatternFlagMask;
    }

    return Transpositions;
}

template <typename CharT1, typename CharT2>
double jaro_similarity_word(basic_string_view<CharT1> P, basic_string_view<CharT2> T,
                            double score_cutoff)
{
    if (!jaro_length_filter(P, T, score_cutoff)) {
        return 0.0;
    }

    common::PatternMatchVector PM(P);

    auto flagged = flag_similar_characters_word(PM, P, T);

    if (!jaro_common_char_filter(P, T, flagged.CommonChars, score_cutoff)) {
        return 0.0;
    }

    size_t Transpositions = count_transpositions_word(PM, flagged.P_flag, T, flagged.T_flag);

    return common::result_cutoff(
        jaro_calculate_similarity(P, T, flagged.CommonChars, Transpositions), score_cutoff);
}

template <typename CharT1, typename CharT2>
double jaro_similarity_original(basic_string_view<CharT2> P, basic_string_view<CharT1> T,
                                 double score_cutoff)
{
    if (!jaro_length_filter(P, T, score_cutoff)) {
        return 0.0;
    }

    auto flagged = flag_similar_characters_original(P, T);

    if (!jaro_common_char_filter(P, T, flagged.CommonChars, score_cutoff)) {
        return 0.0;
    }
    // Count the number of transpositions
    size_t Transpositions = 0;
    size_t k = 0;
    for (size_t i = 0; i < T.size(); i++) {
        if (flagged.T_flag[i]) {
            size_t j = k;
            for (; j < P.size(); j++) {
                if (flagged.P_flag[j]) {
                    k = j + 1;
                    break;
                }
            }
            if (T[i] != P[j]) {
                Transpositions++;
            }
        }
    }

    return common::result_cutoff(
        jaro_calculate_similarity(P, T, flagged.CommonChars, Transpositions), score_cutoff);
}

template <typename CharT1, typename CharT2>
double jaro_similarity(basic_string_view<CharT2> P, basic_string_view<CharT1> T,
                        double score_cutoff)
{
    if (P.size() <= 64 && P.size() <= 64) {
        return jaro_similarity_word(P, T, score_cutoff);
    }
    else {
        return jaro_similarity_original(P, T, score_cutoff);
    }
}

template <typename CharT1, typename CharT2>
double jaro_winkler_similarity(basic_string_view<CharT2> P, basic_string_view<CharT1> T,
                                double prefix_weight, double score_cutoff)
{
    size_t min_len = std::min(P.size(), T.size());
    size_t prefix = 0;
    size_t max_prefix = (min_len >= 4) ? 4 : min_len;

    for (; prefix < max_prefix; ++prefix) {
        if (T[prefix] != P[prefix] || isnum(T[prefix])) {
            break;
        }
    }

    double jaro_score_cutoff = score_cutoff;
    if (jaro_score_cutoff > 0.7) {
        double prefix_sim = prefix * prefix_weight;

        if (prefix_sim == 1.0) {
            jaro_score_cutoff = 0.7;
        }
        else {
            jaro_score_cutoff =
                std::max(0.7, (prefix_sim - jaro_score_cutoff) / (prefix_sim - 1.0));
        }
    }

    double Sim = jaro_similarity(P, T, jaro_score_cutoff);
    if (Sim > 0.7) {
        Sim += prefix * prefix_weight * (1.0 - Sim);
    }

    return common::result_cutoff(Sim, score_cutoff);
    ;
}

} // namespace detail
} // namespace string_metric
} // namespace rapidfuzz

#include <algorithm>
#include <array>
#include <limits>
#include <numeric>

namespace rapidfuzz {
namespace string_metric {
namespace detail {

struct LevenshteinBitMatrix {
    LevenshteinBitMatrix(uint64_t rows, uint64_t cols)
        : VP(rows, cols, (uint64_t)-1), VN(rows, cols, 0), dist(0)
    {}

    common::Matrix<uint64_t> VP;
    common::Matrix<uint64_t> VN;

    size_t dist;
};

/**
 * @brief recover alignment from bitparallel Levenshtein matrix
 */
template <typename CharT1, typename CharT2>
Editops recover_alignment(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                          const LevenshteinBitMatrix& matrix, StringAffix affix)
{
    size_t dist = matrix.dist;
    Editops editops(dist);
    editops.set_src_len(s1.size() + affix.prefix_len + affix.suffix_len);
    editops.set_dest_len(s2.size() + affix.prefix_len + affix.suffix_len);

    if (dist == 0) {
        return editops;
    }

    size_t row = s1.size();
    size_t col = s2.size();

    while (row && col) {
        uint64_t col_pos = col - 1;
        uint64_t col_word = col_pos / 64;
        col_pos = col_pos % 64;
        uint64_t mask = 1ull << col_pos;

        /* Insertion */
        if (matrix.VP[row - 1][col_word] & mask) {
            dist--;
            col--;
            editops[dist].type = EditType::Insert;
            editops[dist].src_pos = row + affix.prefix_len;
            editops[dist].dest_pos = col + affix.prefix_len;
        }
        else {
            row--;

            /* Deletion */
            if (row && matrix.VN[row - 1][col_word] & mask) {
                dist--;
                editops[dist].type = EditType::Delete;
                editops[dist].src_pos = row + affix.prefix_len;
                editops[dist].dest_pos = col + affix.prefix_len;
            }
            /* Match/Mismatch */
            else {
                col--;

                /* Replace (Matches are not recorded) */
                if (s1[row] != s2[col]) {
                    dist--;
                    editops[dist].type = EditType::Replace;
                    editops[dist].src_pos = row + affix.prefix_len;
                    editops[dist].dest_pos = col + affix.prefix_len;
                }
            }
        }
    }

    while (col) {
        dist--;
        col--;
        editops[dist].type = EditType::Insert;
        editops[dist].src_pos = row + affix.prefix_len;
        editops[dist].dest_pos = col + affix.prefix_len;
    }

    while (row) {
        dist--;
        row--;
        editops[dist].type = EditType::Delete;
        editops[dist].src_pos = row + affix.prefix_len;
        editops[dist].dest_pos = col + affix.prefix_len;
    }

    return editops;
}

template <typename CharT1>
LevenshteinBitMatrix levenshtein_matrix_hyrroe2003(basic_string_view<CharT1> s2,
                                                   const common::PatternMatchVector& PM,
                                                   size_t s1_len)
{
    /* VP is set to 1^m. Shifting by bitwidth would be undefined behavior */
    uint64_t VP = (uint64_t)-1;
    uint64_t VN = 0;

    LevenshteinBitMatrix matrix(s2.size(), 1);
    matrix.dist = s1_len;

    /* mask used when computing D[m,j] in the paper 10^(m-1) */
    uint64_t mask = (uint64_t)1 << (s1_len - 1);

    /* Searching */
    for (size_t i = 0; i < s2.size(); ++i) {
        /* Step 1: Computing D0 */
        uint64_t PM_j = PM.get(s2[i]);
        uint64_t X = PM_j;
        uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

        /* Step 2: Computing HP and HN */
        uint64_t HP = VN | ~(D0 | VP);
        uint64_t HN = D0 & VP;

        /* Step 3: Computing the value D[m,j] */
        matrix.dist += bool(HP & mask);
        matrix.dist -= bool(HN & mask);

        /* Step 4: Computing Vp and VN */
        HP = (HP << 1) | 1;
        HN = (HN << 1);

        VP = matrix.VP[i][0] = HN | ~(D0 | HP);
        VN = matrix.VN[i][0] = HP & D0;
    }

    return matrix;
}

template <typename CharT1>
LevenshteinBitMatrix levenshtein_matrix_hyrroe2003_block(basic_string_view<CharT1> s2,
                                                         const common::BlockPatternMatchVector& PM,
                                                         size_t s1_len)
{
    /* todo could be replaced with access to matrix which would slightly
     * reduce memory usage */
    struct Vectors {
        uint64_t VP;
        uint64_t VN;

        Vectors() : VP(~0x0ull), VN(0)
        {}
    };

    const size_t words = PM.m_val.size();
    LevenshteinBitMatrix matrix(s2.size(), words);
    matrix.dist = s1_len;

    std::vector<Vectors> vecs(words);
    const uint64_t Last = (uint64_t)1 << ((s1_len - 1) % 64);

    /* Searching */
    for (size_t i = 0; i < s2.size(); i++) {
        uint64_t HP_carry = 1;
        uint64_t HN_carry = 0;

        // uint64_t PM_j = PM.get(0, s2[i]);

        for (size_t word = 0; word < words - 1; word++) {
            /* Step 1: Computing D0 */
            uint64_t PM_j = PM.get(word, s2[i]);
            uint64_t VN = vecs[word].VN;
            uint64_t VP = vecs[word].VP;

            uint64_t X = PM_j | HN_carry;
            uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

            /* Step 2: Computing HP and HN */
            uint64_t HP = VN | ~(D0 | VP);
            uint64_t HN = D0 & VP;

            /* Step 3: Computing the value D[m,j] */
            // only required for last vector

            /* Step 4: Computing Vp and VN */
            uint64_t HP_carry_temp = HP_carry;
            HP_carry = HP >> 63;
            HP = (HP << 1) | HP_carry_temp;

            uint64_t HN_carry_temp = HN_carry;
            HN_carry = HN >> 63;
            HN = (HN << 1) | HN_carry_temp;

            vecs[word].VP = matrix.VP[i][word] = HN | ~(D0 | HP);
            vecs[word].VN = matrix.VN[i][word] = HP & D0;
        }

        {
            /* Step 1: Computing D0 */
            uint64_t PM_j = PM.get(words - 1, s2[i]);
            uint64_t VN = vecs[words - 1].VN;
            uint64_t VP = vecs[words - 1].VP;

            uint64_t X = PM_j | HN_carry;
            uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

            /* Step 2: Computing HP and HN */
            uint64_t HP = VN | ~(D0 | VP);
            uint64_t HN = D0 & VP;

            /* Step 3: Computing the value D[m,j] */
            matrix.dist += bool(HP & Last);
            matrix.dist -= bool(HN & Last);

            /* Step 4: Computing Vp and VN */
            HP = (HP << 1) | HP_carry;
            HN = (HN << 1) | HN_carry;

            vecs[words - 1].VP = matrix.VP[i][words - 1] = HN | ~(D0 | HP);
            vecs[words - 1].VN = matrix.VN[i][words - 1] = HP & D0;
        }
    }

    return matrix;
}

template <typename CharT1, typename CharT2>
LevenshteinBitMatrix levenshtein_matrix(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2)
{
    if (s2.empty()) {
        LevenshteinBitMatrix matrix(0, 0);
        matrix.dist = s1.size();
        return matrix;
    }
    else if (s1.empty()) {
        LevenshteinBitMatrix matrix(0, 0);
        matrix.dist = s2.size();
        return matrix;
    }
    else if (s2.size() <= 64) {
        return levenshtein_matrix_hyrroe2003(s1, common::PatternMatchVector(s2), s2.size());
    }
    else {
        return levenshtein_matrix_hyrroe2003_block(s1, common::BlockPatternMatchVector(s2),
                                                   s2.size());
    }
}

template <typename CharT1, typename CharT2>
Editops levenshtein_editops(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2)
{
    /* prefix and suffix are no-ops, which do not need to be added to the editops */
    StringAffix affix = common::remove_common_affix(s1, s2);

    return recover_alignment(s1, s2, levenshtein_matrix(s1, s2), affix);
}

} // namespace detail
} // namespace string_metric
} // namespace rapidfuzz

#include <algorithm>
#include <array>
#include <limits>
#include <numeric>

namespace rapidfuzz {
namespace string_metric {
namespace detail {

/*
 * An encoded mbleven model table.
 *
 * Each 8-bit integer represents an edit sequence, with using two
 * bits for a single operation.
 *
 * Each Row of 8 integers represent all possible combinations
 * of edit sequences for a gived maximum edit distance and length
 * difference between the two strings, that is below the maximum
 * edit distance
 *
 *   01 = DELETE, 10 = INSERT, 11 = SUBSTITUTE
 *
 * For example, 3F -> 0b111111 means three substitutions
 */
static constexpr uint8_t levenshtein_mbleven2018_matrix[9][8] = {
    /* max edit distance 1 */
    {0x03}, /* len_diff 0 */
    {0x01}, /* len_diff 1 */
    /* max edit distance 2 */
    {0x0F, 0x09, 0x06}, /* len_diff 0 */
    {0x0D, 0x07},       /* len_diff 1 */
    {0x05},             /* len_diff 2 */
    /* max edit distance 3 */
    {0x3F, 0x27, 0x2D, 0x39, 0x36, 0x1E, 0x1B}, /* len_diff 0 */
    {0x3D, 0x37, 0x1F, 0x25, 0x19, 0x16},       /* len_diff 1 */
    {0x35, 0x1D, 0x17},                         /* len_diff 2 */
    {0x15},                                     /* len_diff 3 */
};

template <typename CharT1, typename CharT2>
size_t levenshtein_mbleven2018(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                               size_t max)
{
    if (s1.size() < s2.size()) {
        return levenshtein_mbleven2018(s2, s1, max);
    }

    size_t len_diff = s1.size() - s2.size();
    auto possible_ops = levenshtein_mbleven2018_matrix[(max + max * max) / 2 + len_diff - 1];
    size_t dist = max + 1;

    for (int pos = 0; possible_ops[pos] != 0; ++pos) {
        int ops = possible_ops[pos];
        size_t s1_pos = 0;
        size_t s2_pos = 0;
        size_t cur_dist = 0;
        while (s1_pos < s1.size() && s2_pos < s2.size()) {
            if (s1[s1_pos] != s2[s2_pos]) {
                cur_dist++;
                if (!ops) break;
                if (ops & 1) s1_pos++;
                if (ops & 2) s2_pos++;
                ops >>= 2;
            }
            else {
                s1_pos++;
                s2_pos++;
            }
        }
        cur_dist += (s1.size() - s1_pos) + (s2.size() - s2_pos);
        dist = std::min(dist, cur_dist);
    }

    return (dist > max) ? (size_t)-1 : dist;
}

/**
 * @brief Bitparallel implementation of the Levenshtein distance.
 *
 * This implementation requires the first string to have a length <= 64.
 * The algorithm used is described @cite hyrro_2002 and has a time complexity
 * of O(N). Comments and variable names in the implementation follow the
 * paper. This implementation is used internally when the strings are short enough
 *
 * @tparam CharT1 This is the char type of the first sentence
 * @tparam CharT2 This is the char type of the second sentence
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 *
 * @return returns the levenshtein distance between s1 and s2
 */
template <typename CharT1>
size_t levenshtein_hyrroe2003(basic_string_view<CharT1> s2, const common::PatternMatchVector& PM,
                              size_t s1_len, size_t max)
{
    /* VP is set to 1^m. Shifting by bitwidth would be undefined behavior */
    uint64_t VP = (uint64_t)-1;
    uint64_t VN = 0;
    size_t currDist = s1_len;

    // saturated addition + subtraction to limit maxMisses to a range of 0 <-> (size_t)-1
    // make sure a wraparound can never occur
    size_t maxMisses = 0;
    if (s1_len > s2.size()) {
        if (s1_len - s2.size() < max) {
            maxMisses = max - (s1_len - s2.size());
        }
        else {
            // minimum is 0
            maxMisses = 0;
        }
    }
    else {
        maxMisses = s2.size() - s1_len;
        if (max <= std::numeric_limits<size_t>::max() - maxMisses) {
            maxMisses = max + maxMisses;
        }
        else {
            // max is (size_t)-1
            maxMisses = std::numeric_limits<size_t>::max();
        }
    }

    /* mask used when computing D[m,j] in the paper 10^(m-1) */
    uint64_t mask = (uint64_t)1 << (s1_len - 1);

    /* Searching */
    for (const auto& ch2 : s2) {
        /* Step 1: Computing D0 */
        uint64_t PM_j = PM.get(ch2);
        uint64_t X = PM_j | VN;
        uint64_t D0 = (((X & VP) + VP) ^ VP) | X;

        /* Step 2: Computing HP and HN */
        uint64_t HP = VN | ~(D0 | VP);
        uint64_t HN = D0 & VP;

        /* Step 3: Computing the value D[m,j] */
        // modification: early exit using maxMisses
        if (HP & mask) {
            currDist++;
            if (maxMisses < 2) {
                return (size_t)-1;
            }
            maxMisses -= 2;
        }
        else if (HN & mask) {
            currDist--;
        }
        else {
            if (maxMisses < 1) {
                return (size_t)-1;
            }
            --maxMisses;
        }

        /* Step 4: Computing Vp and VN */
        X = (HP << 1) | 1;
        VP = (HN << 1) | ~(D0 | X);
        VN = X & D0;
    }

    return currDist;
}

template <typename CharT1>
size_t levenshtein_hyrroe2003_small_band(basic_string_view<CharT1> s2,
                                         const common::BlockPatternMatchVector& PM, size_t s1_len,
                                         size_t max)
{
    /* VP is set to 1^m. Shifting by bitwidth would be undefined behavior */
    uint64_t VP = (uint64_t)-1;
    uint64_t VN = 0;

    size_t currDist = s1_len;

    // saturated addition + subtraction to limit maxMisses to a range of 0 <-> (size_t)-1
    // make sure a wraparound can never occur
    size_t maxMisses = 0;
    if (s1_len > s2.size()) {
        if (s1_len - s2.size() < max) {
            maxMisses = max - (s1_len - s2.size());
        }
        else {
            // minimum is 0
            maxMisses = 0;
        }
    }
    else {
        maxMisses = s2.size() - s1_len;
        if (max <= std::numeric_limits<size_t>::max() - maxMisses) {
            maxMisses = max + maxMisses;
        }
        else {
            // max is (size_t)-1
            maxMisses = std::numeric_limits<size_t>::max();
        }
    }

    /* mask used when computing D[m,j] in the paper 10^(m-1) */
    uint64_t mask = (uint64_t)1 << 63;

    const size_t words = PM.m_val.size();

    /* Searching */
    for (size_t i = 0; i < s2.size(); ++i) {
        /* Step 1: Computing D0 */
        size_t word = i / 64;
        size_t word_pos = i % 64;

        uint64_t PM_j = PM.get(word, s2[i]) >> word_pos;

        if (word + 1 < words) {
            /* avoid shifting by 64 */
            PM_j |= PM.get(word + 1, s2[i]) << 1 << (63 - word_pos);
        }

        /* Step 1: Computing D0 */
        uint64_t X = PM_j;
        uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

        /* Step 2: Computing HP and HN */
        uint64_t HP = VN | ~(D0 | VP);
        uint64_t HN = D0 & VP;

        /* Step 3: Computing the value D[m,j] */
        currDist += bool(HP & mask);
        currDist -= bool(HN & mask);

        /* Step 4: Computing Vp and VN */
        VP = HN | ~((D0 >> 1) | HP);
        VN = (D0 >> 1) & HP;
    }

    return currDist;
}

template <typename CharT1>
size_t levenshtein_hyrroe2003(basic_string_view<CharT1> s2, const common::PatternMatchVector& PM,
                              size_t s1_len)
{
    /* VP is set to 1^m. Shifting by bitwidth would be undefined behavior */
    uint64_t VP = (uint64_t)-1;
    uint64_t VN = 0;
    size_t currDist = s1_len;

    /* mask used when computing D[m,j] in the paper 10^(m-1) */
    uint64_t mask = (uint64_t)1 << (s1_len - 1);

    /* Searching */
    for (const auto& ch2 : s2) {
        /* Step 1: Computing D0 */
        uint64_t PM_j = PM.get(ch2);
        uint64_t X = PM_j;
        uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

        /* Step 2: Computing HP and HN */
        uint64_t HP = VN | ~(D0 | VP);
        uint64_t HN = D0 & VP;

        /* Step 3: Computing the value D[m,j] */
        currDist += bool(HP & mask);
        currDist -= bool(HN & mask);

        /* Step 4: Computing Vp and VN */
        HP = (HP << 1) | 1;
        HN = (HN << 1);

        VP = HN | ~(D0 | HP);
        VN = HP & D0;
    }

    return currDist;
}

template <typename CharT1>
size_t levenshtein_myers1999_block(basic_string_view<CharT1> s2,
                                   const common::BlockPatternMatchVector& PM, size_t s1_len,
                                   size_t max)
{
    struct Vectors {
        uint64_t VP;
        uint64_t VN;

        Vectors() : VP(~0x0ull), VN(0)
        {}
    };

    const size_t words = PM.m_val.size();
    size_t currDist = s1_len;

    // saturated addition + subtraction to limit maxMisses to a range of 0 <-> (size_t)-1
    // make sure a wraparound can never occur
    size_t maxMisses = 0;
    if (s1_len > s2.size()) {
        if (s1_len - s2.size() < max) {
            maxMisses = max - (s1_len - s2.size());
        }
        else {
            // minimum is 0
            maxMisses = 0;
        }
    }
    else {
        maxMisses = s2.size() - s1_len;
        if (max <= std::numeric_limits<size_t>::max() - maxMisses) {
            maxMisses = max + maxMisses;
        }
        else {
            // max is (size_t)-1
            maxMisses = std::numeric_limits<size_t>::max();
        }
    }

    std::vector<Vectors> vecs(words);
    const uint64_t Last = (uint64_t)1 << ((s1_len - 1) % 64);

    /* Searching */
    for (size_t i = 0; i < s2.size(); i++) {
        uint64_t HP_carry = 1;
        uint64_t HN_carry = 0;

        for (size_t word = 0; word < words - 1; word++) {
            /* Step 1: Computing D0 */
            uint64_t PM_j = PM.get(word, s2[i]);
            uint64_t VN = vecs[word].VN;
            uint64_t VP = vecs[word].VP;

            uint64_t X = PM_j | HN_carry;
            uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

            /* Step 2: Computing HP and HN */
            uint64_t HP = VN | ~(D0 | VP);
            uint64_t HN = D0 & VP;

            /* Step 3: Computing the value D[m,j] */
            // only required for last vector

            /* Step 4: Computing Vp and VN */
            uint64_t HP_carry_temp = HP_carry;
            HP_carry = HP >> 63;
            HP = (HP << 1) | HP_carry_temp;

            uint64_t HN_carry_temp = HN_carry;
            HN_carry = HN >> 63;
            HN = (HN << 1) | HN_carry_temp;

            vecs[word].VP = HN | ~(D0 | HP);
            vecs[word].VN = HP & D0;
        }

        {
            /* Step 1: Computing D0 */
            uint64_t PM_j = PM.get(words - 1, s2[i]);
            uint64_t VN = vecs[words - 1].VN;
            uint64_t VP = vecs[words - 1].VP;

            uint64_t X = PM_j | HN_carry;
            uint64_t D0 = (((X & VP) + VP) ^ VP) | X | VN;

            /* Step 2: Computing HP and HN */
            uint64_t HP = VN | ~(D0 | VP);
            uint64_t HN = D0 & VP;

            /* Step 3: Computing the value D[m,j] */
            // modification: early exit using maxMisses
            if (HP & Last) {
                currDist++;
                if (maxMisses < 2) {
                    return (size_t)-1;
                }
                maxMisses -= 2;
            }
            else if (HN & Last) {
                currDist--;
            }
            else {
                if (maxMisses < 1) {
                    return (size_t)-1;
                }
                --maxMisses;
            }

            /* Step 4: Computing Vp and VN */
            HP = (HP << 1) | HP_carry;
            HN = (HN << 1) | HN_carry;

            vecs[words - 1].VP = HN | ~(D0 | HP);
            vecs[words - 1].VN = HP & D0;
        }
    }

    return currDist;
}

template <typename CharT1, typename CharT2>
size_t levenshtein(basic_string_view<CharT1> s1, const common::BlockPatternMatchVector& block,
                   basic_string_view<CharT2> s2, size_t max)
{
    // when no differences are allowed a direct comparision is sufficient
    if (max == 0) {
        if (s1.size() != s2.size()) {
            return (size_t)-1;
        }
        return std::equal(s1.begin(), s1.end(), s2.begin()) ? 0 : (size_t)-1;
    }

    // at least length difference insertions/deletions required
    size_t len_diff = (s1.size() < s2.size()) ? s2.size() - s1.size() : s1.size() - s2.size();
    if (len_diff > max) {
        return (size_t)-1;
    }

    // important to catch, since this causes block.m_val to be empty -> raises exception on access
    if (s2.empty()) {
        return s1.size();
    }

    // do this first, since we can not remove any affix in encoded form
    if (max >= 4) {
        size_t dist = 0;
        if (s2.size() < 65) {
            if (max == (size_t)-1) {
                dist = levenshtein_hyrroe2003(s1, block.m_val[0], s2.size());
            }
            else {
                dist = levenshtein_hyrroe2003(s1, block.m_val[0], s2.size(), max);
            }
        }
        else {
            dist = levenshtein_myers1999_block(s1, block, s2.size(), max);
        }

        return (dist > max) ? (size_t)-1 : dist;
    }

    // The Levenshtein distance between <prefix><string1><suffix> and <prefix><string2><suffix>
    // is similar to the distance between <string1> and <string2>, so they can be removed in linear
    // time
    common::remove_common_affix(s1, s2);

    if (s2.empty()) {
        return s1.size();
    }

    if (s1.empty()) {
        return s2.size();
    }

    return levenshtein_mbleven2018(s1, s2, max);
}

template <typename CharT1, typename CharT2>
size_t levenshtein(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2, size_t max)
{
    /* Swapping the strings so the first string is shorter.
     * Swapping has no effect on the score since Insertion and Deletion have the
     * the same weight */
    if (s1.size() > s2.size()) {
        return levenshtein(s2, s1, max);
    }

    // when no differences are allowed a direct comparision is sufficient
    if (max == 0) {
        if (s1.size() != s2.size()) {
            return (size_t)-1;
        }
        return std::equal(s1.begin(), s1.end(), s2.begin()) ? 0 : (size_t)-1;
    }

    // at least length difference insertions/deletions required
    if (s2.size() - s1.size() > max) {
        return (size_t)-1;
    }

    /* The Levenshtein distance between
     * <prefix><string1><suffix> and <prefix><string2><suffix>
     * is similar to the distance between <string1> and <string2>,
     * so they can be removed in linear time */
    common::remove_common_affix(s1, s2);

    if (s1.empty()) {
        return s2.size();
    }

    common::BlockPatternMatchVector block(s2);

    if (max < 4) {
        return levenshtein_mbleven2018(s1, s2, max);
    }

    /* when the short strings has less then 65 elements Hyyrös' algorithm can be used */
    if (s2.size() < 65) {
        size_t dist;
        if (max == (size_t)-1) {
            dist = levenshtein_hyrroe2003(s1, common::PatternMatchVector(s2), s2.size());
        }
        else {
            dist = levenshtein_hyrroe2003(s1, common::PatternMatchVector(s2), s2.size(), max);
        }
        return (dist > max) ? (size_t)-1 : dist;
    }

    // todo max
    if (max <= 31) {
        size_t dist = levenshtein_hyrroe2003_small_band(s1, block,
                                                        // common::BlockPatternMatchVector(s2),
                                                        s2.size(), max);
        return (dist > max) ? (size_t)-1 : dist;
    }

    size_t dist =
        levenshtein_myers1999_block(s1, common::BlockPatternMatchVector(s2), s2.size(), max);

    return (dist > max) ? (size_t)-1 : dist;
}

template <typename CharT1, typename CharT2>
double normalized_levenshtein(basic_string_view<CharT1> s1,
                              const common::BlockPatternMatchVector& block,
                              basic_string_view<CharT2> s2, const double score_cutoff)
{
    if (s1.empty() || s2.empty()) {
        return static_cast<double>(s1.empty() && s2.empty());
    }

    /* calculate the maximum possible edit distance with
     * Insertion/Deletion/Substitution = 1 */
    size_t max_dist = std::max(s1.size(), s2.size());

    auto cutoff_distance = common::score_cutoff_to_distance(score_cutoff, max_dist);

    size_t dist = levenshtein(s1, block, s2, cutoff_distance);
    return (dist <= cutoff_distance) ? common::norm_distance(dist, max_dist, score_cutoff) : 0.0;
}

template <typename CharT1, typename CharT2>
double normalized_levenshtein(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                              const double score_cutoff)
{
    if (s1.empty() || s2.empty()) {
        return static_cast<double>(s1.empty() && s2.empty());
    }

    /* calculate the maximum possible edit distance with
     * Insertion/Deletion/Substitution = 1 */
    size_t max_dist = std::max(s1.size(), s2.size());

    auto cutoff_distance = common::score_cutoff_to_distance(score_cutoff, max_dist);

    size_t dist = levenshtein(s1, s2, cutoff_distance);
    return (dist <= cutoff_distance) ? common::norm_distance(dist, max_dist, score_cutoff) : 0.0;
}

} // namespace detail
} // namespace string_metric
} // namespace rapidfuzz

#include <algorithm>
#include <array>
#include <limits>
#include <numeric>

namespace rapidfuzz {
namespace string_metric {
namespace detail {

struct LLCSBitMatrix {
    LLCSBitMatrix(uint64_t rows, uint64_t cols) : S(rows, cols, (uint64_t)-1), dist(0)
    {}

    common::Matrix<uint64_t> S;

    size_t dist;
};

/**
 * @brief recover alignment from bitparallel Levenshtein matrix
 */
template <typename CharT1, typename CharT2>
Editops recover_alignment(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                          const LLCSBitMatrix& matrix, StringAffix affix)
{
    size_t dist = matrix.dist;
    Editops editops(dist);
    editops.set_src_len(s1.size() + affix.prefix_len + affix.suffix_len);
    editops.set_dest_len(s2.size() + affix.prefix_len + affix.suffix_len);

    if (dist == 0) {
        return editops;
    }

    size_t row = s1.size();
    size_t col = s2.size();

    while (row && col) {
        uint64_t col_pos = col - 1;
        uint64_t col_word = col_pos / 64;
        col_pos = col_pos % 64;
        uint64_t mask = 1ull << col_pos;

        /* Insertion */
        if (matrix.S[row - 1][col_word] & mask) {
            dist--;
            col--;
            editops[dist].type = EditType::Insert;
            editops[dist].src_pos = row + affix.prefix_len;
            editops[dist].dest_pos = col + affix.prefix_len;
        }
        else {
            row--;

            /* Deletion */
            if (row && (~matrix.S[row - 1][col_word]) & mask) {
                dist--;
                editops[dist].type = EditType::Delete;
                editops[dist].src_pos = row + affix.prefix_len;
                editops[dist].dest_pos = col + affix.prefix_len;
            }
            /* Match */
            else {
                col--;
                assert(s1[row] == s2[col]);
            }
        }
    }

    while (col) {
        dist--;
        col--;
        editops[dist].type = EditType::Insert;
        editops[dist].src_pos = row + affix.prefix_len;
        editops[dist].dest_pos = col + affix.prefix_len;
    }

    while (row) {
        dist--;
        row--;
        editops[dist].type = EditType::Delete;
        editops[dist].src_pos = row + affix.prefix_len;
        editops[dist].dest_pos = col + affix.prefix_len;
    }

    return editops;
}

template <size_t N, typename CharT1>
LLCSBitMatrix llcs_matrix_unroll(basic_string_view<CharT1> s1,
                                 const common::PatternMatchVector* block, size_t s2_len)
{
    std::uint64_t S[N];
    for (size_t i = 0; i < N; ++i) {
        S[i] = ~0x0ull;
    }

    LLCSBitMatrix matrix(s1.size(), N);

    for (size_t i = 0; i < s1.size(); ++i) {
        uint64_t carry = 0;
        std::uint64_t Matches[N];
        std::uint64_t u[N];
        std::uint64_t x[N];
        for (size_t word = 0; word < N; ++word) {
            Matches[word] = block[word].get(s1[i]);
            u[word] = S[word] & Matches[word];
            x[word] = intrinsics::addc64(S[word], u[word], carry, &carry);
            S[word] = matrix.S[i][word] = x[word] | (S[word] - u[word]);
        }
    }

    size_t res = 0;
    for (size_t i = 0; i < N; ++i) {
        res += intrinsics::popcount64(~S[i]);
    }

    matrix.dist = s1.size() + s2_len - 2 * res;

    return matrix;
}

template <typename CharT1>
LLCSBitMatrix llcs_matrix_blockwise(basic_string_view<CharT1> s1,
                                    const common::BlockPatternMatchVector& block, size_t s2_len)
{
    size_t words = block.m_val.size();
    /* todo could be replaced with access to matrix which would slightly
     * reduce memory usage */
    std::vector<std::uint64_t> S(words, ~0x0ull);
    LLCSBitMatrix matrix(s1.size(), words);

    for (size_t i = 0; i < s1.size(); ++i) {
        uint64_t carry = 0;
        for (size_t word = 0; word < words; ++word) {
            const uint64_t Matches = block.get(word, s1[i]);
            uint64_t Stemp = S[word];

            uint64_t u = Stemp & Matches;

            uint64_t x = intrinsics::addc64(Stemp, u, carry, &carry);
            S[word] = matrix.S[i][word] = x | (Stemp - u);
        }
    }

    size_t res = 0;
    for (uint64_t Stemp : S) {
        res += intrinsics::popcount64(~Stemp);
    }

    matrix.dist = s1.size() + s2_len - 2 * res;

    return matrix;
}

template <typename CharT1, typename CharT2>
LLCSBitMatrix llcs_matrix(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2)
{
    if (s2.empty()) {
        LLCSBitMatrix matrix(0, 0);
        matrix.dist = s1.size();
        return matrix;
    }
    else if (s1.empty()) {
        LLCSBitMatrix matrix(0, 0);
        matrix.dist = s2.size();
        return matrix;
    }
    else if (s2.size() <= 64) {
        common::PatternMatchVector block(s2);
        return llcs_matrix_unroll<1>(s1, &block, s2.size());
    }
    else {
        common::BlockPatternMatchVector block(s2);
        switch (block.m_val.size()) {
        case 1:
            return llcs_matrix_unroll<1>(s1, &block.m_val[0], s2.size());
        case 2:
            return llcs_matrix_unroll<2>(s1, &block.m_val[0], s2.size());
        case 3:
            return llcs_matrix_unroll<3>(s1, &block.m_val[0], s2.size());
        case 4:
            return llcs_matrix_unroll<4>(s1, &block.m_val[0], s2.size());
        case 5:
            return llcs_matrix_unroll<5>(s1, &block.m_val[0], s2.size());
        case 6:
            return llcs_matrix_unroll<6>(s1, &block.m_val[0], s2.size());
        case 7:
            return llcs_matrix_unroll<7>(s1, &block.m_val[0], s2.size());
        case 8:
            return llcs_matrix_unroll<8>(s1, &block.m_val[0], s2.size());
        default:
            return llcs_matrix_blockwise(s1, block, s2.size());
        }
    }
}

template <typename CharT1, typename CharT2>
Editops llcs_editops(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2)
{
    /* prefix and suffix are no-ops, which do not need to be added to the editops */
    StringAffix affix = common::remove_common_affix(s1, s2);

    return recover_alignment(s1, s2, llcs_matrix(s1, s2), affix);
}

} // namespace detail
} // namespace string_metric
} // namespace rapidfuzz


#include <algorithm>
#include <array>
#include <limits>
#include <stdexcept>
#include <string>

namespace rapidfuzz {
namespace string_metric {
namespace detail {

/*
 * An encoded mbleven model table.
 *
 * Each 8-bit integer represents an edit sequence, with using two
 * bits for a single operation.
 *
 * Each Row of 8 integers represent all possible combinations
 * of edit sequences for a gived maximum edit distance and length
 * difference between the two strings, that is below the maximum
 * edit distance
 *
 *   0x1 = 01 = DELETE,
 *   0x2 = 10 = INSERT
 *
 * 0x5 -> DEL + DEL
 * 0x6 -> DEL + INS
 * 0x9 -> INS + DEL
 * 0xA -> INS + INS
 */
static constexpr uint8_t weighted_levenshtein_mbleven2018_matrix[14][7] = {
    /* max edit distance 1 */
    {0},
    /* case does not occur */ /* len_diff 0 */
    {0x01},                   /* len_diff 1 */
    /* max edit distance 2 */
    {0x09, 0x06}, /* len_diff 0 */
    {0x01},       /* len_diff 1 */
    {0x05},       /* len_diff 2 */
    /* max edit distance 3 */
    {0x09, 0x06},       /* len_diff 0 */
    {0x25, 0x19, 0x16}, /* len_diff 1 */
    {0x05},             /* len_diff 2 */
    {0x15},             /* len_diff 3 */
    /* max edit distance 4 */
    {0x96, 0x66, 0x5A, 0x99, 0x69, 0xA5}, /* len_diff 0 */
    {0x25, 0x19, 0x16},                   /* len_diff 1 */
    {0x65, 0x56, 0x95, 0x59},             /* len_diff 2 */
    {0x15},                               /* len_diff 3 */
    {0x55},                               /* len_diff 4 */
};

template <typename CharT1, typename CharT2>
size_t weighted_levenshtein_mbleven2018(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                                        size_t max)
{
    if (s1.size() < s2.size()) {
        return weighted_levenshtein_mbleven2018(s2, s1, max);
    }

    size_t len_diff = s1.size() - s2.size();
    auto possible_ops =
        weighted_levenshtein_mbleven2018_matrix[(max + max * max) / 2 + len_diff - 1];
    size_t dist = max + 1;

    for (int pos = 0; possible_ops[pos] != 0; ++pos) {
        int ops = possible_ops[pos];
        size_t s1_pos = 0;
        size_t s2_pos = 0;
        size_t cur_dist = 0;

        while (s1_pos < s1.size() && s2_pos < s2.size()) {
            if (s1[s1_pos] != s2[s2_pos]) {
                cur_dist++;

                if (!ops) break;
                if (ops & 1)
                    s1_pos++;
                else if (ops & 2)
                    s2_pos++;
                ops >>= 2;
            }
            else {
                s1_pos++;
                s2_pos++;
            }
        }

        cur_dist += (s1.size() - s1_pos) + (s2.size() - s2_pos);
        dist = std::min(dist, cur_dist);
    }

    return (dist > max) ? (size_t)-1 : dist;
}

template <size_t N, typename CharT1>
static inline size_t longest_common_subsequence_unroll(basic_string_view<CharT1> s1,
                                                       const common::PatternMatchVector* block,
                                                       size_t s2_len)
{
    std::uint64_t S[N];
    for (size_t i = 0; i < N; ++i) {
        S[i] = ~0x0ull;
    }

    for (const auto& ch1 : s1) {

        uint64_t carry = 0;
        std::uint64_t Matches[N];
        std::uint64_t u[N];
        std::uint64_t x[N];
        for (size_t i = 0; i < N; ++i) {
            Matches[i] = block[i].get(ch1);
            u[i] = S[i] & Matches[i];
            x[i] = intrinsics::addc64(S[i], u[i], carry, &carry);
            S[i] = x[i] | (S[i] - u[i]);
        }
    }

    size_t res = 0;
    for (size_t i = 0; i < N; ++i) {
        res += intrinsics::popcount64(~S[i]);
    }
    return s1.size() + s2_len - 2 * res;
}

template <typename CharT1>
static inline size_t
longest_common_subsequence_blockwise(basic_string_view<CharT1> s1,
                                     const common::BlockPatternMatchVector& block, size_t s2_len)
{
    size_t words = block.m_val.size();
    std::vector<std::uint64_t> S(words, ~0x0ull);

    for (const auto& ch1 : s1) {
        uint64_t carry = 0;
        for (size_t word = 0; word < words; ++word) {
            const uint64_t Matches = block.get(word, ch1);
            uint64_t Stemp = S[word];

            uint64_t u = Stemp & Matches;

            uint64_t x = intrinsics::addc64(Stemp, u, carry, &carry);
            S[word] = x | (Stemp - u);
        }
    }

    size_t res = 0;
    for (uint64_t Stemp : S) {
        res += intrinsics::popcount64(~Stemp);
    }

    return s1.size() + s2_len - 2 * res;
}

template <typename CharT1>
size_t longest_common_subsequence(basic_string_view<CharT1> s1,
                                  const common::BlockPatternMatchVector& block, size_t s2_len)
{
    switch (block.m_val.size()) {
    case 1:
        return longest_common_subsequence_unroll<1>(s1, &block.m_val[0], s2_len);
    case 2:
        return longest_common_subsequence_unroll<2>(s1, &block.m_val[0], s2_len);
    case 3:
        return longest_common_subsequence_unroll<3>(s1, &block.m_val[0], s2_len);
    case 4:
        return longest_common_subsequence_unroll<4>(s1, &block.m_val[0], s2_len);
    case 5:
        return longest_common_subsequence_unroll<5>(s1, &block.m_val[0], s2_len);
    case 6:
        return longest_common_subsequence_unroll<6>(s1, &block.m_val[0], s2_len);
    case 7:
        return longest_common_subsequence_unroll<7>(s1, &block.m_val[0], s2_len);
    case 8:
        return longest_common_subsequence_unroll<8>(s1, &block.m_val[0], s2_len);
    default:
        return longest_common_subsequence_blockwise(s1, block, s2_len);
    }
}

template <typename CharT1, typename CharT2>
size_t longest_common_subsequence(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2)
{
    size_t nr = (s2.size() / 64) + (size_t)((s2.size() % 64) > 0);
    switch (nr) {
    case 1:
    {
        auto block = common::PatternMatchVector(s2);
        return longest_common_subsequence_unroll<1>(s1, &block, s2.size());
    }
    case 2:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<2>(s1, &block.m_val[0], s2.size());
    }
    case 3:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<3>(s1, &block.m_val[0], s2.size());
    }
    case 4:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<4>(s1, &block.m_val[0], s2.size());
    }
    case 5:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<5>(s1, &block.m_val[0], s2.size());
    }
    case 6:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<6>(s1, &block.m_val[0], s2.size());
    }
    case 7:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<7>(s1, &block.m_val[0], s2.size());
    }
    case 8:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_unroll<8>(s1, &block.m_val[0], s2.size());
    }
    default:
    {
        auto block = common::BlockPatternMatchVector(s2);
        return longest_common_subsequence_blockwise(s1, block, s2.size());
    }
    }
}

// TODO this implementation needs some cleanup
template <typename CharT1, typename CharT2>
size_t weighted_levenshtein(basic_string_view<CharT1> s1,
                            const common::BlockPatternMatchVector& block,
                            basic_string_view<CharT2> s2, size_t max)
{
    // when no differences are allowed a direct comparision is sufficient
    if (max == 0) {
        if (s1.size() != s2.size()) {
            return (size_t)-1;
        }
        return std::equal(s1.begin(), s1.end(), s2.begin()) ? 0 : (size_t)-1;
    }

    // when the strings have a similar length each difference causes
    // at least a edit distance of 2, so a direct comparision is sufficient
    if (max == 1) {
        if (s1.size() == s2.size()) {
            return std::equal(s1.begin(), s1.end(), s2.begin()) ? 0 : (size_t)-1;
        }
    }

    // at least length difference insertions/deletions required
    size_t len_diff = (s1.size() < s2.size()) ? s2.size() - s1.size() : s1.size() - s2.size();
    if (len_diff > max) {
        return (size_t)-1;
    }

    // important to catch, since this causes block.m_val to be empty -> raises exception on access
    if (s2.empty()) {
        return s1.size();
    }

    // do this first, since we can not remove any affix in encoded form
    if (max >= 5) {
        size_t dist = longest_common_subsequence(s1, block, s2.size());
        return (dist > max) ? (size_t)-1 : dist;
    }

    // The Levenshtein distance between <prefix><string1><suffix> and <prefix><string2><suffix>
    // is similar to the distance between <string1> and <string2>, so they can be removed in linear
    // time
    common::remove_common_affix(s1, s2);

    if (s2.empty()) {
        return s1.size();
    }

    if (s1.empty()) {
        return s2.size();
    }

    return weighted_levenshtein_mbleven2018(s1, s2, max);
}

template <typename CharT1, typename CharT2>
size_t weighted_levenshtein(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2, size_t max)
{
    // Swapping the strings so the second string is shorter
    if (s1.size() < s2.size()) {
        return weighted_levenshtein(s2, s1, max);
    }

    // when no differences are allowed a direct comparision is sufficient
    if (max == 0) {
        if (s1.size() != s2.size()) {
            return (size_t)-1;
        }
        return std::equal(s1.begin(), s1.end(), s2.begin()) ? 0 : (size_t)-1;
    }

    // when the strings have a similar length each difference causes
    // at least a edit distance of 2, so a direct comparision is sufficient
    if (max == 1) {
        if (s1.size() == s2.size()) {
            return std::equal(s1.begin(), s1.end(), s2.begin()) ? 0 : (size_t)-1;
        }
    }

    // at least length difference insertions/deletions required
    if (s1.size() - s2.size() > max) {
        return (size_t)-1;
    }

    // The Levenshtein distance between <prefix><string1><suffix> and <prefix><string2><suffix>
    // is similar to the distance between <string1> and <string2>, so they can be removed in linear
    // time
    common::remove_common_affix(s1, s2);

    if (s2.empty()) {
        return s1.size();
    }

    if (max < 5) {
        return weighted_levenshtein_mbleven2018(s1, s2, max);
    }

    size_t dist = longest_common_subsequence(s1, s2);
    return (dist > max) ? (size_t)-1 : dist;
}

template <typename CharT1, typename CharT2>
double normalized_weighted_levenshtein(basic_string_view<CharT1> s1,
                                       const common::BlockPatternMatchVector& block,
                                       basic_string_view<CharT2> s2, const double score_cutoff)
{
    if (s1.empty() || s2.empty()) {
        return static_cast<double>(s1.empty() && s2.empty());
    }

    size_t lensum = s1.size() + s2.size();

    auto cutoff_distance = common::score_cutoff_to_distance(score_cutoff, lensum);

    size_t dist = weighted_levenshtein(s1, block, s2, cutoff_distance);
    return (dist <= cutoff_distance) ? common::norm_distance(dist, lensum, score_cutoff) : 0.0;
}

template <typename CharT1, typename CharT2>
double normalized_weighted_levenshtein(basic_string_view<CharT1> s1, basic_string_view<CharT2> s2,
                                       const double score_cutoff)
{
    if (s1.empty() || s2.empty()) {
        return static_cast<double>(s1.empty() && s2.empty());
    }

    size_t lensum = s1.size() + s2.size();

    auto cutoff_distance = common::score_cutoff_to_distance(score_cutoff, lensum);

    size_t dist = weighted_levenshtein(s1, s2, cutoff_distance);
    return (dist <= cutoff_distance) ? common::norm_distance(dist, lensum, score_cutoff) : 0.0;
}

} // namespace detail
} // namespace string_metric
} // namespace rapidfuzz

#include <cmath>
#include <numeric>
#include <stdexcept>

namespace rapidfuzz {
namespace string_metric {

/**
 * @defgroup string_metric string_metric
 * Different useful string_metrics
 * @{
 */

/**
 * @brief Calculates the minimum number of insertions, deletions, and substitutions
 * required to change one sequence into the other according to Levenshtein with custom
 * costs for insertion, deletion and substitution
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 * @param weights
 *   The weights for the three operations in the form
 *   (insertion, deletion, substitution). Default is {1, 1, 1},
 *   which gives all three operations a weight of 1.
 * @param max
 *   Maximum Levenshtein distance between s1 and s2, that is
 *   considered as a result. If the distance is bigger than max,
 *   max + 1 is returned instead. Default is std::numeric_limits<size_t>::max(),
 *   which deactivates this behaviour.
 *
 * @return returns the levenshtein distance between s1 and s2
 *
 * @remarks
 * @parblock
 * Depending on the input parameters different optimized implementation are used
 * to improve the performance. Worst-case performance is ``O(m * n)``.
 *
 * <b>Insertion = Deletion = Substitution:</b>
 *
 *    This is known as uniform Levenshtein distance and is the distance most commonly
 *    referred to as Levenshtein distance. The following implementation is used
 *    with a worst-case performance of ``O([N/64]M)``.
 *
 *    - if max is 0 the similarity can be calculated using a direct comparision,
 *      since no difference between the strings is allowed.  The time complexity of
 *      this algorithm is ``O(N)``.
 *
 *    - A common prefix/suffix of the two compared strings does not affect
 *      the Levenshtein distance, so the affix is removed before calculating the
 *      similarity.
 *
 *    - If max is ≤ 3 the mbleven algorithm is used. This algorithm
 *      checks all possible edit operations that are possible under
 *      the threshold `max`. The time complexity of this algorithm is ``O(N)``.
 *
 *    - If the length of the shorter string is ≤ 64 after removing the common affix
 *      Hyyrös' algorithm is used, which calculates the Levenshtein distance in
 *      parallel. The algorithm is described by @cite hyrro_2002. The time complexity of this
 *      algorithm is ``O(N)``.
 *
 *    - If the length of the shorter string is ≥ 64 after removing the common affix
 *      a blockwise implementation of Myers' algorithm is used, which calculates
 *      the Levenshtein distance in parallel (64 characters at a time).
 *      The algorithm is described by @cite myers_1999. The time complexity of this
 *      algorithm is ``O([N/64]M)``.
 *
 *
 * <b>Insertion = Deletion, Substitution >= Insertion + Deletion:</b>
 *
 *    Since every Substitution can be performed as Insertion + Deletion, this variant
 *    of the Levenshtein distance only uses Insertions and Deletions. Therefore this
 *    variant is often referred to as InDel-Distance.  The following implementation
 *    is used with a worst-case performance of ``O([N/64]M)``.
 *
 *    - if max is 0 the similarity can be calculated using a direct comparision,
 *      since no difference between the strings is allowed.  The time complexity of
 *      this algorithm is ``O(N)``.
 *
 *    - if max is 1 and the two strings have a similar length, the similarity can be
 *      calculated using a direct comparision aswell, since a substitution would cause
 *      a edit distance higher than max. The time complexity of this algorithm
 *      is ``O(N)``.
 *
 *    - A common prefix/suffix of the two compared strings does not affect
 *      the Levenshtein distance, so the affix is removed before calculating the
 *      similarity.
 *
 *    - If max is ≤ 4 the mbleven algorithm is used. This algorithm
 *      checks all possible edit operations that are possible under
 *      the threshold `max`. As a difference to the normal Levenshtein distance this
 *      algorithm can even be used up to a threshold of 4 here, since the higher weight
 *      of substitutions decreases the amount of possible edit operations.
 *      The time complexity of this algorithm is ``O(N)``.
 *
 *    - If the length of the shorter string is ≤ 64 after removing the common affix
 *      Hyyrös' lcs algorithm is used, which calculates the InDel distance in
 *      parallel. The algorithm is described by @cite hyrro_lcs_2004 and is extended with support
 *      for UTF32 in this implementation. The time complexity of this
 *      algorithm is ``O(N)``.
 *
 *    - If the length of the shorter string is ≥ 64 after removing the common affix
 *      a blockwise implementation of Hyyrös' lcs algorithm is used, which calculates
 *      the Levenshtein distance in parallel (64 characters at a time).
 *      The algorithm is described by @cite hyrro_lcs_2004. The time complexity of this
 *      algorithm is ``O([N/64]M)``.
 *
 * <b>Other weights:</b>
 *
 *   The implementation for other weights is based on Wagner-Fischer.
 *   It has a performance of ``O(N * M)`` and has a memory usage of ``O(N)``.
 *   Further details can be found in @cite wagner_fischer_1974.
 * @endparblock
 *
 * @par Examples
 * @parblock
 * Find the Levenshtein distance between two strings:
 * @code{.cpp}
 * // dist is 2
 * size_t dist = levenshtein("lewenstein", "levenshtein");
 * @endcode
 *
 * Setting a maximum distance allows the implementation to select
 * a more efficient implementation:
 * @code{.cpp}
 * // dist is 2
 * size_t dist = levenshtein("lewenstein", "levenshtein", {1, 1, 1}, 1);
 * @endcode
 *
 * It is possible to select different weights by passing a `weight` struct.
 * @code{.cpp}
 * // dist is 3
 * size_t dist = levenshtein("lewenstein", "levenshtein", {1, 1, 2});
 * @endcode
 * @endparblock
 */
template <typename Sentence1, typename Sentence2>
size_t levenshtein(const Sentence1& s1, const Sentence2& s2,
                   LevenshteinWeightTable weights = {1, 1, 1},
                   size_t max = std::numeric_limits<size_t>::max())
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    if (weights.insert_cost == weights.delete_cost) {
        /* when insertions + deletions operations are free there can not be any edit distance */
        if (weights.insert_cost == 0) {
            return 0;
        }

        /* uniform Levenshtein multiplied with the common factor */
        if (weights.insert_cost == weights.replace_cost) {
            // max can make use of the common divisor of the three weights
            const size_t new_max =
                max / weights.insert_cost + (size_t)(max % weights.insert_cost != 0);
            const size_t distance =
                detail::levenshtein(sentence1, sentence2, new_max) * weights.insert_cost;
            return (distance <= max) ? distance : max + 1;
        }
        /*
         * when replace_cost >= insert_cost + delete_cost no substitutions are performed
         * therefore this can be implemented as InDel distance multiplied with the common factor
         */
        else if (weights.replace_cost >= weights.insert_cost + weights.delete_cost) {
            // max can make use of the common divisor of the three weights
            const size_t new_max =
                max / weights.insert_cost + (size_t)(max % weights.insert_cost != 0);
            const size_t distance =
                detail::weighted_levenshtein(sentence1, sentence2, new_max) * weights.insert_cost;
            return (distance <= max) ? distance : max + 1;
        }
    }

    return detail::generic_levenshtein(sentence1, sentence2, weights, max);
}

template <typename Sentence1>
struct CachedLevenshtein {
    using CharT1 = char_type<Sentence1>;

    CachedLevenshtein(const Sentence1& s1, LevenshteinWeightTable aWeights = {1, 1, 1})
        : s1_view(common::to_string_view(s1)), blockmap_s1(s1_view), weights(aWeights)
    {}

    template <typename Sentence2>
    size_t distance(const Sentence2& s2, size_t max = std::numeric_limits<size_t>::max()) const
    {
        auto s2_view = common::to_string_view(s2);

        if (weights.insert_cost == weights.delete_cost) {
            /* when insertions + deletions operations are free there can not be any edit distance */
            if (weights.insert_cost == 0) {
                return 0;
            }

            /* uniform Levenshtein multiplied with the common factor */
            if (weights.insert_cost == weights.replace_cost) {
                // max can make use of the common divisor of the three weights
                const size_t new_max =
                    max / weights.insert_cost + (size_t)(max % weights.insert_cost != 0);
                const size_t distance =
                    detail::levenshtein(s2_view, blockmap_s1, s1_view, new_max) *
                    weights.insert_cost;
                return (distance <= max) ? distance : max + 1;
            }
            /*
             * when replace_cost >= insert_cost + delete_cost no substitutions are performed
             * therefore this can be implemented as InDel distance multiplied with the common factor
             */
            else if (weights.replace_cost >= weights.insert_cost + weights.delete_cost) {
                // max can make use of the common divisor of the three weights
                const size_t new_max =
                    max / weights.insert_cost + (size_t)(max % weights.insert_cost != 0);
                const size_t distance =
                    detail::weighted_levenshtein(s2_view, blockmap_s1, s1_view, new_max) *
                    weights.insert_cost;
                return (distance <= max) ? distance : max + 1;
            }
        }

        return detail::generic_levenshtein(s1_view, s2_view, weights, max);
    }

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
    common::BlockPatternMatchVector blockmap_s1;
    LevenshteinWeightTable weights;
};

/**
 * @brief Calculates a normalized levenshtein distance using custom
 * costs for insertion, deletion and substitution.
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 * @param weights
 *   The weights for the three operations in the form
 *   (insertion, deletion, substitution). Default is {1, 1, 1},
 *   which gives all three operations a weight of 1.
 * @param score_cutoff
 *   Optional argument for a score threshold as a float between 0 and 1.0.
 *   For ratio < score_cutoff 0 is returned instead. Default is 0,
 *   which deactivates this behaviour.
 *
 * @return Normalized weighted levenshtein distance between s1 and s2
 *   as a double between 0 and 1.0
 *
 * @see levenshtein()
 *
 * @remarks
 * @parblock
 * The normalization of the Levenshtein distance is performed in the following way:
 *
 * \f{align*}{
 *   \\
 *   dist_{max} &= \begin{cases}
 *     min(len(s1), len(s2)) \cdot sub,       & \text{if } sub \leq ins + del \\
 *     len(s1) \cdot del + len(s2) \cdot ins, & \text{otherwise}
 *   \end{cases}\\[10pt]
 *
 *   dist_{max} &= \begin{cases}
 *     dist_{max} + (len(s1) - len(s2)) \cdot del, & \text{if } len(s1) > len(s2) \\
 *     dist_{max} + (len(s2) - len(s1)) \cdot ins, & \text{if } len(s1) < len(s2) \\
 *     dist_{max},                                 & \text{if } len(s1) = len(s2)
 *   \end{cases}\\[10pt]
 *
 *   ratio &= \frac{distance(s1, s2)}{dist_{max}}
 * \f}
 * @endparblock
 *
 *
 * @par Examples
 * @parblock
 * Find the normalized Levenshtein distance between two strings:
 * @code{.cpp}
 * // ratio is 81.81818181818181
 * double ratio = normalized_levenshtein("lewenstein", "levenshtein");
 * @endcode
 *
 * Setting a score_cutoff allows the implementation to select
 * a more efficient implementation:
 * @code{.cpp}
 * // ratio is 0.0
 * double ratio = normalized_levenshtein("lewenstein", "levenshtein", {1, 1, 1}, 85.0);
 * @endcode
 *
 * It is possible to select different weights by passing a `weight` struct
 * @code{.cpp}
 * // ratio is 85.71428571428571
 * double ratio = normalized_levenshtein("lewenstein", "levenshtein", {1, 1, 2});
 * @endcode
 * @endparblock
 */
template <typename Sentence1, typename Sentence2>
double normalized_levenshtein(const Sentence1& s1, const Sentence2& s2,
                              LevenshteinWeightTable weights = {1, 1, 1},
                              double score_cutoff = 0.0)
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    if (weights.insert_cost == weights.delete_cost) {
        /* uniform Levenshtein */
        if (weights.insert_cost == weights.replace_cost) {
            return detail::normalized_levenshtein(sentence1, sentence2, score_cutoff);
        }
        /*
         * when replace_cost >= insert_cost + delete_cost no substitutions are performed
         * therefore this can be implemented as InDel distance
         */
        else if (weights.replace_cost >= weights.insert_cost + weights.delete_cost) {
            return detail::normalized_weighted_levenshtein(sentence1, sentence2, score_cutoff);
        }
    }

    return detail::normalized_generic_levenshtein(sentence1, sentence2, weights, score_cutoff);
}

template <typename Sentence1>
struct CachedNormalizedLevenshtein {
    using CharT1 = char_type<Sentence1>;

    CachedNormalizedLevenshtein(const Sentence1& s1, LevenshteinWeightTable aWeights = {1, 1, 1})
        : s1_view(common::to_string_view(s1)), blockmap_s1(s1_view), weights(aWeights)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const
    {
        auto s2_view = common::to_string_view(s2);

        if (weights.insert_cost == weights.delete_cost) {
            /* uniform Levenshtein */
            if (weights.insert_cost == weights.replace_cost) {
                return detail::normalized_levenshtein(s2_view, blockmap_s1, s1_view, score_cutoff);
            }
            /*
             * when replace_cost >= insert_cost + delete_cost no substitutions are performed
             * therefore this can be implemented as InDel distance
             */
            else if (weights.replace_cost >= weights.insert_cost + weights.delete_cost) {
                return detail::normalized_weighted_levenshtein(s2_view, blockmap_s1, s1_view,
                                                               score_cutoff);
            }
        }

        return detail::normalized_generic_levenshtein(s1_view, s2_view, weights, score_cutoff);
    }

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
    common::BlockPatternMatchVector blockmap_s1;
    LevenshteinWeightTable weights;
};

/**
 * @brief Return list of EditOp describing how to turn s1 into s2.
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 *
 * @return Edit operations required to turn s1 into s2
 */
template <typename Sentence1, typename Sentence2>
Editops levenshtein_editops(const Sentence1& s1, const Sentence2& s2)
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    return detail::levenshtein_editops(sentence1, sentence2);
}

template <typename Sentence1, typename Sentence2>
Editops llcs_editops(const Sentence1& s1, const Sentence2& s2)
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    return detail::llcs_editops(sentence1, sentence2);
}

/**
 * @brief Calculates the Hamming distance between two strings.
 *
 * @details
 * Both strings require a similar length
 *
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 * @param max
 *   Maximum Hamming distance between s1 and s2, that is
 *   considered as a result. If the distance is bigger than max,
 *   max + 1 is returned instead. Default is std::numeric_limits<size_t>::max(),
 *   which deactivates this behaviour.
 *
 * @return Hamming distance between s1 and s2
 */
template <typename Sentence1, typename Sentence2>
size_t hamming(const Sentence1& s1, const Sentence2& s2,
               size_t max = std::numeric_limits<size_t>::max())
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    if (sentence1.size() != sentence2.size()) {
        throw std::invalid_argument("s1 and s2 are not the same length.");
    }

    size_t hamm = 0;

    for (size_t i = 0; i < sentence1.length(); i++) {
        if (sentence1[i] != sentence2[i]) {
            hamm++;
        }
    }

    return hamm > max ? max + 1 : hamm;
}

template <typename Sentence1>
struct CachedHamming {
    using CharT1 = char_type<Sentence1>;

    CachedHamming(const Sentence1& s1) : s1_view(common::to_string_view(s1))
    {}

    template <typename Sentence2>
    size_t distance(const Sentence2& s2, size_t max = std::numeric_limits<size_t>::max()) const
    {
        return hamming(s1_view, s2, max);
    }

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
};

/**
 * @brief Calculates a normalized hamming distance
 *
 * @details
 * Both string require a similar length
 *
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 * @param score_cutoff
 *   Optional argument for a score threshold as a float between 0 and 1.0.
 *   For ratio < score_cutoff 0 is returned instead. Default is 0,
 *   which deactivates this behaviour.
 *
 * @return Normalized hamming distance between s1 and s2
 *   as a float between 0 and 1.0
 */
template <typename Sentence1, typename Sentence2>
double normalized_hamming(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0.0)
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);
    return common::norm_distance(hamming(sentence1, sentence2), sentence1.size(), score_cutoff);
}

template <typename Sentence1>
struct CachedNormalizedHamming {
    using CharT1 = char_type<Sentence1>;

    CachedNormalizedHamming(const Sentence1& s1) : s1_view(common::to_string_view(s1))
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const
    {
        return normalized_hamming(s1_view, s2, score_cutoff);
    }

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
};

/**
 * @brief Calculates the jaro winkler similarity
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 * @param prefix_weight
 *   Weight used for the common prefix of the two strings.
 *   Has to be between 0 and 0.25. Default is 0.1.
 * @param score_cutoff
 *   Optional argument for a score threshold as a float between 0 and 1.0.
 *   For ratio < score_cutoff 0 is returned instead. Default is 0,
 *   which deactivates this behaviour.
 *
 * @return jaro winkler similarity between s1 and s2
 *   as a float between 0 and 1.0
 */
template <typename Sentence1, typename Sentence2>
double jaro_winkler_similarity(const Sentence1& s1, const Sentence2& s2, double prefix_weight = 0.1,
                               double score_cutoff = 0.0)
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    if (prefix_weight < 0.0 || prefix_weight > 0.25) {
        throw std::invalid_argument("prefix_weight has to be between 0.0 - 0.25");
    }

    return detail::jaro_winkler_similarity(sentence1, sentence2, prefix_weight, score_cutoff);
}

template <typename Sentence1>
struct CachedJaroWinklerSimilarity {
    using CharT1 = char_type<Sentence1>;

    CachedJaroWinklerSimilarity(const Sentence1& s1, double prefix_weight_ = 0.1)
        : s1_view(common::to_string_view(s1)), prefix_weight(prefix_weight_)
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const
    {
        return jaro_winkler_similarity(s1_view, s2, prefix_weight, score_cutoff);
    }

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
    double prefix_weight;
};

/**
 * @brief Calculates the jaro similarity
 *
 * @tparam Sentence1 This is a string that can be converted to
 * basic_string_view<char_type>
 * @tparam Sentence2 This is a string that can be converted to
 * basic_string_view<char_type>
 *
 * @param s1
 *   string to compare with s2 (for type info check Template parameters above)
 * @param s2
 *   string to compare with s1 (for type info check Template parameters above)
 * @param score_cutoff
 *   Optional argument for a score threshold as a float between 0 and 1.0.
 *   For ratio < score_cutoff 0 is returned instead. Default is 0,
 *   which deactivates this behaviour.
 *
 * @return jaro similarity between s1 and s2
 *   as a float between 0 and 1.0
 */
template <typename Sentence1, typename Sentence2>
double jaro_similarity(const Sentence1& s1, const Sentence2& s2, double score_cutoff = 0.0)
{
    auto sentence1 = common::to_string_view(s1);
    auto sentence2 = common::to_string_view(s2);

    return detail::jaro_similarity(sentence1, sentence2, score_cutoff);
}

template <typename Sentence1>
struct CachedJaroSimilarity {
    using CharT1 = char_type<Sentence1>;

    CachedJaroSimilarity(const Sentence1& s1) : s1_view(common::to_string_view(s1))
    {}

    template <typename Sentence2>
    double ratio(const Sentence2& s2, double score_cutoff = 0) const
    {
        return jaro_similarity(s1_view, s2, score_cutoff);
    }

private:
    rapidfuzz::basic_string_view<CharT1> s1_view;
};

/**@}*/

} // namespace string_metric
} // namespace rapidfuzz

#include <algorithm>
#include <cmath>
#include <iterator>
#include <unordered_map>
#include <vector>

namespace rapidfuzz {
namespace fuzz {

/**********************************************
 *                  ratio
 *********************************************/

template <typename Sentence1, typename Sentence2>
double ratio(const Sentence1& s1, const Sentence2& s2, const double score_cutoff)
{
    return string_metric::normalized_levenshtein(s1, s2, {1, 1, 2}, score_cutoff / 100) * 100;
}

template <typename Sentence1>
template <typename Sentence2>
double CachedRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    auto s2_view = common::to_string_view(s2);

    return string_metric::detail::normalized_weighted_levenshtein(s2_view, blockmap_s1, s1_view,
                                                                  score_cutoff / 100) *
           100;
}

/**********************************************
 *              partial_ratio
 *********************************************/

namespace detail {

template <typename Sentence1, typename CachedSentence1, typename Sentence2>
double
partial_ratio_short_needle(const Sentence1& s1, const CachedRatio<CachedSentence1>& cached_ratio,
                           const common::CharHashTable<char_type<Sentence1>, bool>& s1_char_map,
                           const Sentence2& s2, double score_cutoff)
{
    double max_ratio = 0;
    auto s1_view = common::to_string_view(s1);
    auto s2_view = common::to_string_view(s2);

    for (size_t i = 1; i < s1_view.size(); ++i) {
        auto long_substr = s2_view.substr(0, i);

        if (!s1_char_map[long_substr.back()]) {
            continue;
        }

        double ls_ratio = cached_ratio.ratio(long_substr, score_cutoff);
        if (ls_ratio > max_ratio) {
            score_cutoff = max_ratio = ls_ratio;
            if (ls_ratio == 100.0) {
                return 100.0;
            }
        }
    }

    for (size_t i = 0; i < s2_view.size() - s1_view.size(); ++i) {
        auto long_substr = s2_view.substr(i, s1_view.size());

        if (!s1_char_map[long_substr.back()]) {
            continue;
        }

        double ls_ratio = cached_ratio.ratio(long_substr, score_cutoff);
        if (ls_ratio > max_ratio) {
            score_cutoff = max_ratio = ls_ratio;
            if (ls_ratio == 100.0) {
                return 100.0;
            }
        }
    }

    for (size_t i = s2_view.size() - s1_view.size(); i < s2_view.size(); ++i) {
        auto long_substr = s2_view.substr(i, s1_view.size());

        if (!s1_char_map[long_substr[0]]) {
            continue;
        }

        double ls_ratio = cached_ratio.ratio(long_substr, score_cutoff);
        if (ls_ratio > max_ratio) {
            score_cutoff = max_ratio = ls_ratio;
            if (ls_ratio == 100.0) {
                return 100.0;
            }
        }
    }

    return max_ratio;
}

template <typename Sentence1, typename Sentence2, typename CharT1 = char_type<Sentence1>>
double partial_ratio_short_needle(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    auto s1_view = common::to_string_view(s1);
    CachedRatio<decltype(s1_view)> cached_ratio(s1_view);

    common::CharHashTable<CharT1, bool> s1_char_map;
    for (const CharT1& ch : s1_view) {
        s1_char_map.create(ch) = true;
    }

    return partial_ratio_short_needle(s1_view, cached_ratio, s1_char_map, s2, score_cutoff);
}

template <typename Sentence1, typename CachedSentence1, typename Sentence2>
double partial_ratio_long_needle(const Sentence1& s1,
                                  const CachedRatio<CachedSentence1>& cached_ratio,
                                  const Sentence2& s2, double score_cutoff)
{
    double max_ratio = 0;
    if (score_cutoff > 100) {
        return 0;
    }

    auto s1_view = common::to_string_view(s1);
    auto s2_view = common::to_string_view(s2);

    if (s1_view.empty() || s2_view.empty()) {
        return static_cast<double>(s1_view.empty() && s2_view.empty()) * 100.0;
    }

    auto blocks = rapidfuzz::detail::get_matching_blocks(s1_view, s2_view);

    // when there is a full match exit early
    for (const auto& block : blocks) {
        if (block.length == s1_view.length()) {
            return 100;
        }
    }

    for (const auto& block : blocks) {
        size_t long_start = (block.dpos > block.spos) ? block.dpos - block.spos : 0;
        auto long_substr = s2_view.substr(long_start, s1_view.length());

        double ls_ratio = cached_ratio.ratio(long_substr, score_cutoff);
        if (ls_ratio > max_ratio) {
            score_cutoff = max_ratio = ls_ratio;
        }
    }

    return max_ratio;
}

template <typename Sentence1, typename Sentence2>
double partial_ratio_long_needle(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    auto s1_view = common::to_string_view(s1);
    CachedRatio<decltype(s1_view)> cached_ratio(s1_view);

    return partial_ratio_long_needle(s1_view, cached_ratio, s2, score_cutoff);
}

} // namespace detail

template <typename Sentence1, typename Sentence2, typename CharT1, typename CharT2>
double partial_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) {
        return 0;
    }

    auto s1_view = common::to_string_view(s1);
    auto s2_view = common::to_string_view(s2);

    if (s1_view.empty() || s2_view.empty()) {
        return static_cast<double>(s1_view.empty() && s2_view.empty()) * 100.0;
    }

    if (s1_view.length() > s2_view.length()) {
        return partial_ratio(s2_view, s1_view, score_cutoff);
    }

    if (s1_view.length() <= 64) {
        return detail::partial_ratio_short_needle(s1_view, s2_view, score_cutoff);
    }
    else {
        return detail::partial_ratio_long_needle(s1_view, s2_view, score_cutoff);
    }
}

template <typename Sentence1>
CachedPartialRatio<Sentence1>::CachedPartialRatio(const Sentence1& s1)
    : s1_view(common::to_string_view(s1)), cached_ratio(s1)
{
    for (const CharT1& ch : s1_view) {
        s1_char_map.create(ch) = true;
    }
}

template <typename Sentence1>
template <typename Sentence2>
double CachedPartialRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    auto s2_view = common::to_string_view(s2);

    if (s1_view.size() > s2_view.size()) {
        return partial_ratio(s1_view, s2_view, score_cutoff);
    }

    if (s1_view.empty() || s2_view.empty()) {
        return static_cast<double>(s1_view.empty() && s2_view.empty()) * 100.0;
    }

    if (s1_view.length() <= 64) {
        return detail::partial_ratio_short_needle(s1_view, cached_ratio, s1_char_map, s2_view,
                                                  score_cutoff);
    }
    else {
        return detail::partial_ratio_long_needle(s1_view, cached_ratio, s2_view, score_cutoff);
    }
}

/**********************************************
 *             token_sort_ratio
 *********************************************/

template <typename Sentence1, typename Sentence2, typename CharT1, typename CharT2>
double token_sort_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    return ratio(common::sorted_split(s1).join(), common::sorted_split(s2).join(), score_cutoff);
}

template <typename Sentence1>
template <typename Sentence2>
double CachedTokenSortRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    if (score_cutoff > 100) return 0;

    return cached_ratio.ratio(common::sorted_split(s2).join(), score_cutoff);
}

/**********************************************
 *          partial_token_sort_ratio
 *********************************************/

template <typename Sentence1, typename Sentence2, typename CharT1, typename CharT2>
double partial_token_sort_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    return partial_ratio(common::sorted_split(s1).join(), common::sorted_split(s2).join(),
                         score_cutoff);
}

template <typename Sentence1>
template <typename Sentence2>
double CachedPartialTokenSortRatio<Sentence1>::ratio(const Sentence2& s2,
                                                     double score_cutoff) const
{
    if (score_cutoff > 100) return 0;

    return cached_partial_ratio.ratio(common::sorted_split(s2).join(), score_cutoff);
}

/**********************************************
 *               token_set_ratio
 *********************************************/

namespace detail {
template <typename CharT1, typename CharT2>
double token_set_ratio(const SplittedSentenceView<CharT1>& tokens_a,
                        const SplittedSentenceView<CharT2>& tokens_b, const double score_cutoff)
{
    /* in FuzzyWuzzy this returns 0. For sake of compatibility return 0 here as well
     * see https://github.com/maxbachmann/RapidFuzz/issues/110 */
    if (tokens_a.empty() || tokens_a.empty()) {
        return 0;
    }

    auto decomposition = common::set_decomposition(tokens_a, tokens_b);
    auto intersect = decomposition.intersection;
    auto diff_ab = decomposition.difference_ab;
    auto diff_ba = decomposition.difference_ba;

    // one sentence is part of the other one
    if (!intersect.empty() && (diff_ab.empty() || diff_ba.empty())) {
        return 100;
    }

    auto diff_ab_joined = diff_ab.join();
    auto diff_ba_joined = diff_ba.join();

    size_t ab_len = diff_ab_joined.length();
    size_t ba_len = diff_ba_joined.length();
    size_t sect_len = intersect.length();

    // string length sect+ab <-> sect and sect+ba <-> sect
    size_t sect_ab_len = sect_len + bool(sect_len) + ab_len;
    size_t sect_ba_len = sect_len + bool(sect_len) + ba_len;

    double result = 0;
    auto cutoff_distance = common::score_cutoff_to_distance<100>(score_cutoff, ab_len + ba_len);
    size_t dist =
        string_metric::levenshtein(diff_ab_joined, diff_ba_joined, {1, 1, 2}, cutoff_distance);

    if (dist <= cutoff_distance) {
        result = common::norm_distance<100>(dist, sect_ab_len + sect_ba_len, score_cutoff);
    }

    // exit early since the other ratios are 0
    if (!sect_len) {
        return result;
    }

    // levenshtein distance sect+ab <-> sect and sect+ba <-> sect
    // since only sect is similar in them the distance can be calculated based on
    // the length difference
    size_t sect_ab_dist = bool(sect_len) + ab_len;
    double sect_ab_ratio =
        common::norm_distance<100>(sect_ab_dist, sect_len + sect_ab_len, score_cutoff);

    size_t sect_ba_dist = bool(sect_len) + ba_len;
    double sect_ba_ratio =
        common::norm_distance<100>(sect_ba_dist, sect_len + sect_ba_len, score_cutoff);

    return std::max({result, sect_ab_ratio, sect_ba_ratio});
}
} // namespace detail

template <typename Sentence1, typename Sentence2>
double token_set_ratio(const Sentence1& s1, const Sentence2& s2, const double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    return detail::token_set_ratio(common::sorted_split(s1), common::sorted_split(s2),
                                   score_cutoff);
}

template <typename Sentence1>
CachedTokenSetRatio<Sentence1>::CachedTokenSetRatio(const Sentence1& s1)
    : tokens_s1(common::sorted_split(s1))
{}

template <typename Sentence1>
template <typename Sentence2>
double CachedTokenSetRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    if (score_cutoff > 100) return 0;

    return detail::token_set_ratio(tokens_s1, common::sorted_split(s2), score_cutoff);
}

/**********************************************
 *          partial_token_set_ratio
 *********************************************/

namespace detail {
template <typename CharT1, typename CharT2>
double partial_token_set_ratio(const SplittedSentenceView<CharT1>& tokens_a,
                                const SplittedSentenceView<CharT2>& tokens_b,
                                const double score_cutoff)
{
    /* in FuzzyWuzzy this returns 0. For sake of compatibility return 0 here as well
     * see https://github.com/maxbachmann/RapidFuzz/issues/110 */
    if (tokens_a.empty() || tokens_a.empty()) {
        return 0;
    }

    auto decomposition = common::set_decomposition(tokens_a, tokens_b);

    // exit early when there is a common word in both sequences
    if (!decomposition.intersection.empty()) return 100;

    return partial_ratio(decomposition.difference_ab.join(), decomposition.difference_ba.join(),
                         score_cutoff);
}
} // namespace detail

template <typename Sentence1, typename Sentence2, typename CharT1, typename CharT2>
double partial_token_set_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    return detail::partial_token_set_ratio(common::sorted_split(s1), common::sorted_split(s2),
                                           score_cutoff);
}

template <typename Sentence1>
CachedPartialTokenSetRatio<Sentence1>::CachedPartialTokenSetRatio(const Sentence1& s1)
    : tokens_s1(common::sorted_split(s1))
{}

template <typename Sentence1>
template <typename Sentence2>
double CachedPartialTokenSetRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    if (score_cutoff > 100) return 0;

    return detail::partial_token_set_ratio(tokens_s1, common::sorted_split(s2), score_cutoff);
}

/**********************************************
 *                token_ratio
 *********************************************/

template <typename Sentence1, typename Sentence2>
double token_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    auto tokens_a = common::sorted_split(s1);
    auto tokens_b = common::sorted_split(s2);

    auto decomposition = common::set_decomposition(tokens_a, tokens_b);
    auto intersect = decomposition.intersection;
    auto diff_ab = decomposition.difference_ab;
    auto diff_ba = decomposition.difference_ba;

    if (!intersect.empty() && (diff_ab.empty() || diff_ba.empty())) {
        return 100;
    }

    auto diff_ab_joined = diff_ab.join();
    auto diff_ba_joined = diff_ba.join();

    size_t ab_len = diff_ab_joined.length();
    size_t ba_len = diff_ba_joined.length();
    size_t sect_len = intersect.length();

    double result = ratio(tokens_a.join(), tokens_b.join(), score_cutoff);

    // string length sect+ab <-> sect and sect+ba <-> sect
    size_t sect_ab_len = sect_len + bool(sect_len) + ab_len;
    size_t sect_ba_len = sect_len + bool(sect_len) + ba_len;

    auto cutoff_distance = common::score_cutoff_to_distance<100>(score_cutoff, ab_len + ba_len);
    size_t dist =
        string_metric::levenshtein(diff_ab_joined, diff_ba_joined, {1, 1, 2}, cutoff_distance);
    if (dist <= cutoff_distance) {
        result = std::max(
            result, common::norm_distance<100>(dist, sect_ab_len + sect_ba_len, score_cutoff));
    }

    // exit early since the other ratios are 0
    if (!sect_len) {
        return result;
    }

    // levenshtein distance sect+ab <-> sect and sect+ba <-> sect
    // since only sect is similar in them the distance can be calculated based on
    // the length difference
    size_t sect_ab_dist = bool(sect_len) + ab_len;
    double sect_ab_ratio =
        common::norm_distance<100>(sect_ab_dist, sect_len + sect_ab_len, score_cutoff);

    size_t sect_ba_dist = bool(sect_len) + ba_len;
    double sect_ba_ratio =
        common::norm_distance<100>(sect_ba_dist, sect_len + sect_ba_len, score_cutoff);

    return std::max({result, sect_ab_ratio, sect_ba_ratio});
}

namespace detail {
template <typename CharT1, typename CachedSentence1, typename Sentence2>
double token_ratio(const SplittedSentenceView<CharT1>& s1_tokens,
                    const CachedRatio<CachedSentence1>& cached_ratio_s1_sorted, const Sentence2& s2,
                    double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    auto s2_tokens = common::sorted_split(s2);

    auto decomposition = common::set_decomposition(s1_tokens, s2_tokens);
    auto intersect = decomposition.intersection;
    auto diff_ab = decomposition.difference_ab;
    auto diff_ba = decomposition.difference_ba;

    if (!intersect.empty() && (diff_ab.empty() || diff_ba.empty())) {
        return 100;
    }

    auto diff_ab_joined = diff_ab.join();
    auto diff_ba_joined = diff_ba.join();

    size_t ab_len = diff_ab_joined.length();
    size_t ba_len = diff_ba_joined.length();
    size_t sect_len = intersect.length();

    double result = cached_ratio_s1_sorted.ratio(s2_tokens.join(), score_cutoff);

    // string length sect+ab <-> sect and sect+ba <-> sect
    size_t sect_ab_len = sect_len + bool(sect_len) + ab_len;
    size_t sect_ba_len = sect_len + bool(sect_len) + ba_len;

    auto cutoff_distance = common::score_cutoff_to_distance<100>(score_cutoff, ab_len + ba_len);
    size_t dist =
        string_metric::levenshtein(diff_ab_joined, diff_ba_joined, {1, 1, 2}, cutoff_distance);
    if (dist <= cutoff_distance) {
        result = std::max(
            result, common::norm_distance<100>(dist, sect_ab_len + sect_ba_len, score_cutoff));
    }

    // exit early since the other ratios are 0
    if (!sect_len) {
        return result;
    }

    // levenshtein distance sect+ab <-> sect and sect+ba <-> sect
    // since only sect is similar in them the distance can be calculated based on
    // the length difference
    size_t sect_ab_dist = bool(sect_len) + ab_len;
    double sect_ab_ratio =
        common::norm_distance<100>(sect_ab_dist, sect_len + sect_ab_len, score_cutoff);

    size_t sect_ba_dist = bool(sect_len) + ba_len;
    double sect_ba_ratio =
        common::norm_distance<100>(sect_ba_dist, sect_len + sect_ba_len, score_cutoff);

    return std::max({result, sect_ab_ratio, sect_ba_ratio});
}

// todo this is a temporary solution until WRatio is properly implemented using other scorers
template <typename CharT1, typename Sentence2>
double token_ratio(const std::basic_string<CharT1>& s1_sorted,
                    const SplittedSentenceView<CharT1>& tokens_s1,
                    const common::BlockPatternMatchVector& blockmap_s1_sorted, const Sentence2& s2,
                    double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    auto tokens_b = common::sorted_split(s2);

    auto decomposition = common::set_decomposition(tokens_s1, tokens_b);
    auto intersect = decomposition.intersection;
    auto diff_ab = decomposition.difference_ab;
    auto diff_ba = decomposition.difference_ba;

    if (!intersect.empty() && (diff_ab.empty() || diff_ba.empty())) {
        return 100;
    }

    auto diff_ab_joined = diff_ab.join();
    auto diff_ba_joined = diff_ba.join();

    size_t ab_len = diff_ab_joined.length();
    size_t ba_len = diff_ba_joined.length();
    size_t sect_len = intersect.length();

    double result = 0;
    auto s2_sorted = tokens_b.join();
    if (s1_sorted.size() < 65) {
        result = string_metric::detail::normalized_weighted_levenshtein(
                     common::to_string_view(s2_sorted), blockmap_s1_sorted,
                     common::to_string_view(s1_sorted), score_cutoff / 100) *
                 100;
    }
    else {
        result = fuzz::ratio(s1_sorted, s2_sorted, score_cutoff);
    }

    // string length sect+ab <-> sect and sect+ba <-> sect
    size_t sect_ab_len = sect_len + bool(sect_len) + ab_len;
    size_t sect_ba_len = sect_len + bool(sect_len) + ba_len;

    auto cutoff_distance = common::score_cutoff_to_distance<100>(score_cutoff, ab_len + ba_len);
    size_t dist =
        string_metric::levenshtein(diff_ab_joined, diff_ba_joined, {1, 1, 2}, cutoff_distance);
    if (dist <= cutoff_distance) {
        result = std::max(
            result, common::norm_distance<100>(dist, sect_ab_len + sect_ba_len, score_cutoff));
    }

    // exit early since the other ratios are 0
    if (!sect_len) {
        return result;
    }

    // levenshtein distance sect+ab <-> sect and sect+ba <-> sect
    // since only sect is similar in them the distance can be calculated based on
    // the length difference
    size_t sect_ab_dist = bool(sect_len) + ab_len;
    double sect_ab_ratio =
        common::norm_distance<100>(sect_ab_dist, sect_len + sect_ab_len, score_cutoff);

    size_t sect_ba_dist = bool(sect_len) + ba_len;
    double sect_ba_ratio =
        common::norm_distance<100>(sect_ba_dist, sect_len + sect_ba_len, score_cutoff);

    return std::max({result, sect_ab_ratio, sect_ba_ratio});
}
} // namespace detail

template <typename Sentence1>
template <typename Sentence2>
double CachedTokenRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    return detail::token_ratio(s1_tokens, cached_ratio_s1_sorted, s2, score_cutoff);
}

/**********************************************
 *            partial_token_ratio
 *********************************************/

template <typename Sentence1, typename Sentence2, typename CharT1, typename CharT2>
double partial_token_ratio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    auto tokens_a = common::sorted_split(s1);
    auto tokens_b = common::sorted_split(s2);

    auto decomposition = common::set_decomposition(tokens_a, tokens_b);

    // exit early when there is a common word in both sequences
    if (!decomposition.intersection.empty()) return 100;

    auto diff_ab = decomposition.difference_ab;
    auto diff_ba = decomposition.difference_ba;

    double result = partial_ratio(tokens_a.join(), tokens_b.join(), score_cutoff);

    // do not calculate the same partial_ratio twice
    if (tokens_a.word_count() == diff_ab.word_count() &&
        tokens_b.word_count() == diff_ba.word_count()) {
        return result;
    }

    score_cutoff = std::max(score_cutoff, result);
    return std::max(result, partial_ratio(diff_ab.join(), diff_ba.join(), score_cutoff));
}

namespace detail {
template <typename CharT1, typename Sentence2>
double partial_token_ratio(const std::basic_string<CharT1>& s1_sorted,
                            const SplittedSentenceView<CharT1>& tokens_s1, const Sentence2& s2,
                            double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    auto tokens_b = common::sorted_split(s2);

    auto decomposition = common::set_decomposition(tokens_s1, tokens_b);

    // exit early when there is a common word in both sequences
    if (!decomposition.intersection.empty()) return 100;

    auto diff_ab = decomposition.difference_ab;
    auto diff_ba = decomposition.difference_ba;

    double result = partial_ratio(s1_sorted, tokens_b.join(), score_cutoff);

    // do not calculate the same partial_ratio twice
    if (tokens_s1.word_count() == diff_ab.word_count() &&
        tokens_b.word_count() == diff_ba.word_count()) {
        return result;
    }

    score_cutoff = std::max(score_cutoff, result);
    return std::max(result, partial_ratio(diff_ab.join(), diff_ba.join(), score_cutoff));
}

} // namespace detail

template <typename Sentence1>
CachedPartialTokenRatio<Sentence1>::CachedPartialTokenRatio(const Sentence1& s1)
    : tokens_s1(common::sorted_split(s1))
{
    s1_sorted = tokens_s1.join();
}

template <typename Sentence1>
template <typename Sentence2>
double CachedPartialTokenRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    return detail::partial_token_ratio(s1_sorted, tokens_s1, s2, score_cutoff);
}

/**********************************************
 *                  WRatio
 *********************************************/

template <typename Sentence1, typename Sentence2>
double WRatio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    if (score_cutoff > 100) return 0;

    constexpr double UNBASE_SCALE = 0.95;

    auto s1_view = common::to_string_view(s1);
    auto s2_view = common::to_string_view(s2);

    /* in FuzzyWuzzy this returns 0. For sake of compatibility return 0 here as well
     * see https://github.com/maxbachmann/RapidFuzz/issues/110 */
    if (s1_view.empty() || s2_view.empty()) {
        return 0;
    }

    size_t len_a = s1_view.length();
    size_t len_b = s2_view.length();
    double len_ratio = (len_a > len_b) ? static_cast<double>(len_a) / static_cast<double>(len_b)
                                       : static_cast<double>(len_b) / static_cast<double>(len_a);

    double end_ratio = ratio(s1, s2, score_cutoff);

    if (len_ratio < 1.5) {
        score_cutoff = std::max(score_cutoff, end_ratio) / UNBASE_SCALE;
        return std::max(end_ratio, token_ratio(s1, s2, score_cutoff) * UNBASE_SCALE);
    }

    const double PARTIAL_SCALE = (len_ratio < 8.0) ? 0.9 : 0.6;

    score_cutoff = std::max(score_cutoff, end_ratio) / PARTIAL_SCALE;
    end_ratio = std::max(end_ratio, partial_ratio(s1, s2, score_cutoff) * PARTIAL_SCALE);

    score_cutoff = std::max(score_cutoff, end_ratio) / UNBASE_SCALE;
    return std::max(end_ratio,
                    partial_token_ratio(s1, s2, score_cutoff) * UNBASE_SCALE * PARTIAL_SCALE);
}

template <typename Sentence1>
CachedWRatio<Sentence1>::CachedWRatio(const Sentence1& s1)
    : cached_partial_ratio(s1), tokens_s1(common::sorted_split(s1))
{
    s1_view = common::to_string_view(s1);
    s1_sorted = tokens_s1.join();

    blockmap_s1_sorted.insert(common::to_string_view(s1_sorted));
}

template <typename Sentence1>
template <typename Sentence2>
double CachedWRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    if (score_cutoff > 100) return 0;

    constexpr double UNBASE_SCALE = 0.95;

    auto s2_view = common::to_string_view(s2);

    /* in FuzzyWuzzy this returns 0. For sake of compatibility return 0 here as well
     * see https://github.com/maxbachmann/RapidFuzz/issues/110 */
    if (s1_view.empty() || s2_view.empty()) {
        return 0;
    }

    size_t len_a = s1_view.length();
    size_t len_b = s2_view.length();
    double len_ratio = (len_a > len_b) ? static_cast<double>(len_a) / static_cast<double>(len_b)
                                       : static_cast<double>(len_b) / static_cast<double>(len_a);

    double end_ratio = cached_partial_ratio.cached_ratio.ratio(s2_view, score_cutoff);

    if (len_ratio < 1.5) {
        score_cutoff = std::max(score_cutoff, end_ratio) / UNBASE_SCALE;
        // use pre calculated values
        auto r =
            detail::token_ratio(s1_sorted, tokens_s1, blockmap_s1_sorted, s2_view, score_cutoff);
        return std::max(end_ratio, r * UNBASE_SCALE);
    }

    const double PARTIAL_SCALE = (len_ratio < 8.0) ? 0.9 : 0.6;

    score_cutoff = std::max(score_cutoff, end_ratio) / PARTIAL_SCALE;
    end_ratio =
        std::max(end_ratio, cached_partial_ratio.ratio(s2_view, score_cutoff) * PARTIAL_SCALE);

    score_cutoff = std::max(score_cutoff, end_ratio) / UNBASE_SCALE;
    auto r = detail::partial_token_ratio(s1_sorted, tokens_s1, s2_view, score_cutoff);
    return std::max(end_ratio, r * UNBASE_SCALE * PARTIAL_SCALE);
}

/**********************************************
 *                QRatio
 *********************************************/

template <typename Sentence1, typename Sentence2>
double QRatio(const Sentence1& s1, const Sentence2& s2, double score_cutoff)
{
    auto s1_view = common::to_string_view(s1);
    auto s2_view = common::to_string_view(s2);

    /* in FuzzyWuzzy this returns 0. For sake of compatibility return 0 here as well
     * see https://github.com/maxbachmann/RapidFuzz/issues/110 */
    if (s1_view.empty() || s2_view.empty()) {
        return 0;
    }

    return ratio(s1_view, s2_view, score_cutoff);
}

template <typename Sentence1>
template <typename Sentence2>
double CachedQRatio<Sentence1>::ratio(const Sentence2& s2, double score_cutoff) const
{
    auto s2_view = common::to_string_view(s2);

    /* in FuzzyWuzzy this returns 0. For sake of compatibility return 0 here as well
     * see https://github.com/maxbachmann/RapidFuzz/issues/110 */
    if (s1_view.empty() || s2_view.empty()) {
        return 0;
    }

    return cached_ratio.ratio(s2_view, score_cutoff);
}

} // namespace fuzz
} // namespace rapidfuzz
#endif // RAPIDFUZZ_AMALGAMATED_HPP_INCLUDED
