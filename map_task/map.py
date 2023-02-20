from collections import defaultdict
from sys import getsizeof
from random import random
import time


n = 1

for i in range(8):
    n *= 10
    container = defaultdict(lambda: 0)
    time_start = time.perf_counter_ns()
    for j in range(n):
        container[j] = random() % n
    time_end = time.perf_counter_ns()
    print(n, getsizeof(container), time_end - time_start)