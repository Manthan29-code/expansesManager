#include "login.h"
#include "user.h"
#include "appmenu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "filehandler.h"
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
        printf("\nuser exist");
    }
    if(users==NULL)
    {
        printf("\nuser not exist");
        printf("\nregister yourself first");
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
        saveUsersToFile();
        return;
    }
}


