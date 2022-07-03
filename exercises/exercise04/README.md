# Exercise 4

I suppose we need to continue with the BoundedBuffer implementation.

Some additional questions and exercises:

## Check BoundedBuffer concepts/SFINAE

* for the BoundedBuffer that is not using Raw memory, can you restrict its template parameter, so that one wouldn't use it with types that cannot be default constructed?
* can you unify the BoundedBuffer templates, so that the complicated implementation for raw memory is only used for types where it is necessary?
* Implement tests (static_assert and/or with CUTE) that check if the correct implementation strategy is used?