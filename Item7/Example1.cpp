/*============================================================================
 Name        : Example.cpp
 Author      : DRS
 Version
 Copyright   : Free to the World
 Description : Demonstrate how to declare destructors virtual in
               polymorphic base classes.

               Context: Example is from Effective C++, Scott Meyers
                        Item 7:  Declare destructors virtual in polymorphic
                        base classes.

               IMPORTANT:  Understand the difference between a class that is
                           intended to be used polymorphically vs. a class
                           that is to be used just as a base class.

                        Note, this example requires lines to be commented and
                        uncommented to prove the point.  Also, the use  of
                        the -c compiler options helps to designate between
                        compiler and linker errors.
============================================================================*/
#include <iostream>

/*
    In this example, see how a derived class without a polymorphic virtual
    destructor can cause "undefined" behavior and how adding a virtual
    destructor resolves the problem.
*/

class TimeKeeper {
public:
  TimeKeeper() {
    std::cout << "TimeKeeper constructor called." << std::endl;
  }

  // If this is used, the derived class's destructor will never be called.
  //~TimeKeeper() {
  //    std::cout << "TimeKeeper deconstructor called." << std::endl;
  //}

  // If this is used, both the base class and the derived class destructors
  // will be called.
  virtual ~TimeKeeper();     // Must have implementation below uncommented.

  int getTime() {
    return time;
  }

  void setTime(int timeValue) {
    time = timeValue;
  }

private:
  int time;

};

TimeKeeper::~TimeKeeper() {
  std::cout << "Virtual TimeKeeper deconstructor called." << std::endl;
}

class AtomicClock: public TimeKeeper {
public:
  AtomicClock() {
    std::cout << "AtomicClock constructor called." << std::endl;

    setTime(5);
  }

  ~AtomicClock() {
    std::cout << "AtomicClock deconstructor called." << std::endl;
  }
};

class WaterClock: public TimeKeeper { };
class WristWatch: public TimeKeeper { };

TimeKeeper* getTimeKeeper(int timeKeeperType) {
  TimeKeeper* newTimeKeeper = 0;

  switch (timeKeeperType) {
    case 1:
      newTimeKeeper = new AtomicClock();
      break;
    case 2:
      newTimeKeeper = new WaterClock();
      break;
    case 3:
      newTimeKeeper = new WristWatch();
  }

  return newTimeKeeper;
}

int main() {
  std::cout << "Starting Item 7 Example..." << std::endl << std::endl;

  /*
      In this example a new TimeKeeper is created, used and deleted.
      The output shows that the derived class and base class constructors have
      been called.  If the base class's destructor is NON-VIRTUAL, when the
      class is deleted, only the base classes destructor has been called.
      The derived part of the class is never deleted.  This is leads to a memory
      leak since only half of the total class has been deleted;
      overall results are undefined!

      If the base class's destructor is VIRTUAL, both the base and the derive
      class destructors will be called.
  */

  TimeKeeper* currentTimeKeeper = getTimeKeeper(1);

  std::cout << std::endl << "Time from new TimeKeeper: " << currentTimeKeeper->getTime() << std::endl;

  std::cout << std::endl << "Deleting TimeKeeper..." << std::endl;

  delete currentTimeKeeper;

  std::cout << std::endl << "Item 7 Example Ending..." << std::endl;

  return 0;
}
