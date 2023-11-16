import nanobind_example as m
import numpy as np


# def test_real():
#     assert m.function(1, np.float64(2.)) == -2


def test_add_complex():
    assert np.isclose(m.function(1,  2.7+3.2j), -(2.7+3.2j))


def test_add_complex_input():
    assert np.isclose(m.function(np.uint32(1), np.complex128(2+2j)), -(2+2j))
