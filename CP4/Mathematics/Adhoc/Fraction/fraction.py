from fractions import Fraction

n1, n2 = map(int, input().split())


def toNormal(ls):
    f = Fraction(ls[0])
    if not ls[1:]:
        return f
    return f + Fraction(1, toNormal(ls[1:]))


def toContinued(frac: Fraction):
    if frac.numerator % frac.denominator:
        return [frac.numerator // frac.denominator] + toContinued(Fraction(frac.denominator, frac.numerator % frac.denominator))
    else:
        return [frac.numerator // frac.denominator]


ls1 = list(map(int, input().split()))
ls2 = list(map(int, input().split()))
f1 = toNormal(ls1)
f2 = toNormal(ls2)
for i in toContinued(f1 + f2):
    print(i, end=' ')
print()
for i in toContinued(f1 - f2):
    print(i, end=' ')
print()
for i in toContinued(f1 * f2):
    print(i, end=' ')
print()
for i in toContinued(f1 / f2):
    print(i, end=' ')
