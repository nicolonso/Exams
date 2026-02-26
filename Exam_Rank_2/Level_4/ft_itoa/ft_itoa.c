#include <stdlib.h>
#include <stdio.h>

int ft_intlen(int n){
	int i = 0;

	if (n <=0)
		i++;
	while(n != 0){
		n /= 10;
		i++;
	}
	return (i);
}

char *ft_itoa(int nbr){
	char *result;
	long n = nbr;
	int len = ft_intlen(nbr);
	int i = len - 1;

	if (!(result = (char *) malloc(len + 1)))
		return (NULL);
	if (n == 0)
		result[0] = '0';
	if (n < 0){
		result[0] = '-';
		n = -n;
	}
	while (n > 0){
		result[i--] = (n % 10) + 48;
		n /=10;
	}
	result[len] = '\0';
	return (result);
}

int main(void){
	int i = -1234567890;
	char *ptr = ft_itoa(i);
	
	printf("%s\n", ptr);
	return (0);
}