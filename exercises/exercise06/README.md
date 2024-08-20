# Exercise 6: Compile-time Computation

If your not yet satisfied with your BoundedBuffer implemetnation, please continue

## Literal Vector Type

Implement an N-dimensional `Vector` literal type. Don't worry, we don't want you to implement a STL-like container here. We rather want you to implement a simple type in the mathematical sense of vector, that can be used at compile-time. We have prepared a set of test cases [here](./).

The CUTE tests also contain `static_assert`s to show the compile-time capabilities of your `Vector`, at least for the cases where this is feasible. The CUTE `ASSERT`s in the test are for convenience reasons. Because a `static_assert` will not tell you what the actual and the expected values effectively were on failure, it is amenable to still have the CUTE framework for checking the values at run-time to see the comparison. You just need to comment the `static_assert` out.

**Note:** Since several test cases rely on class template argument deduction, Cevelop might mark the code as incorrect in many places, even though it might be correct! For this exercise rely on the compiler output instead.

Implement the following features:

* Allow creation of a vector with explicit class template arguments: `constexpr Vector<double, 1> v{1.0}`. 
  * Use an `std::array` for storing the `Vector`'s values.
  * You need to implement a constructor that is a variadic template to accommodate the arbitrary number of constructor arguments.
* Implement the subscript operator to access the individual components: `v[0]`
* Check that accessing an invalid index with the subscript operator throws an exception. Can you do this at compile-time?
* Overload the subscript operator that it distinguishes between `const` and non-`const` access. Can both be used in `constexpr` contexts?
* Implement the `==` operator for comparing `Vector`s (note that with C++20 this implicitly defines `operator!=`).
* Implement an output operator (`<<`) for printing `Vector`'s on an `std::ostream`. Can you implement that as `constexpr` function?
* Implement a `length()` member function that returns the length of a `Vector`.
* Implement a `innerProduct()` function for calculating the inner product of a `Vector`.
* **Difficult:** Implement class template argument deduction for `Vector`:
  * Implement a deduction guide for that constructor.
  * Can you restrict that it is not possible to supply different argument types for the construction? 
    * For C++17 you ca use the predefined `are_all_same` predicate. It takes multiple type arguments and has the value `true` if all types are the same. You can apply it in an `std::enable_if_t` default template argument for the constructor.
    * Can you use a concept for C++20 to restrict the types (tip `std::same_as<T>`)
  * Is it possible to check that the compilation fails when initializing a `Vector` with different types through a succeeding test? (tricky but doable)


## Strong Unit Types: Conversion with Tags and Traits

Implement a `Temperature` literal type. The `Temperature` type shall be taggable with the units `Kelvin`, `Celcius` and `Fahrenheit` similar to what was shown wrt. Speed on the slides.

* Add the required tag types to the namespace `units::tags`.
* Specify the `Temperature` class template that stores the temperature in a `double` value.
* Implement comparison operations for the `Temperature` template for comparison with other objects of the same template instance (`==`, `!=`, `<`, `>`, `<=` and `>=`).
* Implement arithmetic operations for the `Temperature` template (`+`, `-`) - unary and binary.
* Implement the `ConversionTraits` class template with a `convert` member function and add a specialization for every possible conversion. You can lookup the conversion formula on the web.
* Implement a `temperatureCast` function template that delegates conversion to the `ConversionTraits` template.
* Add comparison operation templates to allow comparison of objects of arbitrary `Temperature` instances.
* Add user defined literal operators (`_K`, `_C`, `_F`) to the `unit::literals` namespace.

***Note:*** The provided tests for this exercies do not contain test cases for all operations above add them yourself.

If you do not want to set up your IDE with CUTE or use Cevelop, here is a compiler explorer environment for you to work with: 

[Compiler Explorer TemperatureTest](https://godbolt.org/z/K5r8148jK)
