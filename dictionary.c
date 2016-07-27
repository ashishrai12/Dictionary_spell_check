/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

 typedef struct node
    {
        bool complete;
        struct node* children[27];
    }node;
    
    node* root;
    
void freefunc(struct node* new_node)
{
    for(int t=0;t<27;t++)
    {
        if(new_node->children[t]!=NULL)
        {
            freefunc(new_node->children[t]);       
        }
    }
    free(new_node);
}
bool load(const char* dictionary); 
int dwords=-1;
 
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* new_node=root;
    char current = toupper(word[0]);
    for(int i = 1; current != '\0'; i++)
    {
        
        if(!isalpha(current) && current != 39)
        {
            return false;
        }
        else if(isalpha(current))
        {
            
            if(new_node->children[current - 'A'] != NULL)
            {
                new_node = new_node->children[current - 'A'];
            }
            else
            {
                return false;
            }

        }
        else if(current == 39)
        {
            if(new_node->children[26] != NULL)
            {
                new_node = new_node->children[26];
            }
            else
            {
                return false;
            }
        }
        current = toupper(word[i]);
    }
    if(new_node->complete==1)
    {    
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    FILE* dptr = fopen(dictionary, "r");
    if (dptr == NULL)
    {
        return false;
    }
    node* new_node=calloc(1,sizeof(node));
    root=new_node;
    char c=0;
    int indx=0;
    do
    {
        new_node=root;
        for (c = fgetc(dptr); c != '\n'; c = fgetc(dptr))
        {
            if(c == '\n'|| c == EOF || c == 32)
            {
                break;
            }
            else if(isalpha(c))
            {
                indx=(toupper(c))-'A';
                
                if(new_node->children[indx]==NULL)
                {
                    new_node->children[indx]=calloc(1,sizeof(node));     
                }
                new_node=new_node->children[indx];
            }
            else if(c==39)
            {
                if(new_node->children[26]==NULL)
                {
                    new_node->children[26]=calloc(1,sizeof(node));
                }
                new_node=new_node->children[26];
            }
           
        }
        dwords++;
        new_node->complete=1;
    }while(c!=EOF);
    
    fclose(dptr);
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return dwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freefunc(root);
    return true;
}
