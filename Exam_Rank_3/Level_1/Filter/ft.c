# define _GNU_SOURCE
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>

int main(int ac, char **av)
{
	char *ptr;
	char *pending;
	char *p;
	char *match;
	char buf[4096];
	int ptrlen;
	int pendlen;
	int bytes;
	int j;
	int safe;
	int remain;

	if (ac != 2 || !av[1][0])// I forgot the !
		return (1);
	ptr = av[1];
	ptrlen = strlen(ptr);
	pending = NULL;
	pendlen = 0;
	while ((bytes = read(0, buf, sizeof(buf))) > 0)
	{
		pending = realloc(pending, bytes + pendlen + 1);
		if (!pending)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)), 1); // I did not return the error with thef printf
		memcpy(pending + pendlen, buf, bytes); // memccpy onstead of memcpy
		pendlen += bytes; // Not include this 
		pending[pendlen] = '\0';// Check if this is better or the other one.
		p = pending;
		while ((match = memmem(p, pendlen - (p - pending), ptr, ptrlen)))
		{
			write(1, p, match - p); // I not include the (match - p) is necessary always when i ewant use i string as int value of the differences between them
			j = 0; // i better initialize here 
			while (j++ < ptrlen) // No increase my counter seg.foult 
				write(1, "*", 1);
			p = match + ptrlen; // Forgot include ptrlen
		}
		remain = pendlen - (p - pending);
		safe = remain - (ptrlen - 1);
		if (safe < 0)
			safe = 0;
		if (safe > 0)
			write(1, p, safe);
		pendlen = remain - safe;
		memmove(pending, p + safe, pendlen); // I did not remember this function
	}
	if (bytes < 0)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)), free(pending), 1); // I did not return the error with thef printf
	if (pendlen > 0)
		write (1, pending, pendlen);
	free(pending); // free my pointer
	return (0);
}
