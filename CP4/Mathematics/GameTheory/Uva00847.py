import sys


def stan(x):
    return x * 9


def ollie(x):
    return x * 2


for line in sys.stdin:
    n = int(line)
    p = 1
    while True:
        p = stan(p)
        if p >= n:
            print("Stan wins.")
            break
        p = ollie(p)
        if p >= n:
            print("Ollie wins.")
            break
