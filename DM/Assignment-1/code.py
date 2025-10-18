def helper(matrix, n):
    i = 0
    for j in range(1, n):
        if matrix[i][j]:
            i = j
    for j in range(n):
        if j == i:
            continue
        if matrix[i][j] or not matrix[j][i]:
            return -1
        return i


n = int(input("Enter the number of persons: "))
matrix = [
    list(map(int, input(f"Enter the details about person-{i+1}: ").split()))
    for i in range(n)
]
celeb = helper(matrix, n)
if celeb == -1:
    print("There is no celebrity")
else:
    print(f"Person {celeb+1} is a celebrity")
