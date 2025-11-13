def flip(arr, k):
   # Переворачивает первые k элементов массива
    arr[:k] = arr[:k][::-1]

def pancake_sort(arr):
    n = len(arr)
    for curr_size in range(n, 1, -1):
        # Находим индекс максимального элемента в текущем диапазоне
        max_idx = arr.index(max(arr[:curr_size]))

        # Если максимум уже на своем месте, пропускаем
        if max_idx == curr_size - 1:
            continue

        # Если максимум не на вершине, переворачиваем его туда
        if max_idx != 0:
            flip(arr, max_idx + 1)

        # Переворачиваем весь текущий диапазон, чтобы максимум оказался на правильной позиции
        flip(arr, curr_size)

    return arr

