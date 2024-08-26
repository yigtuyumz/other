#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* a linked list */
typedef struct data_s {
    int count;
    char value;
    struct data_s *next;
} data_t;

/* free each node of data_t */
void
destruct(data_t *head)
{
    data_t *tmp;

    /* increment head, free temp */
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

/* create list, which contains len elements */
data_t *
construct(int count, char value, size_t len)
{
    /* zero length means no list */
    if (len == 0) {
        return (NULL);
    }

    data_t *ret = (data_t *) malloc(sizeof(data_t));

    /* when memory allocation fails */
    if (ret == NULL) {
        return (NULL);
    }

    ret->count = count;
    ret->value = value;
    ret->next = NULL;

    data_t *temp = ret;
    data_t *d;

    while (--len) {
        d = (data_t *) malloc(sizeof(data_t));

        /* if last malloc fails, clean the allocated. */
        if (d == NULL) {
            destruct(ret);
            return (NULL);
        }

        d->count = count;
        d->value = value;
        d->next = NULL;
        temp->next = d;
        temp = d;
    }

    return (ret);
}

/* append new data_t to the lst */
void
push_data(int count, char value, data_t **lst)
{
    data_t *new = (data_t *) malloc(sizeof(data_t));

    if (new == NULL) {
        return ;
    }

    new->count = count;
    new->value = value;
    new->next = NULL;

    if (*lst == NULL) {
        *lst = new;
    } else {
        data_t *tmp = *lst;
        while (tmp->next) {
            tmp = tmp->next;
        }

        tmp->next = new;
    }
}

/* updates lst->value if new_value is not '-' */
void
modify_list(size_t idx, data_t *lst, int new_count, char new_value)
{
    data_t *tmp = lst;

    /* is idx OK and tmp points to a data_t */
    while (tmp && idx--) {
        tmp = tmp->next;
    }

    /* check if idx out-of-bounds */
    if (tmp) {
        tmp->count = new_count;
        /* initially char value is '-' */
        if (new_value != '-') {
            tmp->value = new_value;
        }
    }
}

void
print_data(data_t *lst)
{
    data_t *tmp = lst;
    while (tmp) {
        printf("Count: %03d value: %c\n", tmp->count, tmp->value);
        tmp = tmp->next;
    }
}


/* sort by count, using bubble sort (list has statically 26 elements in this situation) */
/* it works, but i just don't like it... */
// void
// sort_data(data_t *head)
// {
//     int swapped;
//     data_t *temp;
//     data_t *last = NULL;


//     if (head == NULL) {
//         return;
//     }

//     /* Bubble sort start */
//     do {
//         swapped = 0;
//         temp = head;

//         while (temp->next != last) {
//             if (temp->count < temp->next->count) {
//                 /* XOR swap for count */
//                 temp->count ^= temp->next->count;
//                 temp->next->count ^= temp->count;
//                 temp->count ^= temp->next->count;

//                 /* XOR swap for value */
//                 temp->value ^= temp->next->value;
//                 temp->next->value ^= temp->value;
//                 temp->value ^= temp->next->value;
//                 swapped = 1;
//             }
//             temp = temp->next;
//         }
//         last = temp;
//     } while (swapped);
//     /* Bubble sort end */
// }


/* scans only uppercase characters */
data_t *
scan_input(const char *input)
{
    data_t *ret = construct(0, '-', 0);
    for (int i = 65; i <= 90; i++) {
        push_data(0, i, &ret);
    }

    char *s = (char *) input;
    int idx;
    data_t *tmp;
    while (*s) {
        /* scan only uppercase letters */
        if (*s >= 65 && *s <= 90) {
            idx = *s - 65;
            tmp = ret;
            while (idx--) {
                tmp = tmp->next;
            }
            tmp->count++;
        }
        s++;
    }

    return (ret);
}

int
main(int argc __attribute__((unused)), char *argv[])
{
    if (argv[1] == NULL) {
        fprintf(stderr, "argv[1] uppercase encrypted value\n");
        return (1);
    }

    data_t *data = scan_input(argv[1]);
    print_data(data);

    destruct(data);
    return (0);
}
