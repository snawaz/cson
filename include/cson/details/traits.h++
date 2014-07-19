
#pragma once

#include <type_traits>
#include <string>


struct any { template<typename T> any(T &&) {} };
using unpack = any[];

template<typename T> struct better { using type = T; };

template<> struct better<char *> { using type = std::string; };
template<> struct better<char const *> { using type = std::string; };

template<typename T>
using better_t = typename better<typename std::decay<T>::type>::type;

template<typename ... T>
struct typelist {};

template<typename Tag, bool, typename TL>
struct find_base_impl;

template<typename Tag, typename U, typename T, typename ... Rest>
struct find_base_impl<Tag,false, typelist<U,T,Rest...>> 
: find_base_impl<Tag, Tag::template match<T>::value, typelist<T, Rest...>> {};

template<typename Tag, typename U, typename ... Rest>
struct find_base_impl<Tag, true, typelist<U, Rest...>> { using type = U; };

template<typename Tag, typename T, typename ... Rest>
struct find_base 
{
	using type = typename find_base_impl<Tag, 
		  Tag::template match<T>::value, typelist<T, Rest...> >::type;
};
