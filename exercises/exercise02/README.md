# Exercise 2

Goal is further familiarization. We will use the bounde buffer as an ongoing exercise and succeedingly create different versions of it until we use it to implement a thread-safe bounded queue.

## Fixed-size BoundedBuffer

`BoundedBuffers` are used in environments that have one or many producers and an consumers. The `BoundedBuffer` is used as a shared data structure for passing elements from the producer to the consumer. A `BoundedBuffer` has a fixed capacity and therefore, features an upper limit of maximum number of elements it can contain. Usually, it is implemented as a *FIFO* queue. Consumers must not be able to retrieve data from an empty buffer and likewise a producer on the other hand, must not be able to write data into a full buffer.

Your implementation will use an [`std::array`](http://en.cppreference.com/w/cpp/container/array) as base data structure and will behave like a circular buffer.

Your `BoundedBuffer` features the following API:
* `empty` – queries whether the buffer is empty
* `full` – queries whether the buffer is full
* `size` – queries the number of elements currently in the buffer
* `front` – returns the first element in the buffer; it allows modification of the first element
* `back` – returns the last element in the buffer; it allows modification of the last element
* `push` – inserts a new element into the buffer
* `pop` – removes the first element from the buffer
* `swap` – swaps the contents with another `BoundedBuffer` (parameter)


Furthermore, your `BoundedBuffer` must feature the following *member types*:
* `container_type`
* `size_type`

You get test suites for each task. Our recommendation is adding one test at a time. You can start by out-commenting every test. Adding one test will usually result in a red bar. Write just as much code to get the required functionality done (compiles and results in a green bar). Then start over with the next test case.

To start, create a new CUTE project within Cevelop and copy all files provided in this folder. For download convenience I also prepared a [zip file](BoundeBufferFixedSizeTests.zip) that you can download directly.

## Member Function Definitions (Signatures)

First implement the declarations of `BoundedBuffer`s members, without any logic, to get it compiled.
* ***Test-Suite***: `bounded_buffer_signatures_suite`

***Hint:*** If you are unsure about the signatures of the individual member functions you can get inspiration from the standard library. The [`std::queue`](http://en.cppreference.com/w/cpp/container/queue) offers a similar interface to your `BoundedBuffer`.

***Note:*** Some of the tests we provide are not really sensible for a real test scenario. But they will help you to get the signatures of your member functions right. There is a dependency to ***Boost*** (`type_index.h`). Accordingly, you need to have the [Boost library](http://www.boost.org) installed on your system and reference it from your project.

***Attention:*** The `boost` headers offered by the *CUTE* project wizard won't be sufficient, as they have an obsolete version.


## Behavior of a default-constructed `BoundedBuffer`

* Now implement the behavior of the member functions for a default-constructed `BoundedBuffer`. As always avoid *Undefined Behavior*.
* `empty` - returns `true`
* `full` – returns `false`, unless the buffer has been created with capacity `0`
* `size` – returns `0`
* `front` – throws an exception (`std::logic_error`)
* `back` – throws an exception (`std::logic_error`)
* `push` – inserts an element. However, you cannot observe this currently and you can ignore actually putting the element into a data strcture for storage. If the `BoundedBuffer` has size `0` and exception (`std::logic_error`) will be thrown, because the buffer is `full()`.
* `pop` – throws an exception (`std::logic_error`)throws an exception (`std::logic_error`)
* `swap` – Nothing happens for empty buffer

* ***Test-Suite:*** `bounded_buffer_default_behavior_suite`


## Contents of a `BoundedBuffer`

Since you now have the buffer's interface implemented, you can start implementing the required logic. You have two possible approaches to implement an array-based circular buffer. You should already be familiar with that from the *Algorithmen & Datanstrukturen* lecture. Nevertheless, we will summarize the possibilities here:
* Either you work with some kind of pointers, in this case the array indices, to mark the start and end positions. The start position points to the first element and the end position points beyond the last element. In case start and end positions point to the same location the buffer is empty. This effectively reduces the number of possible elements in the buffer by one, because a full buffer would have the same state regarding start and end pointer. This would leave the two states indistinguishable only by the indicies. Therefore, additional information would be required like a flag indication whether the buffer is empty or the fundamental array would need to have larger capacity, (`+1`) than the buffers capacity. 
* Alternatively, you only store the index of the first element, similar to the start position above. But instead of also storing the end position, you just store the number of elements currently in the buffer. This allows using an array of the actual buffer capacity.

The latter approach is simpler to implement and easier to read. If you decide to implement the first approach you need to adapt the test checking the `BoundedBuffer::container` type.

Beside the general approach the behvior of the `BoundedBuffer` should be self-explanatory:
* As long as the buffer is not full you can push new elements into the buffer, otherwise an exception will be thrown
* As long as the buffer is not empty you can remove elements from the buffer, otherwise an exception will be thrown
* The basic principle of the `BoundedBuffer` is a *FIFO* queue. The element that is inserted first (`push()`) is removed first (`pop()`). The element first inserted can be accessed with `front()`. `back()` access the last inserted element.
* It is possible to exchange the content of two `BoundedBuffer`s using `swap(BoundedBuffer)`
* Prefer using the `array::at()` member function to recognize accidental out of bounds element access.

* Test suite: `bounded_buffer_content_suite`

Furthermore, there is an additional test suite that ensures the correct use of move and copy operations on the elements. This suite works with an mocked element type that tracks its memory operations and asserts the correct use counts afterwards. Be cautious to apply the correct move and copy operations!

* TestSuite: `bounded_buffer_semantic_suite`


## Constructors

So far the implicitly available constructors have been sufficient. Now explicitly implement them yourself. You need to make sure they use the suitable move or copy operations on the elements. The behavior and the tests of your `BoundedBuffer` will not change if you do it correctly. Implement the following special member functions:
* Default constructor
* Copy constructor
* Move constructor
* Copy assignment operator
* Move assignment operator

***Note:*** Currently, this task seems rather pointless. Later we will modify the `BoundedBuffer` to facilitate heap memory, this will require the implementation of our own constructors and assignment operators. It will be easier if you already have the correct structure as a starting point then.




## extra: DynArray with std::vector member

If you want to exercise implementing forwarding functions (`push_back()`) overloads and constructor templates, change the implementation of your DynArray from [exercise01](../exercise01) to use a data member for the std::vector and implement all member function overloads that previously were introduced through using declarations yourself.

Note: do you still need the explicit deduction guides?