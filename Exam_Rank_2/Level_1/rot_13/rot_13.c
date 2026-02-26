#include <unistd.h>	

int ft_alpha(char c){
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int main(int ac, char **av){
	if (ac == 2)
	{
		int i = -1;
		while (av[1][++i])
		{
			if ((av[1][i] >= 65 && av[1][i] <= 77) || (av[1][i] >= 97 && av[1][i] <= 109))
				av[1][i] += 13;
			else if ((av[1][i] >= 78 && av[1][i] <= 90) || (av[1][i] >= 110 && av[1][i] <= 122))
				av[1][i] -= 13;
			write (1, &av[1][i], 1);
		}
	}
	write (1, "\n", 1);
	return (0);
	
}