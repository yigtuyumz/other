#include <stdlib.h>

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
 * str isaretcisi ile gosterilen string ifadesinin bir kopyasina isaret eden
 * ret_str isaretcisini dondurur.
 * Kopyalanmis olan ret_str icin gerekli alan malloc ile elde edilir.
 * Eger malloc yeteri kadar bellek ayiramaz veya str isaretcisinin
 * gosterdigi ifadenin karakter sayisi sifira esit ise NULL degeri dondurur.
 */
char *
my_strdup(const char *str)
{
	size_t len = my_strlen(str);
	char *ret_str = (char *) malloc(sizeof(char) * (len + 1));

	if (ret_str == NULL) {
		return (NULL);
	}
	size_t i = 0;
	while (*(str + i)) {
		*(ret_str + i) = *(str+i);
		i++;
	}

	*(ret_str + i) = '\0';

	return (ret_str);
}

/*
 * en fazla 'n' adet karakteri str isaretcisi ile gosterilen yere kopyalar.
 */
char *
my_strndup(const char *str, size_t n)
{
/*
	if ((((int) n) < 0) || (n > ((size_t) 0xFFFFFFFF))) {
		n = 0xFFFFFFFF;
	}
*/
	if (n == 0) {
		return (NULL);
	}

	size_t len = my_strlen(str);
	if (n < len) {
		len = n;
	}

	char *dup = (char *) malloc(sizeof(char) * (len + 1));
	if (dup == NULL) {
		return (NULL);
	}

	size_t i = 0;
	while (i < n && *(str + i)) {
		*(dup + i) = *(str + i);
		i++;
	}

	*(dup + i) = '\0';

	return (dup);
}
