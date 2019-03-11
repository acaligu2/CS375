#include "PriceProblem.h"

void PriceProblem::setOutFile(string o){ outputFileName = o; }

void PriceProblem::setFunctionType(int funcType){ functionType = funcType; }

int PriceProblem::getFunctionType(){ return functionType; }

void PriceProblem::setProblemSize(int pS){ problemSize = pS; }

int PriceProblem::getProblemSize(){ return problemSize; }

void PriceProblem::setBudget(int b){ budget = b; }

int PriceProblem::getBudget(){ return budget; }

void PriceProblem::addToMap(int w, int p){

	weights.push_back(w);
	profits.push_back(p);

	//New struct containing weight and profits
	//Used for sorting in non-decreasing order
	ratioStruct r;
	r.weight = w;
	r.profit = p;
	r.index = ratioIndex;
	ratios.push_back(r);

	ratioIndex++;

}

vector<int> PriceProblem::getW(){ return weights; }
vector<int> PriceProblem::getP(){ return profits; }

//Custom sort function
bool PriceProblem::ratioSort(ratioStruct i, ratioStruct j){

	double iRatio = (double) i.profit / i.weight;
	double jRatio = (double) j.profit / j.weight;

	return(iRatio > jRatio);

}

void PriceProblem::greedy1(){

	vector<int> greedy1Set;

	int budgetCopy = budget;

	//Sort ratio vector in non-decreasing order
	sort(ratios.begin(), ratios.end(), ratioSort);

  //Loop through vector
  for(int i = 0; i < ratios.size(); i++){

    //Decrement the budget based on next weight in sequence
		int temp = budgetCopy - ratios[i].weight;

		//If there is room left in the budget, purchase and increment the maxProfit
		if(temp > 0){

			budgetCopy -= ratios[i].weight;
			maxProfit += ratios[i].profit;

		//Budget has been spent, break out of loop
		}else{ continue; }

  }

}

void PriceProblem::greedy2(){

	//Get solution from Greedy1 for comparsion
  greedy1();
  int greedy1Max = maxProfit;

  int greedy2Max = 0;

  //Loop through vector
  for(int i = 0; i < weights.size(); i++){

		//Weight is smaller than budget
  	if(weights[i] <= budget){

			//Weight is associated with the largest profit of all elements
			if(profits[i] > greedy2Max){

				//Set largest
				greedy2Max = profits[i];

			}

		}

  }

	//Greedy1 maxProfit is larger
  if(greedy1Max > greedy2Max){ maxProfit = greedy1Max; }

	//Greedy2 maxProfit is larger
  else{ maxProfit = greedy2Max; }

}

//Calculate bound for backTracking
int PriceProblem::fracKnap(int i, int weight, int profit){

	int remainingCapacity = budget - weight;
	int bound = profit;

	int level = i;

	//Add profit of weight <= capacity to the bound and traverse down the tree
	while(level < ratios.size() && ratios[level].weight <= remainingCapacity){

		remainingCapacity -= ratios[level].weight;
		bound += ratios[level].profit;
		level++;

	}

	//Adding fraction of item to knapsack
	if(level < ratios.size()){

		int r = ratios[level].profit / ratios[level].weight;
		bound += r * remainingCapacity;

	}

	return bound;

}

//Returns if the current node is promising to the solution
bool PriceProblem::promising(int i, int p, int w){

	//Not promising since weight doesn't fit in capacity
	if(w >= budget) return false;

	//Find bound
	int bound = fracKnap(i, w, p);

	//If bound > maxProfit, node is promising
	return(bound > maxProfit);

}

void PriceProblem::backTracking(int index, int profit, int weight){

	//Better solution has been found, save in maxProfit
	if(weight <= budget && profit > maxProfit){
		maxProfit = profit;
	}

	//Weight of element can fit in capacity, add profit
	if(weight + ratios[index].weight <= budget){

		weight += ratios[index].weight;
		profit += ratios[index].profit;

		//Traverse further down the tree from this node
		backTracking(index + 1, profit, weight);

		weight -= ratios[index].weight;
		profit -= ratios[index].profit;

	}

	//Check if node is promising
	bool prom = promising(index + 1, profit, weight);

	if(prom){

		backTracking(index + 1, profit, weight);

	}

}

//*** DYNAMIC PROGRAMMING CODE STARTS HERE ***
void PriceProblem::dynamicProgramming(){

    // matrix to store final result, space efficient with 2 rows
    int mat[2][budget+1];
    memset(mat, 0, sizeof(mat));

    // iterate through all items
    int i = 0;

    while (i < problemSize){

        int j = 0;

				//Store in the second row: index 1
        if (i%2 != 0){

            while (j <= budget){

                if (weights[i] <= j){

									int val1 = profits[i] + mat[0][j - weights[i]];
									int val2 = mat[0][j];

									mat[1][j] = max(val1, val2);

                }else{

                  mat[1][j] = mat[0][j];

								}

								j++;
            }

				//Store in the first row: index 0
        }else{

            while(j <= budget){

                if (weights[i] <= j){

									int val1 = profits[i] + mat[1][j - weights[i]];
									int val2 = mat[1][j];

                  mat[0][j] = max(val1, val2);

								}else{

                  mat[0][j] = mat[1][j];

								}

								j++;

            }

        }

        i++;

    }

		//Problem size is odd, return from first row
		if(problemSize % 2 != 0){

			maxProfit = mat[0][budget];

		//Problem size is even, return from second row
		}else{

			maxProfit = mat[1][budget];

		}

}

//Write results to output file
void PriceProblem::writeToOutput(float seconds, int opt){

  ofstream outputFile;
  outputFile.open(outputFileName, fstream::app);

	if(opt == 3){ outputFile << "Dynamic Programming: "; }

  outputFile << problemSize << " " << maxProfit << " " << seconds << endl;

  outputFile.close();

}
