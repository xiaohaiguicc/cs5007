#include<stdio.h>
void NumPtrExample() {
    int num;
int* numPtr;
    num = 42;
    numPtr = &num;  // Compute a reference to "num", and store it in numPtr
    // At this point, memory looks like drawing above
    printf("numPtr = %p\n", numPtr);
}
void PointerTest() {
    // allocate three integers and two pointers
    int a = 1;
    int b = 2;
    int c = 3;
    int* p;
    int* q;
    p = &a;
    q = &b;
    c = *p;
    printf("c = %d\n", c);
    p = q;
    *p = 13;
    printf("b = %d\n", b);
}
// local vars
void B(int worth) {
    worth = worth + 1;  // T2
}
void A() {
    int netWorth;
    netWorth = 55;  // T1
    B(netWorth);
    printf("Pass by value: netWorth = %d\n", netWorth);
}
// T3 -- B() did not change netWorth


// B() now uses a reference parameter -- a pointer to
// the value of  interest. B() uses a dereference (*) on the
// reference parameter to get at the value of interest.
void Bref(int* worthRef) {       // reference parameter
    *worthRef = *worthRef + 1;  // use * to get at value of interest
}
void Aref() {
    int netWorth;
    netWorth = 55;  // T1 -- the value of interest is local to A()
    Bref(&netWorth);  // Pass a pointer to the value of interest.
                   // In this case using &.
    printf("Pass by reference: netWorth = %d\n", netWorth);
}

void Swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void SwapCaller() {
    int x = 1;
    int y = 2;
    Swap(&x, &y);  // Use & to pass pointers to the int values of interest
                  //  (x and y).
    printf("After swap: x = %d, y = %d\n", x, y);
}

void SwapCaller2() {
    int scores[10];
    scores[0] = 1;
    scores[9] = 2;
    Swap(&(scores[0]), &(scores[9]));
    printf("After swap: scores[0] = %d, scores[9] = %d\n",
        scores[0], scores[9]);
}

int main() {
    NumPtrExample();
    PointerTest();
    A();
    Aref();
    SwapCaller();
    SwapCaller2();
    return 0;
}
