/*
Author: cpriest, Caleb Priester
Filename: MCSTbfsTest.cpp
Description:  This program creates a graph by inserting 1 - 10000 into a graph
in random order, then creates an MCST from that graph using a breadth-first
strategy.  It then tests how long it takes to build a path between two nodes 
from 1000-10000 times.
*/

#include <iostream>
#include <cstdio>
#include <time.h>
#include <cstdlib>
#include "graph.h"


using namespace std;

int main() {
  int key;
  Graph g;
  Graph MCST;
  timespec ts;
  int values[10000];
  int temp;
  int rand1;
  int rand2;
  unsigned long long nano;
  unsigned long long milli;

  srand(time(NULL));

  for(int i = 0; i < 10000; i++) values[i] = i;

  for(int i = 0; i < 100000; i++) {
    rand1 = rand() % 10000;
    rand2 = rand() % 10000;
    temp = values[rand1];
    values[rand1] = values[rand2];
    values[rand2] = temp;
  }

  for(int i = 0; i < 10000; i++) g.inset(values[i]);
  g.buildMCSTbfs();
  MCST = *(g.getMCST());
  
  for(int i = 100; i <= 1000; ) {
    for(int j = 0; j < 100000; j++) {
      rand1 = rand() % 10000;
      rand2 = rand() % 10000;
      temp = values[rand1];
      values[rand1] = values[rand2];
      values[rand2] = temp;
    }
    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &ts);

    for(int j = 0; j < i*2; j+=2) MCST.shortestPath(values[j], values[j+1]);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    nano = (unsigned long long) (ts.tv_sec * 1000000000) + (unsigned long long) ts.tv_nsec;
    milli = nano / 1000000;

    cout << i << " shortest path operations " << milli << " milli seconds" << endl;

    i+=100;
  }
}
