/* Your code here! */

#include "dsets.h"
using namespace std;

//Add elements to array
void DisjointSets::addelements(int num) {
  for (int i = 1; i <= num; i++) {
    elements.push_back(-1);
  }
  return;
}

int DisjointSets::find(int elem) {
  if (elements[elem] < 0) {
    return elem;
  } else {
    elements[elem] = find(elements[elem]);
    return elements[elem];
  }
}

void DisjointSets::setunion(int a, int b) {
  a = find(a);
  b = find(b);

  if (a == b) {
    return;
  }

  if (elements[a] < elements[b]) {
    elements[a] = elements[a] + elements[b];
    elements[b] = a;
  } else {
    elements[b] = elements[a] + elements[b];
    elements[a] = b;
  }

}

int DisjointSets::size(int elem) {
  return -1 * elements[find(elem)];
}
