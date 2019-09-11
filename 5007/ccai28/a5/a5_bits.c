// chenxi cai 2019-2-22
#include<stdio.h>
#include "a5.h"

void displayBits(unsigned value) {
    unsigned c, displayMask = 1 << 15;

    printf("%3c%7u = ", value, value);

    for (c = 1; c <= 16; c++) {
        putchar(value & displayMask ? '1' : '0');
        value <<= 1;

        if (c % 8 == 0) {
            putchar(' ');
        }
     }
    putchar('\n');
}

unsigned int packCharacters(char a, char b) {
    unsigned c = a << 8;
    unsigned d = c | b;
    return d;
}

void unpackCharacters(unsigned int packedInt) {
        displayBits(packedInt);
        unsigned c, mask = 1;
        unsigned a, b = 0 << 15;
        for (c = 0; c <= 7; c++) {
            a = packedInt & mask ? 1 : 0;
            a <<= c;
            b = b | a;
            packedInt >>= 1;
        }
        displayBits(packedInt);
        displayBits(b);
}

int power2(int num, int pow) {
    unsigned a = num << pow;
    displayBits(a);
    return a;
}

int main(void) {
    int c = packCharacters('B', 'i');
    unpackCharacters(17001);
    int a = power2(66, 8);
}
