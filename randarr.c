// Generates random dynamic buffer
// argv[1] -> buffer size

// NOLINTBEGIN clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
#undef MAXBUFSZ
#define MAXBUFSZ 65535

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *
set_buffer(size_t buflen)
{
    // zero initialized 1 buffer
    void *ret = calloc(1, buflen);

    if (ret == NULL) {
        fprintf(stderr, "Memory allocation for new buffer has failed.");
        exit(EXIT_FAILURE);
    }

    return (ret);
}

void
generate_random_data(void *buf, size_t buflen)
{
    int fd = open("/dev/random", O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "Failed to open /dev/random\n");
        exit(EXIT_FAILURE);
    }

    ssize_t readval = read(fd, buf, buflen);

    if (readval != buflen) {
        fprintf(stderr, "Failed to read %lu byte(s) from /dev/random\n",
                buflen);
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

// is it hexdump ??
void
print_random_data(void *buf, size_t buflen)
{
    unsigned char *byte_ptr = (unsigned char *) buf;
    size_t i = 0;
    size_t address = 0;
    size_t j;

    while (i < buflen) {
        printf("%08zx  ", address);

        j = 0;
        while (j < 16) {
            if (i + j >= buflen) {
                printf("   ");
            } else {
                printf("%02X ", byte_ptr[i + j]);
            }
            j++;
        }
        printf(" |");

        j = 0;

        while (j < 16 && i + j < buflen) {
            if (byte_ptr[i + j] >= 32 && byte_ptr[i + j] <= 126) {
                printf("%c", byte_ptr[i + j]);
            } else {
                printf(".");
            }
            j++;
        }
        printf("|\n");
        address += 16;
        i += 16;
    }
}

void
test(void *buf, size_t buflen)
{
    unsigned int val[11] =
        { -169, -159, -153, -159, -158, -145, -146, -156, -207, -206, -256 };
    size_t i = 0;

    while (i < buflen && i < 11) {
        *((unsigned char *) buf + i) = val[i];
        i++;
    }
}

size_t
my_atoi(const char *c)
{
    size_t r = 0;

    size_t i = 0;

    while (*(c + i)) {
        if (*(c + i) < '0' || *(c + i) > '9') {
            return (0);
        }

        r = r * 10 + (*(c + i) - '0');
        i++;
    }

    return (r);
}

int
main(int argc, char *argv[])
{
    if (argv[1] == NULL) {
        fprintf(stderr, "argv[1] -> buffer size\n");
        exit(EXIT_FAILURE);
    }

    size_t buflen = my_atoi(argv[1]);

    if (buflen > MAXBUFSZ || buflen == 0) {
        fprintf(stderr, "buflen > 0 && buflen <= MAXBUFSZ\n");
        exit(EXIT_FAILURE);
    }

    printf("%lu\n", my_atoi(argv[1]));

    void *buf = set_buffer(buflen);

    generate_random_data(buf, buflen);
    test(buf, buflen);
    print_random_data(buf, buflen);

    free(buf);

    return (0);
}

// NOLINTEND clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
