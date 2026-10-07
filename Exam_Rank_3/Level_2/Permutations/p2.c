# include <unistd.h>
# include <unistd.h>
# include <stdlib.h>

static int ft_strlen(char *s)
{
	int i = 0;

	while(s[i])
		i++;
	return (i);
}

static void ft_sort(char *s, int n)
{
	int i = 0;
	int j ;
	char temp;

	while(i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (s[j] < s[i])
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void permute(char *s, char *res, int *used, int pos, int n)
{
	int i = 0;

	if (n == pos)
	{
		puts(res);
		return ;
	}
	while(i < n)
	{
		if(!used[i])
		{
			used[i] = 1;
			res[pos] = s[i];
			permute (s, res, used,pos + 1, n);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int n;
	char *res;
	int *used;

	if (ac != 2)
		return (1);
	n = ft_strlen(av[1]);
	ft_sort(av[1], n);
	res =  malloc(n + 1);
	used = calloc(n, sizeof(int));
	if (!res || !used)
		return (1);
	res[n] = '\0';
	permute(av[1], res, used,0, n);
	free(used);
	free(res);
	return (0);
}