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

    def test_generic_4(self):
        x = [
            0.49, 0.36, 0.36, 0.18, 0.75, 0.33, 0.68, 0.82, 0.38, 0.75, 0.61,
            0.02, 0.57, 0.23, 0.56, 0.03, 0.45, 0.44, 0.36, 0.92
        ]
        weights = [
            0.08, 0.22, 0.79, 0.84, 0.69, 0.84, 0.08, 0.87, 0.95, 0.27, 0.9,
            0.34, 0.75, 0.65, 0.02, 0.83, 0.32, 0.68, 0.92, 0.37
        ]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 0.38)

    def test_generic_5(self):
        x = [
            0.64, 0.95, 0.05, 0.08, 0.32, 0.25, 0.58, 0.69, 0.88, 0.53, 0.48,
            0.58, 0.32, 0.52, 0.42, 0.69, 0.43, 0.91, 0.15, 0.27, 0.31, 0.16,
            0.56, 0.68, 0.58, 0.04, 0.51, 0.06, 0.18, 0.03
        ]
        weights = [
            0.97, 0.2, 0.12, 0.01, 0.86, 0.29, 0.93, 0.96, 0.89, 0.03, 0.24,
            0.56, 0.81, 0.97, 0.48, 0.32, 0.33, 0.22, 0.8, 0.17, 0.96, 0.75,
            0.43, 0.24, 0.81, 0.4, 0.93, 0.43, 0.17, 0.13
        ]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 0.51)

    def test_generic_6(self):
        x = [
            0.19, 0.14, 0.15, 0.79, 0.36, 0.13, 0.44, 0.67, 0.44, 0.98, 0.2,
            0.11, 0.78, 0.67, 0.28, 0.29, 0.99, 0.55, 0.34, 0.36, 0.09, 0.13,
            0.56, 0.19, 0.08, 0.46, 0.62, 0.98, 0.46, 0.37, 0.09, 0.94, 0.84,
            0.64, 0.18, 0.64, 0.78, 0.88, 0.17, 0.28
        ]
        weights = [
            0.67, 0.39, 0.31, 0.06, 0.93, 0.21, 0.09, 0.29, 0.78, 0.42, 0.79,
            0.27, 0.77, 0.35, 0.11, 0.99, 0.05, 0.39, 0.34, 0.97, 0.82, 0.4,
            0.09, 0.77, 0.28, 0.03, 0.63, 0.67, 0.1, 0.3, 0.85, 0.44, 0.66,
            0.52, 0.15, 0.4, 0.82, 0.66, 0.21, 0.72
        ]
        weighted_median = robustats.weighted_median(x, weights)
        self.assertEqual(weighted_median, 0.36)
