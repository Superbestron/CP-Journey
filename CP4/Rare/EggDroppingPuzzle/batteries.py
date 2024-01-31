import sys


def f(d, k):
    ans = 0
    cur = 1

    for i in range(1, k + 1):
        cur = cur * (d - i + 1) // i  # quick way to compute next binomial coefficient fast
        ans += cur
    return ans


for line in sys.stdin:
    n = int(line)
    if n == 0:
        break
    if n == 1:
        print(0)
        continue
    for i in range(1, 98):
        if f(i, 2) >= n - 1:
            print(i)
            break
