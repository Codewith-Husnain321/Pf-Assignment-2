#include <stdio.h>

void inputReadings(int sensors, int hours,
                   int temperature[sensors][hours]);

void analyzeSensor(int hours, int readings[],
                   int *total, float *average,
                   int *max, int *min,
                   int *critical, int *warning,
                   int *longestStreak);

int highestAverageSensor(int sensors, int hours,
                         int temperature[sensors][hours]);

int main()
{
    int sensors, hours;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);

    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    if (sensors <= 0 || hours <= 0)
    {
        printf("Invalid dimensions.\n");
        return 1;
    }

    int temperature[sensors][hours];

    inputReadings(sensors, hours, temperature);

    float averages[sensors];

    for (int i = 0; i < sensors; i++)
    {
        int total, max, min;
        int critical, warning, longestStreak;
        float average;

        analyzeSensor(hours, temperature[i],
                      &total, &average, &max, &min,
                      &critical, &warning, &longestStreak);

        averages[i] = average;

        printf("\nSensor %d\n", i + 1);
        printf("Total temperature: %d\n", total);
        printf("Average temperature: %.2f\n", average);
        printf("Maximum temperature: %d\n", max);
        printf("Minimum temperature: %d\n", min);
        printf("Critical readings: %d\n", critical);
        printf("Warning readings: %d\n", warning);
        printf("Longest hot streak: %d\n", longestStreak);
    }

    int highest = highestAverageSensor(sensors, hours, temperature);

    printf("\nSensor with highest average: %d\n", highest + 1);
    printf("Highest average temperature: %.2f\n", averages[highest]);

    return 0;
}

void inputReadings(int sensors, int hours,
                   int temperature[sensors][hours])
{
    for (int i = 0; i < sensors; i++)
    {
        printf("\nEnter readings for Sensor %d:\n", i + 1);

        for (int j = 0; j < hours; j++)
        {
            printf("Hour %d: ", j + 1);
            scanf("%d", &temperature[i][j]);
        }
    }
}

void analyzeSensor(int hours, int readings[],
                   int *total, float *average,
                   int *max, int *min,
                   int *critical, int *warning,
                   int *longestStreak)
{
    *total = 0;
    *max = readings[0];
    *min = readings[0];
    *critical = 0;
    *warning = 0;
    *longestStreak = 0;

    int streak = 0;

    for (int i = 0; i < hours; i++)
    {
        *total += readings[i];

        if (readings[i] > *max)
        {
            *max = readings[i];
        }

        if (readings[i] < *min)
        {
            *min = readings[i];
        }

        if (readings[i] >= 40)
        {
            (*critical)++;
        }
        else if (readings[i] >= 35)
        {
            (*warning)++;
        }

        if (readings[i] >= 35)
        {
            streak++;

            if (streak > *longestStreak)
            {
                *longestStreak = streak;
            }
        }
        else
        {
            streak = 0;
        }
    }

    *average = (float)*total / hours;
}

int highestAverageSensor(int sensors, int hours,
                         int temperature[sensors][hours])
{
    int highestSensor = 0;
    int highestTotal = 0;

    for (int j = 0; j < hours; j++)
    {
        highestTotal += temperature[0][j];
    }

    for (int i = 1; i < sensors; i++)
    {
        int currentTotal = 0;

        for (int j = 0; j < hours; j++)
        {
            currentTotal += temperature[i][j];
        }

        if (currentTotal > highestTotal)
        {
            highestTotal = currentTotal;
            highestSensor = i;
        }
    }

    return highestSensor;
}