import sys
from functools import lru_cache


@lru_cache(maxsize=None)
def f(n):
    if n <= 1:
        return n
    k = n - round((2 * n + 1) ** 0.5) + 1
    return 2 * f(k) + 2 ** (n - k) - 1


for line in sys.stdin:
    n = int(line)
    print(f(n))
