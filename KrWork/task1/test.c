#include <assert.h>

void sortArray(int array[], int count);

void testSorted() {
    int data[] = {1, 2, 3, 4};
    sortArray(data, 4);

    assert(data[0] == 1);
    assert(data[1] == 2);
    assert(data[2] == 3);
    assert(data[3] == 4);
}

void testReversed() {
    int data[] = {4, 3, 2, 1};
    sortArray(data, 4);

    assert(data[0] == 1);
    assert(data[1] == 2);
    assert(data[2] == 3);
    assert(data[3] == 4);
}

void testDuplicates() {
    int data[] = {5, 2, 5, 4, 2, 5};
    sortArray(data, 6);

    assert(data[0] == 2);
    assert(data[1] == 2);
    assert(data[2] == 4);
    assert(data[3] == 5);
    assert(data[4] == 5);
    assert(data[5] == 5);
}

void testNegative() {
    int data[] = {-1, 3, -2, 0};
    sortArray(data, 4);

    assert(data[0] == -2);
    assert(data[1] == -1);
    assert(data[2] == 0);
    assert(data[3] == 3);
}

int main() {
    testSorted();
    testReversed();
    testDuplicates();
    testNegative();

    return 0;
}