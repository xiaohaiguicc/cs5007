Experiment:

In these sorting experiments, I tried to sort arrays with three different size: large, medium and small.
Each size has 30 trials, which means that 30 different arrays with the same length are sorted parallely. 
The final executing time is an average value.

In my experiments, small, medium and large size means the array contains 10, 1000 and 10000 elements, separately.
After 30 trials, the average running time is:
    
insertion sort:    large  62.96650 msecs;      med    0.635200 msecs;       small  0.000333 msecs       

quicksort:         large  2.382600 msecs;      med    0.126233 msecs;       small  0.000367 msecs

Analysis:

1.I found that when the array contains more elements, the quicksort is faster than insertion sort.
The difference between quicksort and insertion sort in the large case is the biggest.

2.However, when the size of array is small, for example only 10 elements, the insertion sort
will be even faster than quicksort. 

3.Insertion sort time complexity is O(n^2) and quicksort is O(nlogn)(average case).

(1)For insertion sort: O(n^2)  

so time and size^2 should be linear, time = c * size^2, where c is a instance. Becasue 

size(large)^2 : size(med)^2 :size(small)^2 = 1000000 ： 10000 ： 1

time(large) : time(med) : time(small) = 189089 : 1908 : 1

It is clear that time and size^n is linear and c = 0.19. So insertion sort matches expected time.

(2)For quicksort: O(nlogn)  

so time and size should be logarithmic, which means time and size*log(size) should be linear.
time = c * size*log(size)), where c is a instance. Becasue

size(large)*log(size(large)) : size(med)*log(size(med)) : size(small)*log(size(small)) = 4000 ： 300 ： 1

time(large) : time(med) : time(small) = 6492 : 344 : 1

It is clear that time and size*log(size) is linear and c is about 1.2. 
So quicksort matches expected time.

4.The hardest part in my assignment is how to calculate the running time in msecs.
I need to searched online to know which library and function I can use to calculate the execution time.

