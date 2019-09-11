/* implement quicksort*/
#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>
void swap(int* a, int* b){
     int temp = *a;
     *a = *b;
     *b = temp;
}
int partition (int arr[], int p, int r) {
    int pivot = arr[r];
    int i = p - 1;
    for(int j = p; j <= r - 1; j++) {
        if(arr[j] <= pivot) {
           i++;
           swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);
    return (i + 1);
}
void quickSort(int arr[], int p, int r) {
     if (p < r) {
	int pi = partition(arr, p, r);
	quickSort(arr, p, pi - 1);
	quickSort(arr, pi + 1, r);
     }
}
void randomArray(int arr[], int n, int limit) {
     for(int i = 0; i < n; i++) {
      arr[i] = rand()% limit;
   }
}
double buildRun(int n, int limit) {
   int arr[n];
   randomArray(arr, n, limit);
   struct timeval start, end;
   gettimeofday(&start, NULL);

   quickSort(arr, 0,  n - 1);

   gettimeofday(&end, NULL);
   return (double)(end.tv_sec - start.tv_sec) * 1000.0f + (double)(end.tv_usec - start.tv_usec) / 1000.0f;
}
int main() {
   srand(0);
   printf("---------------------\n");
   printf("FAST SORT: QUICKSORT\n");
   printf("---------------------\n");
   int trials = 30;
   int n_large = 10000; double time_large = 0;
   int n_med = 1000;  double time_med = 0;
   int n_small = 10;  double time_small = 0;
   srand(0);
   for (int i = 0; i < trials; i++) {
      int limit = (i + 1) * 10 + 100;
      //Large trial
      time_large += buildRun(n_large, limit);
      //Med trial
      time_med += buildRun(n_med, limit);
      //Small trial
      time_small += buildRun(n_small, limit);
   }

   printf("%d trials\n", trials);
   printf("Large:    %d elements     %f msecs avg\n", n_large, time_large / trials);
   printf("Med:       %d elements     %f msecs avg\n", n_med, time_med / trials);
   printf("Small:     %d elements     %f msecs avg\n", n_small, time_small / trials);
}

