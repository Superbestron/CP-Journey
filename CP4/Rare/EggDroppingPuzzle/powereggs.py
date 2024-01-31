def f(d, k):
    ans = 0
    cur = 1

    for i in range(1, k + 1):
        cur = cur * (d - i + 1) // i  # quick way to compute next binomial coefficient fast
        ans += cur
    return ans


T = int(input())
for _ in range(T):
    n, k = map(int, input().split())
    for i in range(1, 33):
        if f(i, k) >= n:
            print(i)
            break
    else:
        print("Impossible")
