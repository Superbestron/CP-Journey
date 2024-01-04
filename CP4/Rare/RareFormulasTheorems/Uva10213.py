S = int(input())
for _ in range(S):
    N = int(input())
    ans = (N * (N - 1) * (N - 2) * (N - 3)) // 24 + (N * (N - 1) // 2) + 1
    print(ans)
