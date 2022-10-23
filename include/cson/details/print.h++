
#pragma once

#include <ostream>
#include <string>
#include <vector>

#include <cson/details/traits.h++>

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
	std::ostream& print(std::ostream & out, std::vector<Item> const & items, int tab)
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
		out << "\n" <<  std::string(tab, ' ') << "{\n";
		(void) unpack
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
