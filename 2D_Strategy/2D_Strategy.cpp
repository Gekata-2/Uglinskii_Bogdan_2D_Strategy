#include <iostream>
#include <vector>
#include "TBattleground.h"
#include "TArcher.h"
#include "TSwordsman.h"
#include "TConsoleView.h"


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
    bg.AddUnit(&SwA, 4, 3);
    bg.AddUnit(&SwB, 5, 7);
    bg.Print();

    bg.Attack(&SwA, &ArA);
    bg.Attack(&SwB, &ArA);
    bg.Attack(&ArA, &SwA);
    bg.Attack(&SwB, &ArA);
    bg.Attack(&SwB, &ArA);

    SwA.PrintInfo();
    SwB.PrintInfo();
    ArA.PrintInfo();
    bg.Print();
    /*TConsoleView view;
    view.Display();*/

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
