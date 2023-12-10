// #include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

// EXTERNS
// extern int optind;
// extern int opterr;
// extern int optopt;
// extern char *optarg;

// #define no_argument          0
// #define required_argument    1
// #define optional_argument    2

// harfin saginda ':' var ise, zorunlu arguman required_argument
// harfin saginda '::' var ise, opsiyonel arguman optional_argument
const char *opstr = "a::b::c:";


const struct option long_options[] = {
//    name           has_arg        flag  val
//    char *         int            int * int
	{"option_a", optional_argument, NULL, 'a' },
	{"option_b", optional_argument, NULL, 'b' },
	{"option_c", required_argument, NULL, 'c' },
	{0,          0,                 NULL,  0 }

};


void
program_usage(void)
{
	printf("Usage test.c [options]\n");
	printf("Options:\n");
	printf(" -a --option_a [optional] Does nothing.\n");
	printf(" -b --option_b [optional] Does nothing.\n");
	printf(" -c --option_c [required] Does nothing.\n");
}


// !! TEMPORARILY DEFINED !! //
void
dojob_a(void)
{
	printf("JOB A EXECUTED.\n");
}

void
dojob_b(void)
{
	printf("JOB B EXECUTED.\n");
}

void
dojob_c(char *value)
{
	printf("JOB C EXECUTED WITH '%s'.\n", value);
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		program_usage();
		exit(EXIT_FAILURE);
	}
	// opterr is an EXTERN value.
	opterr = 0; // disable getopt error messages.

	int c;
	while (1) {
		c = getopt_long(argc, argv, opstr, long_options, NULL);
		if (c == -1) {
			break ;
		} else if (c == 'a') {
			dojob_a();
		} else if (c == 'b') {
			dojob_b();
		} else if (c == 'c') {
			// optarg is an EXTERN value.
			dojob_c(optarg);
		} else {
			program_usage();
			break ;
		}
	}

	// No options provided. optind is an EXTERN value.
	if (optind < 2) {
		program_usage();
	}

	exit(EXIT_SUCCESS);
}
