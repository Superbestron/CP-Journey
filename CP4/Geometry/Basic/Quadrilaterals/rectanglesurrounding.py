import sys

for line in sys.stdin:
    n = int(line)
    if n == 0:
        break
    arr = [[False for _ in range(500)] for _ in range(500)]
    for i in range(n):
        a, b, c, d = map(int, input().split())
        for k in range(a, c):
            for l in range(b, d):
                arr[k][l] = True
    ans = 0
    for i in range(500):
        for j in range(500):
            if arr[i][j]:
                ans += 1
    print(ans)
