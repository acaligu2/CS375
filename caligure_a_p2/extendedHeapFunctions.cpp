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

int heapSize = -1;
Contestant* heap;
int* handleArray;
ofstream o;
string outputFileName;
int elementsInHeap;

void freeMem(){
  delete [] heap;
  delete [] handleArray;
  return;
}

//Declare the output filename, account for arrays starting at 1, intitalize heap
//and handle array
void initialize(int size, string out){

  outputFileName = out;
  elementsInHeap = 0;
  heapSize = size;
  heap = new Contestant[heapSize+1];

  Contestant x;
  x.setId(-100);
  x.setPointTotal(-100);
  heap[0] = x;

  handleArray = new int[heapSize + 1];
  handleArray[0] = -100;
  for(int i = 1; i <= heapSize; i++){
    handleArray[i] = -1;
  }

}

int getParentIndex(int i){ return (i)/2; }

int getLeftChildIndex(int i){ return (2*i); }

int getRightChildIndex(int i){ return (2*i)+1; }

//Swap two contestants depending on score
void swap(Contestant * larger, Contestant* smaller){
  Contestant temp = *larger;
  *larger = *smaller;
  *smaller = temp;
}

//Re-establish the min-heap property based on changes to score/number of participants
void minHeapify(int i){

  int lChild = getLeftChildIndex(i);
  int rChild = getRightChildIndex(i);
  int lowestVal = i;

  //Left child is smaller
  if(lChild <= elementsInHeap && heap[lChild].getPointTotal() < heap[i].getPointTotal()){
    lowestVal = lChild;
  }

  //Right child is smaller
  if(rChild <= elementsInHeap && heap[rChild].getPointTotal() < heap[lowestVal].getPointTotal()){
    lowestVal = rChild;
  }

  //Swap the smallest value with the first element
  if(lowestVal != i){
    swap(&heap[i], &heap[lowestVal]);
    minHeapify(lowestVal);
  }

}

//Update the handle array to reflect changes in the heap order
void adjustHandleArray(){

  for(int i = 1; i <= heapSize; i++){

    if(heap[i].getId() != -1){
      handleArray[heap[i].getId()] = i;
    }

  }

}

//Check if the handle array contains the ID requested
bool findContestant(int id, string condition){

  //Outputs result to file
  if(condition == "output"){

    o.open(outputFileName, fstream::app);

    //ID isn't in the heap
    if(handleArray[id] == -1){

      o << "Contestant <" << id << "> is not in the extended heap." << endl;

    //ID is in the heap
    }else{

      o << "Contestant <" << id << "> is in the extended heap with score <" <<
      heap[handleArray[id]].getPointTotal() << ">." << endl;

    }

    o.close();

  //Returns a bool for other functions
  }else{

    if(handleArray[id] == -1){
      return false;
    }else{ return true; }

  }

}

//Add new contestant to the heap
void insertContestant(int id, int score){

  o.open(outputFileName, fstream::app);

  //Create an object and initialize with ID and score
  Contestant c;
  c.setId(id);
  c.setPointTotal(score);

  //Heap is full
  if(elementsInHeap >= heapSize){

    o << "Contestant <" << id << "> could not be inserted because the extended heap is full." << endl;
    return;

  }

  //Check if ID has already been inserted
  bool present = findContestant(id, "find");

  if(present){

    o << "Contestant <" << id << "> is already in the extended heap: cannot insert." << endl;
    return;

  }

  //Add new contestant to heap
  elementsInHeap++;
  int index = elementsInHeap;
  heap[index] = c;

  //Re-establish the min-heap property
  minHeapify(index);

  //Adjust handle array to account for changes to the heap
  adjustHandleArray();

  o << "Contestant <" << id << "> inserted with initial score <" << score << ">." << endl;
  o.close();

}

//Remove heap[1] and re-establish the min-heap property
void eliminateWeakest(){

  o.open(outputFileName, fstream::app);

  if(elementsInHeap == 0){
    o << "No contestant can be eliminated since the extended heap is empty." << endl;
    return;
  }

  o << "Contestant <" << heap[1].getId() << "> with current lowest score <" <<
    heap[1].getPointTotal() << "> eliminated." << endl;

  //Swap smallest with the last element
  heap[1] = heap[elementsInHeap];

  //Decrease the elements in the heap by 1
  heap[elementsInHeap].setId(-1);
  heap[elementsInHeap].setPointTotal(-1);
  handleArray[1] = -1;
  elementsInHeap--;

  //Re-adjust the min-heap property
  minHeapify(1);

  //Re-adjust handle array
  adjustHandleArray();

  o.close();

}

//Add value to ID's point total
void earnPoints(int id, int points){

  o.open(outputFileName, fstream::app);

  if(!findContestant(id, "find")){
    o << "Contestant <" << id << "> is not in the extende heap." << endl;
    return;
  }

  int currentPoints = heap[handleArray[id]].getPointTotal();

  int newPoints = currentPoints + points;

  heap[handleArray[id]].setPointTotal(newPoints);

  //Ensure heap and handle array reflect change
  minHeapify(handleArray[id]);
  adjustHandleArray();

  o <<  "Contestant <" << id << ">'s score increased by <" << points <<
  "> points to <" << heap[handleArray[id]].getPointTotal() << ">." << endl;

  o.close();

}

//Subtract points from ID's total
void losePoints(int id, int points){

  o.open(outputFileName, fstream::app);

  if(!findContestant(id, "find")){
    o << "Contestant <" << id << "> is not in the extende heap." << endl;
    return;
  }

  int currentPoints = heap[handleArray[id]].getPointTotal();
  int newPoints = currentPoints - points;

  heap[handleArray[id]].setPointTotal(newPoints);

  //Ensure heap and handle array reflect change
  minHeapify(handleArray[id]);
  adjustHandleArray();

  o <<  "Contestant <" << id << ">'s score decreased by <" << points <<
  "> points to <" << heap[handleArray[id]].getPointTotal() << ">." << endl;

  o.close();

}

//List contestants in order of heap
void showContestants(){

  o.open(outputFileName, fstream::app);

  for(int i = 1; i <= elementsInHeap; i++){

    if(heap[i].getId() != -1){
      o << "Contestant <" << heap[i].getId() <<
        "> in extended heap location <" << handleArray[heap[i].getId()] <<
        "> with score <" << heap[i].getPointTotal() << ">." << endl;
    }

  }

  o.close();

}

//List handle array in order
void showHandles(){

  o.open(outputFileName, fstream::app);

  for(int i = 1; i <= heapSize; i++){

    if(handleArray[i] != -1){
      o << "Contestant <" << i <<
        "> stored in extended heap location <" << handleArray[i] <<
        ">." << endl;
    }else{
      o << "There is no Contestant <" << i << "> in the extended heap: handle[<" <<
        i << ">] = -1." << endl;
    }

  }

  o.close();

}

//Output location of specified ID
void showLocation(int id){

  o.open(outputFileName, fstream::app);
  if(handleArray[id] == -1){
    o << "There is no Contestant <" << id << "> in the extended heap: handle[<" <<
      id << ">] = -1." << endl;
  }else{
    o << "Contestant <" << id << "> stored in extended heap location <" <<
      handleArray[id] << ">." << endl;
  }

  o.close();
}

//Remove smallest element until one remains with the highest score
void crownWinner(){

  o.open(outputFileName, fstream::app);

  while(elementsInHeap > 1){
    heap[1] = heap[elementsInHeap];
    heap[elementsInHeap].setId(-1);
    heap[elementsInHeap].setPointTotal(-1);
    handleArray[1] = -1;
    elementsInHeap--;
    minHeapify(1);
    adjustHandleArray();

  }

  o << "Contestant <" << heap[1].getId() << "> wins with score <" <<
    heap[1].getPointTotal() << ">!" << endl;

}
