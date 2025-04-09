#pragma once

/*
 * @brief Sorts array of elements using insertion sort.
 *
 * Uses insertion sort to sort the array of elements in *data*.
 * The number of elements in *data* is specified by *size*.
 * The size of each element is specified by *esize*.
 * The function pointer *compare* specifies a user-defined
 * function to compare elements.
 * This function should return 1 if *key1* > *key2*, 0 if *key1* == *key2*,
 * and –1 if *key1* < *key2* for an ascending sort.
 * For a descending sort, compare should reverse the cases returning 1 and –1.
 *
 * @param[in, out] data Array of elements to sort.
 * @param[in] size Number of elements in *data*
 * @param[in] esize Size of a single element.
 * @param[in] compare User-defined function to compare elements and determine their order.
 *
 * * The comparison function must follow the signature:
 * ```
 * int compare(const void* key1, const void* key2);
 * ```
 * and return:
 * - `1` if `key1 > key2`
 * - `0` if `key1 == key2`
 * - `-1` if `key1 < key2`
 *
 * For a descending sort, the `compare` function should return:
 * - `1` if `key1 < key2`
 * - `0` if `key1 == key2`
 * - `-1` if `key1 > key2`
 *
 * When the function returns, `data` contains the elements sorted in the specified order.
 *
 * @complexity Best case: O(n), Average and Worst case: O(n^2).
 */

int dsa_issort(
    void *data,
    const int size,
    const int esize,
    int (*compare)(const void *key1, const void *key2));

