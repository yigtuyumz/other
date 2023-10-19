#include <stdio.h>     // for fprintf
#include <math.h>      // for acos, link with -lm parameter

#define RAD2DEG 57.2957795

/*
 * Creates arc-cosinus value table and writes it to file.
 */
void
create_acostable(char *filename, int precision)
{
		FILE *fp;

		if (fp = fopen(filename, "w")) {
			float delta = 1.00F / precision;
			float acos_value;
			int i = 0;
			fprintf(fp, "float acostable_deg[] = {\n");
			// print out from 1 to 0.
			while (i < precision) {
				acos_value = acos(1.00F - (delta * i));
				fprintf(fp, "\t%1.8f,\n", (acos_value * RAD2DEG));
				i++;
			}
			fprintf(fp, "}\n");
			fclose(fp);
		} else {
			fprintf(stderr, "ERROR OPEN FILE\n");
		}
}
