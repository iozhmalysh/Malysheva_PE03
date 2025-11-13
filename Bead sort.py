def bead_sort(array):
    if not array:
        return []

    # Находим максимум, чтобы определить высоту
    max_value = max(array)

    # Создаем матрицу (столбцы бусин)
    beads = [[0] * max_value for _ in range(len(array))]

    # Заполняем матрицу бусинами
    for i, num in enumerate(array):
        for j in range(num):
            beads[i][j] = 1

    # "Опускаем" бусины: считаем, сколько бусин осталось в каждом столбце после "падения"
    for j in range(max_value):
        sum_beads = 0
        for i in range(len(array)):
            sum_beads += beads[i][j]
        # Расставляем бусины снизу
        for i in range(len(array)):
            beads[i][j] = 1 if i < sum_beads else 0

    # Восстанавливаем отсортированный массив
    sorted_array = []
    for i in range(len(array)):
        count = sum(beads[i])
        sorted_array.append(count)

    return sorted_array

