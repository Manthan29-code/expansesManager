#include "appmenu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// comment this all while running programme
// #include "user.c"
// #include "account.c"
// #include "expenses.c"

//to create account
void addAccount(struct user* currUser)
{
    if(currUser->account==NULL)
    {
        float amount;
        char name[30];
        
        printf("\nEnter name for account");
        fflush(stdin);
        gets(name);
        printf("\nEnter amount you want to add");
        fflush(stdin);
        scanf("%f" ,&amount);

        struct account* newAccount=(struct account*)malloc(sizeof( struct account));
        newAccount->balance=amount;
        newAccount->expenses=NULL;
        strcpy(newAccount->name ,name);

        currUser->account=newAccount;
        printf("\nAccount added!!!");

    }
    else{
        printf("\naccount already exist");
        return;
    }
    return;
}

// to add expense
void addExpanse(struct user* currUser)
{
    if(currUser->account==NULL)
    {
        printf("\n Add account first");
        return;
    }
    char title[30];
    float amount;
    int day, month, year;
    
    printf("\nExpanse title: ");
    fflush(stdin);
    gets(title);
    
    printf("\nAdd expanse amount: ");
    fflush(stdin);
    scanf("%f", &amount);
    
    printf("\nEnter expense date (DD MM YYYY): ");
    fflush(stdin);
    scanf("%d %d %d", &day, &month, &year);
    
    // Validate date
    if (!isValidDate(day, month, year)) {
        printf("\nInvalid date! Please enter a valid date.");
        return;
    }

    //to check expense is less then balance or not
    if(amount > currUser->account->balance)
    {
        printf("\n insufficient balance");
        printf("\n add balance first....");
        return;
    }
    else{
        currUser->account->balance-=amount;
    }
    
    struct expense* newExpanse=(struct expense*)malloc(sizeof(struct expense));
    newExpanse->amount=amount;
    strcpy(newExpanse->title, title);
    newExpanse->day = day;
    newExpanse->month = month;
    newExpanse->year = year;
    newExpanse->next=NULL;

    if(currUser->account->expenses==NULL)
    {
        currUser->account->expenses=newExpanse;
        printf("\n Expense added!!!!");
        checkBalance(currUser);
        return;
    }
    struct expense* temp=currUser->account->expenses;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=newExpanse;
    printf("\n Expense added!!!!");
    checkBalance(currUser);
    return;
}

// Expanse History
void listExpanse(struct user* currUser)
{
    if(currUser->account==NULL)
    {
        printf("\nCreate Account first");
        return;
    }
    struct expense* temp=currUser->account->expenses;
    if(temp==NULL)
    {
        printf("\n no any expense");
        return;
    }
    
    printf("\n");
    printTableLine(65);
    printf("|");
    printCenteredText("Title", 27);
    printf("|");
    printCenteredText("Date", 17);
    printf("|");
    printCenteredText("Amount", 17);
    printf("|\n");
    printTableLine(65);
    
    while(temp!=NULL)
    {
        printf("|");
        printCenteredText(temp->title, 27);
        printf("|");
        
        char dateStr[15];
        sprintf(dateStr, "%02d/%02d/%d", temp->day, temp->month, temp->year);
        printCenteredText(dateStr, 17);
        
        printf("|");
        char amountStr[15];
        sprintf(amountStr, "%.2f", temp->amount);
        printCenteredText(amountStr, 17);
        
        printf("|\n");
        temp=temp->next;
    }
    printTableLine(65);
    return;
}


//to check balance
void checkBalance(struct user* currUser)
{
    if(currUser->account==NULL)
    {
        printf("\nCreate Account first");
        return;
    }
    else{
        printf("\nbalance is :- %.2f" , currUser->account->balance);
    }
}

//to add balance 
void addBalance(struct user* currUser)
{
     if(currUser->account==NULL)
    {
        printf("\nCreate Account first");
        return;
    }
    float amount;
    printf("\n enter amount u want to add");
    fflush(stdin);
    scanf("%f" , &amount);
    currUser->account->balance += amount;
    printf("\n balance added ");
    checkBalance(currUser);
}



void appmenu(struct user *currUser)
{
    int choice;
    printf("\n1>   add account");
    printf("\n2>   add Expanse");
    printf("\n3>   list expanse");
    printf("\n4>   check balance");
    printf("\n5>   add balance");
    printf("\n6>   logout");  // redirect ot main menu;
    printf("\nEnter your choice");
    scanf("%d" , &choice);
    switch(choice)
    {
        case 1:
            addAccount(currUser);
            appmenu(currUser);
        break;
        case 2:
            addExpanse(currUser);
            appmenu(currUser);
        break;
        case 3:
            listExpanse(currUser);
            appmenu(currUser);
        break;
        case 4:
            checkBalance(currUser);
            appmenu(currUser);
            break;
            case 5:
            addBalance(currUser);
            appmenu(currUser);
        break;
        case 6:
            return;
        break;
        default:
            printf("\n enter valid choice");
        break;
    }
}


