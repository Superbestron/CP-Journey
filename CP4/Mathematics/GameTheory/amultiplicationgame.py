import sys
from functools import lru_cache


@lru_cache(maxsize=None)
def f(n, x, isStan):
    if x * 9 >= n:
        return isStan
    stanWins = False
    if not isStan:
        stanWins = True
    for i in range(2, 10):
        if isStan:
            stanWins = stanWins or f(n, x * i, not isStan)
        else:
            stanWins = stanWins and f(n, x * i, not isStan)
    return stanWins


for line in sys.stdin:
    n = int(line)
    if f(n, 1, True):
        print("Stan wins.")
    else:
        print("Ollie wins.")
