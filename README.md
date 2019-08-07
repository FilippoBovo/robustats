# Robustats

Robustats is a Python library for high-performance computation of robust statistical estimators.

The functions that compute the robust estimators are [implemented in C](c) for speed and [called by Python](robustats).

Estimators implemented in the library:

- Weighted Median (temporal complexity: `O(n)`) \[1, 2, 3\]

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

x = np.array([1.1, 5.3, 3.7, 2.1, 7.0, 9.9])
weights = np.array([1.1, 0.4, 2.1, 3.5, 1.2, 0.8])

weighted_median = robustats.weighted_median(x, weights)

print("The weighted median is {}".format(weighted_median))

# Output: The weighted median is 2.1
```

## How to Contribute

If you wish to contribute to this library, please follow the patterns and style of the rest of the code.

Tips:

- In C, use `malloc` to allocate memory to the heap, instead of creating arrays that allocate memory to the stack, as with large array we would incur in a [segmentation fault due to stack overflow](https://stackoverflow.com/a/1847886).
- Avoid recursions where possible to limit the spacial complexity of the problem. In place of recursions, use loops.

## References

\[1\] [Cormen, Leiserson, Rivest, Stein - Introduction to Algorithms (3rd Edition)](https://books.google.co.uk/books?id=aefUBQAAQBAJ&lpg=PR5&ots=dN8rWuZQaW&dq=Cormen%2C%20Leiserson%2C%20Rivest%2C%20Stein%20-%20Introduction%20to%20Algorithms&lr&pg=PP1#v=onepage&q&f=false).

\[2\] [Cormen - Introduction to Algorithms (3rd Edition) - Instructor's Manual](https://cdn.manesht.ir/19908/Introduction%20to%20Algorithms.pdf).

\[3\] [Weighted median on Wikipedia](https://en.wikipedia.org/wiki/Weighted_median).

