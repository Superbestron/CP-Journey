import math
import sys

for line in sys.stdin:
    r, m, c = map(float, line.split())
    if r == 0 and m == 0 and c == 0:
        break
    real_area = math.pi * r ** 2
    experimental_area = c / m * (2 * r) ** 2
    print(real_area, experimental_area)
