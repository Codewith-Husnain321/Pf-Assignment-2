
#include <stdio.h>

int sumProperDivisors(int n)
{
    int sum = 0;

    for (int i = 1; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    int n;
    int count = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    for (int i = 2; i <= n; i++)
    {
        int sum1 = sumProperDivisors(i);

        // Skip perfect numbers
        if (sum1 == i)
        {
            continue;
        }

        // The second number must be larger to avoid duplicate pairs
        int j = sum1;

        if (j > i && j <= n)
        {
            int sum2 = sumProperDivisors(j);

            if (sum2 == i)
            {
                printf("(%d, %d)\n", i, j);
                count++;
            }
        }
    }

    if (count == 0)
    {
        printf("No amicable pairs found.\n");
    }

    printf("Total pairs: %d\n", count);

    return 0;
}
