
#include <stdio.h>

int main()
{
    int rows, col;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of seats per row: ");
    scanf("%d", &col);

    if (rows <= 0 || col <= 0)
    {
        printf("Invalid seating dimensions.\n");
        return 0;
    }

    int seats[rows][col];

    // Step 1: Input seating plan
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("Enter status for seat [%d][%d] (0 = available, 1 = booked): ", i, j);
            scanf("%d", &seats[i][j]);

            while (seats[i][j] != 0 && seats[i][j] != 1)
            {
                printf("Enter only 0 or 1: ");
                scanf("%d", &seats[i][j]);
            }
        }
    }

    // Step 2: Display seating arrangement
    printf("\nSeating Arrangement:\n");
    printf("    ");

    for (int j = 0; j < col; j++)
    {
        printf("%d ", j);
    }

    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        printf("R%d  ", i);

        for (int j = 0; j < col; j++)
        {
            if (seats[i][j] == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("X ");
            }
        }

        printf("\n");
    }

    // Step 3: Count available seats
    int freeRow = 0;
    int freeTotal = 0;

    printf("\nFree seats per row:\n");

    for (int i = 0; i < rows; i++)
    {
        freeRow = 0;

        for (int j = 0; j < col; j++)
        {
            if (seats[i][j] == 0)
            {
                freeRow++;
            }
        }

        printf("Row %d: %d\n", i, freeRow);
        freeTotal += freeRow;
    }

    printf("Total free seats: %d\n", freeTotal);

    // Step 4: Input and validate group size
    int k;

    printf("\nEnter number of customers: ");
    scanf("%d", &k);

    if (k <= 0 || k > col)
    {
        printf("Invalid group size.\n");
        return 0;
    }

    // Step 5: Prepare for seat search
    int middle = rows / 2;
    int allocatedRow = -1;
    int startSeat = -1;
    int count = 0;

    // Step 6: Search rows by distance from the middle
    for (int distance = 0;
         distance < rows && allocatedRow == -1;
         distance++)
    {
        int limit;

        if (distance == 0)
        {
            limit = 1;
        }
        else
        {
            limit = 2;
        }

        for (int side = 0;
             side < limit && allocatedRow == -1;
             side++)
        {
            int r;

            if (side == 0)
            {
                r = middle - distance;
            }
            else
            {
                r = middle + distance;
            }

            // Skip invalid row numbers
            if (r < 0 || r >= rows)
            {
                continue;
            }

            count = 0;

            // Find consecutive available seats in this row
            for (int j = 0; j < col; j++)
            {
                if (seats[r][j] == 0)
                {
                    count++;
                }
                else
                {
                    count = 0;
                }

                if (count == k)
                {
                    startSeat = j - k + 1;
                    allocatedRow = r;
                    break;
                }
            }
        }
    }

    // Step 7: Confirm booking
    if (allocatedRow == -1)
    {
        printf("\nNo suitable block of consecutive seats found.\n");
        printf("The seating plan remains unchanged.\n");
    }
    else
    {
        printf("\nBooking successful!\n");
        printf("Allocated row: %d\n", allocatedRow);
        printf("Allocated seats: ");

        for (int j = startSeat; j < startSeat + k; j++)
        {
            printf("%d ", j);
            seats[allocatedRow][j] = 1;
        }

        printf("\n");

        freeTotal -= k;
    }

    // Step 8: Display updated seating arrangement
    printf("\nUpdated Seating Arrangement:\n");
    printf("    ");

    for (int j = 0; j < col; j++)
    {
        printf("%d ", j);
    }

    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        printf("R%d  ", i);

        for (int j = 0; j < col; j++)
        {
            if (seats[i][j] == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("X ");
            }
        }

        printf("\n");
    }

    // Step 9: Display remaining available seats
    printf("\nRemaining available seats: %d\n", freeTotal);

    return 0;
}
