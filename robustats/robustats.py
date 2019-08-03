from typing import List, Union

import numpy as np

import _robustats


def weighted_median(
        x: Union[List[float], np.ndarray],
        weights: Union[List[float], np.ndarray],
        break_tie: str = 'lower'
) -> float:
    """Calculate the weighted median of an array with related weights.

    Args:
        x: List or Numpy array.
        weights: List or Numpy of weights related to 'x'.
        break_tie: This argument can take two values: 'lower' and 'higher'. If
            the weighted median results in a tie between two numbers, use this
            argument to specify whether to choose the lower or higher number.

    Returns:
        Weighted median.

    Examples:
        >>> weighted_median(x=[1., 2., 3.], weights=[1., 1., 1.])
        2.0
        >>> weighted_median(x=[1., 2., 3.], weights=[3., 1., 1.])
        1.0
        >>> weighted_median(
        >>>     x=[1., 2., 3., 4.], weights=[1., 1., 1., 1.], break_tie='lower'
        >>> )
        2.0
        >>> weighted_median(
        >>>     x=[1., 2., 3., 4.], weights=[1., 1., 1., 1.], break_tie='higher'
        >>> )
        3.0
    """
    if break_tie == 'lower':
        return _robustats.weighted_median(x, weights, b'l')
    elif break_tie == 'higher':
        return _robustats.weighted_median(x, weights, b'h')
    else:
        raise ValueError(
            "Argument 'break_tie' can be either 'lower' or 'higher'."
        )
