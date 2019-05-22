/*============================================================================
Name        : Example3cpp   IN PROGRESS
Author      : DRS
Version
Copyright   : Free to the World
Description : Demonstrate why excetions should not leave destructors.

              Context: Example is from Effective C++, Scott Meyers
                       Item 8:  Prevent exceptions from leaving destructors.

              IMPORTANT:  Swallow the exceptions.  SEE THE COMMENTS AT THE END
                          OF THE PROGRAM.

                       Note, this example requires lines to be commented and
                       uncommented to prove the point.  Also, the use  of
                       the -c compiler options helps to designate between
                       compiler and linker errors.
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
