#include <nanobind/nanobind.h>
#include <nanobind/stl/complex.h>
#include <complex.h>
#include <nanobind/ndarray.h>
#include <span>
namespace nb = nanobind;

using namespace nb::literals;

namespace
{
    template <typename T>
    void spanned_function(std::span<T> b)
    {
        std::for_each(b.begin(), b.end(), [](auto &val)
                      { val *= -2; });
    }
}
NB_MODULE(nanobind_example_ext, m)
{
    m.def(
        "add_vector",
        [](nb::ndarray<double, nb::ndim<1>, nb::c_contig> b)
        {
            spanned_function<double>(std::span<double>(b.data(), b.size()));
        },
        nb::arg("b"));
}
