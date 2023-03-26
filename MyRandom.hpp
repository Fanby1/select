#include <random>
#include <iostream>

class MyRandom
{
private:
    int begin,end;
public:
    MyRandom(int,int);
    ~MyRandom();
    int getWord();
};


