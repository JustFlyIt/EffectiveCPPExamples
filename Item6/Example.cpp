/*============================================================================
 Name        : Example.cpp
 Author      : DRS
 Version
 Copyright   : Free to the World
 Description : Demonstrate how to explicitly disallow the use of undesired
               compiler generated functions.

               Context: Example is from Effective C++, Scott Meyers
                        Item 6:  Explicity disallow the use of compiler-
                        generated functions you do not want.

                        Note, this example requires lines to be commented and
                        uncommented to prove the point.  Also, the use  of
                        the -c compiler options helps to designate between
                        compiler and linker errors.
============================================================================*/

/*
    In this example it is desired not to be able to copy an instance of the
    HomeForSale class (supposedly homes would be too unique).  This can usually
    be done by not providing a copy constructor.  But as Item 5 points out, the
    compiler will provide them if they are explicitly called.  So...how to prevent
    this?

    Explicity declare the copy constructor and operator to be private.  This
    prevents the compiler from generating implicit versions of its own.  This
    approach is accepted and used in C++ standard library implementations.
*/
class HomeForSale {
public:
  int price;

  HomeForSale() { };

  friend void copyHomeSale(HomeForSale hx);

private:
  HomeForSale(const HomeForSale&);              //Only need the declaration to fool the
  HomeForSale& operator=(const HomeForSale&);   //compiler.  No implementations are needed.
};

// Example of friend function trying to copy HomeForSale class instance.
// Generates a linker error
void copyHomeSale(HomeForSale hx) {
  //HomeForSale hy(hx);         // Linker error;
}

/*
    In this example the use of the Uncopyable class will move the error generated
    by the a member or friend function trying to use copy the class from the
    linker level to the compiler...a preferred goal.

    Explicity declare the copy constructor and operator to be private.  This
    prevents the compiler from generating implicit versions of its own.  This
    approach is accepted and used in C++ standard library implementations.
*/

class Uncopyable {
protected:
  Uncopyable() {}
  ~Uncopyable() {}

private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

class HomeForSaleB: private Uncopyable {   //NOTE:  INHERITANCE DOES NOT
public:                                   //       NEED TO BE PUBLIC.
  int price;

  HomeForSaleB() { };

  friend void copyHomeBSale(HomeForSaleB hx);
};

// Example of friend function trying to copy HomeForSale class instance.
// Generates a linker error
void copyHomeBSale(HomeForSaleB hx) {
  HomeForSaleB hy(hx);         // No longer a linker error, now a compiler error.
                               // The compiler cannot access the private
                               // copy constructor or = operator
}

int main() {
  HomeForSale h1;
  HomeForSale h2;

  //HomeForSale h3(h1);       // Compiler error; constructor is private
  //h1=h2;                    // Compiler error; operator is private

  return 0;
}
