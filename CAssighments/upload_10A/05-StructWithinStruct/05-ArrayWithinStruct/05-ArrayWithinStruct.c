#include <stdio.h>

struct MyPoint {
    int num;
    int num_table[10];
};

struct NumTables {
    struct MyPoint a;
    struct MyPoint b;
    struct MyPoint c;
};

int main(void) {

    struct NumTables tables;

    tables.a.num = 2;
    for (int i = 0; i < 10; i++) {
        tables.a.num_table[i] = tables.a.num * (i + 1);
    }

    tables.b.num = 3;
    for (int i = 0; i < 10; i++) {
        tables.b.num_table[i] = tables.b.num * (i + 1);
    }

    tables.c.num = 4;
    for (int i = 0; i < 10; i++) {
        tables.c.num_table[i] = tables.c.num * (i + 1);
    }

    // Display tables
    printf("\nTable of %d:\n", tables.a.num);
    for (int i = 0; i < 10; i++) {
        printf("%d x %d = %d\n", tables.a.num, i + 1, tables.a.num_table[i]);
    }

    printf("\nTable of %d:\n", tables.b.num);
    for (int i = 0; i < 10; i++) {
        printf("%d x %d = %d\n", tables.b.num, i + 1, tables.b.num_table[i]);
    }

    printf("\nTable of %d:\n", tables.c.num);
    for (int i = 0; i < 10; i++) {
        printf("%d x %d = %d\n", tables.c.num, i + 1, tables.c.num_table[i]);
    }

    return 0;
}
