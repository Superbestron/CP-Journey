ori = input().split()
v = []
op = {"add", "mul", "sub", "rem", "pow"}
mp = {"zero": 0, "one": 1, "two": 2, "three": 3, "four": 4, "five": 5,
      "six": 6, "seven": 7, "eight": 8, "nine": 9}

for s in ori:
    if s not in op:
        nums = s.split('c')
        total_sum = 0
        for num_str in nums:
            if num_str not in mp:
                print("expression evaluation stopped invalid words present")
                exit(0)
            total_sum *= 10
            total_sum += mp[num_str]
        v.append(str(total_sum))
    else:
        v.append(s)

stk = []
for i in range(len(v) - 1, -1, -1):
    current_str = v[i]
    if current_str in op:
        if len(stk) < 2:
            print("expression is not complete or invalid")
            exit(0)
        first = stk.pop()
        second = stk.pop()
        if first in op or second in op:
            print("expression is not complete or invalid")
            exit(0)
        if current_str == "add":
            stk.append(str(int(first) + int(second)))
        elif current_str == "sub":
            ans = int(first) - int(second)
            stk.append(str(int(first) - int(second)))
        elif current_str == "mul":
            stk.append(str(int(first) * int(second)))
        elif current_str == "rem":
            if int(second) == 0:
                print("expression is not complete or invalid")
                exit(0)
            ans = int(first) % int(second)
            stk.append(str(ans))
        else:
            ans = 1
            for i in range(int(second)):
                ans *= int(first)
            stk.append(str(ans))
    else:
        stk.append(current_str)

if len(stk) != 1:
    print("expression is not complete or invalid")
else:
    print(stk[0])
