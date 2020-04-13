/* SPDX-License-Identifier: MIT */
/* Copyright © 2020 Max Bachmann */
/* Copyright © 2011 Adam Cohen */

#pragma once
#include <boost/utility/string_view.hpp>
#include <type_traits>
#include "utils.hpp"
#include "string_utils.hpp"

template<
    typename Sentence1, typename Sentence2,
	typename Char1 = char_type<Sentence1>,
	typename Char2 = char_type<Sentence2>
>
using IsConvertibleToSameStringView = std::enable_if_t<
        std::is_same<Char1, Char2>{}
     && std::is_convertible<Sentence1 const&, boost::basic_string_view<Char1>>{}
    >;

namespace fuzz {

template<
    typename Sentence1, typename Sentence2,
	typename CharT = char_type<Sentence1>,
    typename = IsConvertibleToSameStringView<Sentence1, Sentence2>
>
percent ratio(const Sentence1 &s1, const Sentence2 &s2, const percent score_cutoff = 0);

template<
    typename Sentence1, typename Sentence2,
	typename CharT = char_type<Sentence1>,
    typename = IsConvertibleToSameStringView<Sentence1, Sentence2>
>
percent partial_ratio(const Sentence1 &s1, const Sentence2 &s2, percent score_cutoff = 0);

template<
    typename Sentence1, typename Sentence2,
	typename CharT = char_type<Sentence1>,
    typename = IsConvertibleToSameStringView<Sentence1, Sentence2>
>
percent token_sort_ratio(const Sentence1& s1, const Sentence2& s2, percent score_cutoff = 0);

template<
    typename Sentence1, typename Sentence2,
	typename CharT = char_type<Sentence1>,
    typename = IsConvertibleToSameStringView<Sentence1, Sentence2>
>
percent partial_token_sort_ratio(const Sentence1& s1, const Sentence2& s2, percent score_cutoff = 0);


template<
    typename Sentence1, typename Sentence2,
	typename CharT = char_type<Sentence1>,
    typename = IsConvertibleToSameStringView<Sentence1, Sentence2>
>
percent token_set_ratio(const Sentence1& s1, const Sentence2& s2, const percent score_cutoff = 0);

template<
    typename Sentence1, typename Sentence2,
	typename CharT = char_type<Sentence1>,
    typename = IsConvertibleToSameStringView<Sentence1, Sentence2>
>
percent partial_token_set_ratio(const Sentence1& s1, const Sentence2& s2, percent score_cutoff = 0);

template<typename CharT>
percent token_ratio(
	const Sentence<CharT>& s1,
	const Sentence<CharT>& s2,
	percent score_cutoff = 0);

template<typename CharT>
percent partial_token_ratio(
	const boost::basic_string_view<CharT>& s1,
	const boost::basic_string_view<CharT>& s2,
	percent score_cutoff = 0);

template<typename CharT>
percent partial_token_ratio(
	const std::basic_string<CharT>& s1,
	const std::basic_string<CharT>& s2,
	percent score_cutoff = 0);

template<typename CharT>
std::size_t bitmap_distance(const Sentence<CharT>& s1, const Sentence<CharT>& s2);

template<typename CharT>
percent bitmap_ratio(const Sentence<CharT>& s1, const Sentence<CharT>& s2, percent score_cutoff = 0);

template<typename CharT>
percent length_ratio(const Sentence<CharT>& s1, const Sentence<CharT>& s2, percent score_cutoff = 0);

template<typename CharT>
percent quick_lev_estimate(const Sentence<CharT>& s1, const Sentence<CharT>& s2, percent score_cutoff = 0);

template<typename CharT>
percent WRatio(const Sentence<CharT>& s1, const Sentence<CharT>& s2, percent score_cutoff = 0);
}

#include "fuzz.txx"
