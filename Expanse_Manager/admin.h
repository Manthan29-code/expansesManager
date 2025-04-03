#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

// Admin credentials
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

// Admin functions
int adminLogin(void);
void adminMenu(void);

// Admin data viewing functions
void viewAllUsers(void);
void viewUserDetails(void);
void viewAllExpenses(void);
void viewExpensesByDateRange(void);
void viewTotalExpenseStats(void);

// New function declarations
void cleanAllUserData();

// Table formatting functions
void printTableLine(int width);
void printCenteredText(const char* text, int width);

// Date handling functions
int isValidDate(int day, int month, int year);
int parseDate(const char* dateStr, int* day, int* month, int* year);
int compareDates(int day1, int month1, int year1, int day2, int month2, int year2);

#endif // ADMIN_H 