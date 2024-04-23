/* Your code here! */

#pragma once
#include <vector>
using namespace std;

class DisjointSets {

  //NOTE: Add constructors if/when needed

public:
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);

  vector<int> elements;
};
