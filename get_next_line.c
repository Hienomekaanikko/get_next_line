#include "get_next_line.h"

char	*make_line(char *line, char *buffer)
{
	char	*new_line;

	new_line = ft_strjoin(buffer, line);
	free (buffer);
	return (new_line);
}

char	*get_line(int fd, char *buffer)
{
	char	*line;
	int		byte_check;

	byte_check = 1;
	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (byte_check > 0)
	{
		byte_check = read(fd, buffer, BUFFER_SIZE);
		if (byte_check == -1)
		{
			free(line);
			return (NULL);
		}
		buffer = make_line(buffer, line);
		if (ft_strchr(buffer, "\n"))
			break ;
	}
	free(line);
	return (buffer);
}

char	*clean_up(char *line)
{
	
}

char *get_next_line(int fd)
{
	static char	*buffer; //empty buffer at the beginning
	char		*clean_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, BUFFER_SIZE) < 0)
		return (NULL);
	buffer = get_line(fd, buffer);
	clean_line = clean_up(buffer);

}
