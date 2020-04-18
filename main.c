#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logic.h"
int counterbooks=0;
int counterusers=0;
int counterborrow=0;
books book[100];
members member[100];
borrowed borrow[100];
int main()
{
    read_books();
    read_borrow();
    read_member();
    popular_books();
    menu();

    return 0;
}
