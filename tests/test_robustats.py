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

    def test_generic_1(self):
        x = [1.3, 5.1, 2.9, 1.9, 7.4]
        weights = [1.4, 0.9, 0.6, 1.2, 1.7]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 2.9)

    def test_generic_2(self):
        x = [4.2, 1.3, 7.4, 0.2, 4.6, 9.8, 5.5, 3.7]
        weights = [0.4, 2.1, 1.1, 1.6, 0.3, 0.9, 1.2, 1.7]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 3.7)

    def test_generic_3(self):
        x = [0.1, 0.35, 0.05, 0.1, 0.15, 0.05, 0.2]
        weights = [0.1, 0.35, 0.05, 0.1, 0.15, 0.05, 0.2]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 0.2)
