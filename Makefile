CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -pedantic -O2

.PHONY: all test clean
all: demo
demo: monitor.c monitor.h demo.c
	$(CC) $(CFLAGS) monitor.c demo.c -o $@
test-bin: monitor.c monitor.h test.c
	$(CC) $(CFLAGS) monitor.c test.c -o $@
test: test-bin
	./test-bin
clean:
	rm -f demo test-bin
