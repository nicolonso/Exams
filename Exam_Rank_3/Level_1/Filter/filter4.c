# define _GNU_SOURCE
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

int main(int ac, char **av)
{
	char 	*pat;
	int		pat_len;
	char	*pending;
	int 	penlen;
	char	buf[4096];
	int		bytes;
	char	*p;
	char	*match;
	int		remain;
	int		safe;
	int 	j;

	if (ac != 2 || !av[1][0])
		return (1);
	pat = av[1];
	pat_len = strlen(pat);
	pending = NULL;
	penlen = 0;
	while((bytes = read(0, buf, sizeof(buf))) > 0)
	{
		pending =  realloc(pending, penlen + bytes + 1);
		if (!pending)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)), 1);
		memcpy(pending + penlen, buf, bytes);
		penlen += bytes;
		pending[bytes] = '\0';
		p = pending;
		while ((match = memmem(p, penlen - (p - pending), pat, pat_len)))
		{
			write(1, p, match - p);
			j = 0;
			while (j++ < pat_len)
				write (1, "*", 1);
			p = match + pat_len;
		}
		remain = penlen - (p - pending);
		safe = remain - (pat_len - 1);
		if (safe < 0)
			safe = 0;
		if (safe > 0)
			write(1, p, safe);
		penlen = remain - safe;
		memmove(pending, p + safe, penlen);
	}
	if (bytes < 0)
		return (fprintf(stderr, "Error:%s\n", strerror(errno)),free(pending), 1);
	if (penlen > 0)
		write (1, pending, penlen);
	free (pending);
	return (0);
}
