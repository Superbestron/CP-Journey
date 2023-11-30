import math
import sys

for line in sys.stdin:
    r, h, s = map(int, line.split())
    if r == 0 and h == 0 and s == 0:
        break
    theta = math.acos(r / h)
    ans = (math.pi - theta) * 2 * r + 2 * (h ** 2 - r ** 2) ** 0.5
    print("{:.2f}".format(ans * (1 + s / 100)))
