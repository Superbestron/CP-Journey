K = int(input())
smallest = 1
while smallest < K:
    smallest *= 2
ctr = smallest
breaks = 0
while K > 0:
    if K >= ctr:
        K -= ctr
    else:
        ctr /= 2
        breaks += 1
print(smallest, breaks)