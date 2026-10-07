# include "get_next_line.h"

char *search(char *s, int c)
{
	int i = 0;

	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

int ft_strlen(char *s)
{
	int i= 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *extract_line(char *buffer)
{
	int i = 0;
	int j = -1;
	char *line;

	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (++j < i)
		line[j] = buffer[j];
	line[j] = '\0';
	return (line);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *ptr;
	int i = 0;
	int j = 0;
	int s1len = ft_strlen(s1);
	int s2len = ft_strlen(s2);

	ptr = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ptr)
		return (NULL);
	while(i < s1len && s1)
	{
		ptr[i] = s1[i];
		i++;
	}
	while(j < s2len && s2)
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	free(s1);
	return (ptr);
}

 char *mv_buffer(char *buffer)
{
	int i = 0;
	int j = 0;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), buffer = NULL, NULL);
	while(buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
	if (j == 0)
		return (free(buffer),  buffer = NULL, NULL); 
	return (buffer);
}

char *get_next_line(int fd)
{
	static char *buffer;
	char 		*line;
	int 		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	while (!search(buffer, '\0'))
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), free(buffer), buffer = NULL, NULL);
		if 	(bytes == 0)
			break;
		line[bytes] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	if (!buffer || !buffer[0])
		return (free(buffer), buffer = NULL, NULL);
	line = extract_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = mv_buffer(buffer);
	return (line);
}

int main(int ac, char **av)
{
	int fd;
	char *line;

	if (ac != 2)
		return 1;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return 1;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free (line);
	}
	close (fd);
	return 0; 
}
