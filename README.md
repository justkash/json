# JSON 
This JSON utility was created with ease of use in mind while still providing a simple, yet performant way of working with JSON structures in C++.

## Usage
In order to work with the primitive types provided by JSON, JSONkit maps each of them to a C++ class as shown below

JSON               | C++
-------------------|-------------
String             | `JsonString`
Number             | `JsonNumber`
Object             | `JsonObject`
Array              | `JsonArray`
`true` & `false`   | `JsonBoolean`
`null`             | `JsonNull`

### Parsing a JSON String
```JSON
{
  "name" : "wubalubadubdub",
  "age"  : 60
}
```
```C++
std::string str = "{\"name\":\"wubalubadubdub\", \"age\":60}";
JsonObject json_obj(str);
JsonString json_str = json_obj.get_string("name");
JsonNumber json_nbr = json_obj.get_number("age");

// Prints wubalubadubdub 
std::cout << json_str.get_string() << std::endl;

// Prints 60
std::cout << json_nbr.get_int() << std::endl;
```

### Serializing a JSON Object
```C++
std::string str = "{\"name\":\"wubalubadubdub\", \"age\":60}";
JsonObject json_obj(str);

// Prints {"name":"wubalubadubdub", "age":60}
std::cout << json_obj.stringify() << std::endl; 

obj.set("num_toes", JsonNumber(7));

// Prints {"name":"wubalubadubdub", "age":60, "num_toes":7}
std::cout << json_obj.stringify() << std::endl; 
```
Note that while `Jsontring`, `JsonNumber`, `JsonBoolean` and `JsonNull` are immutable classes, both `JsonObject` and `JsonArray` are mutable. This means that it is possible to dynamically add and remove objects from either of these two class's objects.

More examples of what can be done with this utility can be found in the unittests.cpp file.

## Purpose
Why write another C++ JSON library? 

1. I didn't want to install Boost or any other libraries 
2. I didn't want to install any programs/scripts
3. I wanted an interface that was easy to use
4. I wanted it to be reasonably fast

## Installation
Installing this utility is as easy as dropping the json folder into a given project.

## Naive Benchmarks
Although execution speed was a concern for this project, it was not the main focus. However I conducted some naive benchmarks against another very popular C++ utility and generated the results below.

Although my benchmarks are not extensive, I am very interested in any profiling, testing and benchmarking results regarding this library. However, note that when performing any comparisons, this utility does not parse everything that is passed into it; it will only parse what is needed.

### Parsing
|Library Name   |Time (ms)      |Webpage                                 |
|---------------|---------------|----------------------------------------|
|json           |0.439          |N/A                                     |
|SuperEasyJson  |6.715          |sourceforge.net/projects/supereasyjson/ |

## License
Licensed under the [MIT](LICENSE.txt) License.