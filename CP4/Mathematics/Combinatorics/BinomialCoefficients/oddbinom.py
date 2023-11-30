def f(k):
    if k == 0:
        return 0
    if k == 1:
        return 1
    if k % 2 == 0:
        return 3 * f(k // 2)
    else:
        return 2 * f(k // 2) + f(k // 2 + 1)


n = int(input())
print(f(n))
