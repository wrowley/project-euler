/**
  * Multiples of 3 and 5
  * Problem 1
  * Published on 05 October 2001 at 06:00 pm [Server Time]
  * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
  *
  * Find the sum of all the multiples of 3 or 5 below 1000.
  */

static
int
is_multiple_of
    (int a
    ,int factor
    )
{
    return (((a/factor)*factor) == a);
}

int
solve00001
    (void)
{
    int i;
    int sum = 0;
    for (i = 0; i < 1000; i++)
    {
        if (is_multiple_of(i,3) || is_multiple_of(i,5))
        {
            sum += i;
        }
    }
    return sum;
}
