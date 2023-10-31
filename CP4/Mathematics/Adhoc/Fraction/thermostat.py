from fractions import Fraction

N, Q = map(int, input().split())
ls = []
for i in range(N):
    ls.append(list(map(int, input().split())))
for i in range(Q):
    x, y, v = map(int, input().split())
    x -= 1
    y -= 1
    ans = Fraction(ls[y][0]) + Fraction((ls[y][1] - ls[y][0]) * (v - ls[x][0]), ls[x][1] - ls[x][0])
    if ans.denominator == 1:
        print(ans, end='')
        print("/1")
    else:
        print(ans)
