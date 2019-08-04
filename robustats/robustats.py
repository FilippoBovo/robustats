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
