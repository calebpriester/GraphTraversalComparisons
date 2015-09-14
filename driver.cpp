/*
Author: cpriest, Caleb Priester
Filename: driver.cpp
Description: Contains a main method that reads in data from a file, creates a
 dictionary and a graph with the data, and then reads in pairs of data from
 another file to create paths between the nodes using a shortest path algorithm
 and an MCST.  After ten sucessful searches, the last read pair gets removed
 and a new MCST is created, and after five unsuccessful searches, the last
 searched pair is added and a new MCST is created. Note: After experimenting, I
 found that creating the MCST breadth-first creates shorter paths at a quicker 
 speed than creating it depth-first would do, so the graph calls buildMCSTbfs 
 when creating MCSTs.
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cassert>

using namespace std;

#include "hash3.h"
#include "graph.h"

int main() {
  long key;
  long start;
  long finish;
  Hash3 *dictionary = new Hash3(27, 13);
  Graph *graph = new Graph();
  string fileName;
  ifstream myFile;
  int successfulCount = 0;
  int failCount = 0;

  cout << "Enter insert file name:" << endl;
  cin >> fileName;
  myFile.open(fileName.c_str());
  while(myFile >> key) {
    if(!(dictionary->search(key))) {
      dictionary->inset(key);
      graph->inset(key);
    }
  }
  graph->buildMCSTbfs();
  myFile.close();

  /*graph->print();
  cout<< endl;
  graph->getMCST()->print();
  cout << endl;*/

  cout << "Enter path-building file name:" << endl;
  cin >> fileName;
  myFile.open(fileName.c_str());
  while(myFile >> start && myFile >> finish) {
    cout << "Start: " << start << ", Finish: " << finish << endl;
    if(start != finish && dictionary->search(start) && dictionary->search(finish)) {
      cout << "MCST Path:" << endl;
      graph->getMCST()->shortestPath(start, finish);
      cout << endl << "Shortest Path:" << endl;
      graph->shortestPath(start, finish);
      cout << endl;
      successfulCount++;
      if(successfulCount == 10) {
        dictionary->remove(start);
	dictionary->remove(finish);
	graph->remove(start);
	graph->remove(finish);
	graph->buildMCSTbfs();
	successfulCount = 0;
      }
    }
    else {
      cout << "Failed search!" << endl << endl;
      failCount++;
      if(failCount == 5) {
        if(!(dictionary->search(start))) {
	  dictionary->inset(start);
	  graph->inset(start);
	}
	if(!(dictionary->search(finish))) {
	  dictionary->inset(finish);
	  graph->inset(finish);
	}
	failCount = 0;
	graph->buildMCSTbfs();
      }
    }
  }
}
