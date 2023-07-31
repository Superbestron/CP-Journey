k = int(input())
me = input()
friend = input()

same = 0
for i in range(len(me)):
    if me[i] == friend[i]:
        same += 1
print(- abs(same - k) + len(me))
