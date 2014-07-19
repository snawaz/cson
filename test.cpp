
#include <iostream>
#include <cson/cson.h++>

CSON_LABEL(name);
CSON_LABEL(age);
CSON_LABEL(work);
CSON_LABEL(dict);
CSON_LABEL(fun);

int main()
{
#if 0
	//1
	match(a)
	(
	   [](int value)         { std::cout << "int = " << value << std::endl; },
	   [](float value)       { std::cout << "float = " << value << std::endl; },
	   [](std::string value) { std::cout << "string = " << value << std::endl; },
	);

#endif
	//auto x = cson(name = "Rafi", age = 55, work = "Singing");
	auto x = cson(name = "Rafi", 
				  age = 55,
				  dict = cson(name = 1947, 
				  	  		  age = "The type of age is deduced now which is std::string", 
				 			  fun = [](std::string const & name) { std::cout << "Hello " << name << std::endl; }),
				  fun = {1,2,3,4}, // fun.array(1,2,3,4,5); fun.tuple(1,2, "Hehe")
				  work = "Singing");

	x.dict.fun("Sarfaraz Nawaz");

	std::cout << x.name << "," << x.age <<"," << x.work << std::endl;
	x.name="Changed Name";
	x.age++; //well it is int
	std::cout << x.name << "," << x.age <<"," << x.work << std::endl;

	std::cout << x << std::endl;
	std::cout << x[work] << std::endl;

	for(auto const & key : x.keys())
		std::cout << "key => " << key << std::endl;

	auto z = _cson {
		name = "Rafi",
		age  = 100
	};

	//auto obj = from(string).into(cson(name="", age=int()));
	//auto obj = cson(name="", age=int()).from(string);
	//auto obj = cson(name="", age=int())(string);
	//
	//auto obj = x.extend(abc = xyz, mnc = opq);
	//auto obj = extend(x, abc = xyz, mnc = opq);
#if 0
	auto y = cson
		(
		 name = "Rafi", 
		 age = 55, 
		 dict = cson
		 (
		  name = "Lata", 
		  work = "Singing",
		  dict = cson
		  (
		   name = 10,
		   age = "Haha",
		   dict = cson
		   (
			name = "Lata", 
			dict = cson
			(
			 name = 10,
			 age = "Haha"
			),
			work = "Singing"
		   )
		  )
		 )
		 );

	//std::cout << y.name << "," << y.dict.name << std::endl;
	std::cout << y << std::endl;
#endif 		
}
