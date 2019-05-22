# Item 8:  Prevent exceptions from leaving destructors

Examples are from pages 44-48 of Scott Meyers book, "Effective C++, Third Edition".

Example1 -  The core problem case...exceptions in destructors can lead to
            uncontrolled shut downs or undefined behaviors

Example2 -  Solution 1 - Controlled termination

Example3 -  Solution 2 - Swallow the exceptions

Compile examples with:  

  g++ Example1 (or 2, 3).cpp     // Compile and linker

  g++ -c Example1 (or 2, 3).cpp  // Compile only

KEY POINTS:
*   destructors should never emit exceptions.  If functions called in a
    destructor may throw, the destructor should catch any exceptions,
    then swallow them or terminate the program.
*   If class clients need to be able to react to exceptions thrown during an
    operation, the class should provide a regular (i.e., non-destructor)
    function that performs the operation.  This does not violate Item 18's
    direction to make interfaces easy to use correctly - KEY POINT:  if an
    exception needs to be thrown, it has to come from a non-destructor function.
