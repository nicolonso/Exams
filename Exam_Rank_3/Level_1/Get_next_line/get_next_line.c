# include "get_next_line.h"

char *get_next_line(int fd)
{
	static char  *buffer;
	char 		*line;
	int 		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (1);
	line = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!line)
		return (1);
	while(search(buffer, '\n'))
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), free(buffer), buffer = NULL, 1);
		if (bytes == 0)
			break ;
		line[bytes] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	line =  extract_line(buffer);
	if (!line)
		return (1);
	buffer = mvbuffer(buffer);
	return (line);
}

int main(int ac, char **av)
{
	

}
