def binary_search(arr, left, right, x):
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] == x:
            return mid
        elif arr[mid] < x:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def exponential_search(arr, x):
    if len(arr) == 0:
        return -1
    
    # Первый элемент
    if arr[0] == x:
        return 0
    
    # Поиск диапазона с экспоненциальным ростом
    index = 1
    while index < len(arr) and arr[index] <= x:
        index *= 2
    
    # Выполняем бинарный поиск в найденном диапазоне
    left = index // 2
    right = min(index, len(arr) - 1)
    return binary_search(arr, left, right, x)
