
#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <cson/details/print.h++>
#include <cson/details/traits.h++>
#include <cson/details/label.h++>

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
