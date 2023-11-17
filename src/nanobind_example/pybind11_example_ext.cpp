#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <span>
namespace py = pybind11;
namespace
{
    template <typename T>
    void spanned_function(std::span<T> b)
    {
        std::for_each(b.begin(), b.end(), [](auto &val)
                      { val *= -2; });
    }
}
PYBIND11_MODULE(pybind11_example_ext, m)
{
    m.def(
        "add_vector",
        [](py::array_t<double, py::array::c_style> b)
        {
            spanned_function<double>(std::span<double>(b.mutable_data(), b.size()));
        },
        py::arg("b"));
}
