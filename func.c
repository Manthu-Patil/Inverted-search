#include<stdio.h>
#include "inverted_search.h"
#include<string.h>
#include<stdlib.h>
sll *head=NULL;
int flag=0;
Status validation(int argc,char *argv[])
{
    int i;
    word_node w_node;
    sub_node s_node;
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
                     //   printf("Success: %s is not empty\n",argv[i]);
                        if(insert(&head,argv[i])==success)
                        {
                       //     printf("Success: %s is inserted to list\n",argv[i]);
                        }
                        else
                        {
                         //   printf("Error: %s is not inserted to list\n",argv[i]);
                        }
                    }
                    else
                    {
                    //    printf("Error: %s is empty\n",argv[i]);
                    }

                }
                else
                {
                   printf("Error: %s is not a txt file  and is not added\n",argv[i]);
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
    {
        fclose(fptr);
        return success;
    }
    else
    {
        return failure;
    }
}

Status check_file_exists(char *fname)
{
    FILE *fptr=fopen(fname,"r");
    if(fptr)
    {
        fclose(fptr);
        return success;
    }
    else
    {
        return failure;
    }
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

Status create_database(sll **head,m_table *m_table)
{
    sll *temp=*head;
    char str[50];
    int index;
    int break_flag;
    while(temp)
    {
        FILE *f_ptr=fopen(temp->file_name,"r");
        while(fscanf(f_ptr,"%s",str)==1)
        {
            index=str[0] % 97;
            word_node *new_wnode=malloc(sizeof(word_node));
            sub_node *new_snode=malloc(sizeof(sub_node));
            //create subnode
            new_snode->word_count=1;
            strcpy(new_snode->file_name,temp->file_name);
            new_snode->subnode_link=NULL;
            //create word node
            new_wnode->file_count=1;
            strcpy(new_wnode->word,str);
           // new_wnode->subnode_link=new_snode;
            new_wnode->subnode_link=NULL;
            new_wnode->wordnode_link=NULL;
            
            break_flag=0;
            //Index link is Null
            if(m_table[index].link==NULL)
            {
                m_table[index].link=new_wnode;
                new_wnode->subnode_link=new_snode;
            }
         
            //Index link is not Null
            else
            {
                word_node *w_temp=m_table[index].link;
                word_node *prev_wtemp=NULL;
                sub_node *s_temp=w_temp->subnode_link;
                sub_node *prev_stemp=NULL;
                while(w_temp)
                {
                    //word matches
                    if(!strcmp(w_temp->word,new_wnode->word))
                    {
                        s_temp=w_temp->subnode_link;
                        while(s_temp)
                        {

                            //word and file matches
                            if(!strcmp(s_temp->file_name,new_snode->file_name))
                            {
                                //increment word count
                                (s_temp->word_count)++;
                                break_flag=1;
                                break;
                            }

                            //word matches file doesn't
                            prev_stemp=s_temp;
                            s_temp=s_temp->subnode_link;
                        }
                        if(s_temp==NULL)
                        {
                        //attach subnode and increment file count
                        prev_stemp->subnode_link=new_snode;
                        (w_temp->file_count)++;
                        break;
                        }

                    }
                    //word doesnt match traverse
                    prev_wtemp=w_temp;
                    w_temp=w_temp->wordnode_link;
                }
                if(w_temp==NULL && break_flag!=1)
                {
                prev_wtemp->wordnode_link=new_wnode;
                new_wnode->subnode_link=new_snode;
                }               
            }
            


        }
        temp=temp->link;
    }
    flag=1;
    return success;
}

Status display_database(m_table m_table[])
{
    if(flag==1)
    {
        for(int i=0;i<index_size;i++)
        {
            if(m_table[i].link!=NULL)
            {
                word_node *w_temp=m_table[i].link;
                
                while(w_temp)
                {
                    printf("Word: [%s] ",w_temp->word);
                    printf("Filecount: %d ",w_temp->file_count);
                    sub_node *s_temp=w_temp->subnode_link;
                    while(s_temp)
                    {
                        printf("Wordcount: %d ",s_temp->word_count);
                        printf("Files: %s \n",s_temp->file_name);
                        s_temp=s_temp->subnode_link;
                    }
                    w_temp=w_temp->wordnode_link;
                }
            }
        }
        return success;
    }
    else
    {
        printf("Database is not created. No data to display\n");
        return failure;
    }
}
