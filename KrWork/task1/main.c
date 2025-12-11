#include <stdio.h>

#define MAX_SIZE 1000

void sortArray(int array[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printFrequencies(int sortedArray[], int count) {
    if (count == 0) {
        return;
    }

    int current = sortedArray[0];
    int frequency = 1;

    for (int i = 1; i < count; i++) {
        if (sortedArray[i] == current) {
            frequency++;
        } else {
            printf("%d встречается %d раз(а)\n", current, frequency);
            current = sortedArray[i];
            frequency = 1;
        }
    }

    printf("%d встречается %d раз(а)\n", current, frequency);
}

int main() {
    int numbers[MAX_SIZE];
    int count = 0;

    printf("Введите целые числа (0 — конец ввода):\n");

    while (1) {
        int value;
        printf("Число: ");
        scanf("%d", &value);

        if (value == 0) {
            break;
        }

        if (count < MAX_SIZE) {
            numbers[count] = value;
            count++;
        }
    }

    sortArray(numbers, count);
    printFrequencies(numbers, count);

    return 0;
}
