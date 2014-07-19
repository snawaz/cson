
C++ Simple Object Notation (CSON)
=================================

It is a library to create objects with static attributes on the fly, using notation inspired from JSON:
```c++
auto x = cson(name = "Rafi", age = 55, work = "Singing");

std::cout << x.name << "," << x.age << "," << x.work << std::endl;
```

Here the type of each attribute is statically determined, which means `x.name` is `std::string`, `x.age` is `int` and so on.

Examples
========
```c++

#include <cson/cson.h++>

int main()
{
	auto x = cson()
}
```
