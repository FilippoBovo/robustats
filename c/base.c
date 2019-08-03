#include <stdio.h>
#include <stdlib.h>
#include "base.h"

/**
 * Sum an array.
 * 
 * Arguments:
 *    x: Array.
 *    n: Length of the array.
 * 
 * Returns:
 *    Sum of the array of numbers.
 */
double sum(double *x, int n)
{
   double sum = 0;

   for (int i = 0; i < n; i++)
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
void swap(double *x, int i, int j)
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
void swap_2d(double **x, int n2, int i, int j)
{
   double temp;

   for (int k = 0; k < n2; k++)
   {
      temp = x[i][k];
      x[i][k] = x[j][k];
      x[j][k] = temp;
   }
}

/**
 * Compare two arrays by comparing their k-th element.
 * 
 * Arguments:
 *    i: First array.
 *    j: Second array.
 *    k: Element along the arrays to compare.
 * 
 * Returns:
 *    Difference of the k-th element between the first and second arrays.
 */
int compare_element_in_arrays(const void *i, const void *j, int k)
{
   double *a = *(double **)i;
   double *b = *(double **)j;

   return a[k] - b[k];
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
int random_range(int begin, int end)
{
   return begin + (int)(random_0_to_1() * (end - begin + 1));
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
double **zip(double *array_a, double *array_b, int n)
{
   double **zip_arr = (double**)malloc(n * sizeof(double*));

   for(int i = 0; i < n; i++) {
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
void free_zip_memory(double **zip_array, int n)
{
   for (int i = 0; i < n; i++)
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
int partition_on_value(double *x, int begin, int end, double value)
{
   int i = begin;
   int j = begin;

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
int partition_on_kth_element(double *x, int begin, int end, int k)
{
   double value = x[k];

   swap(x, k, end);

   int i = begin;
   for (int j = begin; j < end; j++)
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
int partition_on_kth_element_2d(double **x, int begin, int end, int n2, int m, int k)
{
   double value = x[k][m];

   swap_2d(x, n2, k, end);

   int i = begin;
   for (int j = begin; j < end; j++)
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
double partition_on_kth_smallest(double *x, int begin, int end, int k)
{
   while (1)
   {
      if (begin == end)
         return x[begin];

      int pivot_index = random_range(begin, end);
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
double partition_on_kth_smallest_2d(double **x, int begin, int end, int n2, int m, int k)
{
   while (1)
   {
      if (begin == end)
         return x[begin][m];

      int pivot_index = random_range(begin, end);
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
double select(double *x, int n, int k)
{
   double *x_copy = malloc(n * sizeof(double));
   for (int i = 0; i < n; i++)
   {
      x_copy[i] = x[i];
   }

   return partition_on_kth_smallest(x_copy, 0, n - 1, k);
}
