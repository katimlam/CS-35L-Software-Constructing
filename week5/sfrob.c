#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const *b);
int outer_cmp(const void *a, const void *b);


int main()
{  
    //create a string holding the whole input string.
    unsigned long strsize = 0;
    unsigned long prev_memsize = 13;
    unsigned long memsize = 21;
    char input;
 
    char* str = malloc(memsize * sizeof(char));
    if (str == NULL)
    {
        fprintf(stderr, "Error when allocating memory.");
        return(1);
    }
   
    input = getchar();
    while(input != -1)
    {
        if(strsize + 1 >= memsize)
        {
            memsize = memsize + prev_memsize;
            prev_memsize = memsize - prev_memsize;
            str = realloc(str, memsize * sizeof(char));
            if (str == NULL)
            {
                fprintf(stderr, "Error when allocating memory.");
                return(1);
            }
        }
        str[strsize] = input;
        strsize++;
        input = getchar();        
    }

    //add space to the end of the str
    if(str[strsize-1] != ' ') 
    {
        if(strsize + 1 >= memsize)
        {
            memsize++;
            str = realloc(str, memsize * sizeof(char) );
            if (str == NULL)
            {
                fprintf(stderr, "Error when allocating memory.");
                return(1);
            }
        }
        str[strsize] = ' ';
        strsize++;
    }
    
    //create a two-dimension str_array to hold the trunks of words
    prev_memsize = 13;
    memsize = 21;
    unsigned long array_size = 0;
    char **str_array;
    str_array = malloc(memsize * sizeof(char*) );
    if (str_array == NULL)
    {
        fprintf(stderr, "Error when allocating memory.");
        return(1);
    }
    
    unsigned long i;
    unsigned long j;
    unsigned long k;
    unsigned long count;
    unsigned long element_size;
    for(i=0; i<strsize; i++)
    {
        for (j=i; j<strsize; j++)
            if (str[j] == ' ')
            {
                j++;
                break;
            }
        if (j-i == 1)
            continue;
        element_size = j-i+1;
        str_array[array_size] = malloc(element_size* sizeof(char));
        if (str_array[array_size] == NULL)
        {
            fprintf(stderr, "Error when allocating memory.");
            return(1);
        }
        
        count=0;
        for (k=i; k<j; k++)
        {
            str_array[array_size][count] = str[k];
            count++;
        }
        i = j-1;
        array_size++;
    }
    
    qsort(str_array, array_size, sizeof(char*), outer_cmp);
    for(i=0; i<array_size; i++)
    {
        j=0;
        while(str_array[i][j] != ' ')
        {
            putchar(str_array[i][j]);
            j++;
        }
        free(str_array[i]);
        putchar(' ');
    }
    free(str);
    free(str_array);
    return(0);
}


int outer_cmp(const void *a, const void *b)
{
    return frobcmp(*(char const **)a, *(char const **)b);
}


int frobcmp(char const *a, char const *b)
{
    int i=0;
    int diff=0;
    while( a[i]!=' ' && b[i]!=' ')
    {
        diff = (a[i] ^ 42) - (b[i] ^ 42) ;
        if (diff == 0)
            i++;
        else
            return diff;
    }
    if (a[i]==' ' && b[i]==a[i]) 
        return 0;
    else if (b[i] == ' ') 
        return 1;
    else if (a[i] == ' ') 
        return -1;
}