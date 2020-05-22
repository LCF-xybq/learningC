#include <stdio.h>
#include <stdlib.h>

int main() {
	int c;
	FILE *in, *out;

	in = fopen("words.in", "r");
	out = fopen("words.out", "w");

	while ((c = fgetc(in)) != EOF)
		fputc(c, out);

	exit(0);
}
