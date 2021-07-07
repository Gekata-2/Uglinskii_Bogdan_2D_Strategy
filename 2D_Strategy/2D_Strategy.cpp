#include <iostream>
#include <vector>
#include "TBattleground.h"



int main()
{
   

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
