#include <stddef.h>

/**
 * @brief Performs binary search on a sorted array of elements.
 *
 * Searches for the element pointed to by @p target in the sorted array @p sorted,
 * using binary search. The array must contain @p size elements, each of size @p esize bytes.
 * The comparison between elements is performed using the user-provided function @p compare.
 *
 * The comparison function must match the following signature:
 * @code
 * int compare(const void* key1, const void* key2);
 * @endcode
 * and return:
 * - `1` if @p key1 is greater than @p key2
 * - `0` if @p key1 is equal to @p key2
 * - `-1` if @p key1 is less than @p key2
 *
 * @param[in] sorted Pointer to the sorted array to search.
 * @param[in] target Pointer to the element to search for.
 * @param[in] size Number of elements in the array.
 * @param[in] esize Size of each element in bytes.
 * @param[in] compare Comparison function used to determine the order.
 *
 * @return The index of the matching element if found; otherwise, returns @p size.
 *
 * @complexity Time complexity: O(log n), where n is the number of elements.
 */

size_t bisearch(
    const void *sorted,
    const void *target,
    const size_t size,
    const size_t esize,
    int (*compare)(const void *key1, const void *key2));
