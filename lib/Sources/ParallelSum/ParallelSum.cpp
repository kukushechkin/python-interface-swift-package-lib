#include "ParallelSum.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <pybind11/pybind11.h>
#include <thread>
#include <vector>

std::vector<std::thread> threads;
std::vector<std::shared_ptr<pybind11::function>> handles;
std::atomic<bool> stop_threads(false);

namespace ParallelSum {

void register_heartbeat(const pybind11::function &func) {
  auto func_ptr = std::make_shared<pybind11::function>(func);
  handles.push_back(func_ptr);

  threads.push_back(std::thread([func_ptr]() {
    while (!stop_threads.load()) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      {
        // Acquire GIL before calling Python code
        pybind11::gil_scoped_acquire acquire;
        (*func_ptr)();
      }
    }
  }));
}

int sum(int a, int b) { return a + b; }

void apply_callback(const int a, const int b, const pybind11::function &func) {
  int result = sum(a, b);
  func(result); // Call Python back
}

void generate_random_numbers(const int n, const pybind11::function &func) {
  auto func_ptr = std::make_shared<pybind11::function>(func);
  handles.push_back(func_ptr);

  // Start n threads and call the callback function with a random number
  for (int i = 0; i < n; i++) {
    threads.push_back(std::thread([func_ptr]() {
      std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
      int random_number = rand() % 10;
      {
        // Acquire GIL before calling Python code
        pybind11::gil_scoped_acquire acquire;
        int result = (*func_ptr)(random_number).cast<int>();
        std::cout << "Result: " << result << std::endl;
      }
    }));
  }
}

void cleanup_threads() {
  stop_threads.store(true);
  {
    // Release GIL before waiting for threads to join
    pybind11::gil_scoped_release release;
    for (auto &thread : threads) {
      if (thread.joinable()) {
        thread.join();
      }
    }
  }
  threads.clear();
}

} // namespace ParallelSum
