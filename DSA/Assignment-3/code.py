def return_r(arr):
    for i in arr:
        cnt = arr.count(i)
        if cnt > 1:
            return i
    return -1


def sort_around_r(arr, r):
    less = [x for x in arr if x < r]
    equal = [x for x in arr if x == r]
    greater = [x for x in arr if x > r]
    return less + equal + greater


arr = list(map(int, input("Enter integers separated by spaces: ").split()))
r = return_r(arr)
sorted_arr = sort_around_r(arr, r)
print(sorted_arr)
