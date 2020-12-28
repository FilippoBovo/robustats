#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "base.h"

/**
 * Returns the higher of two numbers.
 * 
 * Arguments:
 *    a: First number.
 *    b: Second number.
 * 
 * Returns:
 *    Higher of the two numbers.
 */
double max_(double a, double b)
{
   if (a >= b)
      return a;
   else
      return b;
}

/**
 * Returns the sign of a number.
 * 
 * Arguments:
 *    x: Number.
 * 
 * Returns:
 *    Sign of the input number.
 */
double sign(double x)
{
   if (x > 0.0)
      return 1.0;
   else if (x < 0.0)
      return -1.0;
   else
      return 0.0;
}

/**
 * Sum an array of integers.
 * 
 * Arguments:
 *    x: Array of integers.
 *    n: Length of the array.
 * 
 * Returns:
 *    Sum of the array of integers.
 */
int64_t sum_int(int64_t *x, int64_t n)
{
   int64_t sum = 0;

   for (int64_t i = 0; i < n; i++)
      sum += x[i];

   return sum;
}

/**
 * Sum an array of doubles.
 * 
 * Arguments:
 *    x: Array of doubles.
 *    n: Length of the array.
 * 
 * Returns:
 *    Sum of the array of doubles.
 */
double sum_double(double *x, int64_t n)
{
   double sum = 0;

   for (int64_t i = 0; i < n; i++)
      sum += x[i];

   return sum;
}

/**
 * Swap two elements of an array in-place.
 * 
 * Arguments:
 *    x: Array.
 *    i: index of the first element to swap.
 *    j: index of the second element to swap.
 */
void swap(double *x, int64_t i, int64_t j)
{
   double temp = x[i];
   x[i] = x[j];
   x[j] = temp;
}

/**
 * Swap two columns of a 2D array.
 * 
 * For example, swapping the first and second columns of
 * {{1, 4}, {2, 5}, {3, 6}}
 * gives
 * {{2, 5}, {1, 4}, {3, 6}}
 * 
 * Arguments:
 *    x: 2D array.
 *    n2: Length of the 2D array along the second axis.
 *    i: First row of elements to swap.
 *    j: Second row of elements to swap.
 */
void swap_2d(double **x, int64_t n2, int64_t i, int64_t j)
{
   double temp;

   for (int64_t k = 0; k < n2; k++)
   {
      temp = x[i][k];
      x[i][k] = x[j][k];
      x[j][k] = temp;
   }
}

/**
 * Compare two elements of an array to be sorted ascendingly.
 * 
 * This function can to be used in combination with qsort to sort an array.
 * 
 * Arguments:
 *    i: First element of the array.
 *    j: Second element of the array.
 * 
 * Returns:
 *    Floor different between i-th and j-th elements of the array.
 */
int compare_ascending(const void *i, const void* j)
{
   double a = *(double *)i;
   double b = *(double *)j;

   if (a > b)
      return 1;
   else if (a < b)
      return -1;
   else
      return 0;
}

/**
 * Compare two elements of an array to be sorted descendingly.
 * 
 * This function can to be used in combination with qsort to sort an array.
 * 
 * Arguments:
 *    i: First element of the array.
 *    j: Second element of the array.
 * 
 * Returns:
 *    Floor different between j-th and i-th elements of the array.
 */
int compare_descending(const void *i, const void* j)
{
   double a = *(double *)i;
   double b = *(double *)j;

   if (a > b)
      return -1;
   else if (a < b)
      return 1;
   else
      return 0;
}

/**
 * Compare two elements of a 2D array to be sorted ascendingly in the first axis.
 * 
 * This function can be used in combination with qsort to sort a 2D array.
 * 
 * Arguments:
 *    i: First 1D array.
 *    j: Second 1D array.
 *    k: Element along the second axis of the array to compare.
 * 
 * Returns:
 *    Floor difference between the k-th element of the i-th and j-th 1D arrays.
 */
int compare_ascending_2d(const void *i, const void *j, int64_t k)
{
   double *a = *(double **)i;
   double *b = *(double **)j;

   if (a[k] > b[k])
      return 1;
   else if (a[k] < b[k])
      return -1;
   else
      return 0;
}

/**
 * Compare two elements of a 2D array to be sorted descendingly in the first axis.
 * 
 * This function can be used in combination with qsort to sort a 2D array.
 * 
 * Arguments:
 *    i: First 1D array.
 *    j: Second 1D array.
 *    k: Element along the second axis of the array to compare.
 * 
 * Returns:
 *    Floor difference between the k-th element of the j-th and i-th 1D arrays.
 */
int compare_descending_2d(const void *i, const void *j, int64_t k)
{
   double *a = *(double **)i;
   double *b = *(double **)j;

   if (a[k] > b[k])
      return -1;
   else if (a[k] < b[k])
      return 1;
   else
      return 0;
}

/**
 * Returns a random double in range [0, 1).
 */
double random_0_to_1()
{
   return (double)rand() / (double)RAND_MAX;
}

/**
 * Returns a random integer between 'begin' and 'end', extremes included.
 */
int64_t random_range(int64_t begin, int64_t end)
{
   return begin + (int64_t)(random_0_to_1() * (end - begin + 1));
}

/**
 * Fill an array of integers with a single value.
 * 
 * Arguments:
 *    x: Array.
 *    n: Length of the array.
 *    value: Value to fill the array with.
 */
void fill_array_int(int64_t *x, int64_t n, int64_t value)
{
   for (int64_t i = 0; i < n; i++)
      x[i] = value;
}

/**
 * Copy an array of integers into another array of integers.
 * 
 * Arguments:
 *    x: Array to copy.
 *    y: New copy array.
 *    n: Length of the arrays.
 */
void copy_array_int(int64_t *x, int64_t *y, int64_t n)
{
   for (int64_t i = 0; i < n; i++)
      y[i] = x[i];
}

/**
 * Zip two arrays of the same length.
 * 
 * Example:
 *    array_a = {1, 2, 3}
 *    array_b = {4, 5, 6}
 *    zipped_array = {{1, 4}, {2, 5}, {3, 6}}
 * 
 * Arguments:
 *    array_a: First array.
 *    array_b: Second array.
 *    n: Length of the array.
 * 
 * Returns:
 *    Zipped array.
 */
double **zip(double *array_a, double *array_b, int64_t n)
{
   double **zip_arr = (double**)malloc(n * sizeof(double*));

   for(int64_t i = 0; i < n; i++) {
      zip_arr[i] = (double*)malloc(2 * sizeof(double));
      zip_arr[i][0] = array_a[i];
      zip_arr[i][1] = array_b[i];
   }

   return zip_arr;
}

/**
 * Free the memory allocated the a zipped array.
 * 
 * Arguments:
 *    zip_arr: Zipped array obtained with function 'zip' above.
 *    n: Length of the zipped array.
 */
void free_zip_memory(double **zip_array, int64_t n)
{
   for (int64_t i = 0; i < n; i++)
      free(zip_array[i]);

   free(zip_array);
}

/**
 * Partition an array according to a value.
 * 
 * The partition function rearranges an array in-place into a region lower than
 * the value and a region greater than or equal to the value.
 * 
 * For example, partitioning
 * {6, 1, 2, 4, 3, 5, 3}
 * according to value 3 gives
 * {1, 2, 6, 4, 3, 5, 3}
 * and the function returns index 2 along the array.
 * 
 * Arguments:
 *    x: Array.
 *    begin: Index where to begin partitioning.
 *    end: Index where to end partitioning.
 *    value: Value of the pivot around which to partition the array.
 * 
 * Returns:
 *    Starting index of the region greater than or equal to the pivot.
 */
int64_t partition_on_value(double *x, int64_t begin, int64_t end, double value)
{
   int64_t i = begin;
   int64_t j = begin;

   while (i <= end)
   {
      if (x[i] < value)
      {
         swap(x, j, i);
         j++;
      }

      i++;
   }

   return j;
}

/**
 * Partition an array around a pivot given by its k-th element.
 * 
 * The partition function rearranges an array in-place into a region lower than
 * the pivot value and a region greater than the pivot value, separated by the
 * pivot.
 * 
 * For example, partitioning
 * {6, 1, 2, 4, 3, 5, 3}
 * according to value of the 4-th element, which is 3, gives
 * {1, 2, 3, 4, 3, 5, 6}
 * and the function returns index 2 along the array.
 * 
 * Arguments:
 *    x: Array.
 *    begin: Index where to begin partitioning.
 *    end: Index where to end partitioning.
 *    k: Position in the array of the element to use as a pivot around which to
 *       partition the array.
 * 
 * Returns:
 *    Index of the pivot, separating the lower and the higher regions.
 */
int64_t partition_on_kth_element(double *x, int64_t begin, int64_t end, int64_t k)
{
   double value = x[k];

   swap(x, k, end);

   int64_t i = begin;
   for (int64_t j = begin; j < end; j++)
   {
      if (x[j] < value)
      {
         swap(x, i, j);
         i++;
      }
   }

   swap(x, i, end);

   return i;
}

/**
 * Partition a 2D array around a pivot given by its k-th element.
 * 
 * The partition function rearranges an array in-place into a region lower than
 * the pivot value and a region greater than the pivot value, separated by the
 * pivot.
 * 
 * For example, partitioning
 * {{6, 0}, {1, 1}, {2, 2}, {4, 3}, {3, 4}, {5, 5}, {3, 6}}
 * according to value of the 4-th element, which is {3, 4}, gives
 * {{1, 1}, {2, 2}, {3, 4}, {4, 3}, {3, 6}, {5, 5}, {6, 0}}
 * and the function returns index 2 along the array.
 * 
 * Arguments:
 *    x: 2D array.
 *    begin: Index along the first axis where to begin partitioning.
 *    end: Index along the first axis where to end partitioning.
 *    m: Position along the columns (second axis) of the array over which to
 *       carry out the partition.
 *    n2: Length of the array along the second axis.
 *    k: Position along the first axis of the array of the element to use as a
 *       pivot around which to partition the array.
 * 
 * Returns:
 *    Index of the pivot, separating the lower and the higher regions.
 */
int64_t partition_on_kth_element_2d(double **x, int64_t begin, int64_t end, int64_t n2, int64_t m, int64_t k)
{
   double value = x[k][m];

   swap_2d(x, n2, k, end);

   int64_t i = begin;
   for (int64_t j = begin; j < end; j++)
   {
      if (x[j][m] < value)
      {
         swap_2d(x, n2, i, j);
         i++;
      }
   }

   swap_2d(x, n2, i, end);

   return i;
}

/**
 * Partition an array around a pivot given by its k-th smallest element.
 * 
 * This function returns the value of the k-th smallest element.
 * 
 * The partition function rearranges an array in-place into a region lower than
 * the pivot value and a region greater than the pivot value, separated by the
 * pivot.
 * 
 * For example, partitioning
 * {6, 1, 2, 4, 3, 5, 3}
 * according to value of the 5-th smallest element gives
 * {1, 2, 3, 4, 3, 5, 6}
 * and the function returns 5, which is the pivot and the 5-th smallest element.
 * 
 * Arguments:
 *    x: Array.
 *    begin: Index where to begin partitioning.
 *    end: Index where to end partitioning.
 *    k: Number denoting the k-th smallest element.
 * 
 * Returns:
 *    Value of the pivot, separating the lower and the higher regions. The
 *       pivot is the k-th smallest element of the array.
 */
double partition_on_kth_smallest(double *x, int64_t begin, int64_t end, int64_t k)
{
   while (1)
   {
      if (begin == end)
         return x[begin];

      int64_t pivot_index = random_range(begin, end);
      pivot_index = partition_on_kth_element(x, begin, end, pivot_index);

      if (k == pivot_index)
         return x[k];
      else if (k < pivot_index)
         end = pivot_index - 1;
      else
         begin = pivot_index + 1; 
   }
}

/**
 * Partition an array around a pivot given by its k-th smallest element.
 * 
 * This function returns the value of the k-th smallest element.
 * 
 * The partition function rearranges an array in-place into a region lower than
 * the pivot value and a region greater than the pivot value, separated by the
 * pivot.
 * 
 * For example, partitioning
 * {6, 1, 2, 4, 3, 5, 3}
 * according to value of the 5-th smallest element gives
 * {1, 2, 3, 4, 3, 5, 6}
 * and the function returns 5, which is the pivot and the 5-th smallest element.
 * 
 * Arguments:
 *    x: 2D array.
 *    n1: Length of the array along the first axis.
 *    n2: Length of the array along the second axis.
 *    begin: Index along the first axis where to begin partitioning.
 *    end: Index along the first axis where to end partitioning.
 *    m: Position along the columns (second axis) of the array over which to
 *       carry out the partition.
 *    k: Number denoting the k-th smallest element along the m-th row.
 * 
 * Returns:
 *    Value of the pivot, separating the lower and the higher regions. The
 *       pivot is the k-th smallest element of the m-th row of the array.
 */
double partition_on_kth_smallest_2d(double **x, int64_t begin, int64_t end, int64_t n2, int64_t m, int64_t k)
{
   while (1)
   {
      if (begin == end)
         return x[begin][m];

      int64_t pivot_index = random_range(begin, end);
      pivot_index = partition_on_kth_element_2d(x, begin, end, n2, m, pivot_index);

      if (k == pivot_index)
         return x[k][m];
      else if (k < pivot_index)
         end = pivot_index - 1;
      else
         begin = pivot_index + 1;
   }
}

/**
 * Select the k-th smallest element from an array.
 * 
 * Arguments:
 *    x: Array.
 *    n: Length of the array.
 *    k: Number of the smallest element to look for in the array.
 * 
 * Returns:
 *    K-th smallest element of the array.
 */
double select_kth_smallest(double *x, int64_t n, int64_t k)
{
   double *x_copy = malloc(n * sizeof(double));
   for (int64_t i = 0; i < n; i++)
   {
      x_copy[i] = x[i];
   }

   double kth_smallest = partition_on_kth_smallest(x_copy, 0, n - 1, k);
   free(x_copy);

   return kth_smallest;
}
