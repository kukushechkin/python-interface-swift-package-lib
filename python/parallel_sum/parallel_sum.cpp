#include "../../lib/Sources/ParallelSum/ParallelSum.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_parallel_sum, m) {
  m.doc() = "Python bindings for ParallelSum C++ library";

  m.def("register_heartbeat", &ParallelSum::register_heartbeat,
        "Start heartbeat");
  m.def("sum", &ParallelSum::sum, "Sum two integers");
  m.def("apply_callback", &ParallelSum::apply_callback,
        "Sum two integers and call a callback with result");
  m.def("generate_random_numbers", &ParallelSum::generate_random_numbers,
        "n random numbers and get their squares");
  m.def("cleanup_threads", &ParallelSum::cleanup_threads, "cleanup threads");
}
