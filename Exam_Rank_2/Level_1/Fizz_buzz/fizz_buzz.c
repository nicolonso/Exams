#include <unistd.h>

void put_nbr(int nbr){
	if ( nbr > 9)
		put_nbr(nbr / 10);
	write (1, &"0123456789"[nbr % 10], 1);
}


int main(void){

	int n = 1;

	while (n <= 100){
		if (n % 5 == 0 && n % 3 == 0)
			write (1, "fizzbuzz", 8);
		else if (n % 3 == 0)
			write (1, "fizz", 4);
		else if (n % 5 == 0)
			write (1, "buzz", 4);
		else
			put_nbr(n);
		write (1, "\n", 1);
		n++;
	}
	return (0);
}