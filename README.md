
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


### More examples

```c++

#include <iostream>
#include <cson/cson.h++>

//creates few labels first
CSON_LABEL(name);
CSON_LABEL(age);
CSON_LABEL(work);
CSON_LABEL(func);
CSON_LABEL(child);
CSON_LABEL(items);

int main()
{
	//create a cson object with some attributes, even nested cson object
	auto x = cson(
		name = "Rafi",
		age = 55,
		items = {1,2,3,4,5},  //this turns into a std::vector<int>
		func = [](std::string const & name) { //can be a functor/function/lambda also
			std::cout << ("Hello " + name)  << std::endl; 
		},
		child = cson(   //nested cson object
			name  = 100,                      //now name becomes int
			age   = "here age is string",     //age is std::string now
			items = {"Shaan", "Udit", "Sonu"},//this turns into std::vector<std::string>
			child = cson(                      //yet again
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

It is also possibe to treat the attributes as keys, so we can write as:
```c++

x[func]("Lata");  //invoke function
	
std::cout << x[child][name] << std::endl; //access child attribute to print it
	
```

And we can even mix them:
```c++

std::cout << x.child[name] << std::endl; //access child attribute to print it
std::cout << x[child].name << std::endl; //access child attribute to print it
```

All mean exactly same thing!

### Compilers

Tested with GCC 4.8.2 with `-std=c++11`.


### Suggestions

Suggestions are most welcome. Feel free to report issues, send pull requests or suggest improvements by sending email at sir_nawaz959@yahoo.com. 


