#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i;
	int j;
	int lenFrom = 0;
	int lenTo = 0;
	char input;
	if(argc!=3)
	{
        fprintf(stderr, "Error: only takes two operands");
        return(1);
	}
	
	i = 0;
	while (argv[1][i]!='\0')
	{
		lenFrom++;
		i++;
	}

	i = 0;
	while (argv[2][i]!='\0')
	{
		lenTo++;
		i++;
	}

	if(lenFrom != lenTo)
	{
		fprintf(stderr, "From and To are not the same length");
        return(1);
	}

	for(i = 0; i < lenFrom; i++)
	{
		for(j=i+1; j<lenFrom; j++)
		{
			if (argv[1][i] == argv[1][j])
			{
				fprintf(stderr, "From has duplicate bytes");
				return(1);
			}
		}
	}

	while ( (input = getchar()) != EOF)
	{
		for (i = 0; i < lenFrom; i++)
		{
			if (input == argv[1][i])
			{
				input = argv[2][i];
				break;
			}
		}
		putchar(input);
	}
}