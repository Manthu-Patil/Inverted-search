#include<stdio.h>
#include "inverted_search.h"
int main(int argc,char **argv)
{
    if(validation(argc,argv)==success)
    {
        printf("Validation successfull\n");
    }
    else
    {
        printf("Validation failed\n");
    }
    return 0;
}


