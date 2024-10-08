# What is this?

This is a simple projects demonstrating how to build a C++ library using SPM and wrap it into a Python package.


# Building

First, make sure you have Swift installed. I verified it on macOS with Xcode installed, but theoretically should work on Linux and Windows as well.

Then, create a python environment. Python project is the entry point for the build process:

```bash
uv venv
source venv/bin/activate
```

Then, install dev dependencies:

```bash
uv pip install -r requirements_dev.txt
```

Finally, build the project:

```bash
./build.sh
```

This will:
- build the C++ library using SPM as an external command
- build Python bindings using pybind11
- link the C++ library with the Python bindings
- create a Python package
- install the Python package in the current (virtual) environment


# Examples

There are three example in the `examples` directory:

- `sum_example.py` - demonstrates how to use the library with a simple function
- `callback_example.py` - demonstrates how to use the library with a callback back to Python
- `parallel_example.py` - demonstrates how native threads can call back to Python through GIL
