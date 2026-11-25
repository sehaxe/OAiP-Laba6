all: 1/main 2/main

.PHONY: report screens clean

report: all screens
	typst compile --root .. report/main.typ

1/main: 1/main.c common.h
	gcc -std=c11 -Wall -Wextra -Werror -pedantic 1/main.c -o 1/main

2/main: 2/main.c common.h
	gcc -std=c11 -Wall -Wextra -Werror -pedantic 2/main.c -o 2/main

screens: all
	python3 report/make_screens.py

clean:
	rm -f 1/main 2/main
