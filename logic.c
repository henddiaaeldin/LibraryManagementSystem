#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logic.h"

void read_books()
{
    FILE *fbooks;
    fbooks=fopen("books.txt","r");
    counterbooks=0;
    if(fbooks!=NULL)
    {
        while(!feof(fbooks))
        {
            fscanf(fbooks,"%[^,],%[^,],%[^,],%[^,],",book[counterbooks].title,book[counterbooks].author,book[counterbooks].publisher,book[counterbooks].isbn);
            fscanf(fbooks,"%d/%d/%d,%d,",&book[counterbooks].date.day,&book[counterbooks].date.month,&book[counterbooks].date.year,&book[counterbooks].copies);
            fscanf(fbooks,"%d,%[^\n]\n",&book[counterbooks].availablecopies,book[counterbooks].category);
            counterbooks++;
        }
    }
    else
        printf("file doesn't exist");
    fclose(fbooks);
}
void read_member()
{
    FILE *fusers;
    fusers=fopen("members.txt","r");
    if(fusers!=NULL)
    {
        while(!feof(fusers))
        {
            fscanf(fusers,"%[^,],%[^,],%d,%d,",member[counterusers].firstname,member[counterusers].lastname,&member[counterusers].id,&member[counterusers].address.building);
            fscanf(fusers,"%[^,],%[^,],%[^,],",member[counterusers].address.street,member[counterusers].address.city,member[counterusers].phone);
            fscanf(fusers,"%d,%[^\n]\n",&member[counterusers].age,member[counterusers].email);
            counterusers++;
        }
    }
    else
        printf("file doesn't exist");
    fclose(fusers);
}
void read_borrow()
{
    FILE *fborrows;
    fborrows=fopen("borrows.txt","r");
    if(fborrows!=NULL)
    {
        while(!feof(fborrows))
        {
            fscanf(fborrows,"%[^,],%d,",borrow[counterborrow].isbn,&borrow[counterborrow].id);
            fscanf(fborrows,"%d/%d/%d,",&borrow[counterborrow].borrowdate.day,&borrow[counterborrow].borrowdate.month,&borrow[counterborrow].borrowdate.year);
            fscanf(fborrows,"%d/%d/%d,",&borrow[counterborrow].duetoreturn.day,&borrow[counterborrow].duetoreturn.month,&borrow[counterborrow].duetoreturn.year);
            fscanf(fborrows,"%d/%d/%d\n",&borrow[counterborrow].returndate.day,&borrow[counterborrow].returndate.month,&borrow[counterborrow].returndate.year);
            counterborrow++;
            member_borrows();
            books_borrowed();
        }
    }
    else
        printf("file doesn't exist");
    fclose(fborrows);
}
void member_borrows()
{
    int i,j;
    for(i=0; i<counterusers; i++)
    {
        member[i].noofborrows=0;
        for(j=0; j<counterborrow; j++)
        {
            if(member[i].id==borrow[j].id && borrow[j].returndate.day==0 && borrow[j].returndate.month==0 && borrow[j].returndate.year==0)
                member[i].noofborrows++;
        }
    }
}
void books_borrowed()
{
    int i,j;
    for(i=0; i<counterbooks; i++)
    {
        book[i].noofborrows=0;
        for(j=0; j<counterborrow; j++)
        {
            if(strcmp(book[i].isbn,borrow[j].isbn)==0)
                book[i].noofborrows++;
        }
    }
}
void new_book ()
{
    printf("enter the name of the book:\n");
    fflush(stdin);
    gets(book[counterbooks].title);
    printf("enter the name of the author:\n");
    gets(book[counterbooks].author);
    printf("enter the name of the publisher:\n");
    gets(book[counterbooks].publisher);
    printf("enter the ISBN of the book:\n");
    gets(book[counterbooks].isbn);
    printf("enter the date of publication:\n");
    scanf("%d/%d/%d",&book[counterbooks].date.day,&book[counterbooks].date.month,&book[counterbooks].date.year);
    printf("enter the number of copies:\n");
    scanf("%d",&book[counterbooks].copies);
    printf("enter the current available number of copies:\n");
    scanf("%d",&book[counterbooks].availablecopies);
    printf("enter the category:\n");
    fflush(stdin);
    gets(book[counterbooks].category);
    counterbooks++;
}
void search()
{
    char b[50];
    int i,flag=0;
    printf("Search for:\n");
    fflush(stdin);
    gets(b);
    for(i=0; i<counterbooks; i++)
    {
        if(strstr(book[i].title,b)!=0 || strstr(book[i].author,b)!=0 || strcmp(b,book[i].isbn)==0 || strcmp(b,book[i].category)==0)
        {
            printf("%s,%s,%s,%s,%d/%d/%d,",book[i].title,book[i].author,book[i].publisher,book[i].isbn,book[i].date.day,book[i].date.month,book[i].date.year);
            printf("%d,%d,%s\n",book[i].copies,book[i].availablecopies,book[i].category);
            flag=1;
        }
    }
    if(flag==0)
        printf("No matches found!\n");
}
void add_copy()
{
    char isbn[50];
    int x,i,flag=0;
    printf("enter the book ISBN:\n");
    fflush(stdin);
    gets(isbn);
    printf("enter the new number of copies:\n");
    scanf("%d",&x);
    for(i=0; i<counterbooks; i++)
    {
        if(strcmp(isbn,book[i].isbn)==0 )
        {
            flag=1;
                book[i].copies+=x;
        }
    }
    if (flag==0)
     printf("Book not found!\n");
}
void delete_book()
{
    int i,flag=0;
    char isbn[50];
    printf("Enter the ISBN of the book:");
    fflush(stdin);
    gets(isbn);
    for(i=0; i<counterbooks; i++)
    {
        if(strcmp(isbn,book[i].isbn)==0)
        {
            book[i]=book[counterbooks-1];
            counterbooks--;
            flag=1;
            printf("Book deleted!");
        }
    }
    if(flag==0)
        printf("Not found!\n");
}
void edit_book()
{
    char isbn[50],temp[50];
    int i,x,y,y1,y2,y3;
    printf("Edit:\n1.title\n2.Author name\n3.Publisher\n4.ISBN\n5.Date of publication\n6.Numberof copies\n7.Available number of copies\n8.Category\n9.Back\n");
    scanf("%d",&x);
    if(x==9)
        menu();
    printf("Enter the ISBN of the book to be edited:\n");
    fflush(stdin);
    gets(isbn);
    for(i=0; i<counterbooks; i++)
    {
        if(strcmp(book[i].isbn,isbn)==0)
        {
            switch(x)
            {
            case 1:
                printf("Enter the title to be edited:\n");
                fflush(stdin);
                gets(temp);
                strcpy(book[i].title,temp);
                printf("Title edited!\n");
                menu();
                break;
            case 2:
                printf("Enter the author name to be edited:\n");
                fflush(stdin);
                gets(temp);
                strcpy(book[i].author,temp);
                printf("Author name edited!\n");
                menu();
                break;
            case 3:
                printf("Enter the publisher to be edited:\n");
                fflush(stdin);
                gets(temp);
                strcpy(book[i].publisher,temp);
                printf("Publisher edited!\n");
                menu();
                break;
            case 4:
                printf("Enter the ISBN to be edited:\n");
                fflush(stdin);
                gets(temp);
                strcpy(book[i].isbn,temp);
                printf("ISBN edited!\n");
                edit_book();
                break;
            case 5:
                printf("Enter the date of publication to be edited:\n");
                scanf("%d/%d/%d",&y1,&y2,&y3);
                book[i].date.day=y1;
                book[i].date.month=y2;
                book[i].date.year=y3;
                printf("Date edited!\n");
                menu();
                break;
            case 6:
                printf("Enter the number of copies to be edited:\n");
                scanf("%d",&y);
                book[i].copies=y;
                printf("Number of copies edited!\n");
                menu();
                break;
            case 7:
                printf("Enter the number of available copies to be edited:\n");
                scanf("%d",&y);
                book[i].availablecopies=y;
                printf("Number of available copies edited!\n");
                menu();
                break;
            case 8:
                printf("Enter the category to be edited:\n");
                fflush(stdin);
                gets(temp);
                strcpy(book[i].category,temp);
                printf("Category edited!\n");
                menu();
                break;
            }
        }
    }
}
void registration()
{
    printf("enter the last name:\n");
    fflush(stdin);
    gets(member[counterusers].lastname);
    printf("enter the first name:\n");
    fflush(stdin);
    gets(member[counterusers].firstname);
    printf("enter the id:\n");
    scanf("%d",&member[counterusers].id);
    printf("enter the building:\n");
    scanf("%d",&member[counterusers].address.building);
    printf("Enter the district:\n");
    fflush(stdin);
    gets(member[counterusers].address.street);
    printf("Enter the city:\n");
    fflush(stdin);
    gets(member[counterusers].address.city);
    printf("enter the phone number:\n");
    fflush(stdin);
    gets(member[counterusers].phone);
    printf("enter the age:\n");
    scanf("%d",&member[counterusers].age);
    printf("enter the e-mail:\n");
    fflush(stdin);
    gets(member[counterusers].email);
    counterusers++;
}
void borrowing()
{
    char isbn[50];
    int i,id,j,flag=0,flag1=0;;
    printf("enter the book ISBN:");
    gets(isbn);
     for(i=0;i<counterbooks;i++)
    {
        if(strcmp(book[i].isbn,isbn)==0)
            flag1=1;
    }
    if(flag1==0)
    {
        printf("Book ISBN is incorrect!\n");
        printf("enter the book ISBN:\n");
        gets(isbn);
    }

    printf("enter the user ID:");
    scanf("%d",&id);
    for(i=0; i<counterusers; i++)
    {

        if(member[i].id==id)
        {
            flag=1;
            if(member[i].noofborrows==3)
            {
                printf("The member cannot borrow more than three books at a time!\n");
                break;
            }
            else
            {
                for(j=0; j<counterbooks; j++)
                {
                    if(strcmp(book[j].isbn,isbn)==0)
                        book[j].availablecopies--;
                }
                strcpy(borrow[counterborrow].isbn,isbn);
                borrow[counterborrow].id=id;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                borrow[counterborrow].borrowdate.day=tm.tm_mday;
                borrow[counterborrow].borrowdate.month=tm.tm_mon+1;
                borrow[counterborrow].borrowdate.year=tm.tm_year+1900;
                printf("Enter date due to return:\n");
                scanf("%d/%d/%d",&borrow[counterborrow].duetoreturn.day,&borrow[counterborrow].duetoreturn.month,&borrow[counterborrow].duetoreturn.year);
                borrow[counterborrow].returndate.day=0;
                counterborrow++;
            }
        }
    }
    if(flag==0)
        printf("Id is incorrect!\n");

}
void return_book()
{
    char isbn[50];
    int i,id,j,flag=0,flag1=0;;
    printf("enter the book ISBN:");
    fflush(stdin);
    gets(isbn);
    for(i=0;i<counterbooks;i++)
    {
        if(strcmp(book[i].isbn,isbn)==0)
            flag1=1;
    }
    if(flag1==0)
    {
        printf("Book ISBN is incorrect!\n");
        printf("enter the book ISBN:\n");
        gets(isbn);
    }
    printf("enter the user ID:\n");
    scanf("%d",&id);
    for(i=0; i<counterborrow; i++)
    {
        if(borrow[i].id==id && strcmp(borrow[i].isbn,isbn)==0)
        {
            flag=1;
            for(j=0; j<counterbooks; j++)
            {
                if(strcmp(book[j].isbn,borrow[i].isbn)==0)
                    book[j].availablecopies++;
            }
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            borrow[i].returndate.day=tm.tm_mday;
            borrow[i].returndate.month=tm.tm_mon+1;
            borrow[i].returndate.year=tm.tm_year+1900;

        }
    }
    if(flag==0)
        printf("Id is incorrect!\n");
}
void remove_member()
{
    int i,j,id,flag=0,flag1=0;
    printf("Enter the ID of the member:\n");
    scanf("%d",&id);
    for(i=0; i<counterborrow; i++)
    {
        if(borrow[i].id==id && borrow[i].returndate.day==0)
            flag=1;
    }
    if(flag==1)
        printf("member has borrowed books not returned(cannot remove member)\n");
    if(flag==0)
    {
        for(j=0; j<counterusers; j++)
        {
            if(member[j].id==id)
            {
                member[j]=member[counterusers-1];
                counterusers--;
                flag1=1;
                printf("Member removed!\n");
            }
        }

        if(flag1==0)
            printf("Id is incorrect!\n");
    }
}
void print_overdue(char* isbn,int id)
{
    int i,j;

    for(i=0; i<counterborrow; i++)
    {
        if(strcmp(borrow[i].isbn,isbn)==0 && borrow[i].id==id)
        {
            for(j=0; j<counterbooks; j++)
    {
        if(strcmp(book[j].isbn,isbn)==0)
            printf("%s,",book[j].title);
    }
            printf("%s,%d,",borrow[i].isbn,borrow[i].id);
            printf("%d/%d/%d,",borrow[i].borrowdate.day,borrow[i].borrowdate.month,borrow[i].borrowdate.year);
            printf("%d/%d/%d\n",borrow[i].duetoreturn.day,borrow[i].duetoreturn.month,borrow[i].duetoreturn.year);
        }
    }
}
void overdue_books()
{
    dates date1;
    int i,flag=0;
    for(i=0; i<counterborrow; i++)
    {
        if(borrow[i].returndate.day==0)
        {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            date1.day=tm.tm_mday;
            date1.month=tm.tm_mon+1;
            date1.year=tm.tm_year+1900;
            if(date1.year>borrow[i].duetoreturn.year)
            {
                print_overdue(borrow[i].isbn,borrow[i].id);
                flag=1;
            }
            else if(date1.year==borrow[i].duetoreturn.year)
            {
                if(date1.month>borrow[i].duetoreturn.month)
                {
                    print_overdue(borrow[i].isbn,borrow[i].id);
                    flag=1;
                }
                else if(date1.month==borrow[i].duetoreturn.month)
                {
                    if(date1.day>borrow[i].duetoreturn.day)
                    {
                        print_overdue(borrow[i].isbn,borrow[i].id);
                        flag=1;
                    }
                }

            }
        }
    }
    if(flag==0)
        printf("No overdue books!\n");
}
void popular_books()
{
int i,j;
books temp;
printf("\t\tMost popular books\n");
for(i=0; i<counterbooks; i++)
    {
        for(j=i+1; j<counterbooks; j++)
        {
            if(book[i].noofborrows<book[j].noofborrows)
            {
                temp=book[i];
                book[i]=book[j];
                book[j]=temp;
            }
        }
    }
     for(i=0;i<5;i++)
    {
        printf("%d.%s\n",i+1,book[i].title);
    }
}
void print_all_books()
{
    int i;
    for(i=0;i<counterbooks;i++)
    {
        printf("%s,%s,%s,%s,",book[i].title,book[i].author,book[i].publisher,book[i].isbn);
        printf("%d/%d/%d,%d,",book[i].date.day,book[i].date.month,book[i].date.year,book[i].copies);
        printf("%d,%s\n",book[i].availablecopies,book[i].category);
    }
}
void print_all_users()
{
    int i;
    for(i=0; i<counterusers; i++)
    {
        printf("%s,%s,%d,%d,",member[i].lastname,member[i].firstname,member[i].id,member[i].address.building);
        printf("%s,%s,%s,",member[i].address.street,member[i].address.city,member[i].phone);
        printf("%d,%s\n",member[i].age,member[i].email);
    }
}
void print_all_borrows()
{
    int i;
    for(i=0; i<counterborrow; i++)
    {
        printf("%s,%d,%d/%d/%d,",borrow[i].isbn,borrow[i].id,borrow[i].borrowdate.day,borrow[i].borrowdate.month,borrow[i].borrowdate.year);
        printf("%d/%d/%d,",borrow[i].duetoreturn.day,borrow[i].duetoreturn.month,borrow[i].duetoreturn.year);
        printf("%d/%d/%d\n",borrow[i].returndate.day,borrow[i].returndate.month,borrow[i].returndate.year);
    }

}
void print_file_books()
{
    FILE *fbooks;
    fbooks=fopen("books.txt","w");
    int i;
    for(i=0; i<counterbooks; i++)
    {
        fprintf(fbooks,"%s,%s,%s,%s,",book[i].title,book[i].author,book[i].publisher,book[i].isbn);
        fprintf(fbooks,"%d/%d/%d,%d,",book[i].date.day,book[i].date.month,book[i].date.year,book[i].copies);
        fprintf(fbooks,"%d,%s\n",book[i].availablecopies,book[i].category);
    }
    fclose(fbooks);
}
void print_file_users()
{
    FILE *fusers;
    fusers=fopen("members.txt","w");
    int i;
    for(i=0; i<counterusers; i++)
    {
        fprintf(fusers,"%s,%s,%d,%d,",member[i].lastname,member[i].firstname,member[i].id,member[i].address.building);
        fprintf(fusers,"%s,%s,%s,",member[i].address.street,member[i].address.city,member[i].phone);
        fprintf(fusers,"%d,%s\n",member[i].age,member[i].email);
    }
    fclose(fusers);
}
void print_file_borrows()
{
    FILE *fborrows;
    fborrows=fopen("borrows.txt","w");
    int i;
    for(i=0; i<counterborrow; i++)
    {
        fprintf(fborrows,"%s,%d,%d/%d/%d,",borrow[i].isbn,borrow[i].id,borrow[i].borrowdate.day,borrow[i].borrowdate.month,borrow[i].borrowdate.year);
        fprintf(fborrows,"%d/%d/%d,",borrow[i].duetoreturn.day,borrow[i].duetoreturn.month,borrow[i].duetoreturn.year);
        fprintf(fborrows,"%d/%d/%d\n",borrow[i].returndate.day,borrow[i].returndate.month,borrow[i].returndate.year);
    }
    fclose(fborrows);
}
void menu()
{
    int x,y,i;
    printf("\t\t\tMAIN MENU\n");
    printf("1.Book management\n2.Member management\n3.Borrow management\n4.Administrative actions\n5.Print all books\n6.Print all members\n7.Print all borrows\n8.Save changes\n9.Exit\n");
    scanf("%d",&x);
    switch (x)
    {
    case 1:
        printf("1.Insert a new book\n2.Search\n3.Add new copies\n4.Delete a book\n5.Edit\n6.Back\n");
        scanf("%d",&y);
        switch (y)
        {
        case 1:
            new_book();
            menu();
            break;
        case 2:
            search();
            menu();
            break;
        case 3:
            add_copy();
            menu();
            break;
        case 4:
            delete_book();
            menu();
            break;
        case 5:
            edit_book();
            menu();
            break;
        case 6:
            menu();
            break;

        }
        break;
    case 2:
        printf("1.Register\n2.Remove\n3.Back\n");
        scanf("%d",&y);
        if(y==1)
           {
               registration();
               menu();
           }
        else if(y==2)
           {
               remove_member();
               menu();
           }
        else
            menu();
        break;
    case 3:
        printf("1.Borrow\n2.Return\n3.back\n");
        scanf("%d",&y);
        if(y==1)
        {
            search();
            borrowing();
            menu();
        }
        else if(y==2)
            {
            return_book();
        menu();
            }
        else
            menu();
        break;
    case 4:
        printf("1.Overdue\n2.Popular\n3.Back\n");
        scanf("%d",&y);
        if(y==1)
            {
            overdue_books();
        menu();
            }
        else if(y==2){
            popular_books();
            menu();
        }
        else
            menu();
        break;
    case 5:
        print_all_books();
        menu();
        break;
    case 6:
        print_all_users();
        menu();
        break;
    case 7:
        print_all_borrows();
        menu();
        break;
    case 8:
        print_file_books();
        print_file_users();
        print_file_borrows();
        printf("Data saved in files!\n");
        menu();
        break;
    case 9:
        printf("1.Save and exit\n2.Exit without saving");
        scanf("%d",&y);
        if(y==1)
        {
            print_file_books();
            print_file_users();
            print_file_borrows();
        }
        break;
    }
}
