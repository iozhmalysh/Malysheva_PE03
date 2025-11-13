import math

def jump_search(arr, x):
    n = len(arr)
    step = int(math.sqrt(n))  # Размер шага
    prev = 0
    
    # Поиск блока, в котором может находиться элемент
    while prev < n and arr[min(step, n) - 1] < x:
        prev = step
        step += int(math.sqrt(n))
        if prev >= n:
            return -1  # Элемент не найден
    
    # Линейный поиск внутри блока
    for i in range(prev, min(step, n)):
        if arr[i] == x:
            return i  # Индекс найденного элемента
    
    return -1  # Элемент не найден

