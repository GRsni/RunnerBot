#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Utility.h"
#include "bot.h"

void printGridLine(int cols) {
    int i;
    printf("+");
    for(i=0; i<cols; i++) {
        printf("---+");
    }
    printf("\n");
}

void printIcon(char c) {
    if(c==PAREDC) {
        printf("%c%c%c|", c, c, c);
    } else {
        printf(" %c |", c);
    }
}
