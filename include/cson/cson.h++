
#include <ostream>
#include <type_traits>
#include <string>
#include <vector>

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

struct any { template<typename T> any(T &&) {} };
using unpack = any[];

template<typename T> struct better { using type = T; };

template<> struct better<char *> { using type = std::string; };
template<> struct better<char const *> { using type = std::string; };

template<typename T>
using better_t = typename better<typename std::decay<T>::type>::type;

template<typename ... Ts>
struct cson_t;

namespace details
{
	template<typename Attr>
	std::ostream& print_helper(std::ostream & out, Attr const & attr, int tab);

	template<typename Item>
	std::ostream& print(std::ostream & out, Item const  & item, int tab)
	{
		return out << item  << ",";  
	}

	template<typename Item>
	std::ostream& print(std::ostream & out, std::vector<Item> const  & items, int tab)
	{
		out << "[";
		auto it = items.begin();
		if ( it != items.end() )
		{
			out << *it;
			while( ++it != items.end() )
				out << ", " << *it;
		}
		return out << "]";  
	}

	template<typename ... Ts>
	std::ostream& print(std::ostream & out, cson_t<Ts...> const  & item, int tab)
	{
		//out << std::string(tab, '\t') << "{\n";
		out << "\n" <<  std::string(tab, ' ') << "{\n";
		unpack
		{ 
			print_helper(out, static_cast<Ts const&>(item), tab + 4) ... 
		};
		out << std::string(tab, ' ') << "}";
		return out;
	}
	template<typename Attr>
	std::ostream& print_helper(std::ostream & out, Attr const & attr, int tab) 
	{
		out << std::string(tab, ' ') << attr.attribute_name() << " : ";
		print(out, reinterpret_cast<typename Attr::type const &>(attr), tab);
	    return out << "\n";;
	}
}

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

template<typename ... Ts>
struct cson_t : public Ts ...
{
	template<typename Tag>
	using base_type = typename find_base<Tag, Ts...>::type;
	
	template<typename Tag>
	using value_type = typename base_type<Tag>::type;
public:
	
	template<typename ...Args>
	cson_t(Args && ... args) : Ts(std::forward<Args>(args)) ...
	{
	}

	template<typename Tag>
	auto operator[](Tag const &) -> value_type<Tag> &
	{
		return reinterpret_cast<value_type<Tag>&>(static_cast<base_type<Tag>&>(*this));
	}
	
	template<typename Tag>
	auto operator[](Tag const &) const -> value_type<Tag> const &
	{
		return reinterpret_cast<value_type<Tag> const &>(static_cast<base_type<Tag> const &>(*this));
	}

	std::vector<std::string> keys() const
	{
		return { Ts::attribute_name() ... };
	}
};

template<>
struct cson_t<> {};

template<typename ... Ts>
std::ostream& operator << (std::ostream & out, cson_t<Ts...> const  & item)
{
	out << "cson"; 
   	return details::print(out, item, 0) << "\n";
}

template<typename ... Ts>
auto cson(Ts && ... args) -> cson_t<better_t<Ts>...>
{
	return cson_t<better_t<Ts>...> { std::forward<Ts>(args) ... };
}

struct _cson
{
	template<typename ... Ts>
	_cson(Ts && ... args) { cson(std::forward<Ts>(args)...); }
};
