/*============================================================================
 Name        : Example2.cpp
 Author      : DRS
 Version
 Copyright   : Free to the World
 Description : Demonstrate how to declare destructors virtual in
               polymorphic base classes.

               Context: Example is from Effective C++, Scott Meyers
                        Item 7:  Declare destructors virtual in polymorphic
                        base classes.

                        Note, this example shows the pitfall of inheriting from
                        classes that do not have virtual destructors.
============================================================================*/
#include <iostream>

class SpecialString: public std::string {
public:
  SpecialString(const char *inputValue) {
    std::cout << "SpecialString constructor called..." << std::endl;
  }

  ~SpecialString() {
    std::cout << "SpecialString deconstructor called..." << std::endl;
  }
};

int main() {
  std::cout << "Starting Item 7 Example2...don't extend string" << std::endl << std::endl;

  std::cout << "First test: create SpecialString but delete base reference..." << std::endl;
  SpecialString *newString1 = new SpecialString("Problem Coming");
  std::string *baseString1;
  baseString1 = newString1;
  delete baseString1;
  std::cout << "Deleted the base class reference; the derived destructor is not called, leak and undefined behavior!" << std::endl << std::endl;

  std::cout << "Second test: create SpecialString and delete it..." << std::endl;
  SpecialString *newString2 = new SpecialString("No problem here.");
  std::string *baseString2;
  baseString2 = newString2;
  delete newString2;
  std::cout << "Deleted SpecialString reference; the derived destructor is called!" << std::endl << std::endl;

  std::cout << "Item 7 Example2 Ending...don;t extend string" << std::endl;

  return 0;
}
