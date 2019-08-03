#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "robustats.h"

/**
 * Weighted median.
 * 
 * Arguments:
 *    x: array of values
 *    w: array of weights
 *    begin: Beginning index of the sub-array over which to calculate the
 *       weighted median.
 *    end: Ending index of the sub-array over which to calculate the weighted
 *       median.
 *    break_tie: Break a tie where two medians are found by selecting the lower
 *       or higher median. This argument can take values 'l' and 'h' for lower
 *       and higher, respectively.
 * 
 * Return:
 *    Weighted median.
*/
double weighted_median(double *x, double *w, int begin, int end, char break_tie)
{
   int n, i, median_index, median_in_lower, median_in_higher;
   double median, w_middle, w_lower_sum, w_higher_sum;
   
   n = end - begin + 1;  // Length between begin and end
   double **xw = zip(x, w, n);

   while (1)
   {
      n = end - begin + 1; // Length between begin and end

      if (n == 1)
         return x[begin];
      else if (n == 2)
      {
         if (w[begin] >= w[end])
            return x[begin];
         else
            return x[end];
      }
      else
      {
         if (break_tie == 'l')
            median_index = begin + (n - 1) / 2;  // Lower median index
         else if (break_tie == 'h')
            median_index = begin + n / 2;  // Higher median index
         else
         {
            perror("break_tie argument can only be 'l' or 'h'");
            exit(EXIT_FAILURE);
         }

         median = partition_on_kth_smallest_2d(xw, begin, end, 2, 0, median_index);

         w_middle = xw[median_index][1];

         w_lower_sum = 0.;
         for (i = begin; i < median_index; i++)
            w_lower_sum += xw[i][1];

         w_higher_sum = 0.;
         for (i = median_index + 1; i <= end; i++)
            w_higher_sum += xw[i][1];

         if (w_lower_sum > w_higher_sum + w_middle)
            median_in_lower = 1;  // True (median in lower half)
         else
            median_in_lower = 0;  // False

         if (w_lower_sum + w_middle < w_higher_sum)
            median_in_higher = 1;  // True (median in higher half)
         else
            median_in_higher = 0;  // False
         
         if (!(median_in_lower || median_in_higher))
         {
            free_zip_memory(xw, n);
            
            return median;
         }
         else if (median_in_lower)
            end = median_index;
         else
            begin = median_index;
      }
   }
}
