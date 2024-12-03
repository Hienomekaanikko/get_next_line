#include "get_next_line.h"

char	*join_to_buf(char *result, char *buffer)
{
	char	*new;

	new = ft_strjoin(buffer, result);
	free(buffer);
	return (new);
}

char	*get_line(int fd, char *result)
{
	char	*buffer;
	int		byte_count;

	byte_count = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (byte_count > 0)
	{
		byte_count = read(fd, buffer, BUFFER_SIZE);
		if (byte_count == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_count] = 0;
		result = join_to_buf(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, BUFFER_SIZE) < 0)
		return (NULL);
	buffer = get_line(fd, buffer);
	
}
