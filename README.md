Big integer for C
=================

A big integer library for C. The idea is to store unsigned integers as null-terminated char arrays and provide common 
operations for it.

Version: 1.0

Limitations
-----------

* No negative numbers are supported
* No floating point numbers are supported
* No complex numbers are supported

Motivation
----------

I got my motivation for implementing this library by solving Problem #20 from Project Euler and found this library 
useful. However, I don't provide a solution for this problem.

Usage
-----

You need to compile *src/kmbint.c*. All header files are located in *include*. If you want to see some examples, have a
look at *src/example.c* or *src/tests.c*

Namespaces
----------

All names start with *kmbint*

Big Integer Data Structure
--------------------------

All big integers are encoded as null-terminated char arrays. All digits must be in range '0' to '9'. Support for leading 
zeros is not implemented. If big integers have leading zeros, the behavior is undefined. The zero value must always be 
encoded as "0".

Functions
---------

* *add* ... adds two numbers and stores the result in the first one. It must have sufficient space to store the result.
* *sub* ... subtracts two numbers and stores the result in the first one. The number must be greater than or equal to 
            the number to subtract. Otherwise the behavior of the function is undefined.
* *mul* ... multiplies two numbers and stores the result in the first one. It must have sufficient space to store the 
            result.
* *div* ... divides two numbers and stores the result in the first one. The divider must be greater zero.
* *mod* ... divides two numbers and stores the remainder of the operation in the first one. It must have sufficient 
            space to store the result. The divider must be greater than zero.
* *eq*, *neq*, *gt*, *gte*, *lt*, *lte* ... compares two numbers and returns true if the condition is true or false 
otherwise.
* *cross_sum* ... calculates the cross sum and overwrites the given number with its result.

Advanced considerations
=======================

* *memory management* ... The library uses only the stack for needed buffers and variables, therefore no heap operations
                        like malloc or free were used.
* *thread safety* ... no global variables or buffers are used so the library can be considered thread-safe. However, 
                      the operations are not atomic, so race conditions can happen if the same variable from multiple 
                      threads is used at the same time.
