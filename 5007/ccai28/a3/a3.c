#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<ctype.h>
#include "a3.h"


// YOUR CODE GOES HERE
char* convertName(char* part) {
    int len = strlen(part) + 1;
    char *temp = malloc(sizeof(part));
    temp[0] = toupper(part[0]);
    temp[len - 1] = '\0';

    for (int i = 1; i < len - 1; i++) {
        temp[i] = tolower(part[i]);
    }
    return temp;
}

void big(Name *name) {
    name-> first = convertName(name->first);
    name->last = convertName(name->last);
    if (name->middle == NULL) {
       printf("%s %s", name->first,  name->last);
    } else {
         name->middle = convertName(name->middle);
         printf("%s %s %s", name->first, name->middle, name->last);
    }
}

void last(Name *name) {
    printf("%s, %s", name->last, name->first);
}

void reg(Name *name) {
    printf("%s %s", name->first, name->last);
}

void mid(Name *name) {
    if (name->middle == NULL) {
        printf("%s %s", name->first,  name->last);
    } else {
       printf("%s %c. %s", name->first, *(name->middle), name->last);
    }
}

void small(Name *name) {
    printf("%s", name->first);
}

void formatName(Name *name, char format) {
    switch (toupper(format)) {
        case 'B' :
            big(name);
            break;
        case 'L' :
            last(name);
            break;
        case 'R' :
            reg(name);
            break;
        case 'M' :
            mid(name);
            break;
        case 'S' :
            small(name);
            break;
    }
}

void fillName(Name *name, char format, char *dest) {
    switch (toupper(format)) {
        case 'B' :
            strcpy(dest, name->first);
            if (name->middle != NULL) {
               strcat(dest, name->middle);
            }
            strcat(dest, name->last);
            break;
        case 'L' :
            strcpy(dest, name->last);
            strcat(dest, name->first);
            break;
        case 'R' :
            strcpy(dest, name->first);
            strcat(dest, name->last);
            break;
        case 'M' :
            strcpy(dest, name->first);
            if (name->middle != NULL) {
               char tmp[3] = {*(name->middle), '.', '\0'};
               strcat(dest, tmp);
            }
            strcat(dest, name->last);
            break;
        case 'S' :
            strcpy(dest, name->first);
            break;
    }
}

void listByName(Name *n1, Name *n2, Name *n3, char format) {
    char a1, a2, a3, a4;
    Name *n4;
    if (toupper(format) == 'L') {
        a1 = toupper(*(n1->last));
        a2 = toupper(*(n2->last));
        a3 = toupper(*(n3->last));
    } else {
         a1 = toupper(*(n1->first));
         a2 = toupper(*(n2->first));
         a3 = toupper(*(n3->first));
    }
    if (a1 > a2) {
       a4 = a2;
       a2 = a1;
       a1 = a4;
       n4 = n2;
       n2 = n1;
       n1 = n4;
    }
    if (a2 > a3) {
       a4 = a3;
       a3 = a2;
       a2 = a4;
       n4 = n3;
       n3 = n2;
       n2 = n4;
    }
    if (a1 > a2) {
       a4 = a2;
       a2 = a1;
       a1 = a4;
       n4 = n2;
       n2 = n1;
       n1 = n4;
    }
    switch (toupper(format)) {
       case 'B' :
          big(n1);
          printf("\n");
          big(n2);
          printf("\n");
          big(n3);
          break;
       case 'L' :
          last(n1);
          printf("\n");
          last(n2);
          printf("\n");
          last(n3);
          break;
       case 'R' :
          reg(n1);
          printf("\n");
          reg(n2);
          printf("\n");
          reg(n3);
          break;
       case 'M' :
          mid(n1);
          printf("\n");
          mid(n2);
          printf("\n");
          mid(n3);
          break;
       case 'S' :
          small(n1);
          printf("\n");
          small(n2);
          printf("\n");
          small(n3);
          break;
    }
}

void swap(Name** a, Name** b) {
     Name* temp = *a;
     *a = *b;
     *b = temp;
}
int partition(Name* arr[], int p, int r) {
    int pivot = arr[r]->age;
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (arr[j]->age >= pivot) {
           i++;
           swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);
    return (i + 1);
}
void quickSort(Name* arr[], int p, int r) {
     if (p < r) {
        int pi = partition(arr, p, r);
        quickSort(arr, p, pi - 1);
        quickSort(arr, pi + 1, r);
     }
}
void listByAge(Name* names[], int numNames, char format) {
    quickSort(names, 0, numNames - 1);
    for (int i = 0; i < numNames; i++) {
        switch (toupper(format)) {
          case 'B' :
             big(names[i]);
             printf("       %d\n", names[i]->age);
             break;
          case 'L' :
             last(names[i]);
             printf("       %d\n", names[i]->age);
             break;
          case 'R' :
             reg(names[i]);
             printf("       %d\n", names[i]->age);
             break;
          case 'M' :
             mid(names[i]);
             printf("       %d\n", names[i]->age);
             break;
          case 'S' :
             small(names[i]);
             printf("       %d\n", names[i]->age);
             break;
       }
    }
}
