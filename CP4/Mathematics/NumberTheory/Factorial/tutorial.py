import math

m, n, t = map(int, input().split())
ans = True
if t == 1:
    if n >= 13:
        ans = False
    else:
        ans = math.factorial(n) <= m
elif t == 2:
    if n >= 30:
        ans = False
    else:
        ans = pow(2, n) <= m
elif t == 3:
    ans = n ** 4 <= m
elif t == 4:
    ans = n ** 3 <= m
elif t == 5:
    ans = n ** 2 <= m
elif t == 6:
    ans = n * math.log2(n) <= m
else:
    ans = n <= m
print("AC" if ans else "TLE")
