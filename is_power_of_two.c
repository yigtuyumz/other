// x is actually an uintptr_t
int
is_power_of_two(unsigned long int x)
{
    return ((x & (x - 1)) == 0);
}
