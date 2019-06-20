/*============================================================================
 Name        : Example3.cpp
 Author      : DRS
 Version
 Copyright   : Free to the World
 Description : Demonstrate use of virtual functions.

               Context: Example is from:
                        https://www.geeksforgeeks.org/virtual-function-cpp/

               Key Points:
               * Runtime polymorphism is achieved only through a pointer
               or reference to the base class type. Also, a base class pointer
               can point to the objects of base class as well as to the objects
               of derived class. In code below, base class pointer ‘bptr’
               contains the address of object ‘d’ of derived class.

               * Late binding(Runtime) is done in accordance with the content of
               pointer (i.e. location pointed to by pointer) and Early
               binding(Compile time) is done according to the type of pointer.
               Since the print() function is declared with virtual keyword so it
               will be bound at run-time (output is print derived class as
               pointer is pointing to object of derived class ) and show()
               is non-virtual so it will be bound during compile time(output is
               show base class as pointer is of base type ).

               * For a virtual function in the base class that is being
               overridden in the derived class, then the virtual keyword is not
               needed in the derived class; functions are automatically
               considered as virtual functions in the derived class.
============================================================================*/

#include<iostream>
using namespace std;

class base
{
public:
    virtual void print ()
    { cout<< "print base class" <<endl; }

    void show ()
    { cout<< "show base class" <<endl; }
};

class derived:public base
{
public:
    void print ()
    { cout<< "print derived class" <<endl; }

    void show ()
    { cout<< "show derived class" <<endl; }
};

int main()
{
    base *bptr;
    derived d;
    bptr = &d;

    //virtual function, binded at runtime
    bptr->print();

    // Non-virtual function, binded at compile time
    bptr->show();
}
