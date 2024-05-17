p, q = map(int, input().split())

ans = 0
if p % 2 == 1 and q % 2 == 1:
    ans = 1
elif p % 2 == 0:
    ans = 0
elif q > p:
    ans = 2
print(ans)
