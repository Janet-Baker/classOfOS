#include <stdio.h>

struct A {
    int a;
    int b;
};

int main() {
    // 整形
    int a;
    a=15;
    // 数组
    int b[5];
    b[0]=15;
    b[4]=15;
    // 结构体
    struct A c;
    c.a=15;
    c.b=15;
    // 指针
    int *d;
    d=&a;
    *d=1;
    // 二重指针
    int **e;
    e=&d;
    **e=15;
    // 三重指针
    int ***f;
    f=&e;
    ***f=1;

    // 防止优化
    printf("%d",a);
    printf("%d",b[0]);
    printf("%d",b[4]);
    printf("%d",c.a);
    printf("%d",c.b);
    printf("%d",*d);
    printf("%d",**e);
    printf("%d",***f);

    return 0;
}
