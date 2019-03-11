#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include "Contestant.h"

using namespace std;

extern void initialize(int size, string outFile);
extern void findContestant(int id, string condition);
extern void insertContestant(int id, int score);
extern void eliminateWeakest();
extern void earnPoints(int id, int points);
extern void losePoints(int id, int points);
extern void showContestants();
extern void showHandles();
extern void showLocation(int id);
extern void crownWinner();
extern void freeMem();

void parseInput(string fileName, string out){

  int heapSize = -1;
  bool firstLine = true;
  ifstream inFile(fileName);

  if(inFile.fail()){
    perror("Input file doesn't exist.\n");
    exit(1);
  }

  string line, function;

  ofstream oF;
  oF.open(out, fstream::app);

  while(getline(inFile, line)){

    if(firstLine){
      heapSize = stoi(line);
      initialize(heapSize, out);
      firstLine = false;
      continue;
    }

    oF << line << endl;

    istringstream ss(line);
    ss >> function;

    if(function == "findContestant"){

      string id;
      ss >> id;

      id = id.substr(1, id.size() - 2);

      int i = stoi(id);
      findContestant(i, "output");

    }else if(function == "insertContestant"){

      string id, score;
      ss >> id >> score;

      id = id.substr(1, id.size() - 2);
      score = score.substr(1, score.size() - 2);

      int i, s;
      i = stoi(id);
      s = stoi(score);
      insertContestant(i, s);

    }else if(function == "eliminateWeakest"){

      eliminateWeakest();

    }else if(function == "earnPoints"){

      string id, points;
      ss >> id >> points;

      id = id.substr(1, id.size() - 2);
      points = points.substr(1, points.size() - 2);

      int i, p;
      i = stoi(id);
      p = stoi(points);
      earnPoints(i, p);

    }else if(function == "losePoints"){

      string id, points;
      ss >> id >> points;

      id = id.substr(1, id.size() - 2);
      points = points.substr(1, points.size() - 2);

      int i, p;
      i = stoi(id);
      p = stoi(points);
      losePoints(i, p);

    }else if(function == "showContestants"){

      showContestants();

    }else if(function == "showHandles"){

      showHandles();

    }else if(function == "showLocation"){

      string id;
      ss >> id;

      id = id.substr(1, id.size() - 2);

      int i = stoi(id);
      showLocation(i);

    }else if(function == "crownWinner"){

      crownWinner();

    }

  }

  oF.close();
  inFile.close();

}

int main(int argc, char const *argv[]) {

  if(argc != 3){

    perror("./program2 <inputFile> <outputFile>");
    exit(1);

  }

  string inputFileName = argv[1];
  string outputFileName = argv[2];

  //Start output.txt from a clean slate;
  ofstream initializeOutput;
  initializeOutput.open(outputFileName);
  initializeOutput << "";
  initializeOutput.close();

  parseInput(inputFileName, outputFileName);

  freeMem();

  return 0;
}
