/*============================================================================
 Name        : Example1.cpp
 Author      : DRS
 Version
 Copyright   : Free to the World
 Description : Demonstrate why virtual functions should not be calculated
               from constructors.

               Context: Example is from Effective C++, Scott Meyers
                        Item 9:  Prevent exceptions from leaving destructors.

               IMPORTANT:  Understand that destructor thrown exceptions can
                           lead to simultaneously active exceptions causing
                           the program to terminate prematurely or creating
                           undefined behavior.  SEE THE COMMENTS AT THE END
                           OF THE PROGRAM.

                        Note, this example requires lines to be commented and
                        uncommented to prove the point.  Also, the use  of
                        the -c compiler options helps to designate between
                        compiler and linker errors.
============================================================================*/
#include <iostream>

class Transaction {
public:
    Transaction();

    virtual void logTransaction();
};

Transaction::Transaction() {
  std::cout << "Transaction::Transaction() called..." << std::endl << std::endl;

  logTransaction();
}

void Transaction::logTransaction() {
  std::cout << "Transaction::logTransaction() called..." << std::endl << std::endl;
}

class BuyTransaction: public Transaction {
public:
  BuyTransaction();

  virtual void logTransaction();
};

BuyTransaction::BuyTransaction() {
  std::cout << "BuyTransaction::BuyTransaction() called..." << std::endl << std::endl;

  logTransaction();
}

void BuyTransaction::logTransaction() {
  std::cout << "BuyTransaction::logTransaction() called..." << std::endl << std::endl;
}

class SellTransaction: public Transaction {
public:
  SellTransaction();

  virtual void logTransaction();
};

SellTransaction::SellTransaction() {
  std::cout << "SellTransaction::SellTransaction() called..." << std::endl << std::endl;

  logTransaction();
}

void SellTransaction::logTransaction() {
  std::cout << "SellTransaction::logTransaction called..." << std::endl << std::endl;
}

int main() {
  std::cout << "Starting Item 9 Example 1 - the problem..." << std::endl << std::endl;

  std::cout << "Creating BuyTransaction..." << std::endl;
  BuyTransaction* buyTransaction = new BuyTransaction();

  std::cout << std::endl << "Deleting BuyTransaction..." << std::endl;
  delete buyTransaction;

  std::cout << std::endl << "Item 9 Example Ending..." << std::endl;

  return 0;
}
