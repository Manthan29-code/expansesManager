#ifndef EXPENSES_H
#define EXPENSES_H

struct expense {
    char title[100];
    float amount;
    int day;
    int month;
    int year;
    struct expense *next;
};

#endif // EXPENSES_H 