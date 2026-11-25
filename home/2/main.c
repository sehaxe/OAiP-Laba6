#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../common.h"

static int positive_sum(const int a[], int m)
{
    int j, sum = 0;

    for (j = 0; j < m; j++)
        if (a[j] > 0) sum += a[j];
    return sum;
}

/* Сортировка строк методом Шелла по возрастанию суммы положительных. */
static void sort_rows(int **a, int n, int m)
{
    int gap, i, j;

    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 &&
                 positive_sum(a[j], m) > positive_sum(a[j + gap], m); j -= gap) {
                int *t = a[j];
                a[j] = a[j + gap];
                a[j + gap] = t;
            }
}

static void fill_matrix(int ***a, int *n, int *m)
{
    int i, j, mode;

    read_int("Строк n (1..20): ", 1, 20, n);
    read_int("Столбцов m (1..20): ", 1, 20, m);
    read_int("Заполнение: 1 - вручную, 2 - случайно: ", 1, 2, &mode);

    *a = xmalloc((size_t)*n * sizeof **a);
    for (i = 0; i < *n; i++) {
        (*a)[i] = xmalloc((size_t)*m * sizeof ***a);
        for (j = 0; j < *m; j++) {
            if (mode == 1) {
                char prompt[32];
                snprintf(prompt, sizeof prompt, "a[%d][%d] = ", i, j);
                read_value(prompt, &(*a)[i][j]);
            } else {
                (*a)[i][j] = rand() % 101 - 50;
            }
        }
    }
}

static void print_matrix(const char *title, int **a, int n, int m)
{
    int i, j;

    printf("%s\n", title);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) printf("%5d", a[i][j]);
        putchar('\n');
    }
}

static void free_matrix(int **a, int n)
{
    int i;

    for (i = 0; i < n; i++) free(a[i]);
    free(a);
}

int main(void)
{
    int **a, n, m;

    srand((unsigned)time(NULL));
    fill_matrix(&a, &n, &m);
    print_matrix("Введённая матрица:", a, n, m);

    sort_rows(a, n, m);
    print_matrix("Матрица после сортировки строк:", a, n, m);

    free_matrix(a, n);
    return 0;
}
