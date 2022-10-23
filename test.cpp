
#include <iostream>
#include <cson/cson.h++>

namespace test
{
CSON_LABEL(name);
CSON_LABEL(age);
CSON_LABEL(work);
CSON_LABEL(dict);
CSON_LABEL(fun);
CSON_LABEL(items);
}

int main()
{
	using namespace test;

	auto x = cson
	(
	 	name = "Rafi", 
		age = 55,
		dict = cson
		(
			name = 1947, 
			age = "The type of age is deduced now which is std::string", 
			fun = [](std::string const & name) { std::cout << "Hello " << name << std::endl; },
			items = {"Shaan", "udit", "Sonu"}
		),
		fun = {1,2,3,4}, 
		work = "Singing"
	);

	x.dict.fun("Sarfaraz Nawaz");

	std::cout << x.name << "," << x.age <<"," << x.work << std::endl;
	x.name="Mukesh";
	x.age++; //well it is int
	std::cout << x.name << "," << x.age <<"," << x.work << std::endl;

	std::cout << x << std::endl;
	std::cout << x[work] << std::endl;

	std::cout << x[dict][age] << std::endl;
	std::cout << x.dict[age] << std::endl;
	std::cout << x[dict].age << std::endl;

	for(auto const & key : x.keys()) {
		std::cout << "key => " << key << std::endl;
    }

    std::cout << "---- iterate using .for_each ----" << std::endl;
    // we can also iterate over keys and values, but for that we have to
    // use .for_each() method passing a generic lambda (requires C++14 or above)
    auto printable_values = cson(
        name = "Rafi",
		age = 55,
		dict = cson
		(
			name = 1947,
			age = "The type of age is deduced now which is std::string"
		),
		work = "Singing"
	);

    printable_values.for_each([](std::string const & key, auto && value) {
        // note: in each iteration the type of 'value' could be different, which is why it's declared to be `auto`
        std::cout << key << " : " << value << std::endl;
    });
}
