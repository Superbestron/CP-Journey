import sys

x_max, y_max = map(int, input().split())

windows = []
window_ctr = 0


# One of the most tedious questions...
# I'll only discuss the non-trivial MOVE operation
# 1. Partition the windows into "moving" and "non-moving" set
# 2. For each window in the moving set, calculate the nearest distance min
#    between all possible pairs of moving and non-moving windows.
#    Don't forget to also take into the account the global bounds.
# 3. Move all the moving windows by min, and put the nearest non-moving window
#    into the moving set.
# 4. Repeat this process till the distance to arr = 0 or no more further moves
#    can be made.


def arr(x, y, dx, dy, idx):
    window = has_window(x, y)
    if window is None:
        print(f"Command {idx}: MOVE - no window at given position")
        return
    global windows
    non_moving_windows = [i for i in windows]
    non_moving_windows.remove(window)
    moving_windows = [window]

    def move_window(dx, dy):
        nonlocal moving_windows, non_moving_windows
        if dx == 0 and dy == 0:
            return 0
        nearest_window = ()
        if dx > 0:
            minx = dx
            for (x1, y1, w1, h1, _) in moving_windows:
                minx = min(minx, x_max - (x1 + w1))
            for (x1, y1, w1, h1, _) in moving_windows:
                for (x2, y2, w2, h2, ctr2) in non_moving_windows:
                    if y2 + h2 <= y1 or y1 + h1 <= y2:  # not in path
                        continue
                    if x1 + w1 + dx > x2 >= x1 + w1:  # in the path
                        if x2 - (x1 + w1) < minx:
                            minx = x2 - (x1 + w1)
                            nearest_window = (x2, y2, w2, h2, ctr2)
            moving_windows = [(x1 + minx, y1, w1, h1, ctr1) for (x1, y1, w1, h1, ctr1) in moving_windows]
            if nearest_window:
                moving_windows.append(nearest_window)
                non_moving_windows.remove(nearest_window)
                return minx + move_window(dx - minx, dy)
            else:
                return minx
        elif dx < 0:
            dx = -dx
            minx = dx
            for (x1, y1, w1, h1, _) in moving_windows:
                minx = min(minx, x1)
            for (x1, y1, w1, h1, _) in moving_windows:
                for (x2, y2, w2, h2, ctr2) in non_moving_windows:
                    if y2 + h2 <= y1 or y1 + h1 <= y2:  # not in path
                        continue
                    if x1 - dx < x2 + w2 <= x1:  # in the path
                        if x1 - (x2 + w2) < minx:
                            minx = x1 - (x2 + w2)
                            nearest_window = (x2, y2, w2, h2, ctr2)
            moving_windows = [(x1 - minx, y1, w1, h1, ctr1) for (x1, y1, w1, h1, ctr1) in moving_windows]
            if nearest_window:
                moving_windows.append(nearest_window)
                non_moving_windows.remove(nearest_window)
                return minx + move_window(-(dx - minx), dy)
            else:
                return minx
        elif dy > 0:
            miny = dy
            for (x1, y1, w1, h1, _) in moving_windows:
                miny = min(miny, y_max - (y1 + h1))
            for (x1, y1, w1, h1, _) in moving_windows:
                for (x2, y2, w2, h2, ctr2) in non_moving_windows:
                    if x2 + w2 <= x1 or x1 + w1 <= x2:  # not in path
                        continue
                    if y1 + h1 + dy > y2 >= y1 + h1:  # in the path
                        if y2 - (y1 + h1) < miny:
                            miny = y2 - (y1 + h1)
                            nearest_window = (x2, y2, w2, h2, ctr2)
            moving_windows = [(x1, y1 + miny, w1, h1, ctr1) for (x1, y1, w1, h1, ctr1) in moving_windows]
            if nearest_window:
                moving_windows.append(nearest_window)
                non_moving_windows.remove(nearest_window)
                return miny + move_window(dx, dy - miny)
            else:
                return miny
        else:
            dy = -dy
            miny = dy
            for (x1, y1, w1, h1, _) in moving_windows:
                miny = min(miny, y1)
            for (x1, y1, w1, h1, _) in moving_windows:
                for (x2, y2, w2, h2, ctr2) in non_moving_windows:
                    if x2 + w2 <= x1 or x1 + w1 <= x2:  # not in path
                        continue
                    if y1 - dy < y2 + h2 <= y1:  # in the path
                        if y1 - (y2 + h2) < miny:
                            miny = y1 - (y2 + h2)
                            nearest_window = (x2, y2, w2, h2, ctr2)
            moving_windows = [(x1, y1 - miny, w1, h1, ctr1) for (x1, y1, w1, h1, ctr1) in moving_windows]
            if nearest_window:
                moving_windows.append(nearest_window)
                non_moving_windows.remove(nearest_window)
                return miny + move_window(dx, -(dy - miny))
            else:
                return miny

    dist = move_window(dx, dy)
    windows = moving_windows + non_moving_windows
    if dist < max(abs(dx), abs(dy)):
        print(f"Command {idx}: MOVE - moved {dist} instead of {max(abs(dx), abs(dy))}")


def check_fit(x, y, w, h):
    if x + w > x_max or y + h > y_max:
        return False
    for (winx, winy, winw, winh, _) in windows:
        ## clashes in both axis
        if not (x + w <= winx or x >= winx + winw) and not (y + h <= winy or y >= winy + winh):
            return False
    return True


def has_window(x, y):
    for (winx, winy, winw, winh, _) in windows:
        if winx <= x < winx + winw and winy <= y < winy + winh:
            return winx, winy, winw, winh, _
    return None


def open(x, y, w, h, idx, ctr):
    if not check_fit(x, y, w, h):
        print(f"Command {idx}: OPEN - window does not fit")
        return
    windows.append((x, y, w, h, ctr))


def close(x, y, idx):
    window = has_window(x, y)
    if window is None:
        print(f"Command {idx}: CLOSE - no window at given position")
    else:
        windows.remove(window)


def resize(x, y, w, h, idx):
    window = has_window(x, y)
    if window is None:
        print(f"Command {idx}: RESIZE - no window at given position")
        return
    windows.remove(window)
    if check_fit(window[0], window[1], w, h):
        windows.append((window[0], window[1], w, h, window[4]))
    else:
        windows.append(window)
        print(f"Command {idx}: RESIZE - window does not fit")


for idx, line in enumerate(sys.stdin):
    if len(line) == 1:
        break
    idx += 1
    ls = list(line.split())
    param = [int(i) for i in ls[1:]]
    if ls[0] == "OPEN":
        open(param[0], param[1], param[2], param[3], idx, window_ctr)
        window_ctr += 1
    elif ls[0] == "RESIZE":
        resize(param[0], param[1], param[2], param[3], idx)
    elif ls[0] == "MOVE":
        arr(param[0], param[1], param[2], param[3], idx)
    else:
        close(param[0], param[1], idx)
print(f"{len(windows)} window(s):")
windows.sort(key=lambda window: window[4])
for (x, y, w, h, _) in windows:
    print(x, y, w, h)
