import nanobind_example as m
import numpy as np
import time


arr = np.arange(100_000_000, dtype=np.float64)


def test_vector():
    arr_nb = arr.copy()
    start = time.perf_counter()
    m.add_vector(arr_nb)
    end = time.perf_counter()
    print(f"Nanobind: {end-start:5e}")

    arr_pb = arr.copy()
    start = time.perf_counter()
    m.add_vector_pb(arr_pb)
    end = time.perf_counter()
    print(f"Pybind: {end-start:5e}")
    assert np.allclose(arr_nb, arr_pb)
