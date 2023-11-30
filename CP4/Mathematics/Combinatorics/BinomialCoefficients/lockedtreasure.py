import math

t = int(input())

for i in range(t):
    n, m = map(int, input().split())
    print(math.comb(n, m - 1))
