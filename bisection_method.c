#include <stdio.h>		// printf
#include <stdlib.h>		// exit
#include <math.h>		// pow

/*
 * Lineer olmayan, analitik cozumu olmayan, bir bilinmeyenli denklem
 */
#define EQUATION ((x*x*x) - (7*(x*x)) + (14*x) - 6)

/*
 * Soruda verilen hata payi.
 */
#define TOLERANCE 0.01

/*
 * Fonksiyon sureklidir.
 */
float
f(float x)
{
	return (EQUATION);
}

/*
 * Uyuglanan aralik 'kapali aralik' tir.
 */
float
bisection_method(float low, float high, float tolerance)
{
	float f_low = f(low);
	float f_high = f(high);

	float mid;
	float f_mid;

	int iter_count = 0;
	/* eger soruda reel kok verilmemis ise... */
	while (((high - low) / pow(2, iter_count++)) >= tolerance) {
		/*
		 * x = 0 icin tam emin degilim.
		 */
		if (f_low * f_high >= 0) {
			printf("No root!\n");
			exit(1);
		}

		mid = (low + high) / 2;
		f_mid = f(mid);

		if (f_mid < 0) {
			low = mid;
		} else {
			if (f_mid > 0) {
				high = mid;
			}
		}
	}
	return (mid);
}

int main
(int argc, char **argv)
{
	/*
	 * Soru : x^3 -7x^2 + 14x -6 denkleminin
	 * [0, 1] kapali araliginda 0.01 hatadan az olacak bicimde
	 * yaklasik kokunu bulunuz.
	 */
	float ans = bisection_method(-1, 1, TOLERANCE);
	printf("%f\n", ans);
	return (0);
}
