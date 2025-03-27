#include<stdio.h>
#include<stdlib.h>
#include "signup.h"
#include "login.h"
#include "admin.h"
#include "filehandler.h"


int main()
{
    // Load existing user data when program starts
    loadUsersFromFile();

    int choice;
    while(1)
    {
        printf("\n=== Expense Manager ===");
        printf("\n1>  Signup");
        printf("\n2>  Login");
        printf("\n3>  Admin Login");
        printf("\n4>  Exit");
        printf("\nEnter your choice :-");
        scanf("%d" ,&choice);

        switch(choice)
        {
            case 1:
                signup();
                // Save data after new user signup
                saveUsersToFile();
                break;
            case 2:
                login();
                // Save data after user session
                saveUsersToFile();
                break;
            case 3:
                if(adminLogin()) {
                    adminMenu();
                }
                break;
            case 4:
                // Save all data before exit
                saveUsersToFile();
                printf("\nThank you for using Expense Manager!");
                exit(0);
                break;
            default:
                printf("\nEnter valid choice");
                break;
        }
    }
}