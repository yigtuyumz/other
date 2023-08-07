#include <unistd.h>

/*
 * Bir karakteri ekrana yazar.
 */
void
my_putchar(char c)
{
	write(1, &c, 1);
}

/*
 * Bir string ifadesini ekrana yazar.
 */
void
my_putstr(char *str)
{
	int i = 0;
	while (*(str + i)) {
		write(1, (str + i), 1);
		i++;
	}
}

/*
 * Bir sayiyi ekrana yazar.
 */
void
my_putnbr(int nb)
{
	if (nb < 0) {
		my_putchar('-');
		if (nb == -2147483648) {
			nb = -147483648;
			my_putchar(50);
		}
		nb = -nb;
	}
	if (nb >= 10) {
		my_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10) {
		my_putchar(nb + 48);
	}
}

/*
 * '\0' ile sonlanan bir string ifadesindeki karakter sayisini dondurur.
 * '\0' dahil degildir.
 */
size_t
my_strlen(const char *str)
{
	size_t len = 0;
	while (*(str + len) != '\0') {
		len++;
	}
	return (len);
}

/*
 * Eger a ve b isaretcileri ile gosterilen stringin icerisindekiler
 * birbirlerine esit ise, 1 degil ise 0 dondurur.
 */
int
my_strcmp(char *a, char *b)
{
	int i = 0;
	while (*(a + i) == * (b + i) && \
			(*(b + i) != '\0' || *(a + i) != '\0')) {
		i++;
	}

	if (*(a + i) == '\0') {
		return (1);
	}
	return (0);
}

/*
 * Ozel karakterleri ayirt etmek icin kullanilir.
 * Eger isaretci ile gosterilen string ifadesi ozel bir karaktere
 * denk geliyorsa, bu karakterin ascii degerini dondurur. Eger
 * denk gelmiyorsa, -1 dondurur.
 */
int
ascii_special(char *str)
{
	if (my_strcmp(str, "NUL") || my_strcmp(str, "\\0")) {
		return (0);
	} else if (my_strcmp(str, "SOH"))  {
		return (1);
	} else if (my_strcmp(str, "STX"))  {
		return (2);
	} else if (my_strcmp(str, "ETX"))  {
		return (3);
	} else if (my_strcmp(str, "EOT"))  {
		return (4);
	} else if (my_strcmp(str, "ENQ"))  {
		return (5);
	} else if (my_strcmp(str, "ACK"))  {
		return (6);
	} else if (my_strcmp(str, "BEL") || my_strcmp(str, "\\a"))  {
		return (7);
	} else if (my_strcmp(str, "BS") || my_strcmp(str, "\\b"))  {
		return (8);
	} else if (my_strcmp(str, "HT") || my_strcmp(str, "\\t"))  {
		return (9);
	} else if (my_strcmp(str, "LF") || my_strcmp(str, "\\n"))  {
		return (10);
	} else if (my_strcmp(str, "VT") || my_strcmp(str, "\\v"))  {
		return (11);
	} else if (my_strcmp(str, "FF") || my_strcmp(str, "\\f"))  {
		return (12);
	} else if (my_strcmp(str, "CR") || my_strcmp(str, "\\r"))  {
		return (13);
	} else if (my_strcmp(str, "SO"))  {
		return (14);
	} else if (my_strcmp(str, "SI"))  {
		return (15);
	} else if (my_strcmp(str, "DLE"))  {
		return (16);
	} else if (my_strcmp(str, "DC1"))  {
		return (17);
	} else if (my_strcmp(str, "DC2"))  {
		return (18);
	} else if (my_strcmp(str, "DC3"))  {
		return (19);
	} else if (my_strcmp(str, "DC4"))  {
		return (20);
	} else if (my_strcmp(str, "NAK"))  {
		return (21);
	} else if (my_strcmp(str, "SYN"))  {
		return (22);
	} else if (my_strcmp(str, "ETB"))  {
		return (23);
	} else if (my_strcmp(str, "CAN"))  {
		return (24);
	} else if (my_strcmp(str, "EM"))  {
		return (25);
	} else if (my_strcmp(str, "SUB"))  {
		return (26);
	} else if (my_strcmp(str, "ESC"))  {
		return (27);
	} else if (my_strcmp(str, "FS"))  {
		return (28);
	} else if (my_strcmp(str, "GS"))  {
		return (29);
	} else if (my_strcmp(str, "RS"))  {
		return (30);
	} else if (my_strcmp(str, "US"))  {
		return (31);
	} else if (my_strcmp(str, "SPACE"))  {
		return (32);
	} else if (my_strcmp(str, "DEL"))  {
		return (127);
	} else {
		if (my_strlen(str) == 1) {
			return (str[0]);
		}
		return (-1);
	}
}

/*
 * Karakterlerin ascii degerlerini ekrana yazar.
 */
void
ascii_routine(int ac, char **ap)
{
	int i = 0;
	while (++i < ac) {
		int ascii_value = ascii_special(ap[i]);
		my_putchar('\'');
		my_putstr(ap[i]);
		my_putchar('\'');
		my_putstr("    ");
		my_putnbr(ascii_value);
		my_putchar(10);
	}
}

int
main(int argc, char **argv)
{
	if (argc == 1) {
		my_putstr("Please provide at least one ASCII character!\n");
		return (-1);
	}
	ascii_routine(argc, argv);
	return (0);
}
