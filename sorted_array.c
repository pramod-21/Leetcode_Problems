

#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

// Fenwick Tree (BIT)
int* fenwick;
int MAXVAL = 100000; // constraint: values <= 1e5

void update(int idx, int val) {
    while (idx <= MAXVAL) {
        fenwick[idx] += val;
        idx += idx & -idx;
    }
}

int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += fenwick[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int createSortedArray(int* instructions, int instructionsSize) {
    fenwick = (int*)calloc(MAXVAL + 2, sizeof(int));
    long long cost = 0;

    for (int i = 0; i < instructionsSize; i++) {
        int num = instructions[i];
        int left = query(num - 1);                 // count < num
        int right = query(MAXVAL) - query(num);    // count > num

        cost = (cost + (left < right ? left : right)) % MOD;

        update(num, 1); // insert into BIT
    }

    free(fenwick);
    return (int)cost;
}


