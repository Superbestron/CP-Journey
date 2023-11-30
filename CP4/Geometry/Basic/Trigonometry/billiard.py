import math
import sys

for line in sys.stdin:
    a, b, s, m, n = map(int, line.split())
    if a == b == s == m == n == 0:
        break
    hori_v = m * a / s
    vert_v = n * b / s
    print(f'{math.atan(vert_v / hori_v) * 180 / math.pi:.2f} {math.hypot(vert_v, hori_v):.2f}')
