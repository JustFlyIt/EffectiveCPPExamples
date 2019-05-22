/*============================================================================
 Name        : Example1.cpp
 Author      : DRS
 Version
 Copyright   : Free to the World
 Description : Demonstrate why excetions should not leave destructors.

               Context: Example is from Effective C++, Scott Meyers
                        Item 8:  Prevent exceptions from leaving destructors.

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

class DBConnection {
  public:
    DBConnection() {
      std::cout << "DBConnection constructor called." << std::endl;
      std::cout << "DBConnection constructor ending." << std::endl;
    }

    static DBConnection* getConnection() {
        return new DBConnection();
    }

    void open() {
      std::cout << "DBConnection open() called." << std::endl;
    }

    void close() {
      std::cout << "DBConnection close() called." << std::endl;
      // THROW AND EXCEPTION HERE TO DEMONSTRATE THE ISSUE
      std::cout << "DBConnection close() throwing exception 20." << std::endl;
      throw 20;
      std::cout << "DBConnection close() threw exception 20." << std::endl;
    }

    ~DBConnection() {
      std::cout << "DBConnection deconstructor called." << std::endl;
      std::cout << "DBConnection deconstructor ending." << std::endl;
    }
};

class DBConnUser {
  public:
    DBConnUser() {
      std::cout << "DBConnUser constructor called." << std::endl;
      db = DBConnection::getConnection();
      db->open();
      std::cout << "DBConnUser constructor ending." << std::endl;
    }

    ~DBConnUser() {
      std::cout << "~DBConnUser destructor called." << std::endl;
      db->close();

      // CODED AFTER THE ABOVE CLOSED IS NEVER REACHED BECAUSE THE
      // DB CONNECTION THREW AN EXCEPTION.  ANY RESOURCES THAT
      // STILL NEED TO BE RETURNED ARE NOW LOST.  AND THIS IS JUST WITH
      // ONE EXCEPTION.

      std::cout << "~DBConnUser destructor ending." << std::endl;
    }

  private:
    DBConnection* db;
};

int main() {
  std::cout << "Starting Item 8 Example 1 - the problem..." << std::endl << std::endl;

  std::cout << std::endl << "Creating dbConnUser..." << std::endl;
  DBConnUser* dbConnUser = new DBConnUser();

  std::cout << std::endl << "Deleting dbConnUser..." << std::endl;
  delete dbConnUser;

  // CODED AFTER THE ABOVE DELETE IS NEVER REACHED BECAUSE THE
  // DB CONNECTION THREW AN EXCEPTION.  ANY RESOURCES THAT
  // STILL NEED TO BE RETURNED ARE NOW LOST.  AND THIS IS JUST WITH
  // ONE EXCEPTION.

  std::cout << std::endl << "Item 8 Example Ending..." << std::endl;

  return 0;
}
