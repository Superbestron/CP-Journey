import sys

factorial = [1]
for i in range(1, 101):
    factorial.append(factorial[i - 1] * i)

for line in sys.stdin:
    dict = {}
    sum = factorial[len(line) - 1]
    for c in line:
        if c not in dict:
            dict[c] = 1
        else:
            dict[c] += 1
    for k, v in dict.items():
        sum //= factorial[v]
    print(sum)
