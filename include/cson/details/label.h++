
#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <cson/details/traits.h++>

#define CSON_LABEL(label) \
template<typename T> \
struct label##_t \
{\
	using type = T;\
	T label;\
	static std::string attribute_name() { return #label; } \
	template<typename U> struct rebind { using type = label##_t<U>; }; \
} ; \
struct generic_##label \
{\
	template<typename Label>\
	struct match\
	{\
		static const bool value = std::is_same<label##_t<typename Label::type>, Label>::value;\
	};\
	template<typename T> \
	label##_t<better_t<T>> operator=(T const & data)\
	{ \
		return { data };\
	}\
	template<typename T> \
	label##_t<std::vector<better_t<T>>> operator=(std::initializer_list<T> items)\
	{ \
		std::vector<better_t<T>> v; \
		v.reserve(items.size());\
		for(auto & item : items) v.emplace_back(std::move(item));\
		return { std::move(v) };\
	}\
}label

