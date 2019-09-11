/* implement insertion sort*/
#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>
void insertionSort(int arr[], int n) {
   int i, key;
   for (int j = 1; j < n; j++) {
       key = arr[j];
       i = j - 1;
       while(i >= 0 && arr[i] > key) {
	    arr[i + 1] = arr[i];
	    i = i - 1;
       }
       arr[i + 1] = key;
   }
}
void randomArray(int arr[], int n, int limit) {
     for(int i = 0; i < n; i++) {
      arr[i] = rand()% limit;
   }
}
//void printArray(int arr[], int n) {
    // for(int i = 0; i < n; i++) {
     // printf("%d ", arr[i]);
   //}
//}
double buildRun(int n, int limit) {
   int arr[n];
   randomArray(arr, n, limit);
   struct timeval start, end;
   gettimeofday(&start, NULL);

   insertionSort(arr, n);

   gettimeofday(&end, NULL);
   return (double)(end.tv_sec - start.tv_sec) * 1000.0f + (double)(end.tv_usec - start.tv_usec) / 1000.0f;
}
int main() {
   printf("---------------------\n");
   printf("SLOW SORT: INSERTION\n");
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
