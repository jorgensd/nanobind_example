#include <nanobind/nanobind.h>
#include <nanobind/stl/complex.h>
#include <complex.h>
#include <iostream>
namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(nanobind_example_ext, m)
{
    m.def(
        "function", [](std::uint32_t a, const std::complex<float> &b)
        { 
            std::cout << "COMPLEX\n";
            return -b; },
        "a"_a, "b"_a);

    m.def(
        "function", [](std::uint32_t a, float b)
        { 
            std::cout << "REAL\n";
            return b; },
        "a"_a, "b"_a);
}
