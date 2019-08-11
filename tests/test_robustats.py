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


class TestMedcouple(unittest.TestCase):
    def test_homogeneous_sample_1(self):
        x = [1., 2., 3.]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, 0.)

    def test_homogeneous_sample_2(self):
        x = [-1., 0., 1.]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, 0.)

    def test_homogeneous_sample_3(self):
        x = [1., 2., 3., 4., 5., 6.]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, 0.)

    def test_generic_1(self):
        x = [1., 2., 2., 2., 3., 4., 5., 6.]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, 1.)

    def test_generic_2(self):
        x = [0.2, 0.17, 0.08, 0.16, 0.88, 0.86, 0.09, 0.54, 0.27, 0.14]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, 0.7692307692307692)

    def test_generic_3(self):
        x = [
            0.61, 0.96, 0.76, 0.69, 0.18, 0.81, 0.32, 0.69, 0.91, 0.37, 0.0,
            0.66, 0.99, 0.59, 0.73, 0.41, 0.28, 0.45, 0.63, 0.03
        ]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, -0.3333333333333333)

    def test_generic_4(self):
        x = [
            0.44, 0.66, 0.18, 0.51, 0.34, 0.7, 0.86, 0.97, 0.15, 0.53, 0.85,
            0.28, 0.13, 0.74, 0.52, 0.21, 0.87, 0.7, 0.17, 0.84, 0.86, 0.01,
            0.42, 0.27, 0.22, 0.88, 0.16, 0.57, 0.66, 0.88
        ]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, -0.014925373134328474)

    def test_generic_5(self):
        x = [
            0.7, 0.49, 0.07, 0.4, 0.44, 0.36, 0.02, 0.88, 0.94, 0.9, 0.46,
            0.93, 0.81, 0.92, 0.32, 0.43, 0.64, 0.01, 0.37, 0.46, 0.47, 0.13,
            0.29, 0.1, 0.04, 0.9, 0.55, 0.27, 0.28, 0.46, 0.46, 0.1, 0.81,
            0.55, 0.95, 0.58, 0.12, 0.61, 0.92, 0.93
        ]
        weighted_median = robustats.medcouple(x)
        self.assertEqual(weighted_median, 0.11363636363636356)


class TestMode(unittest.TestCase):
    def test_homogeneous_sample(self):
        x = [1., 2., 3., 4., 5.]
        mode = robustats.mode(x)
        self.assertEqual(mode, 2.)

    def test_generic_1(self):
        x = [1., 2., 3., 3., 4., 5.]
        mode = robustats.mode(x)
        self.assertEqual(mode, 3.)

    def test_generic_2(self):
        x = [1., 2., 2., 3., 3., 3., 4., 4., 5.]
        mode = robustats.mode(x)
        self.assertEqual(mode, 3.)

    def test_generic_3(self):
        x = [1., 2., 3., 3., 3., 4., 4., 4., 4., 5.]
        mode = robustats.mode(x)
        self.assertEqual(mode, 3.)

    def test_generic_4(self):
        x = [1., 2., 3., 3., 3., 4., 4., 4., 4., 4., 5., 6., 7.]
        mode = robustats.mode(x)
        self.assertEqual(mode, 4.)

    def test_gaussian_1(self):
        # Gaussian distribution with mu = 1.0 and sigma = 0.2 --> mode = 1.0
        x = [1.06, 1.25, 0.99, 1.07, 1.46, 1.02, 1.14, 1.04, 0.6, 1.0]
        mode = robustats.mode(x)
        self.assertEqual(mode, 0.995)

    def test_gaussian_2(self):
        # Gaussian distribution with mu = 3.0 and sigma = 0.5 --> mode = 3.0
        x = [
            2.89, 3.32, 3.19, 3.35, 3.84, 3.22, 3.46, 3.45, 3.06, 3.59, 2.44,
            3.51, 3.73, 3.35, 2.26, 2.0, 2.15, 3.25, 3.21, 3.4
        ]
        mode = robustats.mode(x)
        self.assertEqual(mode, 3.35)

    def test_gaussian_3(self):
        # Gaussian distribution with mu = 10.0 and sigma = 1.0 --> mode = 10.0
        x = [
            9.67, 10.43, 8.34, 8.47, 10.31, 11.01, 9.99, 10.72, 8.61, 11.33,
            10.87, 9.38, 8.79, 9.07, 10.7, 11.14, 9.73, 9.72, 9.8, 12.06,
            10.99, 10.12, 10.67, 9.71, 9.74, 9.85, 8.65, 8.71, 10.07, 8.54
        ]
        mode = robustats.mode(x)
        self.assertEqual(mode, 9.715)

    def test_gamma_1(self):
        # Gamma distribution with alpha = 11.0 and beta = 10.0 --> mode = 1.0
        x = [1.17, 0.82, 0.85, 2.1, 1.35, 1.21, 1.07, 0.81, 1.09, 1.27]
        mode = robustats.mode(x)
        self.assertEqual(mode, 1.08)

    def test_gamma_2(self):
        # Gamma distribution with alpha = 21.0 and beta = 10.0 --> mode = 2.0
        x = [
            2.04, 2.22, 2.27, 1.71, 2.45, 1.55, 2.38, 2.15, 1.95, 3.34, 2.74,
            1.92, 1.68, 2.1, 2.13, 2.6, 1.36, 2.25, 2.85, 1.55
        ]
        mode = robustats.mode(x)
        self.assertEqual(mode, 2.26)

    def test_gamma_3(self):
        # Gamma distribution with alpha = 61.0 and beta = 20.0 --> mode = 3.0
        x = [
            2.95, 2.29, 3.24, 3.57, 3.7, 3.0, 3.07, 3.73, 2.98, 2.96, 2.59,
            3.61, 3.09, 2.65, 2.37, 2.66, 2.88, 2.92, 2.3, 3.9, 3.49, 3.67,
            2.09, 2.98, 2.52, 3.37, 3.29, 3.18, 3.16, 2.68
        ]
        mode = robustats.mode(x)
        self.assertEqual(mode, 2.98)
