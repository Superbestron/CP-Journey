import sys
from functools import lru_cache


@lru_cache(maxsize=None)
def comb(n, r):
    if r == 0 or r == n:
        return 1
    return comb(n - 1, r - 1) + comb(n - 1, r)


P = int(input())
for line in sys.stdin:
    K, S = map(int, line.split())
    x = S // 2

    if x % 2:  # odd case
        one_steps = 1
    else:
        one_steps = 0

    two_steps = x // 2
    ans = 0
    while one_steps <= two_steps:
        ans += comb(two_steps + one_steps, two_steps) ** 2
        two_steps -= 1
        one_steps += 2

    print(K, ans)
