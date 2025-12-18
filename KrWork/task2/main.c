#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void buildSmallestNumber(char input[], char output[]) {
    int digits[10];
    for (int i = 0; i < 10; i++) {
        digits[i] = 0;
    }

    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        int d = input[i] - '0';
        digits[d]++;
    }

    int index = 0;

    for (int d = 1; d <= 9; d++) {
        if (digits[d] > 0) {
            output[index] = d + '0';
            index++;
            digits[d]--;
            break;
        }
    }

    while (digits[0] > 0) {
        output[index] = '0';
        index++;
        digits[0]--;
    }

    for (int d = 1; d <= 9; d++) {
        while (digits[d] > 0) {
            output[index] = d + '0';
            index++;
            digits[d]--;
        }
    }

    output[index] = '\0';
}

int main() {
    char input[MAX_LEN];
    char result[MAX_LEN];

    printf("Введите натуральное число: ");
    scanf("%s", input);

    buildSmallestNumber(input, result);

    printf("Наименьшее число: %s\n", result);

    return 0;
}