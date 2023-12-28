#include<stdio.h>
#include<stdlib.h>
#include "inverted_search.h"
extern sll *head;
int main(int argc,char **argv)
{
    int choice;
    m_table main_table[index_size];

    for(int i=0;i<index_size;i++)
    {
        main_table[i].index=i;
        main_table[i].link=NULL;
    }

    if(validation(argc,argv)==success)
    {
        printf("Validation successfull\n");
        printf("-----------------------------------------INVERTED SEARCH----------------------------------------\n");
        while(1)
        {
            printf("1-Create Database\n2-Display Database\n3-Exit\n");
            printf("Enter your choice: ");

            scanf("%d",&choice);
            switch(choice)
            {
                case 1: 
                    if(create_database(&head,main_table)==success)
                    {
                        printf("Create database successfull\n");
                    }
                    else
                    {
                        printf("Create database failure\n");
                    }
                    break;
                case 2:
                    if(display_database(main_table)==success)
                    {
                        printf("Display database successfull\n");
                    }
                    else
                    {
                        printf("Display database failure\n");
                    }
                    break;
                case 3:
                    exit(0);
                default: printf("Invalid choice\n");

            }
        }
    }
    else
    {
        printf("Validation failed\n");
    }

    return 0;
}


