#include <stdio.h>

int print2(void){
    unsigned int un = 3000000000;
    short end = 200;
    long big = 65537;
    long long veryBig = 12345678908642;
    printf("un = %u and not %d\n", un, un);
    printf("end = %hd and %d\n", end, end);
    printf("big = %ld and not %hd\n", big, big);
    printf("veryBig = %lld and not %ld\n", veryBig, veryBig);
    return 0;
}