
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

int main()
{
	auto x = cson()
}
```
