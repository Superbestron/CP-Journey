import random

tc = 50
print(tc)
# depends on parameters
N = 500
# print(*[random.randint(1, MAX) for _ in range(N)])
for i in range(tc):
    str = ""
    for i in range(N):
        str += chr(random.randint(ord('a'), ord('z')))
    print(str)
