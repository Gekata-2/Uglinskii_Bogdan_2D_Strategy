#include <iostream>
#include <vector>
#include "TBattleground.h"
#include "TArcher.h"
#include "TSwordsman.h"



int main()
{
    TBattleground bg;

    std::vector<TSwordsman> sw_vec;
    std::vector<TArcher> ar_vec;

    TSwordsman SwA;
    TSwordsman SwB;

    TArcher ArA;

    bg.AddUnit(&ArA,4,4);
    bg.Print();
    bg.Move(&ArA, 5, 5);
    bg.Print();
    bg.Move(&ArA, 6, 6);
    bg.Print();
    bg.Move(&ArA, 7, 7);
    bg.Print();
    bg.Move(&ArA, 0, 7);
    bg.Print();
    bg.Move(&ArA, 4, 6);
    bg.Print();



    /*sw_vec.push_back(SwA);
    sw_vec.push_back(SwB);

    ar_vec.push_back(ArA);*/

   
    /*sw_vec[0].PrintInfo();
    bg.AddUnit(&sw_vec[0],5,5);
    bg.AddUnit(&sw_vec[1], 4, 4);
    bg.AddUnit(&ar_vec[0], 2, 2);
    bg.Attack(&sw_vec[0],&sw_vec[1]);*/
    /*for (size_t i = 0; i < sw_vec.size(); i++)
    {
        sw_vec[i].PrintInfo();
    }*/
   // bg.Print();
    std::cout << "Hello World!\n";
}
