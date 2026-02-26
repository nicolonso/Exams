#include <unistd.h>
int ft_alpha(char c){
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int main(int ac, char **av){
	if (ac == 2){
		int i = -1; 
		while (av[1][++i]){
			if (ft_alpha(av[1][i])){
				char c = av[1][i] + 1;
				if (av[1][i] == 'Z' || av[1][i] == 'z')
					c = av[1][i] - 25;
				write (1, &c, 1);
			}
			else
				write (1, &av[1][i], 1);
		}
	}
	write (1, "\n", 1);
	return (0);
}