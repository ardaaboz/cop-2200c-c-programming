#include "header.h" // For testing purpose: To verify function definition
#include <stdio.h>
#include <string.h>

FindMthIndexOf

    int count = 0;
    int index = -1;
    int i;

    for (i = 0; i < strlen(srcString); ++i) {
        if (srcString[i] == '!') {
            count += 1;
            if (count == m) {
                index = i;
            }
        }
    }
    return index;
}

int main(void) {
    const int MAX_SIZE = 100;
    char namesString[MAX_SIZE];
    int num;
    int foundAt;

    fgets(namesString, MAX_SIZE, stdin);
    scanf("%d", &num);

    foundAt = FindMthIndexOfExclamation(namesString, num);

    if (foundAt == -1) {
        printf("'!' occurs less than %d times\n", num);
    }
    else {
        printf("m is %d. The m-th occurrence of '!' is at index %d.\n", num, foundAt);
    }

    return 0;
}