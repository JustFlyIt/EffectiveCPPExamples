/*============================================================================
Name        : Example2.cpp    
Author      : DRS
Version
Copyright   : Free to the World
Description : Demonstrate why excetions should not leave destructors.

              Context: Example is from Effective C++, Scott Meyers
                       Item 8:  Prevent exceptions from leaving destructors.

              IMPORTANT:  Controlled termination.  SEE THE COMMENTS AT THE END
                          OF THE PROGRAM.  This approach has problems of its own
                          but its advantage is that it can be easily determined
                          where the exception and resultant abort occurred.  Then
                          quick analysis allows for what has and hasn't be released,
                          finished, resolved, etc.

                       Note, this example requires lines to be commented and
                       uncommented to prove the point.  Also, the use  of
                       the -c compiler options helps to designate between
                       compiler and linker errors.
============================================================================*/
#include <stdlib.h>
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
      try {
        db->close();
      } catch (int e) {
        std::cout << "Exception thrown by db->close() - aborting operation." << std::endl;
        abort();
      }

      // CODE AFTER THE ABOVE TRY CATCH BLOCK IS NEVER REACHED BECAUSE THE
      // DB CONNECTION THREW AN EXCEPTION AND EXECUTION IS ABORTED; THIS
      // IS TO PREVENT UNDEFINED BEHAVIOR...IT IS KNOWN EXACTLY WHERE THE ABORT
      // OCCURRED ALONG WITH WHAT HAS AND HAS NOT BEEN RELEASE/FINISHED.

      std::cout << "~DBConnUser destructor ending." << std::endl;
    }

  private:
    DBConnection* db;
};

int main() {
  std::cout << "Starting Item 8 Example 2 - Controlled termination..." << std::endl << std::endl;

  std::cout << std::endl << "Creating dbConnUser..." << std::endl;
  DBConnUser* dbConnUser = new DBConnUser();

  std::cout << std::endl << "Deleting dbConnUser..." << std::endl;
  delete dbConnUser;

  // CODE AFTER THE ABOVE DELETE IS NEVER REACHED BECAUSE THE
  // DB CONNECTION THREW AN EXCEPTION AND EXECUTION IS ABORTED; THIS
  // IS TO PREVENT UNDEFINED BEHAVIOR...IT IS KNOWN EXACTLY WHERE THE ABORT
  // OCCURRED ALONG WITH WHAT HAS AND HAS NOT BEEN RELEASE/FINISHED.
  std::cout << std::endl << "Item 8 Example 2 Ending..." << std::endl;

  return 0;
}
