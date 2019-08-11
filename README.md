# Robustats

Robustats is a Python library for high-performance computation of robust statistical estimators.

The functions that compute the robust estimators are [implemented in C](c) for speed and [called by Python](robustats).

Estimators implemented in the library:

- **Weighted Median** (temporal complexity: `O(n)`) \[1, 2, 3\]
- **Medcouple** (temporal complexity: `O(n * log(n))`) [4, 5, 6, 7]
- **Mode** (temporal complexity: `O(n * log(n))`) [8]

## How to Install

This library requires Python 3.

You can install the library directly from GitHub using the following command.

```shell
pip install -e 'git+https://github.com/FilippoBovo/robustats.git#egg=robustats'
```

Otherwise, you may clone the repository, and install and test the Robustats package in the following way.

```shell
git clone https://github.com/FilippoBovo/robustats.git
cd robustats
pip install -e .
python -m unittest
```

## How to Use

This is an example of how to use the Robustats library in Python.

```python
import numpy as np
import robustats


# Weighted Median
x = np.array([1.1, 5.3, 3.7, 2.1, 7.0, 9.9])
weights = np.array([1.1, 0.4, 2.1, 3.5, 1.2, 0.8])

weighted_median = robustats.weighted_median(x, weights)

print("The weighted median is {}".format(weighted_median))
# Output: The weighted median is 2.1


# Medcouple
x = np.array([0.2, 0.17, 0.08, 0.16, 0.88, 0.86, 0.09, 0.54, 0.27, 0.14])

medcouple = robustats.medcouple(x)

print("The medcouple is {}".format(medcouple))
# Output: The medcouple is 0.7692307692307692


# Mode
x = np.array([1., 2., 2., 3., 3., 3., 4., 4., 5.])

mode = robustats.mode(x)

print("The mode is {}".format(mode))
# Output: The mode is 3.0
```

## How to Contribute

If you wish to contribute to this library, please follow the patterns and style of the rest of the code.

Tips:

- In C, use `malloc` to allocate memory to the heap, instead of creating arrays that allocate memory to the stack, as with large array we would incur in a [segmentation fault due to stack overflow](https://stackoverflow.com/a/1847886).
- Avoid recursions where possible to limit the spatial complexity of the problem. In place of recursions, use loops.

## References

\[1\] [Cormen, Leiserson, Rivest, Stein - Introduction to Algorithms (3rd Edition)](https://books.google.co.uk/books?id=aefUBQAAQBAJ&lpg=PR5&ots=dN8rWuZQaW&dq=Cormen%2C%20Leiserson%2C%20Rivest%2C%20Stein%20-%20Introduction%20to%20Algorithms&lr&pg=PP1#v=onepage&q&f=false).

\[2\] [Cormen - Introduction to Algorithms (3rd Edition) - Instructor's Manual](https://cdn.manesht.ir/19908/Introduction%20to%20Algorithms.pdf).

\[3\] [Weighted median on Wikipedia](https://en.wikipedia.org/wiki/Weighted_median).

\[4\] [G. Brys; M. Hubert; A. Struyf (November 2004). "A Robust Measure of Skewness". *Journal of Computational and Graphical Statistics*. **13** (4): 996–1017.](https://doi.org/10.1198%2F106186004X12632)

\[5\] [Donald B. Johnson; Tetsuo Mizoguchi (May 1978). "Selecting The Kth Element In X + Y And X1 + X2 +...+ Xm". *SIAM Journal on Computing*. **7** (2): 147–153.](https://doi.org/10.1137%2F0207013)

\[6\] [Medcouple implementation in Python by Jordi Gutiérrez Hermoso.](http://inversethought.com/hg/)

\[7\] [Medcouple on Wikipedia.](https://en.wikipedia.org/wiki/Medcouple)

\[8\] [David R. Bickel, Rudolf Frühwirth. "On a fast, robust estimator of the mode: Comparisons to other robust estimators with applications", *Computational Statistics & Data Analysis*, Volume 50, Issue 12, 2006, Pages 3500-3530, ISSN 0167-9473.](https://doi.org/10.1016/j.csda.2005.07.011)