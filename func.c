#include<stdio.h>
#include "inverted_search.h"
#include<string.h>
#include<stdlib.h>
Status validation(int argc,char *argv[])
{
    int i;
    sll *head=NULL;
    if(argc>1)
    {
        for(i=1;i<argc;i++)
        {
            if(check_file_exists(argv[i])==success)
            {
                printf("Success: %s exists\n",argv[i]);

                if(strcmp(strstr(argv[i], "."),".txt")==0 && check_file_exists(argv[i])==success)
                {
                    printf("FILE %s is added\n",argv[i]);
                    if(check_file_empty(argv[i])==success)
                    {
                        printf("Success: %s is not empty\n",argv[i]);
                        if(insert(&head,argv[i])==success)
                        {
                            printf("Success: %s is inserted to list\n",argv[i]);
                        }
                        else
                        {
                            printf("Error: %s is not inserted to list\n",argv[i]);
                        }
                    }
                    else
                    {
                        printf("Error: %s is empty\n",argv[i]);
                    }

                }
                else
                {
                    printf("Error: %s is not a txt file\n",argv[i]);
                }
            }
            else
            {
                printf("Error: %s doesn't exists\n",argv[i]);
            }
        }
        print_list(head);
        return success;

    }
    return failure;
}

Status check_file_empty(char *fname)
{
    FILE *fptr=fopen(fname,"r");
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr)>0)
        return success;
    else
        return failure;
}

Status check_file_exists(char *fname)
{
    FILE *fptr=fopen(fname,"r");
    if(fptr)
        return success;
    else
        return failure;
}

Status insert(sll **head,char *fname)
{
    sll *New=malloc(sizeof(sll));
    if(New==NULL)
        return failure;
    else
    {
      strcpy(New->file_name,fname);
      New->link=NULL;

      if(*head==NULL)
      {
          *head=New;
          (*head)->link=NULL;
          return success;
      }

     sll *temp=*head;
     sll *prev=*head;

      while(temp)
      {
         if((strcmp(temp->file_name,fname)==0))
         {
             printf("%s is duplicate file\n",fname);
            return failure;
         }
         prev=temp;
         temp=temp->link;
      }
      prev->link=New;
      return success;
    }
}


void print_list(sll *head)
{
    sll *temp=head;
    while(temp)
    {
        printf("%s ",temp->file_name);
        temp=temp->link;
    }
    printf("<-NULL\n");
}
