def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def ternary_search(arr, target, left=0, right=None):
  #Отсортируем 
    ar = bubble_sort(arr)
    print("Отсортировка:",ar)
    if right is None:
        right = len(ar) - 1

    if left > right:
        return -1  # элемент не найден

    # Делим диапазон на три части
    third_part = (right - left) // 3
    mid1 = left + third_part
    mid2 = right - third_part

    # Проверяем середины
    if ar[mid1] == target:
        return mid1
    if ar[mid2] == target:
        return mid2

    # Решаем, в какой части искать дальше
    if target < ar[mid1]:
        return ternary_search(ar, target, left, mid1 - 1)
  
    elif target > arr[mid2]:
        return ternary_search(arr, target, mid2 + 1, right)
    else:
        return ternary_search(arr, target, mid1 + 1, mid2 - 1)
