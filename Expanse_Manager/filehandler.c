#include "filehandler.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Save all users data to a file
void saveUsersToFile() {
    FILE *userFile = fopen("users.dat", "wb");
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
    FILE *userFile = fopen("users.dat", "rb");
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

    char filename[100];
    sprintf(filename, "expenses_%s.dat", user->email);
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

    char filename[100];
    sprintf(filename, "expenses_%s.dat", user->email);
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