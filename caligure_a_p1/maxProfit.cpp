#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <unistd.h>
#include "PriceProblem.h"

using namespace std;

int numOfMarketPrices = 0;
int totalNumOfCards = 0;
map<string, int> marketPrices;
vector<PriceProblem*> problems;

//Ensure Granny's cards have market value
bool checkIfValidName(string name){

  if(marketPrices.find(name) == marketPrices.end()){

    return false;

  }else{ return true; }

}

//Parses the priceList.txt and creates an object for each "problem"
void parsePriceList(string priceListFileName){

  string lineNums;
  int problemSize = -1;
  string budget;
  int budgetNum = -1;

  ifstream newFile(priceListFileName);

  while(true){

    string line, probSize, budget;
    getline(newFile, line);

    //Accounts for EOF
    if(line == ""){ break; }

    //New instance of a problem class
    PriceProblem *p = new PriceProblem();

    //Get problem size and budget from first line of problem
    istringstream ss(line);
    getline(ss, probSize, ' ');
    getline(ss, budget, ' ');

    int numOfIterations = stoi(probSize);
    int b = stoi(budget);

    p->setBudget(b);
    p->setProblemSize(numOfIterations);

    //Loop for number of cards in problem and grab info
    int counter = 0;
    while(counter < numOfIterations){

      string line, name, listedPrice;
      getline(newFile, line);

      istringstream ss(line);
      getline(ss, name, ' ');
      getline(ss, listedPrice, ' ');

      bool v = checkIfValidName(name);
      if(!v){

        cout << "Error: Card " << name << " doesn't have a market price. Exiting..." << endl;
        exit(1);

      }

      int grannysPrice = stoi(listedPrice);
      p->setProblemPriceList(name, grannysPrice);

      counter++;

    }

    //Add to vector containing all problem obejcts
    problems.push_back(p);

  }

  newFile.close();

}

//Grab info from marketprice.txt
void parseMarketPrice(string marketPriceFileName){

  int counter = 1;

  string line;
  ifstream newFile(marketPriceFileName);
  if(newFile.is_open()){

    while(getline(newFile, line)){

      //Grab the number of prices from the first line
      if(counter == 1){

        numOfMarketPrices = stoi(line);
        counter++;
        continue;

      }

      //Get card name and value until EOF
      istringstream ss(line);
      string name;
      string val;
      getline(ss, name, ' ');
      getline(ss, val, ' ');

      int cardValue = stoi(val);
      marketPrices[name] = cardValue;

    }

  }

}

int main(int argc, char **argv) {

  //Start output.txt from a clean slate;
  ofstream initializeOutput;
  initializeOutput.open("output.txt");
  initializeOutput << "";
  initializeOutput.close();

  string marketPriceFileName;
  string priceListFileName;

  //Grab filenames from user input
  int opt;
  while((opt = getopt(argc, argv, "m:p:")) != -1){
    switch(opt){

      case 'm':
        marketPriceFileName = optarg;
        break;

      case 'p':
        priceListFileName = optarg;
        break;

      //Unknown flag
      case '?':
  			fprintf(stderr, "./program1 -m <market price file> -p <price list file>\n");
  			exit(1);

      //Flag is missing value
  		case ':':
  			fprintf(stderr, "./program1 -m <market price file> -p <price list file>\n");
  			exit(1);

    }

  }

  //Parse files
  parseMarketPrice(marketPriceFileName);
  parsePriceList(priceListFileName);

  //Compute max profit for all problems
  for(int i = 0; i < problems.size(); i++){

    problems[i]->computeMaxProfit(marketPrices);


  }

  //Free memory used for problem objects
  vector<PriceProblem*>::iterator it;
  for(it = problems.begin(); it != problems.end(); ++it){

    delete(*it);

  }

  problems.clear();

  return 0;
}
