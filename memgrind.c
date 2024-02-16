#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "mymalloc.h"

#define NUM_ITERATIONS 50
#define NUM_ALLOCATIONS 120

long long getCurrentTime() {
    LARGE_INTEGER freq, count;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&count);
    return (1000000LL * count.QuadPart) / freq.QuadPart;
}

void test1() {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (int j = 0; j < NUM_ALLOCATIONS; j++) {
            char* ptr = (char*)malloc(1);
            free(ptr);
        }
    }
}

void test2() {
    char* pointers[NUM_ALLOCATIONS];
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (int j = 0; j < NUM_ALLOCATIONS; j++) {
            pointers[j] = (char*)malloc(1);
        }
        for (int j = 0; j < NUM_ALLOCATIONS; j++) {
            free(pointers[j]);
        }
    }
}

void test3() {
    char* pointers[NUM_ALLOCATIONS];
    int count = 0;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        while (count < NUM_ALLOCATIONS) {
            int action = rand() % 2;
            if (action == 0 && count < NUM_ALLOCATIONS) {
                pointers[count++] = (char*)malloc(1);
            }
            else if (count > 0) {
                free(pointers[--count]);
            }
        }

        while (count > 0) {
            free(pointers[--count]);
        }
    }
}

void test4() {
    char* pointers[NUM_ALLOCATIONS / 2];
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (int j = 0; j < NUM_ALLOCATIONS / 2; j++) {
            pointers[j] = (char*)malloc((j % 4) + 1);
        }
        for (int j = 0; j < NUM_ALLOCATIONS / 2; j++) {
            if (j % 2 == 0) {
                free(pointers[j]);
            }
        }
        for (int j = 0; j < NUM_ALLOCATIONS / 2; j++) {
            if (j % 2 != 0) {
                free(pointers[j]);
            }
        }
    }
}

void test5() {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (int j = 0; j < NUM_ALLOCATIONS * 2; j++) {
            char* ptr = (char*)malloc((rand() % 10) + 1);
            if (ptr) {
                free(ptr);
            }
        }
    }
}

int main() {
    long long startTime, endTime, timeDiff;

    // Test 1
    startTime = getCurrentTime();
    test1();
    endTime = getCurrentTime();
    timeDiff = endTime - startTime;
    printf("Test 1 completed in %lld microseconds.\n", timeDiff);

    // Test 2
    startTime = getCurrentTime();
    test2();
    endTime = getCurrentTime();
    timeDiff = endTime - startTime;
    printf("Test 2 completed in %lld microseconds.\n", timeDiff);

    // Test 3
    startTime = getCurrentTime();
    test3();
    endTime = getCurrentTime();
    timeDiff = endTime - startTime;
    printf("Test 3 completed in %lld microseconds.\n", timeDiff);

    // Test 4
    startTime = getCurrentTime();
    test4();
    endTime = getCurrentTime();
    timeDiff = endTime - startTime;
    printf("Test 4 completed in %lld microseconds.\n", timeDiff);

    // Test 5
    startTime = getCurrentTime();
    test5();
    endTime = getCurrentTime();
    timeDiff = endTime - startTime;
    printf("Test 5 completed in %lld microseconds.\n", timeDiff);

    printf("All tests completed.\n");

    return 0;
}

