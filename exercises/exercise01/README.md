# Exercises 01

Goal: Familiarize yourself with IDE Cevelop, CUTE unit testing.

## C++ Rehearsal

In Cevelop, create one CUTE project for all of the follwing.

You can directly implement test cases and the functions under test within the Test.cpp file generated.
For each test case required, either manually implement a function without parameters returning void and copy the code provided, 
or use the pop-up menu in the editor and select "Source->New Test Function" or select the appropriate hot key displayed.

If you can think of additional useful test cases (you should) implement those as well.

Do not hesitate to summon your trainer, when you seem stuck. Often a minimal input can help with a usability or thinking roadblock.


For the following tasks write/copy test cases first!

1.  Create a function that takes an `int` as parameter and returns the
    next value (`increment`).

    ``` cpp
    int const value = 19;
    auto const next = increment(value);
    ASSERT_EQUAL(20, next);
    ```

2.  Add an overload of `increment` that modifies the parameter as
    side-effect. Do you encounter any problems when calling increment in
    the presence of both overloads? Stick with the side-effect version
    for the following exercises.

    ``` cpp
    int value = 19;
    increment(value);
    ASSERT_EQUAL(20, value);
    ```

3.  Signed integers overflow is undefined behavior in C++. Make your
    function safe. If such an overflow would happen throw an exception
    instead of incrementing the value (`std::overflow_error`).

    ``` cpp
    int maxValue = std::numeric_limits<int>::max();
    ASSERT_THROWS(increment(maxValue), std::overflow_error);
    ```

4.  Change your `increment` to accept parameters of arbitrary type and
    increments them - given they support the prefix increment operator
    and `std::numeric_limits` provides a corresponding maximum value.
    Start your test cases with `double`.

    ``` cpp
    double value = 1.5;
    increment(value);
    ASSERT_EQUAL(2.5, value);
    ```

5.  Overflow for `unsigned` types is well defined. Add an overload for this
    case that does not throw. Does it need to be a template
    specialization?

    ``` cpp
    auto maxValue = std::numeric_limits<unsigned long long>::max();
    increment(maxValue);
    ASSERT_EQUAL(0, maxValue);
    ```

6.  Several overloads are required to cover all cases of `unsigned` type
    (i.e. `unsigned`, `unsigned long`) because the template has an exact
    match for the overload resolution unless you provide an overload for
    the specific type. Example: If you provide the overload for
    `unsigned long long` and call increment with an `unsigned` variable
    as argument the template will be chosen instead of the
    `unsigned long long` overload. Therefore, try an alternative
    approach to tackle overflows. Create a predicate (as template)
    `allowOverflow` that returns `false` by default but can and should
    be specialized for `unsigned` types to be `true`. You can implement
    the predicate as variable, class or function template for that
    matter.

7.  With all the template specializations for the different `unsigned`
    types there is still much code, at least it avoids duplication in
    the logic. As usual, the standard library can help. Have a look at
    `std::numeric_limits::is_integer` and the `is_unsigned` type trait.
    Can you implement your predicate with those?

8.  Can you also pass an iterator to your `increment` function? You
    might experience different outcomes depending on your compiler. It
    might not be happy if you want to get `numeric_limits` for your
    iterator. Adapt your `increment` function to also have the
    capability to take a second parameter to have a user-provided limit.
    Your previous tests should still remain working. Therefore, add a
    default argument to that parameter. You probably used comparisons
    and a `-1` operation to your limit. Does this restrict the iterators
    you can use with `increment`?

    ``` cpp
    std::vector<int> v{1};
    auto it = std::end(v);
    ASSERT_THROWS(increment(it, std::end(v)), std::overflow_error);

    double d{9.5};
    ASSERT_THROWS(increment(d, 9.0), std::overflow_error);
    ```


## `dynArray` - a vector wrapper

We will create a generic wrapper class around std::vector that mimics most of its behavior, but is safer to use, because it will always do bounds checking. 
In addition we allow indexing with negative numbers to index from the end. So the last element in the `dynArray` will have index -1 (in addition to `size()-1`)

see the file [DynArrayTest.cpp](DynArrayTest.cpp) as a potential starting place for tests required. I recommend that you first comment the test cases and then succeedingly uncomment them and make them work.

For the implementation most functions will just forward to the corresponding function of std::vector, except for those, where checking that the vector is not empty is required, or where the behavior (indexing) is adjusted.

The only template parameer of your DynArray class should be the element type.

Note: if you do not have the boost libraries installed, use my header only counter iterator library available as [range_counter.h](https://github.com/PeterSommerlad/CPPCourseAdvanced/raw/main/exercises/solutions/exercise05/range_counter.h) or as 
[full PSRangeCounter repository](https://github.com/PeterSommerlad/PSRangeCounter) (you'd only need to copy `range_counter.h`)

The same exercise is also part of the C++ Advanced training. The following text is given there (the unit tests are provided here):

----

Many scripting languages allow dynamic arrays to be indexed with negative indices where `a[-1] ` denotes the last element in the array`a[size-1] `  and `a[-size] ` the first element `a[0] `.

Create a template class dynArray<T> that uses a std::vector<T> as a member (not as a super class) for its implementation. Implement the indexing member functions similar to std::vector for dynArray in a way that negative indices are allowed and every index access is actually bounds checked (use std::vector's facility for that).

*  Provide constructors for the following initializations, as it would be with std::vector (ignore allocator argument versions of std::vector) :
```
dynArray<char> a1{};
dynArray<int> a2{1,2,3,4,5}; // initializer_list
dynArray<std::string> a3(std::istream_iterator<std::string>{std::cin},std::istream_iterator<std::string>{}); // any iterator type!
```

*  Provide a Factory Function template `makedynArray()` that takes an `initializer_list<T>` and returns a dynArray<T> filled with the elements from the initializer list. Create an overload for accepting two iterators as well.
   or provide deduction guides, initialize a dynarray without needing to specify the template argument.


*  Create Unit Tests for all of your template class' behaviors. Best, one or more tests for a feature, before you implement it.
  *  Use different element types for your template class in the tests to prove that it works with different instantiations
  *  you must implement your class in a header file (dynArray.h) in the unit test project, a separate library won't work easily, because a template class lacks a .cpp file with content the linker is happy with.

The following functions of std::vector you **should not implement**:
*  allocator template parameter and functions using it
*  `getallocator()`
*  `reserve()`,`max_size()`
*  `operator=()` -- automatically provided one should be OK
*  `assign()`
*  `data()`
*  `shrink_to_fit()`
*  `emplace()`, `emplace_back()`, `insert()`
*  `swap`
*  `comparison operators`
*  all rvalue-reference overloads (unless you want to)

But you must implement all other members of std::vector by delegating to the corresponding member functions of your template class' data member of type std::vector.

----

