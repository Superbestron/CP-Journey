n = int(input())
x = 1

for i in range(1, n + 1):
    x *= i
    while x % 10 == 0:
        x //= 10
    x %= 1000000000000

print(str(x)[-3:])
