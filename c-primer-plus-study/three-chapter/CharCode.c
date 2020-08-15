#include <stdio.h>

int printCharCode(){
    char ch;
    printf("please enter a character\n");
    scanf("%c", &ch);
    printf("the code for %c is %d\n", ch, ch);
    return 0;
}