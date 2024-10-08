#ifndef PARALLEL_SUM_H
#define PARALLEL_SUM_H

#include <pybind11/pybind11.h>

namespace ParallelSum {
int sum(int a, int b);
void register_heartbeat(const pybind11::function &func);
void apply_callback(const int a, const int b, const pybind11::function &func);
void generate_random_numbers(const int n, const pybind11::function &func);
void cleanup_threads();
} // namespace ParallelSum

#endif // PARALLEL_SUM_H
