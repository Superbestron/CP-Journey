from math import gcd
import sys


def lcm(a, b):
    return a // gcd(a, b) * b


for line in sys.stdin:
    ls = [int(x) for x in line.split()]
    curr = ls[0]
    for j in range(1, len(ls)):
        curr = lcm(curr, ls[j])
    print(curr)
