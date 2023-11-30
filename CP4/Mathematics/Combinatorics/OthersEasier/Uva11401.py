import math
import sys

# f(n) = (n - 3) + (n - 5) + (n - 7) + ...
# f(n) + f(n - 1) = (n - 3) + (n - 4) + (n - 5) + (n - 6) + ... => math.comb(n - 2, 2)
# memo[n] = f(n) + f(n - 1) + ...
memo = [0 for _ in range(1000001)]
for i in range(5, 1000001, 2):
    memo[i] = math.comb(i - 2, 2) + memo[i - 2]
for i in range(4, 1000001, 2):
    memo[i] = math.comb(i - 2, 2) + memo[i - 2]
for line in sys.stdin:
    n = int(line)
    if n < 3:
        break
    print(memo[n])
