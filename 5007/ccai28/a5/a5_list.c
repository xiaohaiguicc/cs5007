// chenxi cai 2019-2-22
// Part of the Adjacency List implement is searched from
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include "a5.h"

int convertToSec(int hour, int min, int sec) {
    return hour * HOUR_TO_SEC + min * MIN_TO_SEC + sec;
}

void readNode(char *city[]) {
  FILE *cfPtr;
  char *record, *line;
  int i = 0;

  cfPtr = fopen("nodes.csv", "r");
  if (cfPtr == NULL) {
    printf("File could not be opened\n");
  } else {
        char buffer[1024];
        line = fgets(buffer, 1024, cfPtr);
        while ((line = fgets(buffer, 1024, cfPtr)) != NULL) {
            record = strsep(&line, ",");
            city[i] = strdup(strsep(&line, "\n"));
            ++i;
        }
     }
  fclose(cfPtr);
}

int searchCity(char* city[], char* cityName) {
    int i = 0;
    while (strcmp(city[i], cityName) != 0) {
       i++;
    }
    return i;
}

void readEdges(int** time, char* city[]) {
  FILE *cfPtr;
  char* line;
  char *src;
  char *dest;
  int hms[3];

  cfPtr = fopen("edges.csv", "r");
  if (cfPtr == NULL) {
    printf("File could not be opened\n");
  } else {
        char buffer[20240];

        while ((line = fgets(buffer, 20240, cfPtr)) != NULL) {
            char* record;
            int srcIndex, destIndex;

            src = strsep(&line, " ");
            dest = strsep(&line, " ");
            srcIndex = searchCity(city, src);
            destIndex = searchCity(city, dest);
            int k = 0;
            while ((record = strsep(&line, " ")) != NULL) {
                hms[k] = atoi(record);
                k++;
             }
            time[srcIndex][destIndex] = convertToSec(hms[0], hms[1], hms[2]);
        }
     }
  fclose(cfPtr);
}

ListNode* newListNode(int dest, int weight) {
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    graph->array = (List*) malloc(V * sizeof(List));

    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    ListNode* newNode = newListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void destroyGraph(Graph* graph) {
    int V = graph->V;
    ListNode* tmp;
    for (int i = 0; i < V; i++) {
       while (graph->array[i].head != NULL) {
          tmp = graph->array[i].head;
          graph->array[i].head = graph->array[i].head->next;
          free(tmp);
      }
  }
  free(graph->array);
  free(graph);
}


int minimumPathListNode(int distance[], int finalized[], int V) {
    int minPath = INT_MAX;
    int minIndex;
    for (int i = 0; i < V; i++) {
        if (distance[i] <= minPath && finalized[i] == 0) {
            minPath = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int dijkstraList(Graph* graph, int source, int destIndex, char *city[]) {
    int V = graph->V;
    int distance[V], finalized[V];
    int index[V];
    int i;

    for (i = 0; i < V; ++i) {
        distance[i] = INT_MAX;
        finalized[i] = 0;
    }
    distance[source] = 0;

    for (i = 0; i < V; i++) {
        int u = minimumPathListNode(distance, finalized, V);
        finalized[u] = 1;

        ListNode* minNode = graph->array[u].head;

        while (minNode != NULL) {
           int v = minNode->dest;

            if (finalized[v] == 0 && minNode->weight != -1
               && distance[u] != INT_MAX
               && minNode->weight + distance[u] < distance[v]) {
               distance[v] = minNode->weight + distance[u];
               index[v] = u;
           }
           minNode = minNode->next;
         }
     }

    i = destIndex;
    int j = 0;
    int path[V];
    while (i != source) {
        path[j] = i;
        i = index[i];
        j++;
    }
    path[j] = source;

    for (i = j; i >= 0; i--) {
        if (path[i] != -1) {
            if (path[i] == destIndex) {
                printf("%s\n", city[destIndex]);
            } else {
                  printf("%s - ", city[path[i]]);
            }
        }
    }

  return distance[destIndex];
}

void fastestPath(char* sourceCityName, char* destCityName,
    char* city[], Graph* graph) {
    int source = searchCity(city, sourceCityName);
    int dest = searchCity(city, destCityName);
    printf("The fastest path from %s to %s is:\n",
        sourceCityName, destCityName);
    int time = dijkstraList(graph, source, dest, city);
    int hour = time / HOUR_TO_SEC;
    int min = (time - hour * HOUR_TO_SEC) / MIN_TO_SEC;
    int sec = time - hour * HOUR_TO_SEC - min * MIN_TO_SEC;
    printf("%s to %s time: %d hour %d min %d sec\n",
            sourceCityName, destCityName, hour, min, sec);
}


int main(void) {
    int i;
    int** time;
    char* city[NUM_CITY];

    Graph* graph = createGraph(NUM_CITY);

    time = (int **)malloc(NUM_CITY * sizeof(int *));
    for (i = 0; i < NUM_CITY; ++i) {
        int a;
        time[i] = (int *)malloc(NUM_CITY * sizeof(a));
    }

    for (i = 0; i < NUM_CITY; ++i) {
        for (int j = 0; j < NUM_CITY; ++j) {
            time[i][j] = -1;
        }
    }

    readNode(city);
    readEdges(time, city);

    for (i = 0; i < NUM_CITY; ++i) {
        for (int j = 0; j < NUM_CITY; ++j) {
            addEdge(graph, i, j, time[i][j]);
        }
    }

    printf("\n");
    fastestPath("Seattle_WA", "Boston_MA", city, graph);
    printf("\n");
    fastestPath("Ann_Arbor_MI", "Minneapolis_MN", city, graph);

    destroyGraph(graph);

    for (i = 0; i < NUM_CITY; i++) {
        free(time[i]);
        free(city[i]);
    }

    free(time);
}
