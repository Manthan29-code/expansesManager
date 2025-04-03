#include "admin.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Function to print a line of dashes for table borders
void printTableLine(int width) {
    for(int i = 0; i < width; i++) printf("-");
    printf("\n");
}

// Function to print centered text in a column
void printCenteredText(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    for(int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for(int i = 0; i < width - padding - len; i++) printf(" ");
}

// Function to handle admin login
int adminLogin() {
    char username[50];
    char password[50];
    
    printf("\nAdmin Login");
    printf("\nUsername: ");
    fflush(stdin);
    gets(username);
    printf("Password: ");
    fflush(stdin);
    gets(password);
    
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("\nAdmin login successful!");
        return 1;
    }
    
    printf("\nInvalid credentials!");
    return 0;
}

// Function to display admin menu and handle admin operations
void adminMenu() {
    int choice;
    
    while(1) {
        printf("\n\n=== Admin Menu ===");
        printf("\n1. View All Users");
        printf("\n2. View Specific User Details");
        printf("\n3. View All Expenses");
        printf("\n4. View Expenses by Date Range");
        printf("\n5. View Total Expense Statistics");
        printf("\n6. Clean All User Data");
        printf("\n7. Logout");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                viewAllUsers();
                break;
            case 2:
                viewUserDetails();
                break;
            case 3:
                viewAllExpenses();
                break;
            case 4:
                viewExpensesByDateRange();
                break;
            case 5:
                viewTotalExpenseStats();
                break;
            case 6:
                cleanAllUserData();
                break;
            case 7:
                printf("\nLogging out from admin panel...");
                return;
            default:
                printf("\nInvalid choice!");
        }
    }
}

// Function to view all registered users
void viewAllUsers() {
    if(users == NULL) {
        printf("\nNo users registered yet!");
        return;
    }
    
    struct user *temp = users;
    int count = 0;
    
    // Table header
    printf("\n");
    printTableLine(80);
    printf("|");
    printCenteredText("No.", 5);
    printf("|");
    printCenteredText("Name", 30);
    printf("|");
    printCenteredText("Email", 40);
    printf("|\n");
    printTableLine(80);
    
    while(temp != NULL) {
        count++;
        printf("|");
        char numStr[10];
        sprintf(numStr, "%d", count);
        printCenteredText(numStr, 5);
        printf("|");
        printCenteredText(temp->firstname, 30);
        printf("|");
        printCenteredText(temp->email, 40);
        printf("|\n");
        temp = temp->next;
    }
    printTableLine(80);
    printf("\nTotal Users: %d", count);
}

// Function to view specific user details
void viewUserDetails() {
    char email[50];
    printf("\nEnter user email to view details: ");
    fflush(stdin);
    gets(email);
    
    struct user *temp = users;
    while(temp != NULL) {
        if(strcmp(temp->email, email) == 0) {
            printf("\n");
            printTableLine(80);
            printf("|");
            printCenteredText("User Details", 78);
            printf("|\n");
            printTableLine(80);
            
            printf("|");
            printCenteredText("Name", 38);
            printf("|");
            printCenteredText(temp->firstname, 38);
            printf("|\n");
            
            printf("|");
            printCenteredText("Email", 38);
            printf("|");
            printCenteredText(temp->email, 38);
            printf("|\n");
            
            if(temp->account != NULL) {
                printf("|");
                printCenteredText("Account Name", 38);
                printf("|");
                printCenteredText(temp->account->name, 38);
                printf("|\n");
                
                char balanceStr[20];
                sprintf(balanceStr, "%.2f", temp->account->balance);
                printf("|");
                printCenteredText("Current Balance", 38);
                printf("|");
                printCenteredText(balanceStr, 38);
                printf("|\n");
                
                // Show expenses
                struct expense *exp = temp->account->expenses;
                if(exp != NULL) {
                    printTableLine(80);
                    printf("|");
                    printCenteredText("Expenses", 78);
                    printf("|\n");
                    printTableLine(80);
                    
                    printf("|");
                    printCenteredText("Title", 38);
                    printf("|");
                    printCenteredText("Amount", 38);
                    printf("|\n");
                    printTableLine(80);
                    
                    while(exp != NULL) {
                        printf("|");
                        printCenteredText(exp->title, 38);
                        printf("|");
                        char amountStr[20];
                        sprintf(amountStr, "%.2f", exp->amount);
                        printCenteredText(amountStr, 38);
                        printf("|\n");
                        exp = exp->next;
                    }
                }
            } else {
                printf("|");
                printCenteredText("Account Status", 38);
                printf("|");
                printCenteredText("No account created yet", 38);
                printf("|\n");
            }
            printTableLine(80);
            return;
        }
        temp = temp->next;
    }
    printf("\nUser not found!");
}

// Function to view all expenses across all users
void viewAllExpenses() {
    if(users == NULL) {
        printf("\nNo users registered yet!");
        return;
    }
    
    float totalExpenses = 0;
    struct user *temp = users;
    
    printf("\n");
    printTableLine(100);
    printf("|");
    printCenteredText("User", 30);
    printf("|");
    printCenteredText("Expense Title", 40);
    printf("|");
    printCenteredText("Amount", 25);
    printf("|\n");
    printTableLine(100);
    
    while(temp != NULL) {
        if(temp->account != NULL && temp->account->expenses != NULL) {
            struct expense *exp = temp->account->expenses;
            float userTotal = 0;
            int isFirstExpense = 1;
            
            while(exp != NULL) {
                printf("|");
                if(isFirstExpense) {
                    printCenteredText(temp->firstname, 30);
                    isFirstExpense = 0;
                } else {
                    printCenteredText("", 30);
                }
                printf("|");
                printCenteredText(exp->title, 40);
                printf("|");
                char amountStr[20];
                sprintf(amountStr, "%.2f", exp->amount);
                printCenteredText(amountStr, 25);
                printf("|\n");
                
                userTotal += exp->amount;
                exp = exp->next;
            }
            
            printf("|");
            printCenteredText("", 30);
            printf("|");
            printCenteredText("Total for User", 40);
            printf("|");
            char totalStr[20];
            sprintf(totalStr, "%.2f", userTotal);
            printCenteredText(totalStr, 25);
            printf("|\n");
            printTableLine(100);
            
            totalExpenses += userTotal;
        }
        temp = temp->next;
    }
    
    printf("\nTotal Expenses Across All Users: %.2f", totalExpenses);
}

// Function to validate date
int isValidDate(int day, int month, int year) {
    if (year < 2000 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;
    
    // Check for February
    if (month == 2) {
        int isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) return 0;
    }
    
    return 1;
}

// Function to convert date string to integers
int parseDate(const char* dateStr, int* day, int* month, int* year) {
    return sscanf(dateStr, "%d %d %d", day, month, year) == 3;
}

// Function to compare dates
int compareDates(int day1, int month1, int year1, int day2, int month2, int year2) {
    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

// Function to view expenses by date range
void viewExpensesByDateRange() {
    if(users == NULL) {
        printf("\nNo users registered yet!");
        return;
    }
    
    char startDateStr[20], endDateStr[20];
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;
    
    printf("\nEnter start date (DD MM YYYY): ");
    fflush(stdin);
    gets(startDateStr);
    
    printf("Enter end date (DD MM YYYY): ");
    fflush(stdin);
    gets(endDateStr);
    
    if (!parseDate(startDateStr, &startDay, &startMonth, &startYear) ||
        !parseDate(endDateStr, &endDay, &endMonth, &endYear)) {
        printf("\nInvalid date format! Please use DD MM YYYY format.");
        return;
    }
    
    if (!isValidDate(startDay, startMonth, startYear) ||
        !isValidDate(endDay, endMonth, endYear)) {
        printf("\nInvalid date! Please enter a valid date.");
        return;
    }
    
    if (compareDates(startDay, startMonth, startYear, endDay, endMonth, endYear) > 0) {
        printf("\nStart date must be before or equal to end date!");
        return;
    }
    
    float totalExpenses = 0;
    int totalExpenseCount = 0;
    struct user *temp = users;
    
    printf("\n");
    printTableLine(100);
    printf("|");
    printCenteredText("User", 30);
    printf("|");
    printCenteredText("Expense Title", 40);
    printf("|");
    printCenteredText("Date", 15);
    printf("|");
    printCenteredText("Amount", 10);
    printf("|\n");
    printTableLine(100);
    
    while(temp != NULL) {
        if(temp->account != NULL && temp->account->expenses != NULL) {
            struct expense *exp = temp->account->expenses;
            float userTotal = 0;
            int userExpenseCount = 0;
            int isFirstExpense = 1;
            
            while(exp != NULL) {
                // Check if expense date is within range
                if (compareDates(exp->day, exp->month, exp->year, startDay, startMonth, startYear) >= 0 &&
                    compareDates(exp->day, exp->month, exp->year, endDay, endMonth, endYear) <= 0) {
                    
                    printf("|");
                    if(isFirstExpense) {
                        printCenteredText(temp->firstname, 30);
                        isFirstExpense = 0;
                    } else {
                        printCenteredText("", 30);
                    }
                    printf("|");
                    printCenteredText(exp->title, 40);
                    printf("|");
                    
                    char dateStr[15];
                    sprintf(dateStr, "%02d/%02d/%d", exp->day, exp->month, exp->year);
                    printCenteredText(dateStr, 15);
                    
                    printf("|");
                    char amountStr[10];
                    sprintf(amountStr, "%.2f", exp->amount);
                    printCenteredText(amountStr, 10);
                    printf("|\n");
                    
                    userTotal += exp->amount;
                    userExpenseCount++;
                }
                exp = exp->next;
            }
            
            if (userExpenseCount > 0) {
                printf("|");
                printCenteredText("", 30);
                printf("|");
                printCenteredText("Total for User", 40);
                printf("|");
                printCenteredText("", 15);
                printf("|");
                char totalStr[10];
                sprintf(totalStr, "%.2f", userTotal);
                printCenteredText(totalStr, 10);
                printf("|\n");
                printTableLine(100);
                
                totalExpenses += userTotal;
                totalExpenseCount += userExpenseCount;
            }
        }
        temp = temp->next;
    }
    
    if (totalExpenseCount == 0) {
        printf("\nNo expenses found in the specified date range.");
        return;
    }
    
    printf("\nSummary Statistics:");
    printf("\nTotal number of expenses: %d", totalExpenseCount);
    printf("\nTotal amount: %.2f", totalExpenses);
    printf("\nAverage expense amount: %.2f", totalExpenses / totalExpenseCount);
}

// Function to view total expense statistics
void viewTotalExpenseStats() {
    if(users == NULL) {
        printf("\nNo users registered yet!");
        return;
    }
    
    int totalUsers = 0;
    int usersWithExpenses = 0;
    float totalExpenses = 0;
    float maxExpense = 0;
    char maxExpenseUser[50] = "";
    
    struct user *temp = users;
    
    while(temp != NULL) {
        totalUsers++;
        float userTotal = 0;
        
        if(temp->account != NULL && temp->account->expenses != NULL) {
            usersWithExpenses++;
            struct expense *exp = temp->account->expenses;
            
            while(exp != NULL) {
                userTotal += exp->amount;
                exp = exp->next;
            }
            
            totalExpenses += userTotal;
            
            if(userTotal > maxExpense) {
                maxExpense = userTotal;
                strcpy(maxExpenseUser, temp->firstname);
            }
        }
        
        temp = temp->next;
    }
    
    printf("\n");
    printTableLine(80);
    printf("|");
    printCenteredText("Expense Statistics", 78);
    printf("|\n");
    printTableLine(80);
    
    printf("|");
    printCenteredText("Metric", 38);
    printf("|");
    printCenteredText("Value", 38);
    printf("|\n");
    printTableLine(80);
    
    char valueStr[20];
    
    sprintf(valueStr, "%d", totalUsers);
    printf("|");
    printCenteredText("Total Users", 38);
    printf("|");
    printCenteredText(valueStr, 38);
    printf("|\n");
    
    sprintf(valueStr, "%d", usersWithExpenses);
    printf("|");
    printCenteredText("Users with Expenses", 38);
    printf("|");
    printCenteredText(valueStr, 38);
    printf("|\n");
    
    sprintf(valueStr, "%.2f", totalExpenses);
    printf("|");
    printCenteredText("Total Expenses", 38);
    printf("|");
    printCenteredText(valueStr, 38);
    printf("|\n");
    
    sprintf(valueStr, "%.2f", usersWithExpenses > 0 ? totalExpenses/usersWithExpenses : 0);
    printf("|");
    printCenteredText("Average Expense per User", 38);
    printf("|");
    printCenteredText(valueStr, 38);
    printf("|\n");
    
    if(strlen(maxExpenseUser) > 0) {
        char maxExpenseStr[50];
        sprintf(maxExpenseStr, "%s (%.2f)", maxExpenseUser, maxExpense);
        printf("|");
        printCenteredText("Highest Expense User", 38);
        printf("|");
        printCenteredText(maxExpenseStr, 38);
        printf("|\n");
    }
    
    printTableLine(80);
} 