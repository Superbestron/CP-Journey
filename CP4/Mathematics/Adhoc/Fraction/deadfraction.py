from fractions import Fraction

while True:
    s = input()
    if s == "0":
        break

    s = s[2:-3]  # remove 0. and ...

    l = len(s)
    x = int(s)

    best_f = Fraction(0, 1)
    for i in range(1, l + 1):  # last i digits are repeating...
        f = Fraction(x - (x // 10 ** i), 10 ** l - 10 ** (l - i))
        # print(i, f)
        if (f.denominator < best_f.denominator or best_f == Fraction(0, 1)):
            best_f = f

    print(str(best_f.numerator) + '/' + str(best_f.denominator))
