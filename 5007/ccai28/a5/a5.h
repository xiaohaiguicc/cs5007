// chenxi cai 2019-2-22
#ifndef A5_H
#define A5_H

#define NUM_CITY 1000
#define HOUR_TO_SEC 3600
#define MIN_TO_SEC 60

// ----------------Part1----------------
// a5_bits

// Dispaly bits
void displayBits(unsigned value);

// takes two characters as parameters,
// and returns a 16 bit integer that is holding the packed characters.
unsigned int packCharacters(char a, char b);

// Reverse operation of the packCharacters function
void unpackCharacters(unsigned int packedInt);

// Takes two integer arguments, number and pow and calculates (number * 2pow)
int power2(int num, int pow);

// -----------------Part2------------------
// a5_matrix
// reads city name data from nodes.csv
void readNode(char *city[]);

// reads city distance data from miles_graph_FINAL.csv
void readMiles(double **graph);

// Return the vertics index that has shortest path to source.
// distance[] is the distance from source to vertics
// finalize[] is the conditions that if the vertics distance updated.
// V is the number of vertics
int minimumPathVertics(double distance[], int finalized[], int V);

// Djikstra's using a matrix graph rep
// Return the dest city of shortest distance from source city
// graph is the distance matrix
// source is the source vertice's index
// V is the number of vertics
// dest is the des city's index
// city[] is the city name array
double dijkstra(double **graph, int source, int V, int dest, char *city[]);

// With city's name, return it' index
int searchCity(char* city[], char* cityName);

// The shortest path and distance from source city to dest city.
void shortestPath(char* sourceCityName, char* destCityName,
    char* city[], double** graph);

// ---------------------Part3-----------------
// a5_list

struct ListNode {
    int dest;
    int weight;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

struct List {
    struct ListNode *head;
};
typedef struct List List;

struct Graph {
    int V;
    struct List* array;
};

typedef struct Graph Graph;

// convert hout-min-sec to sec values
int convertToSec(int hour, int min, int sec);

// read edges data from edge file
void readEdges(int** time, char* city[]);

// minimum path
int minimumPathListNode(int distance[], int finalized[], int V);

// dijkstra algorithm with list
int dijkstraList(Graph* graph, int source, int destIndex, char *city[]);

// fastest path
void fastestPath(char* sourceCityName, char* destCityName,
    char* city[], Graph* graph);

// Create a new adjacency list node
ListNode* newListNode(int dest, int weight);

// Creates a graph of V vertices
Graph* createGraph(int V);

// destroy graph
void destroyGraph(Graph* graph);

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest, int weight);
#endif
