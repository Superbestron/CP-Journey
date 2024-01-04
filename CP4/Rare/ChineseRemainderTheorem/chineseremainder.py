from operator import mul
from functools import reduce


def mod(a, m):
    return ((a % m) + m) % m


def extEuclid(a, b):
    xx = y = 0
    yy = x = 1
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - q * xx
        y, yy = yy, y - q * yy
    return a, x, y


def modInverse(b, m):
    a, x, y = extEuclid(b, m)
    if a != 1:
        return -1
    return mod(x, m)


def crt(r, m):
    mt = reduce(mul, m, 1)
    x = 0
    for i in range(len(m)):
        a = mod(r[i] * modInverse(mt // m[i], m[i]), m[i])
        x = mod(x + a * (mt // m[i]), mt)
    return x


T = int(input())
for i in range(T):
    a, n, b, m = map(int, input().split())
    moduli = [n, m]
    r = [a, b]
    ans = crt(r, moduli)
    print(ans, n * m)
