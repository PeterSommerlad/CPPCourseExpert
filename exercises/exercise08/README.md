# Exercise 8

Here it is time for using the code that you were asked to bring along to look at.

Depending on how it is created try one or more of the following refactorings. See if you can employ Cevelop's static analisys and quick fix or refactoring features to support it:

* make your code const clean (Cevelop automates this) and provide mutating member functions with an lvalue-reference qualifier.
* replace usage of plain pointers or arrays
* replace usage of integer types with the safer integer replacement types from [https://github.com/PeterSommerlad/PSsimplesafeint](https://github.com/PeterSommerlad/PSsimplesafeint)
* replace domain specific use of a numeric type with a strong type, i.e. using [https://github.com/PeterSommerlad/PSsst](https://github.com/PeterSommerlad/PSsst)
* replace dynamic polymorphism using inheritance and virtual with either `std::variant` or type erasure
* replace macros constexpr values and function (note: Cevelop can automate this)
* take your own idea from this course for code modernization