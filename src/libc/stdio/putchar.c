#include <stdio.h>

int putchar(int chr) {
	return putc(chr, stdout);
}
