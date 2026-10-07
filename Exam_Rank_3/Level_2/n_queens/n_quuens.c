# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

 static void print_sol(int *q, int n)
  {
      int i = 0;

      while (i < n)
      {
          if (i > 0)
              printf(" ");
          printf("%d", q[i] + 1);
          i++;
      }
      printf("\n");
  }

static int is_safe(int *q, int col)
{
	int	i = 0;

	while(i < col)
	{
		if (q[i] == q[col])
			return (0);
		if (col - i == q[col] - q[i] || col - i == q[i] - q[col])
			return (0);
		i++;
	}
	return (1);
}

static void solve(int n, int *q, int col)
{
	int row;

	if (col == n)
	{
		print_sol(q, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		q[col] = row;
		if (is_safe(q, col))
			solve(n, q, col + 1);
		row++;
	}
}

int main(int ac, char **av)
{
	int 	n;
	int 	*q;

	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	if (n <=0)
		return (1);
	q = calloc(n, sizeof(int));
	if (!q)
		return (1);
	solve(n, q, 0);
	free(q);
	return (0);
}
