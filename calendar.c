#include <stdio.h>

int main() {
    int year, month;

    printf("=====================================\n");
    printf("         CALENDAR APPLICATION        \n");
    printf("=====================================\n");

    // 1. Get year input
    printf("Enter year (e.g., 2026): ");
    if (scanf("%d", &year) != 1 || year < 1) {
        printf("Error: Please enter a valid positive year.\n");
        return 1;
    }

    // Check and print whether the entered year is a leap year
    int is_leap_year = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    if (is_leap_year) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }

    // 2. Get month input
    printf("Enter month (1 - 12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Error: Month must be between 1 and 12.\n");
        return 1;
    }

    // 3. Determine the number of days in the month (without arrays)
    // - February has 29 days in a leap year, 28 in a common year
    // - April, June, September, November have 30 days
    // - January, March, May, July, August, October, December have 31 days
    int total_days;
    if (month == 2) {
        if (is_leap_year) {
            total_days = 29;
        } else {
            total_days = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        total_days = 30;
    } else {
        total_days = 31;
    }

    // 4. Calculate day of the week for the 1st of the month using Zeller's Congruence (without arrays)
    int q = 1;          // 1st day of the month
    int m = month;
    int y = year;

    // In Zeller's algorithm, January and February are counted as months 13 and 14 of previous year
    if (m < 3) {
        m = m + 12;
        y = y - 1;
    }

    int k = y % 100;    // Year of the century
    int j = y / 100;    // Zero-based century

    // Zeller's formula calculates: 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday
    int h = (q + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;

    // Week starts on Saturday: 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday
    int first_day = h;

    // 5. Print the Calendar Header (using switch-case instead of an array)
    printf("\n=====================================\n         ");
    switch (month) {
        case 1:  printf("January");   break;
        case 2:  printf("February");  break;
        case 3:  printf("March");     break;
        case 4:  printf("April");     break;
        case 5:  printf("May");       break;
        case 6:  printf("June");      break;
        case 7:  printf("July");      break;
        case 8:  printf("August");    break;
        case 9:  printf("September"); break;
        case 10: printf("October");   break;
        case 11: printf("November");  break;
        case 12: printf("December");  break;
    }
    printf(" %d\n", year);
    printf("=====================================\n");
    printf("  Sat  Sun  Mon  Tue  Wed  Thu  Fri\n");

    // 6. Print leading spaces for days before the 1st
    for (int i = 0; i < first_day; i++) {
        printf("     ");
    }

    // 7. Print all days of the month
    int current_column = first_day;
    for (int day = 1; day <= total_days; day++) {
        printf("%5d", day);
        current_column++;

        // Wrap to a new line after Friday (every 7 columns)
        if (current_column % 7 == 0) {
            printf("\n");
        }
    }

    // Final newline if the month didn't end on Friday
    if (current_column % 7 != 0) {
        printf("\n");
    }

    printf("=====================================\n");

    return 0;
}
