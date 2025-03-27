#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "user.h"

// Function to save all user data to files
void saveUsersToFile(void);

// Function to load all user data from files
void loadUsersFromFile(void);

// Function to save specific user's expenses to file
void saveUserExpenses(struct user* user);

// Function to load specific user's expenses from file
void loadUserExpenses(struct user* user);

#endif // FILEHANDLER_H 