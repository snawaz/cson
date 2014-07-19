
C++ Simple Object Notation (CSON)
=================================

CSON allows users to create objects with named type-safe attributes on the fly, using notation inspired from JSON:

```c++
auto x = cson(name = "Rafi", age = 55, work = "Singing");

std::cout << x.name << "," << x.age << "," << x.work << std::endl;
```

Here the type of each attribute is statically determined during the creation of object &mdash; which means `x.name` is `std::string`, `x.age` is `int` and so on:

```c++

x.age = "I'm a string"; //compilation error :  age is int
x.age++;                //okay         
x.worK = "New job";     //compilation error :  object x has no member named `worK`
```

That's very intuitive. 


###More examples

```c++

#include <cson/cson.h++>

CSON_LABEL(name);
CSON_LABEL(age);
CSON_LABEL(work);
CSON_LABEL(func);
CSON_LABEL(child);

int main()
{
	//create a cson object with some attributes, even nested cson object
	auto x = cson
	(
		name = "Rafi",
		age = 55,
		func = [](std::string const & name) { std::cout << ("Hello " + name)  << std::endl; },
		child = cson
		(
			name = 100,   //now name becomes int
			age  = "here age is string",
			child = cson
			(
				func = "Hi",
				child = "Bye"
			)
		)
	);
	
	x.func("Lata");  //invoke function
	
	std::cout << x.child.name << std::endl; //access child attribute to print it
	
	std::cout << x << std::endl;  //print the entire object
}
```
