from fractions import Fraction

N = input()
ls = list(map(int, input().split()))

first = ls[0]
for i in range(1, len(ls)):
    ans = Fraction(first, ls[i])
    if ans.denominator == 1:
        print(f'{ans}/1')
    else:
        print(ans)
