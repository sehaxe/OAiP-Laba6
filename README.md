# OAiP-Laba6

Лабораторная работа №6 по ОАиП (БГУИР), тема «Сортировки», вариант 5.
Две задачи на Си с динамическим выделением памяти и готовый отчёт
без блок-схем: условия, ход решения, листинги и реальные прогоны.

## Быстрый запуск

```bash
git clone https://github.com/sehaxe/OAiP-Laba6
cd OAiP-Laba6/home
make            # соберёт 1/main, 2/main
./1/main
./2/main
```

Нужен только `gcc`. Готовый отчёт: `home/report/main.pdf`.

## Задачи

| № | Условие (вариант 5) | Файл |
|----|---------------------|------|
| 1 | Отсортировать чётные элементы после максимального методом пузырька | `home/1/main.c` |
| 2 | Сортировать строки матрицы по возрастанию суммы положительных методом Шелла | `home/2/main.c` |

## Пересборка отчёта

```bash
cd home
make report     # gcc -> term.json -> report/main.pdf
```

Нужны `gcc`, `python3` и `typst`. Блок-схем в этой работе нет.

Общее — `home/common.h`: `read_int`, `read_value`, `xmalloc`.
Компиляция: `gcc -std=c11 -Wall -Wextra -Werror -pedantic`.

## Структура

```
home/1/main.c .. home/2/main.c   задачи
home/common.h                    ввод и выделение памяти
home/report/main.typ             исходник отчёта
home/report/main.pdf             готовый отчёт
home/report/assets/term.json     реальный вывод программ
template/oaip.typ                оформление отчёта
```
