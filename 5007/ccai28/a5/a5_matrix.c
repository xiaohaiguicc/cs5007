// chenxi cai 2019-2-22
#include<stdio.h>
#include<float.h>
#include<stdlib.h>
#include<string.h>
#include "a5.h"

int minimumPathVertics(double distance[], int finalized[], int V) {
    double minPath = DBL_MAX;
    int minIndex;
    for (int i = 0; i < V; i++) {
        if (distance[i] <= minPath && finalized[i] == 0) {
            minPath = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

double dijkstra(double **graph, int source, int V, int dest, char* city[]) {
    double distance[V];
    int finalized[V], index[V];
    int i, j;

    for (i = 0; i < V; i++) {
        distance[i] = DBL_MAX;
        finalized[i] = 0;
    }

    distance[source] = 0;
    for (i = 0; i < V; i++) {
        int minIndex = minimumPathVertics(distance, finalized, V);

        finalized[minIndex] = 1;

        for (j = 0; j < V; j++) {
            if (finalized[j] == 0 && graph[minIndex][j] != -1
                && distance[minIndex] != DBL_MAX
                && distance[minIndex] + graph[minIndex][j] < distance[j]) {
                distance[j] = distance[minIndex] + graph[minIndex][j];
                index[j] = minIndex;
              }
        }
    }

    i = dest;
    j = 0;
    int path[V];
    while (i != source) {
        path[j] = i;
        i = index[i];
        j++;
    }
    path[j] = source;

    for (i = j; i >= 0; i--) {
        if (path[i] != -1) {
            if (path[i] == dest) {
                printf("%s\n", city[dest]);
            } else {
                  printf("%s - ", city[path[i]]);
              }
         }
     }

     return distance[dest];
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
            record = strsep(&line, "\n");
            city[i] = strdup(record);
            ++i;
        }
     }
  fclose(cfPtr);
}

void readMiles(double **graph) {
  FILE *cfPtr;
  char* line;
  int i = 0;

  cfPtr = fopen("miles_graph_FINAL.csv", "r");

  if (cfPtr == NULL) {
    printf("File could not be opened\n");
  } else {
        char buffer[20240];
        fgets(buffer, 20240, cfPtr);

        while ((line = fgets(buffer, 20240, cfPtr)) != NULL) {
            int j = 0;
            char* record;
            record = strsep(&line, ",");

            while ((record = strsep(&line, ",")) != NULL) {
                 graph[i][j] = atof(record);
                 if (i != j && graph[i][j] == 0) {
                     graph[i][j] = -1;
                  }
                 j++;
            }

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

void shortestPath(char* sourceCityName, char* destCityName,
                  char* city[], double** graph) {
    int source = searchCity(city, sourceCityName);
    int dest = searchCity(city, destCityName);
    printf("The shortest path from %s to %s is:\n", sourceCityName,
        destCityName);
    double dis = dijkstra(graph, source, NUM_CITY, dest, city);
    printf("%s to %s distance: %f\n", sourceCityName, destCityName, dis);
}

int main() {
  char* city[NUM_CITY];
  double **graph;
  int i;


  graph = (double **)malloc(NUM_CITY * sizeof(double *));
  for (i = 0; i < NUM_CITY; ++i) {
      double a;
      graph[i] = (double *)malloc(NUM_CITY * sizeof(a));
  }

  readNode(city);
  readMiles(graph);

  printf("\n");
  shortestPath("Seattle_WA", "Boston_MA", city, graph);
  printf("\n");
  shortestPath("Minneapolis_MN", "Ann_Arbor_MI", city, graph);
  printf("\n");

  for (i = 0; i < NUM_CITY; i++) {
      free(graph[i]);
      free(city[i]);
  }

  free(graph);
}

