#include "filehandler.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>
#ifdef _WIN32
    #include <direct.h>
    #define mkdir(dir, mode) _mkdir(dir)
#endif

// Create directory if it doesn't exist
void createDirectoryIfNotExists(const char* dirname) {
    struct stat st = {0};
    if (stat(dirname, &st) == -1) {
        #ifdef _WIN32
            if (_mkdir(dirname) == -1 && errno != EEXIST) {
                printf("\nError creating directory: %s", dirname);
                return;
            }
        #else
            if (mkdir(dirname, 0700) == -1 && errno != EEXIST) {
                printf("\nError creating directory: %s", dirname);
                return;
            }
        #endif
    }
}

// Save all users data to a file
void saveUsersToFile() {
    createDirectoryIfNotExists("userdata");
    
    char userFilePath[200];
    sprintf(userFilePath, "userdata/users.dat");
    FILE *userFile = fopen(userFilePath, "wb");
    if (userFile == NULL) {
        printf("\nError opening file for writing!");
        return;
    }

    struct user *temp = users;
    while (temp != NULL) {
        // Write user data
        fwrite(temp, sizeof(struct user), 1, userFile);
        // Save user's expenses separately
        saveUserExpenses(temp);
        temp = temp->next;
    }
    fclose(userFile);
    printf("\nAll user data saved successfully!");
}

// Load all users data from file
void loadUsersFromFile() {
    char userFilePath[200];
    sprintf(userFilePath, "userdata/users.dat");
    FILE *userFile = fopen(userFilePath, "rb");
    if (userFile == NULL) {
        printf("\nNo existing user data found.");
        return;
    }

    struct user *temp, *last = NULL;
    users = NULL; // Clear existing users list

    while (1) {
        temp = (struct user*)malloc(sizeof(struct user));
        if (fread(temp, sizeof(struct user), 1, userFile) != 1) {
            free(temp);
            break;
        }

        temp->next = NULL;
        temp->account = NULL;

        // Load user's expenses
        loadUserExpenses(temp);

        if (users == NULL) {
            users = temp;
        } else {
            last->next = temp;
        }
        last = temp;
    }

    fclose(userFile);
    printf("\nUser data loaded successfully!");
}

// Save specific user's expenses to file
void saveUserExpenses(struct user* user) {
    if (user == NULL || user->account == NULL) return;

    createDirectoryIfNotExists("userdata");
    
    char filename[200];
    sprintf(filename, "userdata/expenses_%s.dat", user->email);
    FILE *expFile = fopen(filename, "wb");
    if (expFile == NULL) {
        printf("\nError opening expense file for writing!");
        return;
    }

    // Write account information
    fwrite(user->account, sizeof(struct account), 1, expFile);

    // Write all expenses
    struct expense *exp = user->account->expenses;
    while (exp != NULL) {
        fwrite(exp, sizeof(struct expense), 1, expFile);
        exp = exp->next;
    }

    fclose(expFile);
}

// Load specific user's expenses from file
void loadUserExpenses(struct user* user) {
    if (user == NULL) return;

    char filename[200];
    sprintf(filename, "userdata/expenses_%s.dat", user->email);
    FILE *expFile = fopen(filename, "rb");
    if (expFile == NULL) {
        return; // No expenses file exists for this user
    }

    // Read account information
    user->account = (struct account*)malloc(sizeof(struct account));
    fread(user->account, sizeof(struct account), 1, expFile);
    user->account->expenses = NULL;

    // Read all expenses
    struct expense *exp, *last = NULL;
    while (1) {
        exp = (struct expense*)malloc(sizeof(struct expense));
        if (fread(exp, sizeof(struct expense), 1, expFile) != 1) {
            free(exp);
            break;
        }
        exp->next = NULL;

        if (user->account->expenses == NULL) {
            user->account->expenses = exp;
        } else {
            last->next = exp;
        }
        last = exp;
    }

    fclose(expFile);
}

// Function to clean all user data
void cleanAllUserData() {
    struct user *temp = users;
    while (temp != NULL) {
        char filename[200];
        sprintf(filename, "userdata/expenses_%s.dat", temp->email);
        if (remove(filename) != 0) {
            printf("\nFailed to remove %s", filename);
        }
        // Free all expenses
        if (temp->account != NULL) {
            struct expense *exp = temp->account->expenses;
            while (exp != NULL) {
                struct expense *nextExp = exp->next;
                free(exp);
                exp = nextExp;
            }
            free(temp->account);
        }
        struct user *nextUser = temp->next;
        free(temp);
        temp = nextUser;
    }
    users = NULL;

    // Remove user data files
    if (remove("userdata/users.dat") != 0) {
        printf("\nFailed to remove userdata/users.dat");
    }
    printf("\nAll user data has been cleaned successfully!\n");
}
