import sys

time = []
for line in sys.stdin:
    time = [int(x) for x in line.split()][1:]
    break

memo = [0] * (len(time) + 1)
time.sort()
memo[1] = time[0]
memo[2] = time[1]
for i in range(3, len(time) + 1):
    memo[i] = min(memo[i - 1] + time[0] + time[i - 1], memo[i - 2] + time[0] + time[i - 1] + time[1] * 2)
print(memo[len(time)])