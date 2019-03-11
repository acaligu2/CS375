#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

class PriceProblem{

  private:

    int problemSize = 0;                  //Number of cards in problem
    int budget = 0;                       //Budget alloted for the problem
    int problemMaxProfit = 0;             //Max profit of the problem
    vector<string> purchasedCards;        //Vector containing all cards pruchased for max subsetMaxProfit
    map<string, int> problemPriceList;    //Map containing card names and granny's prices

  public:

    vector<vector<string>> generateSubset(vector<string> set, int size);

    void setProblemSize(int pS);
    int getProblemSize();

    void setBudget(int b);
    int getBudget();

    void setProblemPriceList(string name, int grannysPrice);
    map<string, int> getProblemPriceList();

    int getProblemMaxProfit();

    void computeMaxProfit(map<string, int> marketPriceList);

    void writeToOutput(float seconds);

};
