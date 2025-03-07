a = [34, 8, 64, 51, 32, 21, 34, 8, 64, 51, 32, 21, 34, 8, 64, 51, 32, 21, 34, 8, 64, 51, 32, 21]
n = len(a)

# for i in range(1, n):
#     tmp = a[i]
#     j = i
#     while j != 0 and tmp < a[j - 1]:
#         a[j] = a[j - 1]
#         j -= 1
#     a[j] = tmp

# 2^k - 1 < n
#
def highest_power_of_2(n):
    if n < 0b1:
        raise ValueError("n should be nonzero")
    if n < 0b11:
        return 0b1
    if n < 0b111:
        return 0b11
    if n < 0b1111:
        return 0b111
    if n < 0b11111:
        return 0b1111
    if n < 0b111111:
        return 0b11111

gap = highest_power_of_2(n)
while gap > 0: # 3
    for i in range(gap, n): # 3,4,5
        tmp = a[i] # = 51
        j = i # 3
        while j >= gap and tmp < a[j - gap]:
            a[j] = a[j - gap]
            j -= gap
        a[j] = tmp
    gap >>= 1

print(a)
