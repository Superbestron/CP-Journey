from math import log2

n, k = map(int, input().split())
if k >= log2(n):
    print('Your wish is granted!')
else:
    print('You will become a flying monkey!')