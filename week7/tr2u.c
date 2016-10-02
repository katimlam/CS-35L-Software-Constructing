#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int i;
	int j;
	int lenFrom = 0;
	int lenTo = 0;
	char buf[1]; 

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
	
	while ( read(0, buf, sizeof(buf)) > 0)
	{
		for (i = 0; i < lenFrom; i++)
		{
			if (buf[0] == argv[1][i])
			{
				buf[0] = argv[2][i];
				break;
			}
		}
		write(1, buf, sizeof(buf));
	}
}