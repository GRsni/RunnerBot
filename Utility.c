#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Utility.h"

void printGridLine(int cols) {
    int i;
    printf("+");
    for(i=0; i<cols; i++) {
        printf("---+");
    }
    printf("\n");
}
