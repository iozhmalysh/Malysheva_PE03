def bubble_sort(list):
    n = len(list)
    for i in range(n):
        for j in range(0, n - i - 1):
            if list[j] > list[j + 1]:
                list[j], list[j + 1] = list[j + 1], list[j]
    


def bead_sort(array):
    if not array:
        return []

    max_value = max(array)
    beads = [[0] * max_value for _ in range(len(array))]

    # Заполняем бусинами
    for i, num in enumerate(array):
        for j in range(num):
            beads[i][j] = 1

    # "Падение" бусин
    for j in range(max_value):
        sum_beads = 0
        for i in range(len(array)):
            sum_beads += beads[i][j]
        for i in range(len(array)):
            beads[i][j] = 1 if i < sum_beads else 0

    # Восстановление отсортированного массива
    sorted_array = []
    for i in range(len(array)):
        count = sum(beads[i])
        sorted_array.append(count)
    #Для сортировки по возрастанию применим bubble sort
    bubble_sort(sorted_array)
    return sorted_array
    
