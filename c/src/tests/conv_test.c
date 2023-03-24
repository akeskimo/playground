#include <stdio.h>
#include <stdlib.h>

void print_usage(char *prog) {
	printf("\
Usage:  %s value\n", prog);
	exit(-1);
}

long long int dtoll(double d)
{
	return (long long int)(d);
}

double lltod(long long i)
{
	return (double)i;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		print_usage(argv[0]);
		return -1;
	}

	double d = atof(argv[1]);
	printf("0x%016\n", d);

	long long int t = dtoll(d);
	double d2 = lltod(t);

	if (d != d2) {
		printf("Converted value does not match expected: %lf != %lf\n", d, d2);
	}

	return 0;
}
