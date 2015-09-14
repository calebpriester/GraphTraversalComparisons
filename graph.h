/*
Author: cpriest, Caleb Priester
Filename: graph.h
Description: The definition of a graph and its nodes.
*/

class GraphNode {
  friend class Graph;

  private:
  GraphNode **adjacentNodes;
  GraphNode *prevNode;   //Used in shortestDistance() in graph
  long key;
  int numOfAdj;
  int capacity;
  bool visited;
  void doubleAdjacentNodes();
  
  public:
  GraphNode() : key(0), numOfAdj(0), capacity(5), visited(false) {adjacentNodes = new GraphNode* [capacity]; prevNode = NULL;}
  GraphNode(long k) : key(k), numOfAdj(0), capacity(1), visited(false) {adjacentNodes = new GraphNode* [capacity]; prevNode = NULL;}
  void connect(GraphNode *n);
  void disconnect(GraphNode *n);
  int getNumOfAdj();
  void printAdjacents();
};

class Graph {
  private:
  GraphNode **nodes;
  Graph *MCST;
  int numOfNodes;
  int capacity;
  void connect();
  void doubleNodes();
  void MCSTInset(GraphNode *n, GraphNode* p);

  public:
  Graph() : numOfNodes(0), capacity(20) {nodes = new GraphNode* [capacity];}
  void inset(long key);
  void remove(long key);
  int getNumOfNodes();
  void shortestPath(long start, long finish);
  void buildMCST();         //Randomly selects a method to build the MCST.
  void buildMCSTdfs();      //Creates an MCST using a depth-first technique.
  void buildMCSTbfs();      //Creates an MCST using a breadth-first technique.
  Graph* getMCST();
  void print();

};
