#include "admin.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
        printf("\n6. Logout");
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
    
    printf("\n=== Registered Users ===");
    while(temp != NULL) {
        count++;
        printf("\n%d. Name: %s, Email: %s", count, temp->firstname, temp->email);
        temp = temp->next;
    }
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
            printf("\n=== User Details ===");
            printf("\nName: %s", temp->firstname);
            printf("\nEmail: %s", temp->email);
            
            if(temp->account != NULL) {
                printf("\nAccount Name: %s", temp->account->name);
                printf("\nCurrent Balance: %.2f", temp->account->balance);
                
                // Show expenses
                struct expense *exp = temp->account->expenses;
                if(exp != NULL) {
                    printf("\n\nExpenses:");
                    while(exp != NULL) {
                        printf("\n- %s: %.2f", exp->title, exp->amount);
                        exp = exp->next;
                    }
                } else {
                    printf("\nNo expenses recorded.");
                }
            } else {
                printf("\nNo account created yet.");
            }
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
    
    printf("\n=== All Expenses ===");
    while(temp != NULL) {
        if(temp->account != NULL && temp->account->expenses != NULL) {
            printf("\n\nUser: %s", temp->firstname);
            struct expense *exp = temp->account->expenses;
            float userTotal = 0;
            
            while(exp != NULL) {
                printf("\n- %s: %.2f", exp->title, exp->amount);
                userTotal += exp->amount;
                exp = exp->next;
            }
            
            printf("\nTotal for %s: %.2f", temp->firstname, userTotal);
            totalExpenses += userTotal;
        }
        temp = temp->next;
    }
    printf("\n\nTotal Expenses Across All Users: %.2f", totalExpenses);
}

// Function to view expenses by date range (placeholder - needs date field in expense struct)
void viewExpensesByDateRange() {
    printf("\nNote: Date range functionality will be implemented in future versions.");
    printf("\nCurrently showing all expenses instead:");
    viewAllExpenses();
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
    
    printf("\n=== Expense Statistics ===");
    printf("\nTotal Users: %d", totalUsers);
    printf("\nUsers with Expenses: %d", usersWithExpenses);
    printf("\nTotal Expenses: %.2f", totalExpenses);
    printf("\nAverage Expense per User: %.2f", usersWithExpenses > 0 ? totalExpenses/usersWithExpenses : 0);
    if(strlen(maxExpenseUser) > 0) {
        printf("\nUser with Highest Expenses: %s (%.2f)", maxExpenseUser, maxExpense);
    }
} 