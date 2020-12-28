#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "base.h"
#include "robustats.h"

/**
 * Weighted median.
 * 
 * For arrays with an even number of elements, this function calculates the
 * lower weighted median.
 * 
 * Arguments:
 *    x: array of values
 *    w: array of weights
 *    begin: Beginning index of the sub-array over which to calculate the
 *       weighted median.
 *    end: Ending index of the sub-array over which to calculate the weighted
 *       median.
 * 
 * Returns:
 *    Weighted median.
*/
double weighted_median(double *x, double *w, int64_t begin, int64_t end)
{
   int64_t xw_n, n, i, median_index;
   double median;
   double w_lower_sum, w_lower_sum_norm, w_higher_sum, w_higher_sum_norm;
   
   xw_n = end - begin + 1;  // Length between begin and end
   double **xw = zip(x, w, xw_n);

   double w_sum = sum_double(w, xw_n);

   while (1)
   {
      n = end - begin + 1; // Length between begin and end

      if (n == 1)
      {
         free_zip_memory(xw, xw_n);
         return x[begin];
      }
      else if (n == 2)
      {
         free_zip_memory(xw, xw_n);
         if (w[begin] >= w[end])
            return x[begin];
         else
            return x[end];
      }
      else
      {
         median_index = begin + (n - 1) / 2;  // Lower median index
         median = partition_on_kth_smallest_2d(xw, begin, end, 2, 0, median_index);

         w_lower_sum = 0.;
         for (i = begin; i < median_index; i++)
            w_lower_sum += xw[i][1];
         w_lower_sum_norm = w_lower_sum / w_sum;

         w_higher_sum = 0.;
         for (i = median_index + 1; i <= end; i++)
            w_higher_sum += xw[i][1];
         w_higher_sum_norm = w_higher_sum / w_sum;
         
         if (w_lower_sum_norm < 0.5 && w_higher_sum_norm < 0.5)
         {
            free_zip_memory(xw, xw_n);
            return median;
         }
         else if (w_lower_sum_norm > 0.5)
         {
            xw[median_index][1] = xw[median_index][1] + w_higher_sum;
            end = median_index;
         }
         else
         {
            xw[median_index][1] = xw[median_index][1] + w_lower_sum;
            begin = median_index;
         }
      }
   }
}

/**
 * Function used in function 'medcouple'.
 */
double h_kernel(
   int64_t i, int64_t j, double *z_plus, int64_t n_plus, double *z_minus, int64_t n_minus,
   double epsilon
   )
{
   double a = z_plus[i];
   double b = z_minus[j];

   if (fabs(a - b) <= 2 * epsilon)
      return sign(n_plus - i - j - 1);
   else
      return (a + b) / (a - b);
}

/**
 * Function used in function 'medcouple'.
 */
void where_h_greater_than_u(
   int64_t *p, int64_t n_p, double *z_plus, int64_t n_plus, double *z_minus, int64_t n_minus,
   double u, double epsilon, double k_epsilon
   )
{
   fill_array_int(p, n_p, 0);

   double h;
   int64_t j = 0;

   for (int64_t i = n_plus - 1; i >= 0; i--)
   {  
      h = h_kernel(i, j, z_plus, n_plus, z_minus, n_minus, k_epsilon);

      while (j < n_minus && h - u > epsilon)
      {
         j++;
         h = h_kernel(i, j, z_plus, n_plus, z_minus, n_minus, k_epsilon);
      }
      
      p[i] = j - 1;
   }
}

/**
 * Function used in function 'medcouple'.
 */
void where_h_less_than_u(
   int64_t *q, int64_t n_q, double *z_plus, int64_t n_plus, double *z_minus, int64_t n_minus,
   double u, double epsilon, double k_epsilon
   )
{
   fill_array_int(q, n_q, 0);

   double h;
   int64_t j = n_minus - 1;

   for (int64_t i = 0; i < n_plus; i++)
   {  
      h = h_kernel(i, j, z_plus, n_plus, z_minus, n_minus, k_epsilon);

      while (j >= 0 && h - u < -epsilon)
      {
         j--;
         h = h_kernel(i, j, z_plus, n_plus, z_minus, n_minus, k_epsilon);
      }
      
      q[i] = j + 1;
   }
}

/**
 * Medcouple.
 * 
 * Arguments:
 *    x: Array.
 *    n: Length of the array.
 *    epsilon1: Machine epsilon. The smallest representable positive number
 *       such that 1.0 + epsilon != 1.0.
 *    epsilon2: The smallest representable number.
 * 
 * Returns:
 *    Medcouple.
 */
double medcouple(double *x, int64_t n, double epsilon1, double epsilon2)
{
   int64_t i, j;

   if (n < 3)
      return 0.;
   
   // Sort x descendingly
   qsort(x, n, sizeof(double), compare_descending);

   int64_t median_index = n / 2;  // Lower median because sorted descendingly
   double median = x[median_index];

   // Check if the median is at the edges up to relative epsilon
   if (fabs(x[0] - median) < epsilon1 * (epsilon1 + fabs(median)))
      return -1.0;
   if (fabs(x[n - 1] - median) < epsilon1 * (epsilon1 + fabs(median)))
      return 1.0;

   // To rescale z_minus and z_plus inside [-0.5, 0.5], for greater numerical
   // stability.
   double scale_factor = 2 * max_(x[0] - median, median - x[n - 1]);

   // Create z_plus
   int64_t lowest_median_index = median_index;
   double lowest_median = median;
   while(lowest_median == median)
   {
      lowest_median_index++;
      lowest_median = x[lowest_median_index];
   }
   lowest_median_index--;
   int64_t n_plus = lowest_median_index + 1;
   double *z_plus = malloc(n_plus * sizeof(double));
   for (i = 0; i < n_plus; i++)
      z_plus[i] = (x[i] - median) / scale_factor;
   
   // Create z_minus
   int64_t highest_median_index = median_index;
   double highest_median = median;
   while(highest_median == median)
   {
      highest_median_index--;
      highest_median = x[highest_median_index];
   }
   highest_median_index++;
   int64_t n_minus = n - highest_median_index;
   double *z_minus = malloc(n_minus * sizeof(double));
   for (i = 0; i < n_minus; i++)
      z_minus[i] = (x[highest_median_index + i] - median) / scale_factor;
   
   int64_t *left_border = malloc(n_plus * sizeof(int64_t));
   fill_array_int(left_border, n_plus, 0);
   
   int64_t *right_border = malloc(n_plus * sizeof(int64_t));
   fill_array_int(right_border, n_plus, n_minus - 1);

   // Number of entries to the left of the left border
   int64_t left_total = 0;

   // Number of entries to the left of the right boundary
   int64_t right_total = n_minus * n_plus;

   int64_t medcouple_index = right_total / 2;

   // Iterate while the number of entries between the boundaries is greater
   // than the number of rows in the matrix
   int64_t mid_border;
   int64_t right_tent_total, left_tent_total;
   double *row_medians = malloc(n_plus * sizeof(double));
   double *weights = malloc(n_plus * sizeof(double));
   double w_median, wm_epsilon;
   int64_t *left_border_tent = malloc(n_plus * sizeof(int64_t));  // Tentative border
   int64_t *right_border_tent = malloc(n_plus * sizeof(int64_t));  // Tentative border
   while (right_total - left_total > n_plus)
   {
      int64_t n_middle_indices = 0;
      for (i = 0; i < n_plus; i++)
         if (left_border[i] <= right_border[i])
            n_middle_indices++;
      
      j = 0;
      for (i = 0; i < n_plus; i++)
         if (left_border[i] <= right_border[i])
         {
            mid_border = (left_border[i] + right_border[i]) / 2;
            row_medians[j] = h_kernel(
               i, mid_border, z_plus, n_plus, z_minus, n_minus, epsilon2);
            weights[j] = right_border[i] - left_border[i] + 1;
            j++;
         }

      w_median = weighted_median(
         row_medians, weights, 0, n_middle_indices - 1);

      // New tentative right and left boundaries
      wm_epsilon = epsilon1 * (epsilon1 + fabs(w_median));
      where_h_greater_than_u(
         right_border_tent, n_plus, z_plus, n_plus, z_minus, n_minus, w_median,
         wm_epsilon, epsilon2);
      where_h_less_than_u(
         left_border_tent, n_plus, z_plus, n_plus, z_minus, n_minus, w_median,
         wm_epsilon, epsilon2);

      right_tent_total = sum_int(right_border_tent, n_plus) + n_plus;
      left_tent_total = sum_int(left_border_tent, n_plus);

      if (medcouple_index <= right_tent_total - 1)
      {
         copy_array_int(right_border_tent, right_border, n_plus);
         right_total = right_tent_total;
      }
      else
      {
         if (medcouple_index > left_tent_total - 1)
         {
            copy_array_int(left_border_tent, left_border, n_plus);
            left_total = left_tent_total;
         }
         else
         {
            free(row_medians);
            free(weights);
            free(right_border_tent);
            free(left_border_tent);
            free(z_minus);
            free(z_plus);
            free(left_border);
            free(right_border);

            return w_median;
         }
      }
   }
   free(row_medians);
   free(weights);
   free(right_border_tent);
   free(left_border_tent);

   int64_t n_remaining = 0;
   for (i = 0; i < n_plus; i++)
   {
      for (j = left_border[i]; j <= right_border[i]; j++)
         n_remaining++;
   }
   
   double *remaining = malloc(n_remaining * sizeof(double));
   
   int64_t k = 0;
   for (i = 0; i < n_plus; i++)
      for (j = left_border[i]; j <= right_border[i]; j++)
      {
         remaining[k] = - h_kernel(
            i, j, z_plus, n_plus, z_minus, n_minus, epsilon2);
         k++;
      }

   double medcouple_ = - select_kth_smallest(
      remaining, n_remaining, medcouple_index - left_total);

   free(z_minus);
   free(z_plus);
   free(left_border);
   free(right_border);
   free(remaining);

   return medcouple_;
}

/**
 * Mode.
 * 
 * Arguments:
 *    x: Array.
 *    x: Length of the array.
 * 
 * Returns:
 *    Mode.
 */
double mode(double *x, int64_t n)
{
   int64_t m, m_half, i, j;
   double width, min_width;

   // Sort x ascendingly
   qsort(x, n, sizeof(double), compare_ascending);

   int64_t begin = 0;
   int64_t end = n - 1;

   while(1)
   {
      m = end - begin + 1;

      if (m == 1)
         return x[begin];
      else if (m == 2)
         return (x[begin] + x[end]) / 2.;
      else if (m == 3)
      {
         if (x[begin + 1] - x[begin] < x[end] - x[begin + 1])
            return (x[begin] + x[begin + 1]) / 2.;
         else if (x[begin + 1] - x[begin] > x[end] - x[begin + 1])
            return (x[begin + 1] + x[end]) / 2.;
         else
            return x[begin + 1];
      }
      else
      {
         min_width = x[end] - x[begin];

         m_half = (m + 1) / 2;

         j = begin;
         for (i = begin; i <= begin + m - m_half; i++)
         {
            width = x[i + m_half - 1] - x[i];

            if (width < min_width)
            {
               min_width = width;
               j = i;
            }
         }

         begin = j;
         end = j + m_half - 1;
      }
   }
}
