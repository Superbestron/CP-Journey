T = int(input())
for t in range(T):
    ls = list(map(float, input().split()))
    ls = ls[1:]
    ls.sort()
    ans = 0
    for i in range(len(ls) - 2):
        if ls[i + 2] < ls[i] + ls[i + 1]:
            s = (ls[i] + ls[i + 1] + ls[i + 2]) / 2
            ans = max(ans, (s * (s - ls[i]) * (s - ls[i + 1]) * (s - ls[i + 2])) ** 0.5)
    print(f'{ans:.2f}')
