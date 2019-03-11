#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Contestant{

  private:

    int id = -1;
    int pointTotal = -1;

  public:

    int getId();
    void setId(int i);

    int getPointTotal();
    void setPointTotal(int val);

};
