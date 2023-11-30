import sys
from fractions import Fraction
from functools import lru_cache

factorial = [1]
for line in sys.stdin:
    n, x = map(int, line.split())
    if n == 0 and x == 0:
        break


    @lru_cache(maxsize=None)
    def dp(dice, score):
        if dice == 0:
            return score >= x
        ans = 0
        for i in range(1, 7):
            ans += dp(dice - 1, score + i)
        return ans

    num = dp(n, 0)
    denom = 6 ** n
    fraction = Fraction(num, denom)
    print(fraction)
