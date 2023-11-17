import nanobind_example as m
import numpy as np
import time


arr = np.arange(10_000_000_00, dtype=np.float64)


def test_vector():
    start = time.perf_counter()
    m.add_vector(arr)
    end = time.perf_counter()
    print(f"Nanobind: {end-start:5e}")
    start = time.perf_counter()
    m.add_vector_pb(arr)
    end = time.perf_counter()
    print(f"Pybind: {end-start:5e}")
