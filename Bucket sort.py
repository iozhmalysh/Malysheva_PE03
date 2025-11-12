def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def bucket_sort(arr):
    if len(arr) == 0:
        return arr

    min_value = min(arr)
    max_value = max(arr)

    bucket_count = 10
    buckets = [[] for _ in range(bucket_count)]

    # Распределение элементов по корзинам
    for num in arr:
        index = int((num - min_value) / (max_value - min_value + 1) * bucket_count)
        if index == bucket_count:
            index -= 1
        buckets[index].append(num)

    # Сортировка каждой корзины пузырьком
    for bucket in buckets:
        bubble_sort(bucket)

    # Объединение отсортированных корзин
    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(bucket)

    return sorted_arr
