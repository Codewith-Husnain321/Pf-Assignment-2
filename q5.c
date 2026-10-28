
#include <stdio.h>

#define MAX_BOOKS 4
#define MAX_TITLE 50
#define MAX_NAME 50
#define MAX_BORROWED 3

void displayMenu()
{
    printf("\n===== UNIVERSITY LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    int type;

    printf("\nEnter member name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do
    {
        printf("Membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", &type);

        if (type != 1 && type != 2)
        {
            printf("Invalid membership type. Try again.\n");
        }

    } while (type != 1 && type != 2);

    *memberType = type;

    printf("Member registered successfully!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks)
{
    printf("\n%-10s %-30s %s\n", "ID", "Title", "Copies");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < totalBooks; i++)
    {
        printf("%-10d %-30s %d\n",
               bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50],
                int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount,
                int memberType)
{
    int bookID, index = -1, days;

    if (*borrowedCount >= MAX_BORROWED)
    {
        printf("You cannot borrow more than three books at a time.\n");
        return;
    }

    printf("\nEnter book ID: ");
    scanf("%d", &bookID);

    for (int i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == bookID)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Invalid book ID.\n");
        return;
    }

    if (availableCopies[index] <= 0)
    {
        printf("This book is currently unavailable.\n");
        return;
    }

    for (int i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == bookID)
        {
            printf("You have already borrowed this book.\n");
            return;
        }
    }

    do
    {
        printf("Enter intended borrowing days: ");
        scanf("%d", &days);

        if (days <= 0)
        {
            printf("Days must be positive.\n");
        }

    } while (days <= 0);

    int allowedDays = (memberType == 1) ? 14 : 30;

    borrowedBookIDs[*borrowedCount] = bookID;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("\nBook borrowed successfully: %s\n", bookTitles[index]);
    printf("Allowed borrowing period: %d days\n", allowedDays);

    if (days > allowedDays)
    {
        printf("Warning: Your intended period exceeds the allowed limit.\n");
    }
}

float returnBook(int bookIDs[], int availableCopies[],
                 int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType,
                 float *totalFine)
{
    int bookID, index = -1, borrowedIndex = -1;
    int actualDays, allowedDays;
    float fine = 0, payable;

    printf("\nEnter book ID to return: ");
    scanf("%d", &bookID);

    for (int i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == bookID)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Invalid book ID.\n");
        return 0;
    }

    for (int i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == bookID)
        {
            borrowedIndex = i;
            break;
        }
    }

    if (borrowedIndex == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    do
    {
        printf("Enter actual days the book was kept: ");
        scanf("%d", &actualDays);

        if (actualDays <= 0)
        {
            printf("Days must be positive.\n");
        }

    } while (actualDays <= 0);

    allowedDays = (memberType == 1) ? 14 : 30;

    if (actualDays > allowedDays)
    {
        int extraDays = actualDays - allowedDays;

        if (memberType == 1)
        {
            fine = extraDays * 20.0f;
        }
        else
        {
            fine = extraDays * 10.0f;
        }
    }

    payable = fine;

    if (fine > 0)
    {
        char code[20];

        printf("Fine before waiver: Rs. %.2f\n", fine);
        printf("Enter membership code for 50%% waiver (or NONE): ");
        scanf("%19s", code);

        if (code[0] == 'L' &&
            code[1] == 'I' &&
            code[2] == 'B' &&
            code[3] == '2' &&
            code[4] == '0' &&
            code[5] == '2' &&
            code[6] == '6' &&
            code[7] == '\0')
        {
            payable = fine * 0.5f;
            printf("Valid code! 50%% waiver applied.\n");
        }
        else
        {
            printf("Invalid code. No waiver applied.\n");
        }
    }
    else
    {
        printf("No late fine. Book returned within the allowed period.\n");
    }

    *totalFine += fine;
    availableCopies[index]++;

    for (int i = borrowedIndex; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }

    (*borrowedCount)--;

    printf("Fine payable for this return: Rs. %.2f\n", payable);
    printf("Book returned successfully!\n");

    return payable;
}

void displayMemberRecord(char name[], int studentID,
                         int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine,
                         float fineAfterWaiver)
{
    printf("\n========== MEMBER RECORD ==========\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == 1)
    {
        printf("Membership Type: Student\n");
        printf("Allowed Borrowing Period: 14 days\n");
    }
    else
    {
        printf("Membership Type: Faculty\n");
        printf("Allowed Borrowing Period: 30 days\n");
    }

    printf("\nCurrently Borrowed Book IDs:\n");

    if (borrowedCount == 0)
    {
        printf("No books currently borrowed.\n");
    }
    else
    {
        for (int i = 0; i < borrowedCount; i++)
        {
            printf("%d\n", borrowedBookIDs[i]);
        }
    }

    printf("\nTotal Fine Before Waivers: Rs. %.2f\n", totalFine);
    printf("Total Fine Payable After Waivers: Rs. %.2f\n",
           fineAfterWaiver);
    printf("===================================\n");
}

int main()
{
    int bookIDs[MAX_BOOKS] = {101, 102, 103, 104};

    char bookTitles[MAX_BOOKS][MAX_TITLE] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };

    int availableCopies[MAX_BOOKS] = {5, 3, 0, 4};

    char name[MAX_NAME] = "";
    int studentID = 0;
    int memberType = 0;

    int borrowedBookIDs[MAX_BORROWED];
    int borrowedCount = 0;

    float totalFine = 0;
    float fineAfterWaiver = 0;

    int choice;
    int registered = 0;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                registerMember(name, &studentID, &memberType);
                registered = 1;
                break;

            case 2:
                displayBooks(bookIDs, bookTitles,
                             availableCopies, MAX_BOOKS);
                break;

            case 3:
                if (!registered)
                {
                    printf("Please register a member first.\n");
                }
                else
                {
                    borrowBook(bookIDs, bookTitles,
                               availableCopies, MAX_BOOKS,
                               borrowedBookIDs, &borrowedCount,
                               memberType);
                }
                break;

            case 4:
                if (!registered)
                {
                    printf("Please register a member first.\n");
                }
                else
                {
                    fineAfterWaiver += returnBook(
                        bookIDs, availableCopies, MAX_BOOKS,
                        borrowedBookIDs, &borrowedCount,
                        memberType, &totalFine
                    );
                }
                break;

            case 5:
                if (!registered)
                {
                    printf("Please register a member first.\n");
                }
                else
                {
                    displayMemberRecord(
                        name, studentID, memberType,
                        borrowedBookIDs, borrowedCount,
                        totalFine, fineAfterWaiver
                    );
                }
                break;

            case 6:
                printf("Exiting Library Management System.\n");
                break;

            default:
                printf("Invalid menu choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}
