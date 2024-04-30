from fractions import Fraction

n = int(input())
for i in range(n):
    ls = input().split()
    ans = Fraction
    if ls[2] == '+':
        ans = Fraction(int(ls[0]), int(ls[1])) + Fraction(int(ls[3]), int(ls[4]))
    elif ls[2] == '-':
        ans = Fraction(int(ls[0]), int(ls[1])) - Fraction(int(ls[3]), int(ls[4]))
    elif ls[2] == '/':
        ans = Fraction(int(ls[0]), int(ls[1])) / Fraction(int(ls[3]), int(ls[4]))
    else:
        ans = Fraction(int(ls[0]), int(ls[1])) * Fraction(int(ls[3]), int(ls[4]))
    print(f"{ans.numerator} / {ans.denominator}")
