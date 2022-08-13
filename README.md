# Differences to the args-kata branch
This is essentially the same problem as the one described in the 
[args kata branch](https://github.com/raz-m12/kata-template/tree/args-kata).
The difference between these two branches is that here I try to use the 
[mocking API](https://google.github.io/googletest/gmock_cook_book.html) of GMock. 

# Problem description
This is a programming problem described in the book [The Coding Dojo Handbook](https://www.amazon.com/Coding-Dojo-Handbook-Emily-Bache/dp/919811803X) on page 111.

> The arguments passed to the program consist of flags and
values. Flags should be one character, preceded by a minus
sign. Each flag should have zero, or one value associated with
it.

> You should write a parser for this kind of arguments. This
parser takes a schema detailing what arguments the program
expects. The schema specifies the number and types of flags
and values the program expects.

> Once the schema has been specified, the program should pass
the actual argument list to the args parser. It will verify that
the arguments match the schema. The program can then ask
the args parser for each of the values, using the names of
the flags. The values are returned with the correct types, as
specified in the schema.

## Example
If the program is to be called with these arguments:

> -l -p 8080 -d /usr/logs

this indicates a schema with 3 flags: l (a boolean), p (an integer), d (a string).

# Proposed schema structure:

|Character| Type    | Schema Example | Value Example
|---------|---------|----------------|---------------------|
|char     | boolean | (b)            | -b                  |
|char*    | string  | (s*)           | -s Michael          |
|char#    | integer | (i#)           | -i 400              |
|char##   | double  | (d##)          | -d 3.14             |
|char[*]  | string array | (s[*])    | -s value1 -s value2 |


## Another example:

| Example schema     | Corresponding example                   |
|--------------------|-----------------------------------------|
| (f,s*,n#,a##,p[*]) | -f -s Bob -n 1 -a 3.2 -p e1 -p e2 -p e3 |

## Dependencies
### Necessary
* clang version 10.0.0
* cmake version 3.21.4
### Optional:
* c++ linters (with vs code support): clang-tidy and cppcheck
* clang-format
### Installed automatically:
* vcpkg (package management program)
* gtest/gmock (downloaded via vcpkg)

# Installation, building and running the tests

## Downloading the repository
```
git clone --single-branch --branch args-kata https://github.com/raz-m12/kata-template.git
cd kata-template
```

## Installation
Inside the project root run:
```
./install.sh
```
This will configure the package manager vcpkg together with the dependency gtest, the c++ unit testing framework.

From the root directory, to compile and link the project use:
```
cd .build && cmake -D CMAKE_C_COMPILER=clang .. -D CMAKE_CXX_COMPILER=clang++
cmake --build . --target kata
```

## Running the tests
From the root directory:
```bash
# From the .build directory, run tests individually
./kata
# Or using cmake (ctest)
ctest --rerun-failed --output-on-failure
```
