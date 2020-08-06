#include <stdio.h>

int bases(void){
    int x = 100;
    printf("dec = %d; octal = %o; hex = %x\n", x, x, x);
    printf("dec =  %d; octal = %#o; hex = %#x\n", x, x, x);
    return 0;
}