import sys


def gcd(a, b):
    if b > a:
        return gcd(b, a)
    if b == 0:
        return False
    if a // b == 1:
        return not gcd(b, a % b)
    # this part is not easy to see...
    # Consider a >= 2b
    # either going to (a - b, b) or (a - 2b, b) leads to victory
    # 1. (a, b) => (a - b, b)
    # If (a - b, b) leads to victory we are done
    # else (a - b, b) => (a - 2b, b) is the only possible path
    # so (a - 2b, b) must lead to victory, and in that case, proves my above point
    # This prove works for (a - xb, b)
    return True


for line in sys.stdin:
    x, y = map(int, line.split())
    if x == y == 0:
        break
    if gcd(x, y):
        print("Stan wins")
    else:
        print("Ollie wins")
