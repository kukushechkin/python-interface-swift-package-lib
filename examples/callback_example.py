import parallel_sum

def print_result(x):
    print(f"Sum is {x}")

parallel_sum.apply_callback(5, 4, print_result)
