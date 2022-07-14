# Problem description
This is a programming problem described in the book [The Coding Dojo Handbook](https://www.amazon.com/Coding-Dojo-Handbook-Emily-Bache/dp/919811803X) on page 111.

> The arguments passed to the program consist of flags and
> values. Flags should be one character, preceded by a minus
> sign. Each flag should have zero, or one value associated with
> it.

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

|Character| Type | Schema Example | Value Example
|---|---|---|----|
|char    | boolean | (b)          | -b
|char*   | string  | (s*)         | -s Michael
|char#   | integer | (i#)         | -i 400
|char##  | double  | (d##)        | -d 3.14
|char[*] | string array | (s[*])  | -s value1 -s value2


## Another example:

| Example schema     | Corresponding example |
|--------------------|-----------------------|
| (f,s*,n#,a##,p[*]) | -f -s Bob -n 1 -a 3.2 -p e1 -p e2 -p e3 |

# Installation, building and running the tests

## Dependencies
* clang version 10.0.0
* cmake version 3.21.4
* vcpkg (package management program)
* gtest/gmock (downloaded via vcpkg)
* c++ linters (with vs code support): clang-tidy and cppcheck

## Installation
Inside the project root run:
```
./install
```
This will configure the package manager vcpkg together with the dependency gtest, the c++ unit testing framework.

From the root directory, to compile and link the project use:
```
cmake .build
cmake --build .build --target kata
```

## Running the tests
From the root directory:
```bash
cd .build
# Then either to run tests individually
./kata
# Or using cmake (ctest)
ctest --rerun-failed --output-on-failure
```

