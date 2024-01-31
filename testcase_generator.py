import random

MAX = 10
print(1)
# depends on parameters
N = 10
print(N)
print(*[random.randint(1, MAX) for _ in range(N)])
