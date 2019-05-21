# Item 7:  Explicitly disallow the use of compiler-generated functions you do not want.

Examples are from pages 37-40 of Scott Meyers book, "Effective C++, Third Edition".

Example1 -  non-virtual and virtual destructors

Example2 -  Be cautious when inheriting from classes without virtual destructors.
            This includes all STL container types such as vector, list, set etc.

Compile examples with:  

  g++ Example1 (or 2).cpp     // Compile and linker

  g++ -c Example1 (or 2).cpp  // Compile only

KEY POINTS:
*   Note...polymorphic base classes are intended to be used polymorphically:  
    allows for the manipulation of derived class objects via base class interfaces.
    This is different from a class being used a base class.
*   A class without virtual methods is generally considered a class not to be
    used polymorphically.
*   C++ does not offer a feature such as Java's final that prevents a class
    from being inherited/extended.
*   A polymorphic base classes should declare a virtual destructor.  If a class has
    any virtual functions, it should have a virtual destructor.  
*   If a class is not intended to be used polymorphically, it can be extended but
    does not need a virtual destructor.  Example of this is the text's Uncopyable
    class.
