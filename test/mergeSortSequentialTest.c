#include <stdio.h>
#include "../CommonFunctions/commonFunctions.h"

int main() {


    return 0;
}

void randomizeIntArray(int* array, int arraySize, int minNumber, int maxNumber) {
    int i;
    for (i = 0; i < arraySize; i++)
    {
        array[i] = randomInt(minNumber, maxNumber);
    }
}

void randomInt(int minNumber, int maxNumber) {
    return rand() % (maxNumber - minNumber + 1) + minNumber;
}
