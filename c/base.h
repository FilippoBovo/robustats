#include <stdint.h>

double max_(double a, double b);
double sign(double x);
int64_t sum_int(int64_t *x, int64_t n);
double sum_double(double *x, int64_t n);
void swap(double *x, int64_t i, int64_t j);
void swap_2d(double **x, int64_t n2, int64_t i, int64_t j);
int compare_ascending(const void *i, const void *j);
int compare_descending(const void *i, const void *j);
int compare_ascending_2d(const void *i, const void *j, int64_t k);
int compare_descending_2d(const void *i, const void *j, int64_t k);

double random_0_to_1();
int64_t random_range(int64_t begin, int64_t end);

void fill_array_int(int64_t *x, int64_t n, int64_t value);
void copy_array_int(int64_t *x, int64_t *y, int64_t n);
double **zip(double *array_a, double *array_b, int64_t n);
void free_zip_memory(double **zip_array, int64_t n);

int64_t partition_on_value(double *x, int64_t begin, int64_t end, double value);
int64_t partition_on_kth_element(double *x, int64_t begin, int64_t end, int64_t k);
int64_t partition_on_kth_element_2d(double **x, int64_t begin, int64_t end, int64_t n2, int64_t m, int64_t k);
double partition_on_kth_smallest(double *x, int64_t begin, int64_t end, int64_t k);
double partition_on_kth_smallest_2d(double **x, int64_t begin, int64_t end, int64_t n2, int64_t m, int64_t k);
double select_kth_smallest(double *x, int64_t n, int64_t k);
