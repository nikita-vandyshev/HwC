#include <assert.h>
#include <string.h>

void buildSmallestNumber(char input[], char output[]);

void testSingleDigit() {
    char result[10];
    buildSmallestNumber("5", result);
    assert(strcmp(result, "5") == 0);
}

void testSimplePermutation() {
    char result[10];
    buildSmallestNumber("5310", result);
    assert(strcmp(result, "1035") == 0);
}

void testWithZerosInside() {
    char result[10];
    buildSmallestNumber("1002", result);
    assert(strcmp(result, "1002") == 0);
}

void testManyZerosAndBigDigit() {
    char result[10];
    buildSmallestNumber("9000", result);
    assert(strcmp(result, "9000") == 0);
}

int main() {
    testSingleDigit();
    testSimplePermutation();
    testWithZerosInside();
    testManyZerosAndBigDigit();

    return 0;
}