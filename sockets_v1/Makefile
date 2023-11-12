ifeq ($(shell uname), FreeBSD)
	CC = gcc13
else
	CC = gcc
endif

LIBDIR = $(realpath /root)
LDFLAGS = -L$(LIBDIR) -lutils -Wl,-rpath=$(LIBDIR)
CFLAGS = -std=c99

RELEASE ?= no
ifeq ($(RELEASE),yes)
	CFLAGS := -Wall -Wextra -Werror
endif

.PHONY: a r clean s c


a: s c

clean:
	rm -rf s c

r: clean a

s:
	$(CC) $(CFLAGS) server.c -o s $(LDFLAGS)

c:
	$(CC) $(CFLAGS) client.c -o c $(LDFLAGS)

# DO NOT DELETE
