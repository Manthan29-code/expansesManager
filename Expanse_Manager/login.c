#include "login.h"
#include "user.h"
#include "appmenu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include "user.c"

void login()
{
    char  password[20];
    char  email[50];

    printf("\nEnter password:- ");
    fflush(stdin);
    gets(password);
    printf("\nEnter email:- ");
    fflush(stdin);
    gets(email);
    if(users!=NULL)
    {
        printf("\nuser exist (create first user) let's check you are among them or not");
    }
    if(users==NULL)
    {
        printf("\nuser not exist (create first user)");
        return;
    }
    else{
        struct user *temp=users;
        while(temp!= NULL)
        {
            if ( (strcmp(temp->email, email) == 0) && (strcmp(temp->password, password) == 0) )
            {
                printf("\nuser found");
                appmenu(temp);
                printf("\nexit from appMenu");
            }
            temp=temp->next;
        }
        return;
    }
}


// int main()
// {
//     login();
// }


// int main()
// {
//     int choice;
//     while(1)
//     {
//         printf("1>  signup");
//         printf("1>  Login");
//         printf("1>  Exit");

//         switch(choice)
//         {
//             case 1:
//                 signup();
//             break;
//             case 2:
//                 Login();
//             break;
//             case 3:
//                 exit(0);
//             break;
//             default:
//                 printf("\nEnter valid choice");
//             break;
    
//         }
//     }    
// }