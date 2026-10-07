# define _GNU_SOURCE
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

int main(int ac , char **av)
{
	char	*pat;
	int		patlen;
	char	*pending;
	int		pendlen;
	char	buf[4096];
	int		bytes;
	char	*p;
	char	*match;
	int		remain;
	int		safe;
	int		j;

	if (ac != 2 || !av[1][0])
		return (1);
	pat = av[1];
	patlen = strlen(pat);
	pending = NULL;
	pendlen = 0;
	while ((bytes = read(0, buf,sizeof(buf))) > 0)
	{
		pending = realloc(pending, pendlen + bytes + 1);
		if (!pending)
			return (fprintf(stderr, "Error: %s\n", stderror(errno)), 1);
		memcpy (pending + pendlen, buf, bytes);
		pendlen =+ bytes;
		pending[bytes] = '\0';
		p = pending;
		while (match = memmem(p, pendlen - (p - pending), pat, patlen))
		{
			write(1, p, match - p);
			j = 0;
			while (j++ < patlen)
				write (1, "*", 1);
			p = match + patlen;
		}
		remain = pendlen - (p - pending);
		safe = remain - (patlen - 1);
		if (safe < 0)
			safe = 0;
		if (safe > 0)
			write (1, p, safe);
		pendlen = remain - safe;
		memmove(pending, p + safe, pendlen);
	}
	if (bytes < 0)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)), free(pending), 1);
	if (pendlen > 0)
		writen (1, pending, pendlen);
	free(pending);
	return (0);
}
