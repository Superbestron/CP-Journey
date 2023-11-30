import sys
from functools import lru_cache


@lru_cache(maxsize=None)
def f(x):
    if x < 0:
        return 0
    if x == 0:
        return 1
    if x == 2:
        return 3
    ans = f(x - 2) * 3
    for i in range(4, x + 1, 2):
        ans += f(x - i) * 2
    return ans


for line in sys.stdin:
    n = int(line)
    if n == -1:
        break
    print(f(n))
