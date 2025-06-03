#ifndef APPMENU_H
#define APPMENU_H

#include "user.h"
#include "admin.h"

void addAccount(struct user* currUser);
void addExpanse(struct user* currUser);
void listExpanse(struct user* currUser);
void checkBalance(struct user* currUser);
void addBalance(struct user* currUser);
void appmenu(struct user *currUser);

#endif // APPMENU_H 