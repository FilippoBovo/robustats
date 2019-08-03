double sum (double *x, int n);
void swap(double *x, int i, int j);
void swap_2d(double **x, int n2, int i, int j);
int compare_element_in_arrays(const void *i, const void *j, int k);

double random_0_to_1();
int random_range(int begin, int end);

double **zip(double *array_a, double *array_b, int n);
void free_zip_memory(double **zip_array, int n);

int partition_on_value(double *x, int begin, int end, double value);
int partition_on_kth_element(double *x, int begin, int end, int k);
int partition_on_kth_element_2d(double **x, int begin, int end, int n2, int m, int k);
double partition_on_kth_smallest(double *x, int begin, int end, int k);
double partition_on_kth_smallest_2d(double **x, int begin, int end, int n2, int m, int k);
double select(double *x, int n, int k);
