int
does_it_overlap(void *a, void *b, unsigned long int n)
{
    unsigned char *p1 = (unsigned char *) a;
    unsigned char *p2 = (unsigned char *) b;

    return ((p1 < p2 + n) && (p2 < p1 + n));
}
