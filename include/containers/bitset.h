/*
 * bitset.h
 *
 */

#ifndef INCLUDE_CONTAINERS_BITSET_H_
#define INCLUDE_CONTAINERS_BITSET_H_

#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h>

//#define USEAVX  now controlled by makefile

#ifdef USEAVX
#define ALIGN_AVX __attribute__((aligned(sizeof(__m256i))))
#else
#define ALIGN_AVX
#endif

enum { BITSET_CONTAINER_SIZE_IN_WORDS = (1 << 16) / 64 };

struct bitset_container_s {
    int32_t cardinality;
    uint64_t *array;
};

typedef struct bitset_container_s bitset_container_t;

/* Create a new bitset. Return NULL in case of failure. */
bitset_container_t *bitset_container_create();

/* Free memory. */
void bitset_container_free(bitset_container_t *bitset);

/* Set the bit at position `pos'.  */
void bitset_container_set(bitset_container_t *bitset, uint16_t pos);

/* Set the bit at position `pos'.  */
void bitset_container_unset(bitset_container_t *bitset, uint16_t pos);

/* Get the value of bit at position `pos'.  */
bool bitset_container_get(const bitset_container_t *bitset, uint16_t pos);

/* Get the number of bits set */
static inline int bitset_container_cardinality(bitset_container_t *bitset) {
    return bitset->cardinality;
}

/* Get the number of bits set (force computation) */
int bitset_container_compute_cardinality(const bitset_container_t *bitset);

/* Computes the union of bitsets `src_1' and `src_2' into `dst'. */
int bitset_container_or(const bitset_container_t *src_1,
                        const bitset_container_t *src_2,
                        bitset_container_t *dst);

/* Computes the union of bitsets `src_1' and `src_2' into `dst', but does not
 * update the cardinality. Provided to optimize chained operations. */
int bitset_container_or_nocard(const bitset_container_t *src_1,
                               const bitset_container_t *src_2,
                               bitset_container_t *dst);

/* Computes the intersection of bitsets `src_1' and `src_2' into `dst'. */
int bitset_container_and(const bitset_container_t *src_1,
                         const bitset_container_t *src_2,
                         bitset_container_t *dst);

/* Computes the intersection of bitsets `src_1' and `src_2' into `dst', but does
 * not update the cardinality. Provided to optimize chained operations. */
int bitset_container_and_nocard(const bitset_container_t *src_1,
                                const bitset_container_t *src_2,
                                bitset_container_t *dst);

/* Computes the exclusive or of bitsets `src_1' and `src_2' into `dst'. */
int bitset_container_xor(const bitset_container_t *src_1,
                         const bitset_container_t *src_2,
                         bitset_container_t *dst);

/* Computes the exclusive or of bitsets `src_1' and `src_2' into `dst', but does
 * not update the cardinality. Provided to optimize chained operations. */
int bitset_container_xor_nocard(const bitset_container_t *src_1,
                                const bitset_container_t *src_2,
                                bitset_container_t *dst);

/* Computes the and not of bitsets `src_1' and `src_2' into `dst'. */
int bitset_container_andnot(const bitset_container_t *src_1,
                            const bitset_container_t *src_2,
                            bitset_container_t *dst);

/* Computes the and not or of bitsets `src_1' and `src_2' into `dst', but does
 * not update the cardinality. Provided to optimize chained operations. */
int bitset_container_andnot_nocard(const bitset_container_t *src_1,
                                   const bitset_container_t *src_2,
                                   bitset_container_t *dst);

#endif /* INCLUDE_CONTAINERS_BITSET_H_ */
