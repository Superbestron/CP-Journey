import sys
from math import hypot

EPS = 1e-9
x1, y1, x2, y2 = map(float, input().split())
found = False
for line in sys.stdin:
    x, y = map(float, line.split())
    dist1 = hypot(x1 - x, y1 - y)
    dist2 = hypot(x2 - x, y2 - y)
    if dist2 - 2 * dist1 > EPS:
        print(f"The gopher can escape through the hole at ({x},{y}).")
        found = True
        break
if not found:
    print("The gopher cannot escape.")
