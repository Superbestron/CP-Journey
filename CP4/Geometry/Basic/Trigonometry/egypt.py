import sys

# Be careful, the numbers might not be given in sorted order
for line in sys.stdin:
    ls = list(map(int, line.split()))
    if ls[0] == 0 and ls[1] == 0 and ls[2] == 0:
        break
    ls.sort()
    if ls[0] ** 2 + ls[1] ** 2 == ls[2] ** 2:
        print("right")
    else:
        print("wrong")
