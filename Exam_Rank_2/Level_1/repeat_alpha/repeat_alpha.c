#include <unistd.h>
#include <stdio.h>

int ft_Capital(char c){
	return (c >= 'A' && c <= 'Z');
}

int ft_Lower(char c){
	return (c >= 'a' && c <= 'z');
}

int main(int ac, char **av){
	if (ac == 2){
		int i = -1;
		
		while (av[1][++i]){
			int x = 0;
			
			if (ft_Capital(av[1][i])){
				x = av[1][i] - 65 + 1;
				while(x > 0){
					write (1, &av[1][i], 1);
					x--;
				}
			}
			else if (ft_Lower(av[1][i])){
				x = av[1][i]- 97 + 1;
				while(x > 0){
					write (1, &av[1][i], 1);
					x--;
				}
			}
			else
				write (1, &av[1][i], 1);
		}
	}
	write (1, "\n", 1);
	return (0);
}

/*

65 = A

90 = Z

97 = a

122 = z


int x = 65 - c(int)
*/