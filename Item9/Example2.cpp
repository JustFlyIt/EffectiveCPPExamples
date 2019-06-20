
// CPP program to illustrate
// calling virtual methods in
// constructor/destructor
#include<iostream>
using namespace std;

class dog
{
public:
    dog()
    {
        cout<< "dog Constructor called" <<endl;
        bark() ;
    }

    ~dog()
    {
        bark();
    }

    virtual void bark()
    {
        cout<< "Virtual method dog::bark called" <<endl;
    }

    void seeCat()
    {
        bark();
    }
};

class Yellowdog : public dog
{
public:
        Yellowdog()
        {
            cout<< "Derived class Yellowdog Constructor called" <<endl;
        }
        void bark()
        {
            cout<< "Derived class Yellowdog::bark Virtual method called" <<endl;
        }
};

int main()
{
    Yellowdog d;
    d.seeCat();
}
