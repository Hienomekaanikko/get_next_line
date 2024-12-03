#include "get_next_line.h"

char	*join_to_buf(char *result, char *buffer)
{
	char	*new;

	new = ft_strjoin(buffer, result);
	if (result)
		free(result);
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

char	*clean_line(char *line)
{
	char	*cleaned_line;
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	cleaned_line = malloc((i + 2) * sizeof(char));
	if (cleaned_line == NULL)
		return (NULL);
	i = 0;
	while (cleaned_line[i])
	{
		cleaned_line[i] = line[i];
		i++;
	}
	cleaned_line[i] = '\0';
	return (cleaned_line);
}
char	*remove_first_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;
	int		total_len;

	i = 0;
	j = 0;
	total_len = ft_strlen(buffer);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = malloc((total_len - i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (line[j] != '\0')
	{
		line[j] = buffer[i];
		i++;
		j++;
	}
	free(buffer);
	return (line);

}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, BUFFER_SIZE) < 0)
		return (NULL);
	buffer = get_line(fd, buffer);
	line = clean_line(buffer);
	buffer = remove_first_line(buffer);
	return (line);
}
