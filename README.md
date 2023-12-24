# vlark
vlark is a C++20-based VHDL parser that can tokenize, lex, parse, and generate abstract syntax trees for VHDL code. It is a fast and agile tool that leverages the latest features of C++20 to create efficient and elegant code.

Features
------

* Supports the full VHDL 2008 standard
* Uses C++20 features such as concepts, ranges, and modules
* Generates abstract syntax trees in JSON format
* Provides a command-line interface and a library interface
* Supports cross-platform compilation with CMake


Installation
-------

To install vlark, you need to have a C++20 compiler and CMake installed on your system. 
Then, follow these steps:

*  Clone this repository:


```bash

git clone https://github.com/your-username/vlark.git
cd vlark

```

*  Create a build directory and run CMake:

```bash

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release

cmake --build .


## test run

ctest
```



Library
-----

To use vlark as a library in your own C++ projects, you need to include the vlark.hpp header file and link with the vlark library. For example, to parse a VHDL source code from a string and print the abstract syntax tree to the standard output, you can write something like this:


```bash

#include <iostream>
#include <string>
#include "vlark.hpp"

int main() {
    // A sample VHDL source code
    std::string code = R"(
        entity AND_GATE is
            port (A, B: in bit; Y: out bit);
        end entity;
    )";

    // Create a vlark parser object
    vlark::parser parser;

    // Parse the code and get the abstract syntax tree
    vlark::ast ast = parser.parse(code);

    // Print the abstract syntax tree in JSON format
    std::cout << ast.to_json() << std::endl;

    return 0;
}

```