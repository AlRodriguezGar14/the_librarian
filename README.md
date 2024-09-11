# Library Program

This program is a simple library management system implemented in C. It allows you to create books, insert them in sorted order into a library, find them, and remove them. It also includes some basic tests for edge cases.

## Features

- Create a book with a title, author, and publication year
- Insert a book into a library
- Find a book in the library by title
- Remove a book from the library

## Building

The program can be built using the provided Makefile. The following commands are available:

- `make all`: Compiles the program
- `make clean`: Removes the object files
- `make fclean`: Removes the object files and the executable
- `make re`: Re-compiles the program from scratch
- `make sanitize`: Compiles the program with address sanitizer enabled
- `make test`: Runs the program
- `make memory`: Runs the program with `valgrind -s` to check for memory leaks

## Usage

After building the program with `make all`, you can run it with `./library_program`.
You can also use `make test` or `make memory`

