#include <stdio.h>
#include "two-sum-1.c"

int main(void){
    int num1 = 10;
    float num2 = 3.14f;
    char num3 = 'a';
    double num4 = 5.12;
    short num5 = 10;
    long num6 = 10;
    long long  num7 = 0;
    printf("%llu %llu %llu %llu %llu %llu %llu",
           sizeof(num1), sizeof(num2),
           sizeof(num3), sizeof(num4),
           sizeof(num5), sizeof(num6),
           sizeof(num7));
    return 0;
}