/*
 * array_container_unit.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "containers/array.h"
#include "benchmark.h"

enum{TESTSIZE=2048};

int add_test(array_container_t* B) {
    int x;
    for (x = 0; x < TESTSIZE*3; x += 3) {
        array_container_add(B, (uint16_t)x);
    }
    return 0;
}

int remove_test(array_container_t* B) {
    int x;
    for (x = 0; x < TESTSIZE*3; x += 3) {
        array_container_remove(B, (uint16_t)x);
    }
    return 0;
}
int contains_test(array_container_t* B) {
    int card = 0;
    int x;
    for (x = 0; x < TESTSIZE*3; x++) {
        card += array_container_contains(B, (uint16_t)x);
    }
    return card;
}

int union_test(array_container_t* B1, array_container_t* B2, array_container_t* BO) {
	array_container_union(B1, B2, BO);
	return BO->cardinality;
}

int intersection_test(array_container_t* B1, array_container_t* B2, array_container_t* BO) {
	array_container_intersection(B1, B2, BO);
	return BO->cardinality;
}
int main() {
    int repeat = 5000;
    int size = TESTSIZE;
    tellmeall();
    printf("array container benchmarks\n");
    array_container_t* B = array_container_create();
    BEST_TIME(add_test(B), 0, repeat, size);
    int answer = contains_test(B);
    size = 1 << 16;
    BEST_TIME(contains_test(B), answer, repeat, size);

    size = (1 << 16) / 3;
    BEST_TIME(remove_test(B), 0, repeat, size);
    array_container_free(B);

    array_container_t* B1 = array_container_create();
    for (int x = 0; x < 1 << 16; x += 3) {
        array_container_add(B1, (uint16_t)x);
    }
    array_container_t* B2 = array_container_create();
    for (int x = 0; x < 1 << 16; x += 5) {
        array_container_add(B2, (uint16_t)x);
    }
    int32_t inputsize = B1->cardinality + B2->cardinality;
    array_container_t* BO = array_container_create();
    printf("union and intersection times are expressed in cycles per number of input elements (both arrays)");
    answer = union_test(B1, B2, BO);
    BEST_TIME(union_test(B1, B2, BO), answer, repeat,
    		inputsize);
    answer = intersection_test(B1, B2, BO);
    BEST_TIME(intersection_test(B1, B2, BO), answer, repeat,
    		inputsize);

    return 0;
}
