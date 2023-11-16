#include <nanobind/nanobind.h>
#include <nanobind/stl/complex.h>
#include <complex.h>
#include <iostream>
#include <nanobind/ndarray.h>
#include <span>
namespace nb = nanobind;

using namespace nb::literals;

namespace
{
    template <typename T>
    void templated_function(nb::ndarray<T, nb::ndim<1>, nb::c_contig> b, std::uint32_t a)
    {
        std::span<T> c(b.data(), b.size());
        std::for_each(c.begin(), c.end(), [](auto &val)
                      { val *= -2; });
    }
}
NB_MODULE(nanobind_example_ext, m)
{
    m.def(
        "function", [](nb::ndarray<std::complex<double>, nb::ndim<1>, nb::c_contig> b, std::uint32_t a)
        {
        std::cout << "COMPLEX\n";
       std::span<std::complex<double>>c(b.data(), b.size());
        std::for_each(c.begin(), c.end(), [](auto &val)
                      {
            val *= -2; }); },
        "b"_a,
        "a"_a);

    m.def(
        "function", [](nb::ndarray<double, nb::ndim<1>, nb::c_contig> b, std::uint32_t a)
        {
        std::cout << "REAL\n";
        std::span<double>c(b.data(), b.size());
        std::for_each(c.begin(), c.end(), [](auto &val)
                      {
            val *= -2; }); },
        "b"_a,
        "a"_a);

    m.def("new_func", [](nb::ndarray<double, nb::ndim<1>, nb::c_contig> b, std::uint32_t a)
          { templated_function(b, a); });
    m.def("new_func", [](nb::ndarray<std::complex<double>, nb::ndim<1>, nb::c_contig> b, std::uint32_t a)
          { templated_function(b, a); });
}
