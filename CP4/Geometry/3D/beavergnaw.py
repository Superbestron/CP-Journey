import sys
from math import pi

for line in sys.stdin:
    D, V = map(int, line.split())
    if D == 0 and V == 0:
        break
    print((D ** 3 - 6 * V / pi) ** (1/3))
