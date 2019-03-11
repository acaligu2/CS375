#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

typedef struct{

  int weight;
  int profit;
  int index;

}ratioStruct;

class PriceProblem{

  private:

    int ratioIndex = 0;
    string outputFileName = "";
    int functionType = -1;                //Value determining which algorithm
    int problemSize = 0;                  //Number of cards in problem
    int budget = 0;                       //Budget alloted for the problem
    int maxProfit = 0;                    //Largest profit generated
    int elementCounter = 0;

    vector<ratioStruct> ratios;
    vector<int> weights;
    vector<int> profits;

  public:

    void setOutFile(string o);

    void setFunctionType(int funcType);
    int getFunctionType();

    void setProblemSize(int pS);
    int getProblemSize();

    void setBudget(int b);
    int getBudget();

    void addToMap(int w, int p);
    vector<int> getW();
    vector<int> getP();

    static bool ratioSort(ratioStruct i, ratioStruct j);
    void greedy1();
    void greedy2();

    bool promising(int i, int p, int w);
    int fracKnap(int i, int weight, int profit);
    void backTracking(int index, int weightI, int profitI);

    void dynamicProgramming();

    void writeToOutput(float seconds, int opt);

};
