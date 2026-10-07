# define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

# define BUFFER_SIZE 1024

typedef struct s_filter
{
	char		*pattern;
	char		*hold;
	size_t		pattern_len;
	size_t		hold_len;
	int			true;
} t_filter;

void	ft_initialize(t_filter *f, char *av)
{
	f->pattern = av;
	f->pattern_len = strlen(av);
	f->hold = NULL;
	f->hold_len = 0;
}

int error_msg(void)
{
	fprintf(stderr, "Error: %s\n", strerror(errno));
	return (1);
}

int append_data(t_filter *f, char *buffer, ssize_t n_read)
{
	char *new_buffer;

	new_buffer = realloc(f->hold, f->hold_len + n_read);
	if (!new_buffer)
		return (-1);
	f->hold = new_buffer;
	memmove(f->hold + f->hold_len, buffer, n_read); // Why this line, why is passing this argument??
	f->hold_len += n_read;
	return (0);
}

int process_hold(t_filter *f, int eof)
{
	size_t	safe_len;
	size_t	pos;
	void	*match;

	if (f->hold_len == 0)
		return (0);
	if (eof || f->hold_len < f->pattern_len)
		safe_len = f->hold_len;
	else
		safe_len = f->hold_len - (f->pattern_len - 1);
	pos = 0;
	while (pos < safe_len)
	{
		match = memmem()
	}
	
}

int main(int ac, char **av)
{
	t_filter	f;
	char		buffer[BUFFER_SIZE];
	ssize_t		n_read;

	if (ac != 2 || !av[1][0])
		return (1);
	ft_initialize(&f, av[1]);

	while (1)
	{
		n_read = read(0, buffer, BUFFER_SIZE);
		
		if (n_read < 0)
		{
			free (f.hold);
			return (error_msg());
		}

		if (n_read == 0)
			break ;
		if (append_data(&f, buffer, n_read) < 0)
		{
			free (f.hold);
			return (error_msg());
		}
		if (process_hold(&f, 0) < 0)
		{
			free(f.hold);
			return (error_msg());
		}
	}
	if (process_hold(&f, 1) < 0)
	{
		free(f.hold);
		return (error_msg());
	}
	free(f.hold);
	return (0);
}
