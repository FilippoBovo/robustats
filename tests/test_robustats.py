import unittest

import robustats


class TestWeightedMedian(unittest.TestCase):
    def test_same_weights(self):
        x = [1., 2., 3.]
        weights = [1., 1., 1.]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 2.)

    def test_edge_case(self):
        x = [1., 2., 3.]
        weights = [2., 1., 1.]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 2.)

    def test_dominant_weight(self):
        x = [1., 2., 3.]
        weights = [3., 1., 1.]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 1.)

    def test_even_list(self):
        x = [1., 2.]
        weights = [1., 1.]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 1.)
