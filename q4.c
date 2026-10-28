
#include <stdio.h>

int getValidDays()
{
    int days;

    do
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);

        if (days < 1 || days > 7)
        {
            printf("Invalid number of days. Try again.\n");
        }

    } while (days < 1 || days > 7);

    return days;
}

float calculateDailySales(int dayNumber)
{
    int orders;
    float amount, total = 0;
    float average, highest = 0;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    for (int i = 1; i <= orders; i++)
    {
        do
        {
            printf("Enter amount for order %d: ", i);
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Amount must be greater than zero. Try again.\n");
            }

        } while (amount <= 0);

        total += amount;

        if (amount > highest)
        {
            highest = amount;
        }
    }

    average = total / orders;

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", average);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int highestDay = 0;

    for (int i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > dailySales[highestDay])
        {
            highestDay = i;
        }
    }

    return highestDay + 1;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    printf("\n===== DAILY SALES BAR CHART =====\n");

    for (int i = 0; i < numberOfDays; i++)
    {
        printf("Day %d: ", i + 1);

        int stars = (int)(dailySales[i] / 100);

        for (int j = 0; j < stars; j++)
        {
            printf("*");
        }

        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main()
{
    int days;
    float dailySales[7];
    float totalFestivalSales = 0;

    days = getValidDays();

    for (int i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        totalFestivalSales += dailySales[i];
    }

    int highestDay = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n",
           totalFestivalSales);

    printf("Day with highest sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n",
           dailySales[highestDay - 1]);

    displayBarChart(dailySales, days);

    return 0;
}
