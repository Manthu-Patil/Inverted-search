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
    sub_node *subnode_link;
    struct word *wordnode_link;
}word_node;

typedef struct main
{
   int index;
   word_node *link;
}m_table;


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
Status create_database(sll **head,m_table *m_table);
Status display_database(m_table m_table[]);
Status search_database(m_table m_table[],char *);
#endif
