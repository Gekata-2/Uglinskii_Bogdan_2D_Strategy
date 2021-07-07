#include <iostream>
#include <vector>
#include "TBattleground.h"
using namespace std;
class Parent
{
public:
    virtual void foo()
    {
        cout << "parent is called";
    }
};

class archer : public Parent
{
public:
    virtual void foo()
    {
        cout << "archer is called";
    }
};
class sword : public Parent
{
public:
    int a = 11;
    virtual void foo()
    {
        cout << "sword is called";
    }
    void set_a(int tmp)
    {
        a = tmp;
    }
};

class map
{
    Parent* arr[10];
   
    
public:
    void asd(sword* sw)
    {
        sw->set_a(100);
        std::cout << sw->a<<std::endl;
    }
    
};

int main()
{
    map mp;
    sword s;
    std::cout << s.a << std::endl;
    mp.asd(&s);
    std::cout << s.a << std::endl;

    TBattleground bg;
    std::vector<TSwordsman> sw_vec;
    TSwordsman A(1, 1);
    TSwordsman B(1, 2);
    sw_vec.push_back(A);
    sw_vec.push_back(B);
    bg.AddUnit(&sw_vec[0],3,3);
    bg.AddUnit(&sw_vec[1], 4, 4);
    bg.Attack(&sw_vec[0],&sw_vec[1]);
    for (size_t i = 0; i < sw_vec.size(); i++)
    {
        sw_vec[i].PrintInfo();
    }
    bg.Print();
    std::cout << "Hello World!\n";
}
