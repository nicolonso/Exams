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
	int i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *ft_strjoin(char *s1, char	*s2)
{
	int i = 0;
	int j = 0;
	int s1_len = 0;
	int s2_len = 0;
	char *ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (NULL);
	while (i < s1_len && s1)
	{
		ptr[i] = s1[i];
		i++;
	}
	while(j < s2_len && s2)
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	free (s1);
	return (ptr);
}

char *extract_line(char *buffer)
{
	char *line;
	int i = 0;
	int j = 0;

	while (buffer[i] && buffer[i] != 'e')
		i++;
	if (buffer[i] == '\n') // i did not include this conditional
		i++;
	line = malloc (sizeof(char) *  (i + 1));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
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
		return (free(buffer), NULL);
	while (buffer[i])
	{
		buffer[j] = buffer[i];
		j++;
		i++;
	}
	buffer[j] = '\0';
	if (j == 0)
		return (free(buffer), NULL);
	return (buffer);
}

char *get_next_line(int fd)
{
	static char	*buffer = NULL;
	char *line;
	int bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc (sizeof (char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	while (!search(buffer, '\n'))
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
	// This part I miss in the exam, I need to test it if this is the reason why im get in Seg.foult
	if (!buffer || !buffer[0])
		return (free(buffer), buffer = NULL ,NULL);
	line = extract_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = mv_buffer(buffer);
	return (line);
}

// Bug # 1 I miss the new line in the extract line when I copy the line and the other one it was get in segmation foult 

int main(int ac, char **av)
{
	char *line;
	int fd;

	if (ac != 2)
		return 1;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
/* 	while((line = get_next_line(fd)))
	{
		//write (1, line, sizeof(line));
		printf("%s", line);
		free(line);
	} */
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}
