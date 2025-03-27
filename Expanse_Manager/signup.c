#include "signup.h"
#include "user.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int validateEmail(char *newEmail)
{
    if(users==NULL)
    {
        return 0;
    }
    struct user *temp=users;
    while(temp!=NULL)
    {
        if(strcmp(temp->email ,newEmail) == 0)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;

}

void signup()
{
    char  password[20];
    char  firstname[20];
    char  email[30];

    printf("\nEnter first name:-");
    fflush(stdin);
    gets(firstname);
    printf("\nEnter email:-");
    gets(email);
    while(validateEmail(email))
    {
        printf("\nUser with same email already exit ");
        printf("\nEnter another email:-");
        gets(email);  
    }    
    printf("\nEnter password:-");
    gets(password);

    struct user *newUser=(struct user*)malloc(sizeof(struct user));
    strcpy(newUser->firstname, firstname);
    strcpy(newUser->email, email);
    strcpy(newUser->password, password);
    newUser->account=NULL;
    newUser->next=NULL;
    

    if(users == NULL)
    {
        users=newUser;
        printf("\nSignup successful");
        return;
    }
    else
    {
        struct user *temp = users;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next=newUser;
    }

    printf("\nSignup successful");
    return;
}



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

// int main()
// {
//     signup();
// }