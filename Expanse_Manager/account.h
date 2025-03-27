#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "expenses.h"

struct account {
    char name[50];
    float balance;
    struct expense *expenses;   // Pointer to the head of the expenses linked list
};

#endif // ACCOUNT_H 