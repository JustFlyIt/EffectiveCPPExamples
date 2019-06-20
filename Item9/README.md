Item 9: Never call virtual functions during construction or destruction.

Examples are from pages 48-52 of Scott Meyers book, "Effective C++, Third Edition".

Example1 

IN PROGRESS

Compile examples with:

g++ Example1 (or 2).cpp // Compile and linker

KEY POINTS:

    Don't call virtual functions during construction or destruction; such calls will never go to a more derived class than that or the currently executing constructor or destructor.
