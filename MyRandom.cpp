#include "MyRandom.hpp"

MyRandom::MyRandom(int begin, int end)
{
    this->begin = begin;
    this->end = end;
}

MyRandom::~MyRandom()
{
}

int MyRandom::getWord(){
    std::random_device rd;  //如果可用的话，从一个随机数发生器上获得一个真正的随机数
    std::mt19937 gen(rd()); //gen是一个使用rd()作种子初始化的标准梅森旋转算法的随机数发生器
    std::uniform_int_distribution<> distrib(begin, end);
    return distrib(gen);
}