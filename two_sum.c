/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

// structure to hold value + original index
typedef struct {
    int value;
    int index;
} Pair;

// comparator for qsort
int cmp(const void* a, const void* b) {
    return ((Pair*)a)->value - ((Pair*)b)->value;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* res = (int*)malloc(2 * sizeof(int));

    // create array of pairs
    Pair* arr = (Pair*)malloc(numsSize * sizeof(Pair));
    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].index = i;
    }

    // sort by value
    qsort(arr, numsSize, sizeof(Pair), cmp);

    // two-pointer search
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = arr[left].value + arr[right].value;
        if (sum == target) {
            res[0] = arr[left].index;
            res[1] = arr[right].index;
            free(arr);
            return res;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    free(arr);
    return NULL; // should never happen (guaranteed one solution)
}
