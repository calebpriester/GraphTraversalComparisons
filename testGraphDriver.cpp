#include <iostream>
#include <stdlib.h>

using namespace std;

#include "graph.h"

int main() {
  Graph *g = new Graph();
  /*g->inset(1);
  g->inset(2);
  g->inset(3);
  g->inset(4);
  g->inset(5);
  g->inset(6);
  g->inset(7);
  g->inset(8);
  g->inset(9);
  g->remove(1);
  g->remove(6);
  g->remove(9);*/

/*  g->inset(10);
  g->inset(4);
  g->inset(14);
  g->inset(13);
  g->inset(11);
  g->inset(17);
  g->inset(16);
  g->inset(15);*/

  for(int i = 0; i < 20000; i++) g->inset(i);
  //for(int i = 0; i < 20000; i+=2) g->remove(i);
  //for(int i = 1; i < 19950; i+=2) g->remove(i);
  //for(int i = 9999; i > 5; i--) g->remove(i);
  //for(int i = 0; i < 100; i++) g->inset(i);
  //g->print();
  //cout << endl;
  cout << g->getNumOfNodes();
  cout << endl;
  g->shortestPath(55, 49);
  g->buildMCSTbfs();
  //g->getMCST()->print();
  //cout << endl;
  //g->buildMCSTdfs();
  //g->getMCST()->print();
  //cout << endl;
  //g->getMCST()->shortestPath(10, 4);
  cout << endl;
  //g->shortestPath(10, 4);
  g->getMCST()->shortestPath(55, 49);
  //g->shortestPath(98, 996);
  //g->shortestPath(1, 9999);
  //g->shortestPath(666, 584);
  //g->shortestPath(1, 5);
}
