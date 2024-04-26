void    count_sets(input)
{
    int     num_of_sets;
    char    **sets;
    int     *logops;
    int     i;

    num_of_sets = how_many_sets(input);
    if (num_of_sets == 1)
        parse(sets[i]);
    else
    {
        sets = malloc(num_of_sets * sizeof(char *));
        int i = 0;
        while (i < num_of_sets)
        {
            sets[i] = get_unit(input, i);
            count_sets(sets[i]);
        }
    }
}