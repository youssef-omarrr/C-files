#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap (char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

int next_permutation(int n, char **s)
{
    int flag = 0;
	for (int i=0 ; i<n; i++)
    {
        for (int j =0; j<n; j++)
        {
            if (i == j)
               break;
            swap (&s[i], &s[j]);
            if (strcmp(s[i], s[j]) != 0)
            {
                for (int z = 0; z < n; z++)
                    printf("%s%c", s[z], z == n - 1 ? '\n' : ' ');
            }
            else
                break;
            swap (&s[i], &s[j]);
        }
        
    }
    return 0;
}



int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}