import sys

f0 = "F_in_Finals_stands_for_Fizz_Buzz!"
first = "_in_"
second = "inals_stands_for_"
third = "izz_Buzz!"
output = []
length = [33] * 36

for i in range(1, 36):
    length[i] = length[i - 1] * 3 + 30


def f(seq, idx):
    if seq == 0:
        return f0[idx]
    prev_f = length[seq - 1]
    if idx < prev_f:
        return f(seq - 1, idx)
    idx -= prev_f
    if idx < 4:
        return first[idx]
    idx -= 4
    if idx < prev_f:
        return f(seq - 1, idx)
    idx -= prev_f
    if idx < 17:
        return second[idx]
    idx -= 17
    if idx < prev_f:
        return f(seq - 1, idx)
    idx -= prev_f
    return third[idx]


def solve(x, y):
    x -= 1
    y = min(y, 35)
    if x >= length[y]:
        output.append('?')
    else:
        output.append(f(y, x))

input()
for line in sys.stdin:
    x, y = map(int, line.split())
    solve(x, y)
sys.stdout.write(''.join(output))
