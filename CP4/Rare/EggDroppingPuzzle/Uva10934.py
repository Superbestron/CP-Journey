import sys


def f(d, k):
    ans = 0
    cur = 1

    for i in range(1, k + 1):
        cur = cur * (d - i + 1) // i  # quick way to compute next binomial coefficient fast
        ans += cur
    return ans


for line in sys.stdin:
    k, n = map(int, line.split())
    if k == 0:
        break
    for i in range(1, 64):
        if f(i, k) >= n:
            print(i)
            break
    else:
        print("More than 63 trials needed.")
