int
does_it_overlap(void *a, void *b, unsigned long int n)
{
    return ((a > b) ? ((a - b) < n) : ((b - a) < n));
}
