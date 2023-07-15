import math

running_pow = 4
running_n = 3
m = {196: 3}
for i in range(197, 217):
    running_pow *= 2
    while running_pow - (running_n * math.log(running_n, 2) - running_n * math.log(math.e, 2) + 0.5 * math.log(2 * math.pi * running_n, 2)) >= 0:
        running_n += 1
    m[i] = running_n - 1

while True:
    y = int(input())
    if y == 0:
        break
    y //= 10
    print(m[y])

