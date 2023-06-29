import math
import sys

for line in sys.stdin:
    n = int(line)
    s = str(input().strip())
    ans = ''
    limit = math.pow(2, n)
    slash = '\\' * int(limit - 1)
    for char in s:
        if '!' <= char <= '*' or '[' <= char <= ']':
            ans += slash
        ans += char
    print(ans)