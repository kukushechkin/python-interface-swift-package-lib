import time
import parallel_sum

def print_result(x) -> int:
    print(f"Number is {x}, will calculate square...")
    time.sleep(x)
    return x * x

def heartbeat():
    print("Heartbeat!")

parallel_sum.register_heartbeat(heartbeat)

# Will generate 12 random numbers [0, 9]
parallel_sum.generate_random_numbers(12, print_result)

print("Waiting for the callback to finish for 12 secs...")
time.sleep(12)
print("Done waiting, cleaning up.")

parallel_sum.cleanup_threads()
