#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include "PriceProblem.h"

using namespace std;

int capacity;

vector<PriceProblem*> problems;

//Parses the priceList.txt and creates an object for each "problem"
void parsePriceList(string priceListFileName, int functionOption, string outputFile){

  string lineNums;
  int problemSize = -1;
  string budget;
  int budgetNum = -1;

  ifstream newFile(priceListFileName);

  while(true){

    string line, probSize, budget;
    getline(newFile, line);

    if(line == ""){ break; }

    //New instance of a problem class
    PriceProblem *p = new PriceProblem();
    p->setFunctionType(functionOption);
    p->setOutFile(outputFile);

    //Get problem size and budget from first line of problem
    istringstream ss(line);
    getline(ss, probSize, ' ');
    getline(ss, budget, ' ');

    int numOfIterations = stoi(probSize);
    int problemBudget = stoi(budget);
    capacity = problemBudget;

    p->setProblemSize(numOfIterations);
    p->setBudget(problemBudget);

    //Loop for number of weight/profit pairs in the problem and grab info
    int counter = 0;
    while(counter < numOfIterations){

      string line, weight, profit;
      getline(newFile, line);

      istringstream ss(line);

      getline(ss, weight, ' ');
      getline(ss, profit, ' ');

      int newWeight = stoi(weight);
      int newProfit = stoi(profit);

      p->addToMap(newWeight, newProfit);

      counter++;

    }

    problems.push_back(p);

  }

  newFile.close();

}


int main(int argc, char const *argv[]) {

  if(argc != 4){
    cout << "./program3 <inputFile> <outputFile> <0 or 1 or 2>" << endl;
    exit(1);
  }

  string inputFile = argv[1];
  string outputFile = argv[2];
  int functionOption = atoi(argv[3]);

  //Start output.txt from a clean slate;
  ofstream initializeOutput;
  initializeOutput.open(outputFile);
  initializeOutput << "";
  initializeOutput.close();

  if(functionOption != 0 && functionOption != 1 && functionOption != 2){
    cout << "Invalid function request: select 0/1/2" << endl;
    exit(1);
  }

  //Initilaize problem objects
  parsePriceList(inputFile, functionOption, outputFile);

  //Calculate maxProfit for each problem
  for(int i = 0; i < problems.size(); i++){

    int opt = problems[i]->getFunctionType();

    //Start clock for algorithm timing
    clock_t start;
    clock_t end;
    float seconds;

    //Greedy1 Algorithm
    if(opt == 0){

      start = clock();
      problems[i]->greedy1();
      end = clock();
      float funcTime = ((float)end - (float)start);
      seconds = (funcTime / CLOCKS_PER_SEC)*1000;

    //Greedy2 Algorithm
    }else if(opt == 1){

      start = clock();
      problems[i]->greedy2();
      end = clock();
      float funcTime = ((float)end - (float)start);
      seconds = (funcTime / CLOCKS_PER_SEC) * 1000;

    //Backtracking Algorithm
    }else if(opt == 2){

      start = clock();

      //Initialize maxProfit to greedy2()
      problems[i]->greedy2();
      problems[i]->backTracking(0, 0, 0);
      end = clock();
      float funcTime = ((float)end - (float)start);
      seconds = (funcTime / CLOCKS_PER_SEC) * 1000;

    }else{ exit(1); }

    //Format output
    problems[i]->writeToOutput(seconds);

  }

  return 0;

}
