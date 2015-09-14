/*
Author: cpriest, Caleb Priester
Filename: graph.cpp
Description: The implementation of the methods declared in graph.h
*/

#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "graph.h"

using namespace std;

int GraphNode::getNumOfAdj() {
  return numOfAdj;
}

void GraphNode::doubleAdjacentNodes() {
  GraphNode **oldAdjacents = adjacentNodes;
  int oldCapacity = capacity;

  capacity = capacity*2;
  adjacentNodes = new GraphNode* [capacity];

  for(int i = 0; i < oldCapacity; i++) {
    adjacentNodes[i] = oldAdjacents[i];
    oldAdjacents[i] = NULL;
  }
}

void GraphNode::connect(GraphNode* n) {
  adjacentNodes[numOfAdj] = n;
  numOfAdj++;
  if(numOfAdj == capacity) doubleAdjacentNodes();
}

void GraphNode::disconnect(GraphNode* n) {
  bool shiftBack = false;
  for(int i = 0; i < numOfAdj; i++) {
    if(adjacentNodes[i]->key == n->key) {
      adjacentNodes[i] = NULL;
      shiftBack = true;
    }
    else if(shiftBack) {
      adjacentNodes[i-1] = adjacentNodes[i];
    }
  }
  numOfAdj--;
}

void GraphNode::printAdjacents() {
  for(int i = 0; i < numOfAdj; i++) cout << adjacentNodes[i]->key << ", ";
  cout << endl;
}

//--------------------------------------------

void Graph::doubleNodes() {
  GraphNode **oldNodes = nodes;
  int oldCapacity = capacity;

  capacity = capacity*2;
  nodes = new GraphNode* [capacity];

  for(int i = 0; i < oldCapacity; i++) {
    nodes[i] = oldNodes[i];
    oldNodes[i] = NULL;
  }

}

void Graph::inset(long key) {
  srand(time(NULL));
  GraphNode *n = new GraphNode(key);
  nodes[numOfNodes] = n;
  int connectCount = 0;
  int connectSpot;
  int connectedSpot[5];
  bool alreadyConnected = false;
  for(int i = 0; i < 5; i++) connectedSpot[i] = -1;
  if(numOfNodes <= 5) {
    for(int i = 0; i < numOfNodes; i++) {
      nodes[i]->connect(n);
      n->connect(nodes[i]);
    }
  }
  else {
    while(connectCount <= 4) {
      connectSpot = rand() % numOfNodes;
      for(int i = 0; i < connectCount; i++)
        if(connectedSpot[i] == connectSpot) alreadyConnected = true;
      if(!alreadyConnected) {
        nodes[connectSpot]->connect(n);
	n->connect(nodes[connectSpot]);
	connectedSpot[connectCount] = connectSpot;
	connectCount++;
      }
      alreadyConnected = false;
    }
  }
  numOfNodes++;
  if(numOfNodes == capacity) doubleNodes();
  //connect();
}

void Graph::remove(long key) {
  int removeSpot = 0;
  bool siftBack = false;
  for(int i = 0; i < numOfNodes; i++) {
    if(nodes[i]->key == key) {
      for(int j = 0; j < nodes[i]->numOfAdj;) {
        nodes[i]->adjacentNodes[j]->disconnect(nodes[i]);
	nodes[i]->disconnect(nodes[i]->adjacentNodes[j]);
      }
      delete nodes[i];
      siftBack = true;
    }
    else if(siftBack) {
      nodes[i-1] = nodes[i];
    }
  }
  numOfNodes--;
  connect();
}

void Graph::connect() {
  if(numOfNodes == 0) return;
  srand(time(NULL));
  GraphNode *n = nodes[0];
  GraphNode *a;
  GraphNode **visitedNodes = new GraphNode*[numOfNodes];
  GraphNode **stack = new GraphNode*[numOfNodes];
  bool keepSifting = true;
  int stackTop = 0;
  int visitedCount = 0;
  int randVisited;

  stack[stackTop] = nodes[0];
  stackTop++;
  visitedNodes[visitedCount] = n;
  visitedCount++;
  while(stackTop != 0) {
    stackTop--;
    n = stack[stackTop];
    n->visited = true;
    for(int i = 0; i < n->numOfAdj; i++) {
      a = n->adjacentNodes[i];
      if(!(a->visited)) {
        a->visited = true;
	stack[stackTop] = a;
	stackTop++;
	visitedNodes[visitedCount] = a;
	visitedCount++;
      }
    }
/*    if(stackTop == 0 && visitedCount < numOfNodes) {
      for(int i = 0; i < numOfNodes && keepSifting; i++) {
        if(!(nodes[i]->visited)) {
          randVisited = rand() % visitedCount;
	  nodes[i]->connect(visitedNodes[randVisited]);
	  visitedNodes[randVisited]->connect(nodes[i]);
	  //nodes[i]->visited = true;
	  stack[stackTop] = nodes[i];
	  stackTop++;
	  visitedNodes[visitedCount] = nodes[i];
	  visitedCount++;
	  keepSifting = false;
        }
      }
    }*/
  }

  if(visitedCount < numOfNodes) {
    for(int i = 0; i < numOfNodes && keepSifting; i++) {
      if(!(nodes[i]->visited)) {
        randVisited = rand() % visitedCount;
	nodes[i]->connect(visitedNodes[randVisited]);
	visitedNodes[randVisited]->connect(nodes[i]);
	keepSifting = false;
      }
    }
  for(int i = 0; i < numOfNodes; i++) nodes[i]->visited = false;
    connect();
  }
  for(int i = 0; i < numOfNodes; i++) nodes[i]->visited = false;
}

void Graph::MCSTInset(GraphNode* n, GraphNode* p) {
  MCST->nodes[MCST->numOfNodes] = n;
  MCST->numOfNodes++;
  if(MCST->numOfNodes == MCST->capacity) MCST->doubleNodes();
  if(p!=NULL) {
    n->connect(p);
    p->connect(n);
  }
}

void Graph::buildMCST() {
  int r = rand() % 2;
  if(r == 0) buildMCSTdfs();
  else buildMCSTbfs();
}

void Graph::buildMCSTdfs() {
  MCST = new Graph();
  srand(time(NULL));
  GraphNode *n;
  GraphNode *a;
  GraphNode *MCSTa;
  GraphNode *MCSTn;
  GraphNode **stack = new GraphNode*[numOfNodes];
  GraphNode **MCSTstack = new GraphNode*[numOfNodes];
  int stackTop = 0;

  n = nodes[rand()%numOfNodes];
  n->visited = true;
  MCSTn = new GraphNode(n->key);
  MCSTInset(MCSTn, NULL);
  stack[stackTop] = n;
  MCSTstack[stackTop] = MCSTn;
  stackTop++;

  while(stackTop != 0) {
    stackTop--;
    n = stack[stackTop];
    MCSTn = MCSTstack[stackTop];
    for(int i = 0; i < n->numOfAdj; i++) {
      a = n->adjacentNodes[i];
      if(!(a->visited)) {
        a->visited = true;
	MCSTa = new GraphNode(a->key);
	MCSTInset(MCSTa, MCSTn);
	stack[stackTop] = a;
	MCSTstack[stackTop] = MCSTa;
	stackTop++;
      }
    }
  }
  for(int i = 0; i < numOfNodes; i++) nodes[i]->visited = false;
  
}

void Graph::buildMCSTbfs() {
  MCST = new Graph();
  srand(time(NULL));
  GraphNode *n;
  GraphNode *a;
  GraphNode *MCSTa;
  GraphNode *MCSTn;
  GraphNode **q = new GraphNode*[numOfNodes];
  GraphNode **MCSTq = new GraphNode*[numOfNodes];
  int qStart = 0;
  int qEnd = 0;

  n = nodes[rand()%numOfNodes];
  n->visited = true;
  MCSTn = new GraphNode(n->key);
  MCSTInset(MCSTn, NULL);
  q[qEnd] = n;
  MCSTq[qEnd] = MCSTn;
  qEnd++;

  while(qStart != qEnd) {
    n = q[qStart];
    MCSTn = MCSTq[qStart];
    qStart++;
    for(int i = 0; i < n->numOfAdj; i++) {
      a = n->adjacentNodes[i];
      if(!(a->visited)) {
        a->visited = true;
	MCSTa = new GraphNode(a->key);
	MCSTInset(MCSTa, MCSTn);
	q[qEnd] = a;
	MCSTq[qEnd] = MCSTa;
	qEnd++;
      }
    }
  }
  for(int i = 0; i < numOfNodes; i++) nodes[i]->visited = false;
  
}

Graph* Graph::getMCST() {
  return MCST;
}

void Graph::shortestPath(long start, long finish) {
  GraphNode **q = new GraphNode* [numOfNodes];
  GraphNode **path = new GraphNode* [numOfNodes];
  GraphNode **visitedNodes = new GraphNode* [numOfNodes];
  int qStart = 0;
  int qEnd = 0;
  int pathCount = 0;
  int visitedCount = 0;
  GraphNode *first;
  GraphNode *end;
  GraphNode *temp;
  GraphNode *n;
  GraphNode *a;
  bool keepSearching = true;

  for(int i = 0; i < numOfNodes && keepSearching; i++) {
    if(nodes[i]->key == start) {
      first = nodes[i];
      keepSearching = false;
    }
  }
  
  keepSearching = true;

  q[qEnd] = first;
  qEnd++;
  visitedNodes[visitedCount] = first;
  visitedCount++;

  while(qStart != qEnd && keepSearching) {
    n = q[qStart];
    qStart++;
    n->visited = true;
    for(int i = 0; i < n->numOfAdj && keepSearching; i++) {
      a = n->adjacentNodes[i];
      if(!(a->visited)) {
        a->visited = true;
	q[qEnd] = a;
	qEnd++;
	a->prevNode = n;
        visitedNodes[visitedCount] = a;
        visitedCount++;
	if(a->key == finish) {
	  end = a;
	  keepSearching = false;
	}
      }
    }
  }

  temp = end;
  while(temp != NULL) {
    path[pathCount] = temp;
    pathCount++;
    temp = temp->prevNode;
  }

  cout << "Shortest Path From " << start << " To " << finish <<":" << endl;
  for(int i = pathCount-1; i >= 0; i--) {
    cout << path[i]->key << endl;
  }
  for(int i = 0; i < visitedCount; i++) {
    visitedNodes[i]->visited = false;
    visitedNodes[i]->prevNode = NULL;
  }
}

void Graph::print() {
  for(int i = 0; i < numOfNodes; i++) {
    cout << nodes[i]->key << ": ";
    nodes[i]->printAdjacents();
  }
}

int Graph::getNumOfNodes() {
  return numOfNodes;
}
