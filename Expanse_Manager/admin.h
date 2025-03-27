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

#endif // ADMIN_H 