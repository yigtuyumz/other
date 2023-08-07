//TODO man 3 getopt

#include <unistd.h>
#include <stdlib.h> // exit, malloc
#include <getopt.h>

#define PROGRAM_NAME    "Get Long Options"
#define PROGRAM_AUTHOR  "Wagabond12"
#define PROGRAM_VERSION "Version 1.0"

/*
 * Hangi descriptor'un stantart olarak hangi degerde oldugunu belirtmek icin
 * enum icerisinde deger atamalari yapilmistir.
 */
enum {
	STDIN  = 0,
	STDOUT = 1,
	STDERR = 2,
};

/*
 * getopt.h icindeki option struct'u.
 */
typedef struct long_opt_s {
	const char	*name;
	/*
	 * 0            no_argument          deger almayan arguman
	 * 1            required_argument    bir deger almasi zorunlu arguman
	 * 2            optional_argument    istege bagli deger alan arguman
	 */
	int		has_arg;
	/*
	 * NULL verilirse val degeri doner.
	 * diger turlu 0 degeri doner.
	 */
	int		*flag;
	int		val;
} long_opt_t;

/*
 * Bir adet karakteri ekrana yazar.
 */
void
my_putchar(int file_descriptor, char c)
{
	write(file_descriptor, &c, 1);
}

/*
 * String'in kac karakterden olustugunu dondurur.
 */
size_t
my_strlen(const char *str)
{
	size_t len = 0;
	while (*(str + len)) {
		len++;
	}

	return (len);
}

/*
 * String'in n degerine kadar kac karakterden olustugunu dondurur.
 */
size_t
my_strnlen(const char *str, size_t n)
{
	size_t len = 0;
	while (*(str + len) && len < n) {
		len++;
	}

	return (len);
}

/*
 * Belirtilen descriptor'a string'i yazar.
 *
 * unistd.h icerisinde
 * 0    STDIN_FILENO
 * 1    STDOUT_FILENO
 * 2    STDERR_FILENO
 * tanimlari bulunmaktadir.
 */
void
my_putstr(int file_descriptor, const char *str)
{
	write(file_descriptor, str, my_strlen(str));
}

/*
 * Sayisal degerleri ekrana yazar.
 */
void
my_putnbr(int file_descriptor, int nb)
{
	if (nb < 0) {
		my_putchar(file_descriptor, 45);
		if (nb == -2147483648) {
			nb = -147483648;
			my_putchar(file_descriptor, 50);
		}
		nb *= -1;
	}
	if (nb > 10) {
		my_putnbr(file_descriptor, (nb / 10));
		nb = nb % 10;
	}
	if (nb < 10) {
		my_putchar(file_descriptor, (nb + 48));
	}
}

/*
 * hatali veya eksik kullanim durumunda program kullanimini aciklayan fonksiyon.
 */
void
program_usage(int file_description, char *program_name)
{
	my_putstr(file_description, "Usage ");
	my_putstr(file_description, program_name);
	my_putstr(file_description, " [options]\n");
	my_putstr(file_description, "Options:\n");
	my_putstr(file_description, "  -a, --author         Display the author of this program.\n");
	my_putstr(file_description, "  -V, --version        Display the version of this program.\n");
	my_putstr(file_description, "  -n, --name           Display the full name of this program.\n");
	my_putstr(file_description, "  --var                Debug of required_argument.\n");
	my_putstr(file_description, "  -n, --help           Display this menu.\n");
}

// TODO

/*
 * Eger tekil bir argumanda birden fazla karakter varsa
 * ornegin -abc argumanini getopts fonksiyonlari
 * -a -b -c
 * olarak degerlendiriyor.
 * Asagidaki fonksiyon bu durumu engellemek icin vardir.
 */
int
filter_arg(const char *s)
{
	return ((my_strlen(s) == 2) && (*s == '-'));
}

int
main(int argc, char **argv)
{
	int	opt;
	int	opt_index;

	/*
	 * Array olusturdugumuz icin son argumani NULL olarak ayarliyoruz.
	 */
	const	long_opt_t opts[] = {
		{"author",  no_argument,       NULL, 'a'},
		{"version", no_argument,       NULL, 'V'},
		{"name",    no_argument,       NULL, 'n'},
		{"var",     required_argument, NULL,  0 },
		{"help",    no_argument      , NULL, 'h'},
		{NULL,      0,                 NULL,  0 }
	};
/*
 * 	int getopt_long(
 * 	        int argc,
 * 	        char *argv[],
 * 	        const char *opstring,
 * 	        const struct option *longopts,
 * 	        int *longindex
 * 	);
 */
	/*
	 * getopt mesajlarini gizler.
	 */
	opterr = 0;
	while (1) {
		opt_index = 0;
		opt = getopt_long(argc, argv, "0aVnr:h", (const struct option*)opts, &opt_index);

		/*
		 * getopt sonlandiginda -1 degeri dondurur.
		 */
		if (opt == -1) {
			break ;
		}

		switch (opt) {
			case 0:
				my_putstr(STDOUT, opts[opt_index].name);
				my_putstr(STDOUT, "\n");
				break ;
			case 'a':
				my_putstr(STDOUT, PROGRAM_AUTHOR);
				my_putstr(STDOUT, "\n");
				break ;
			case 'V':
				my_putstr(STDOUT, PROGRAM_VERSION);
				my_putstr(STDOUT, "\n");
				break ;
			case 'n':
				my_putstr(STDOUT, PROGRAM_NAME);
				my_putstr(STDOUT, "\n");
				break ;
			case 'r':
				my_putstr(STDOUT, optarg);
				my_putstr(STDOUT, "\n");
				break ;
			case 'h':
				program_usage(STDERR, argv[0]);
				break ;
			default :
				my_putstr(STDERR, "Unknown option argument: ");
				my_putstr(STDERR, "\"--");
				my_putstr(STDERR, opts[opt_index].name);
				my_putstr(STDERR, "\"\n");
				my_putstr(STDERR, "More info with: \"");
				my_putstr(STDERR, argv[0]);
				my_putstr(STDERR, " -h\n");
				break ;
		}
	}
	return (0);
}

