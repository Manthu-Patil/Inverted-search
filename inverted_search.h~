#ifndef SEARCH
#define SEARCH

#define index_size 26
#define file_size 50
#define word_size 100
typedef enum status
{
   success,
   failure
}Status;

typedef struct main
{
   int index[index_size];
   int *link;
}m_table;

typedef struct sub
{
    int word_count;
    char file_name[file_size];
    struct sub *subnode_link;
}sub_node;

typedef struct word
{
    int file_count;
    char word[word_size];
    struct word *subnode_link;
    struct word *wordnode_link;
}word_node;

typedef struct node
{
    char file_name[file_size];
    struct node *link;
}sll;

Status validation(int ,char **);
Status check_file_empty(char* );
Status check_file_exists(char*);
Status insert(sll **head,char *);
void print_list(sll *head);
#endif
