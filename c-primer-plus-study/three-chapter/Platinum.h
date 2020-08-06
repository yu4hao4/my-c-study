#include <stdio.h>

int test(void){
//    体重
    float weight;
//    体重白金
    float value;
    printf("are you worth your weight in platinum?\n");
    printf("let check it out \n");
    printf("please enter your weight in pounds: \n");
//    获取用户输入
    scanf("%f", &weight);
//    假设每盎司￥1700
    value = 1700.0 * weight * 14.5833;
    printf("your weight in platinum is worth %.2f\n", value);
    printf("your are easily worth that! if platinum prices drop\n");
    printf("eat more to maintain your value");
    return 0;
}