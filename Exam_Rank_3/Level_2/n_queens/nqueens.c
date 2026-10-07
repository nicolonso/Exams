#include <unistd.h>
#include <stdlib.h>
# include <stdio.h>

static void print_sol(int n, int *q)
{
	int i = 0;

	while (i < n)
	{
		if (i > 0)
			printf(" ");
		printf("%i", q[i] + 1); // q[i + 1] instead of q[i] + 1
		i++;	
	}
	printf("\n");
}

static int is_safe(int *q, int col)
{
	int i = 0;

	while(i < col) // i < n instead of i < col. Change it complety the algorimyth 
	{
		if (q[col] == q[i])
			return (0);
		if (col - i == q[col] - q[i] || col - i == q[i] -q[col])
			return (0);
		i++;
	}
	return (1);
}

static void solve(int n, int *q, int col)
{
	int row = 0;

	if (n == col)
	{	
		print_sol(n, q);
		return ;
	}
	while (row < n)
	{
		q[col] = row;
		if (is_safe(q, col)) // In this funtion I add this variable "n" that it wasnt need it
			solve(n, q, col + 1);
		row++;
	}
} 


int main(int ac, char **av)
{
	int n;
	int *q;

	if (ac != 2)
		return (1);
	n = atoi(av[1]); //  I did not remember if it was atoi or itoa
	//printf("%i",n);
	if (n <= 0) // Missing = operator
		return (1);
	q = calloc(n, sizeof(int));
	if (!q)
		return(1);
	solve(n, q, 0);
	free(q);
	return (0);
}
