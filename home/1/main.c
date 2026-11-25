#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../common.h"

#define MAX_N 100

static void print_array(const char *title, const int a[], int n)
{
    int i;

    printf("%s\n", title);
    for (i = 0; i < n; i++) printf("%5d", a[i]);
    putchar('\n');
}

static int max_index(const int a[], int n)
{
    int i, best = 0;

    for (i = 1; i < n; i++)
        if (a[i] > a[best]) best = i;
    return best;
}

/* Пузырьковая сортировка чётных элементов после максимального. */
static void sort_even_after_max(int a[], int n)
{
    int start = max_index(a, n) + 1;
    int i, j, k = 0, count = 0;
    int *evens;

    for (i = start; i < n; i++)
        if (a[i] % 2 == 0) count++;
    if (count == 0) return;

    evens = xmalloc((size_t)count * sizeof *evens);
    for (i = start; i < n; i++)
        if (a[i] % 2 == 0) evens[k++] = a[i];

    for (i = 0; i < count - 1; i++)
        for (j = 0; j < count - 1 - i; j++)
            if (evens[j] > evens[j + 1]) {
                int t = evens[j];
                evens[j] = evens[j + 1];
                evens[j + 1] = t;
            }

    k = 0;
    for (i = start; i < n; i++)
        if (a[i] % 2 == 0) a[i] = evens[k++];
    free(evens);
}

int main(void)
{
    int *a, n, mode, i;
    char prompt[32];

    srand((unsigned)time(NULL));
    read_int("Размер массива n (1..100): ", 1, MAX_N, &n);
    read_int("Заполнение: 1 - вручную, 2 - случайно: ", 1, 2, &mode);

    a = xmalloc((size_t)n * sizeof *a);
    for (i = 0; i < n; i++) {
        if (mode == 1) {
            snprintf(prompt, sizeof prompt, "a[%d] = ", i);
            read_value(prompt, &a[i]);
        } else {
            a[i] = rand() % 201 - 100;
            printf("a[%d] = %d\n", i, a[i]);
        }
    }

    print_array("Введённый массив:", a, n);
    sort_even_after_max(a, n);
    print_array("Массив после сортировки:", a, n);

    free(a);
    return 0;
}
