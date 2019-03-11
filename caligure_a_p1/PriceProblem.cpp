#include "PriceProblem.h"

void PriceProblem::setProblemSize(int pS){ problemSize = pS; }

int PriceProblem::getProblemSize(){ return problemSize; }

void PriceProblem::setBudget(int b){ budget = b; }

int PriceProblem::getBudget(){ return budget; }

void PriceProblem::setProblemPriceList(string name, int grannysPrice){

  problemPriceList[name] = grannysPrice;

}

map<string, int> PriceProblem::getProblemPriceList(){ return problemPriceList; }

int PriceProblem::getProblemMaxProfit(){ return problemMaxProfit; }

void PriceProblem::computeMaxProfit(map<string, int> marketPriceList){

  //Start clock for algorithm timing
  clock_t start;
  clock_t end;
  start = clock();

  vector<string> masterSet;

  int totalSumOfWeights = 0;

  //Calculate total cost of all of granny's cards and add to masterSet vector
  map<string, int>::iterator it;
  for ( it = problemPriceList.begin(); it != problemPriceList.end(); it++ ){
      totalSumOfWeights += it->second;
      masterSet.push_back(it->first);
  }

  //Can purchase every card with alloted budget
  if(totalSumOfWeights <= budget){

    //Loop through avaiable cards and compute profit
    for (it = problemPriceList.begin(); it != problemPriceList.end(); it++){

      string cardName = it->first;

      problemMaxProfit += marketPriceList[cardName] - problemPriceList[cardName];

      //Add name to vector for output file
      purchasedCards.push_back(it->first);

    }

  //Actual brute force to determine max profit
  }else{

    //return a vector containing all possible subsets of the master set
    vector<vector<string>> allSubsets;
    allSubsets = generateSubset(masterSet, masterSet.size());

    //Calculate max profit per subset
    for(int i = 0; i < allSubsets.size(); i++){

      int subsetMaxProfit = 0;
      int totalSumOfWeights = 0;

      vector<string> subjectedSet = allSubsets[i];

      //Grab total cost of all cards in subset
      for(int j = 0; j < subjectedSet.size(); j++){

        totalSumOfWeights += problemPriceList[subjectedSet[j]];

      }

      //Can purchase all cards with alloted budget
      if(totalSumOfWeights <= budget){

        for(int j = 0; j < subjectedSet.size(); j++){

          //Calculate profit of all cards
          subsetMaxProfit += marketPriceList[subjectedSet[j]] - problemPriceList[subjectedSet[j]];

        }

        //This subset's profit is larger than previous max
        if(subsetMaxProfit > problemMaxProfit){

          //Update the max prfoit
          problemMaxProfit = subsetMaxProfit;

          //Update vector for output file containing card names
          purchasedCards = subjectedSet;

        }

      //Cant afford all cards, continue to next subset
      }else{ continue; }

    }

  }

  //End clock and compute elapsed time
  end = clock();
  float funcTime = ((float)end - (float)start);
  float seconds = funcTime / CLOCKS_PER_SEC;

  //Write data to output file
  writeToOutput(seconds);

}

vector<vector<string>> PriceProblem::generateSubset(vector<string> set, int size){

  //Vector containing vectors of all subsets
  vector<vector<string>> allSubsets;

  //Max number of subsets from a given set
  int numOfSubsets = (int)pow(2, size);

  //Loop for all possible number of subsets
  for(int i = 0; i < numOfSubsets; i++){

    vector<string> subset;

    //Loop through size of master set
    for(int j = 0; j < size; j++){

      //If jth bit in i is set, add the jth element of master set to the subset
      int bitSetCondition = (i & (1 << j));

      if(bitSetCondition != 0){

        subset.push_back(set[j]);

      }

      //Push subset onto allSubset vector if not already added
      if(find(allSubsets.begin(), allSubsets.end(), subset) == allSubsets.end()){ allSubsets.push_back(subset); }

    }

  }

  return allSubsets;

}

void PriceProblem::writeToOutput(float seconds){

  ofstream outputFile;
  outputFile.open("output.txt", fstream::app);

  outputFile << problemSize << " " << problemMaxProfit << " " << purchasedCards.size() << " " << seconds << endl;

  for(int i = 0; i < purchasedCards.size(); i++){

    outputFile << purchasedCards[i] << endl;

  }

  outputFile << "\n";

  outputFile.close();

}
