T = int(input())
for i in range(T):
    n, A, B, C, D, X, Y, M = map(int, input().split())
    ls = [(X, Y)]
    for j in range(n - 1):
        X = (A * X + B) % M
        Y = (C * Y + D) % M
        ls.append((X, Y))
    ans = 0
    for j in range(n):
        for k in range(j + 1, n):
            for l in range(k + 1, n):
                num1 = ls[j][0] + ls[k][0] + ls[l][0]
                num2 = ls[j][1] + ls[k][1] + ls[l][1]
                if num1 % 3 == 0 and num2 % 3 == 0:
                    ans += 1
    print(f"Case #{i + 1}: {ans}")
