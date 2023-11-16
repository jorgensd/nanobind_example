import nanobind_example as m
import numpy as np
import pytest

# def test_real():
#     assert m.function(1, np.float64(2.)) == -2

arr_real = np.array([2.7], dtype=np.float64)
arr_complex = np.array([3+2.8j], dtype=np.complex128)


@pytest.mark.parametrize("func", [m.function, m.new_func])
def test_complex(func):
    a2 = arr_complex.copy()
    func(a2, 2)
    assert np.allclose(a2, -2*arr_complex)


@pytest.mark.parametrize("func", [m.function, m.new_func])
def test_real(func):
    a2 = arr_real.copy()
    func(a2, 2)
    assert np.allclose(a2, -2*arr_real)


@pytest.mark.parametrize("func", [m.function, m.new_func])
def test_complex_uint32(func):
    a2 = arr_complex.copy()
    print(a2)
    func(a2, np.uint32(2), )
    print(a2)
    assert np.allclose(a2, -2*arr_complex)
