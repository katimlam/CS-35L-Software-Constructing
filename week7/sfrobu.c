#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int frobcmp(char const *a, char const *b);
int outer_cmp(const void *a, const void *b);
long comparison = 0;

int main()
{
	//create a string holding the whole input string.
	long strsize = 0;
	long prev_memsize = 13;
	long memsize = 21;
	struct stat buffer;
	int status;
	char* str = NULL;
	char input[1];

	if (fstat(0, &buffer)<0)
		return (1);
	memsize = (long)buffer.st_size;
	
	if (memsize > 0 && S_ISREG(buffer.st_mode)) {}
	else
		memsize = 21;

	str = malloc(memsize * sizeof(char));
	if (str == NULL)
	{
		fprintf(stderr, "Error when allocating memory.");
		return(1);
	}

	while (read(0, input, 1) > 0)
	{
		if (strsize + 1 >= memsize)
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
		str[strsize] = input[0];
		strsize++;
	}
	
	//add space to the end of the str
	if (str[strsize - 1] != ' ')
	{
		if (strsize + 1 >= memsize)
		{
			memsize++;
			str = realloc(str, memsize * sizeof(char));
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
    long array_size = 0;
    char **str_array = NULL;
    str_array = malloc(memsize * sizeof(char*) );
    if (str_array == NULL)
    {
        fprintf(stderr, "Error when allocating memory.");
        return(1);
    }
    
    long i;
    long j;
    long k;
    long count;
    long element_size;
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
		if (array_size >= memsize)
		{
			memsize += prev_memsize;
			prev_memsize = memsize - prev_memsize;
			str_array = realloc(str_array, memsize * sizeof(char*));
			if (str_array == NULL)
			{
				fprintf(stderr, "Error when allocating memory.");
				return(1);
			}
		}
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

	char output[1];
	for (i = 0; i<array_size; i++)
	{
		j = 0;
		while ( (output[0] = str_array[i][j]) != ' ')
		{
			write(1,output,1);
			j++;
		}
		free(str_array[i]);
		output[0] = ' ';
		write(1, output, 1);
	}

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (str_array != NULL)
	{
		free(str_array);
		str_array = NULL;
	}
	fprintf(stderr, "Comparisons: %d\n", comparison);
    return(0);
	
}


int outer_cmp(const void *a, const void *b)
{
	comparison++;
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
