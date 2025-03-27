#ifndef USER_H
#define USER_H

#include "account.h"

struct user {
    char firstname[50];
    char email[100];
    char password[50];
    struct account *account;    // Pointer to the user's account
    struct user *next;
};

extern struct user *users;

#endif // USER_H 