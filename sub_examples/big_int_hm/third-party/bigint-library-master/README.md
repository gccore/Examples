# bigint-library
C++ Library for Large Integers  

## Overview
This is a C++ library for large integers. I made this C++ code library because there are no built-in large integers library (like BigInteger in Java) in C++.  
In this version, **integer is restricted to be non-negative.** We will add some features because it is still in development. Though, you still can use this version because it supports addition, subtraction, and multiplication, and even division!  

In this implementation, arithmetic operations especially for multiplication and division **run in a rapid time complexities**!  

* Addition: O(n) time complexity  
* Subtraction: O(n) time complexity  
* Multiplication: O(n log n) time complexity  
* Division: O(n log n) time complexity, about 10x slower than multiplication  

## How to use?
The class name of this library is "bigint".  
In order to use "bigint", we need to include "bigint.h" in your source code.  

The example of code is like this:  
~~~
#include "bigint.h"
int main() {
	bigint x = 13, y = 8;
	std::cout << x + y << '\n'; // outputs 21
	std::cout << x - y << '\n'; // outputs 5
	std::cout << x * y << '\n'; // outputs 104
	return 0;
}
~~~

## Basic Implementation / Functions

### Implementation
It stores numbers as a 10<sup>4</sup>-ary number. In this implementation, the number of digits can be represented as <sup>2^n</sup>, because doing this makes implementation easier (and it is convenient to do FFT)
In this library, we can hold up to 2<sup>27</sup> digits in decimal (in 10<sup>4</sup>-ary number, it is 2<sup>25</sup> digits).  
So, the range of bigint x is, 0 ≤ x < 10<sup>2<sup>27</sup></sup>.  

### Overview of Functions
Although the content of bigint class is light (currently about 7KB), there are many functions in bigint class.  
 1. Constructors / Assigning Operators
 2. Basic Functions
 3. Addition / Subtraction
 4. Multiplication
 5. Division

### 1. Constructors / Assigning Operators
There are four constructors there, like following:  
~~~
bigint::bigint() // initialize to zero
bigint::bigint(long long x) // initialize to 64-bit value x
bigint::bigint(string s) // initialize to string s which represents a number without leading-zero
bigint::bigint(bigint& x) // copy constructor
~~~

Also, there are some assigning operators, but assigning string is not allowed (so, it means only "long long" and "bigint" type is allowed to assign)  

### 2. Basic Functions
There are three basic functions.  
~~~
int bigint::size() // return size of bigint vector, which can be always represented as 2^n
int bigint::digit() // return the number of digits in decimal
std::string bigint::to_string() // return string converted from bigint value
~~~

### 3. Addition / Subtraction
The algorithm is to calculate from least digit and hold a carry with a boolean value.  
The following is the algorithm to calculate A+B which A = a<sub>0</sub>×v<sup>0</sup>+a<sub>1</sub>×v<sup>1</sup>+...+a<sub>m-1</sub>×v<sup>m-1</sup> and B = b<sub>0</sub>×v<sup>0</sup>+b<sub>1</sub>×v<sup>1</sup>+...+b<sub>m-1</sub>×v<sup>m-1</sup>.  
~~~
carry <-- false
for i = 0 to m-1:
  a[i] <-- a[i]+b[i]+carry
  if a[i] >= v:
    a[i] <-- a[i]-v
    carry <-- true
  else:
    carry <-- false
~~~
The algorithm for subtraction is basically the same.  

The time complexity is O(n / log n), if n is the number of digits in decimal.

### 4. Multiplication
I used [Number Theoretic Transform](https://en.wikipedia.org/wiki/Discrete_Fourier_transform_(general)#Number-theoretic_transform) algorithm for multiplication. The implementation is non-recursive.  
The used moduli is following:  
- mod = 167772161, primitive root = 3, cycle = 2<sup>25</sup>  
- mod = 469762049, primitive root = 3, cycle = 2<sup>26</sup>  

We used [Chinese Remainder Theorem](https://en.wikipedia.org/wiki/Chinese_remainder_theorem) to merge results in two moduli.  

The time complexity is O(n), if n is the number of digits in decimal.  
