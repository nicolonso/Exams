# include "get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *search(char *s, int c)
{
	if (!s)
		return (NULL);
	int i = 0;
	while(s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

 char *ft_strjoin(char *buffer, char *line)
 {
	int i = 0;
	int j = 0;
	int l_len = ft_strlen(line);
	int b_len = ft_strlen(buffer);
	char *ptr = malloc(sizeof(char *) * (l_len + b_len + 1));

	if (!ptr)
		return (NULL);
	while (buffer && buffer[i])
	{
		ptr[i] = buffer[i];
		i++;
	}
	while (line && line[j])
	{
		ptr[i] = line[j];
		j++;
		i++;
	}
	ptr[i] = '\0';
	free(buffer);
	return (ptr);
}

char *extract_line(char *buffer)
{
	char *line;
	int i = 0;
	int j = 0;

	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char *) * (i + 1));
	if (!line)
		return (NULL);
	if (buffer[i] == '\n')
		i++;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char *buffer_mv(char *buffer)
{
	int i = 0;
	int j = 0;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), buffer = NULL, NULL);
	i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
	if (j == 0)
		return (free(buffer), NULL);
	return (buffer);
}

char *get_next_line(int fd)
{
	static char *buffer;
	char	*line;
	int		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!(line =  malloc(sizeof(char *) * (BUFFER_SIZE + 1))))
		return (NULL);
	while (search(buffer, '\n') == NULL)
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), free(buffer), buffer = NULL, NULL);
		if (bytes == 0)
			break ;
		line[bytes] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	if (!buffer || !buffer[0])
		return (NULL);
	if (!(line = extract_line(buffer)))
		return (free(buffer), buffer = NULL, NULL);
	buffer = buffer_mv(buffer);
	return (line);
}


int main (int ac, char **av)
{
	int fd;
	char *line;

	if (ac != 2)
		return 1;	
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
