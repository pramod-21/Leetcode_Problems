#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    int *mem;
} Allocator;

Allocator* allocatorCreate(int n) {
    Allocator *obj = malloc(sizeof(Allocator));
    obj->n = n;
    obj->mem = calloc(n, sizeof(int));
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int count = 0;
    for (int i = 0; i < obj->n; i++) {
        if (obj->mem[i] == 0) {
            count++;
        } else {
            count = 0;
        }

        if (count == size) {
            int start = i - size + 1;
            for (int j = start; j <= i; j++) {
                obj->mem[j] = mID;
            }
            return start;
        }
    }
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int freed = 0;
    for (int i = 0; i < obj->n; i++) {
        if (obj->mem[i] == mID) {
            obj->mem[i] = 0;
            freed++;
        }
    }
    return freed;
}

void allocatorFree(Allocator* obj) {
    if (!obj) return;
    free(obj->mem);
    free(obj);
}