import sys
from typing import List, Union

import numpy as np

import _robustats


def weighted_median(
        x: Union[List[float], np.ndarray],
        weights: Union[List[float], np.ndarray]
) -> float:
    """Calculate the weighted median of an array with related weights.

    For arrays with an even number of elements, this function calculates the
    lower weighted median.

    Args:
        x: List or Numpy array.
        weights: List or Numpy of weights related to 'x'.

    Returns:
        Weighted median.

    Examples:
        >>> weighted_median(x=[1., 2., 3.], weights=[1., 1., 1.])
        2.0
        >>> weighted_median(x=[1., 2., 3.], weights=[2., 1., 1.])
        2.0
        >>> weighted_median(x=[1., 2., 3.], weights=[3., 1., 1.])
        1.0
        >>> weighted_median(x=[1., 2.], weights=[1., 1.])
        1.0
    """
    return _robustats.weighted_median(x, weights)


def medcouple(x: Union[List[float], np.ndarray]) -> float:
    """Calculate the medcouple of a list of numbers.

    Args:
        x: List or Numpy array.

    Returns:
        Medcouple.

    Examples:
        >>> medcouple(x=[1., 2., 3.])
        0.0
        >>> medcouple(x=[1., 2., 3., 4., 5., 6.])
        0.0
        >>> medcouple(x=[1., 2., 2., 2., 3., 4., 5., 6.])
        1.0
        >>> medcouple(x=[0.2, 0.17, 0.08, 0.16, 0.88, 0.86, 0.09, 0.54, 0.27])
        0.7
    """
    if type(x) == list:
        epsilon1 = sys.float_info.epsilon
        epsilon2 = sys.float_info.min
    elif type(x) == np.ndarray:
        epsilon1 = np.finfo(x.dtype).eps
        epsilon2 = np.finfo(x.dtype).min
    else:
        raise ValueError(
            "Wrong function argument: array type not supported; please use a "
            "Python list or a Numpy array."
        )

    return _robustats.medcouple(x, epsilon1, epsilon2)


def mode(x: Union[List[float], np.ndarray]) -> float:
    """Calculate the mode of a list of numbers.

    Args:
        x: List or Numpy array.

    Returns:
        Mode.

    Examples:
        >>> mode(x=[1., 2., 3., 4., 5.])
        2.0
        >>> mode(x=[1., 2., 3., 3., 4., 5.])
        3.0
        >>> mode(x=[1., 2., 2., 3., 3., 3., 4., 4., 5.])
        3.0
        >>> mode(x=[1., 2., 3., 3., 3., 4., 4., 4., 4., 5.])
        3.0
        >>> mode(x=[1., 2., 3., 3., 3., 4., 4., 4., 4., 4., 5., 6., 7.])
        4.0
    """
    return _robustats.mode(x)
