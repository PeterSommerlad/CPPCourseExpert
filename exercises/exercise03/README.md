# Exercise 3 BoundedBuffer with dynamic allocation

If you haven't finished with the fixed size buffer, do so first.

The exercises here will consume more than just one slot, so be patient, if you cannot finish it in time.

## Overview

Take your `BoundedBuffer.h` file and change the implementation and interface (best copy the whole project and change the namespace)

* Remove the integral type template parameter
* Add a `size_type` constructor parameter and a corresponding member
* Replace the `std::array` container member by a uniqe pointer to an array that is allocated dynamically on the heap
* Now your type becomes a General Manager type where you need to care about all special member functions
* Imlement move and copy operations to deal with the dynamically allocated buffer space.
  * Make sure, that you do not produce memory leaks and that you do not unnecessarily copy buffer elements when moving from another buffer
  * You should not copy elements from the *empty* part of the source buffer, since that memory might be uninitialized and thus could result in Undefined Behavior if accessed.
* Otherwise, your BoundedBuffer should behave similarly to the original one.

For a fresh start, you can also just take the test cases provided in this directory


## Detailed Description

A major disadvantage of the first `BoundedBuffer` is requirement to specify the size at compile-time. In this exercise you will change that. Apply what you have learned about dynamic heap memory management to improve your `BoundedBuffer` this lifts the necessity to specify the capacity as a template argument. The adapter version allows specifying the capacity through a constructor argument. This does not mean that the buffer now should be resizable, the size is still fix, but it can be specified at run-time.

***Before:***
```cpp
BoundedBuffer<S, 23> buffer{};
```

***After:***
```cpp
BoundedBuffer<S> buffer{23};
```


### Data Structure
You will not be able to use an `std::array` for storing the elements anymore (since it requires knowing the number of elements at compile-time). Instead, allocate an array of `T` objects on the heap using `std::make_unique<T[]>(size)`. And store the unique pointer in your `BoundedBuffer`.

* What is the type of the member variable for storing the elements?


### Element Access
Element access using `at` does not work using the plain array on the heap anymore. Therefore, you need to access the elements with the array index operator `[]`.

```cpp
T copy = values[0];  //reading the first element
values[23] = copy;   //writing the 24th element
```

## Constructors 

So far the implicitly available constructors have been sufficient. Now explicitly implement them yourself. You need to make sure they use the suitable move or copy operations on the elements. The behavior and the tests of your `BoundedBuffer` will not change if you do it correctly. Implement the following special member functions:
* Default constructor
* Copy constructor
* Move constructor
* Copy assignment operator
* Move assignment operator

### Special Member Functions

The most interesting part is the implementation of the constructor's and assignment operators. Think about how every special member function should behave:

* Default-Constructor: It probably does not make sense to provide a default constructor. Or what size would it have? zero?
* `BoundedBuffer(size_type capacity)`: Obviously we need a constructor that allows to specify the capacity of our dynamic `BoundedBuffer`. It needs to establish the invariant of the `BoundedBuffer`. Theoretically, it could be allowed to create a buffer of capacity `0`. Our test cases don't allow that though.
  * Prevent creation of a `BoundedBuffer` with capacity `0`
  * Allocate the required memory on the heap
  * Initialize all members correctly
* Copy-Constructor: It creates a new `BoundedBuffer` that represents a copy of the argument. After the constructor both `BoundedBuffer` objects must have their own memory for storing the elements.
  * Allocate the required memory on the heap
  * Copy the elements from the other `BoundedBuffer`
  * Initialize the members correctly
* Move-Constructor: This constructor steals the internal values of the argument. It is imporant that the `BoundedBuffer` passed as argument does not share the heap memory with the `this` object *after* the construction, even though the moved-from object should not be used afterwards (it's in coma state). ***Important Question:*** Why is that?
* Assignment-Operators: The assignment operators are similar to the corresponding constructor. ***Beware*** similar does not mean exactly the same! While construction always creates new object only the already existing object is involved. This is different during a (copy/move)-assignment, which involves always two existing objects, each with their own resources.
  * Move-Assignment Operator: The simplest implementation of the move-assignment operator is swapping the `BoundedBuffer` objects. As the argument of move-assignment operator is about to be expiring, the destructor will take care of resource deallocation and we don't need to do that explicitly.
  * Copy-Assignment Operator: Here the case is different. We need to create a copy of the argument and its resources. That is not very difficult, as we already did that in the copy-constructor. But there's a catch! The resources of the overwritten object need to be released explicitly. Think carefully about what you have to release.
* Destructor: While implementing the Copy-Assignment Operator you have already thought about what resources/memory to explicitly release. Here you have to do the same.

***Remark:*** You will recognize, if you have implemented the move operations properly, that you now need less move operations. Because only the pointers to the heap allocated array need to be moved the elements are left untouched.

***Question:*** What would be the impact (for you as an implementer and a user of the `BoundedBuffer`) if you provided an `std::initializer_list<T>` constructor that derives the capacity from the number of elements in the list? I.e. the `BoundedBuffer` is created and filled completely with the elements in the list.

You find an updated set of test cases in the exercise template. Our suggestion is again that you import them as a new project and copy your existing `BoundedBuffer.h` file into the tests.


## Advanced: Make your BoundedBuffer work with non-default-constructible classes



For example, the following class would not be default-constructible.
```cpp
struct X {
  X(int i) : x{i}{}
  int x;
};
```
Allocating arrays (`std::array<X, 5>` or plain C-arrays `X[5]`) of a type that cannot be default constructed, requires specifying the elements of that array upon allocation. Therefore, it is not possible to use an array of `X` as a buffer, as we would need to supply all elements upfront.

The solution will require you to allocate "raw" storage by using `make_unique<std::byte[]>(size)` for a reasonably sized buffer and placement `new` into that array. T Please make sure, that alignment and sizing of the array follow the rules for the template argument type.

You have to consider the following properties when implementing this feature:

* All constructors have to allocate that `std::byte` array with enough size to hold all elements of the buffer. `sizeof(Type[capacity])` allows you to figure out how many bytes you need to store `capacity` number of `Type` elements.
* The copy constructor must copy all valid elements from the buffer argument.
* The move constructor can simply swap its state with the buffer argument's state.
* Copy assignment can use the copy constructor to clone the other buffer and then just swap the content of the `this` object with the content of the copy.
* Move assigment can just swap the contents
* However, both assignments should to nothing when the argument is the same object as the `this` object.
* The destructor must delete all elements in the buffer before releasing the memory. It must not release non-allocated elements. This is cruicial as the memory (`std::byte[]`) is not aware of its content. Even when managed through a `std::unique_ptr` this will not change. Make sure that elements in the buffer get destructed exactly once (no undestroyed elements and no double deletes)!
* Accessing the elements (`at()`, etc.) requires correct determination of the memory location and a forceful cast of that location to the element type: `* std::launder(reinterpret_cast<Type*>(memoryLocation))`.

***Note:*** An updated project with test cases for this exercise is available in the subdirectory [BoundedBufferRawMemoryTest](BoundedBufferRawMemoryTest). We suggest you copy the tests into a new CUTE project and copy the `BoundedBuffer.h` from your previous exercise as a starting point. Since you do not allocate arrays of the element type anymore the test cases for `new` and `delete` change, i.e. those operators of the element type are not used anymore. The `bounded_buffer_heap_memory_suite` has been adapted accordingly and is available in the corresponding template project.

